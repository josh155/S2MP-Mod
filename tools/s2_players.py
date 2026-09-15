#!/usr/bin/env python3
"""
s2_players.py -- pull the PLAYER ROSTER out of native .demo recordings.

Offline. No game, no probe, no IDA.

WHY THIS EXISTS
    Every S2 demo carries, in its recorded gamestate, one configstring per
    player in the lobby:

        cs[266] 0110000107498c6e <80 hex chars> 2 3a7a007d9f69f652 0 0
                ^^^^^^^^^^^^^^^^ SteamID64      ^ team
                                 ^^^^^^^^^^^^^^ 40-byte customization blob

    So the demos you already have ARE the name list -- except they carry
    Steam IDs rather than names, because S2 resolves display names from Steam
    rather than replicating them in the clientinfo.

    That is better than a hand-typed list, because each ID comes paired with
    the exact 40-byte cosmetic record that player was wearing in that match.

SHAPE VALIDATION
    A clientinfo configstring is identified by SHAPE, not by index:
        <16 hex> <80 hex> <int> <16 hex> 0 0
    so this keeps working if the index range moves. Anything that does not
    match is skipped rather than guessed at.

USAGE
    python tools/s2_players.py                       # scan the default demo dir
    python tools/s2_players.py --dir <path>
    python tools/s2_players.py <file.demo> [...]
    python tools/s2_players.py --csv players.csv
    python tools/s2_players.py --blob                # lay the 40 bytes out as u16s
    python tools/s2_players.py --key <steam api key> # resolve IDs -> persona names

    A Steam Web API key is free from https://steamcommunity.com/dev/apikey and is
    only needed for name resolution; everything else works without one.
"""

import argparse
import csv as csvmod
import json
import os
import re
import sys
import urllib.request

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s2_gamestate

# Steam persona names are arbitrary Unicode; a Windows console defaults to cp1252
# and dies on the first one it cannot map. Never let a player's name crash the
# tool -- degrade the DISPLAY, not the data.
for _stream in (sys.stdout, sys.stderr):
    try:
        _stream.reconfigure(encoding="utf-8", errors="replace")
    except Exception:
        pass

DEFAULT_DIR = r"E:\SteamLibrary\steamapps\common\Call of Duty WWII\main\demo"

# A SteamID64 for an INDIVIDUAL account always has this exact high dword:
#   universe 1 (public) | type 1 (individual) | instance 1 (desktop)
# i.e. 0x0110000100000000 | accountID. Testing the signature rather than the
# magnitude is what rejects the junk that bot/offline demos leave in this field
# (measured: one such entry decoded to high dword 0xb941e4ca).
STEAM_INDIVIDUAL_HIGH = 0x01100001

# <16 hex> <80 hex> <int> <16 hex> 0 0
CLIENTINFO_RE = re.compile(
    r"^([0-9a-fA-F]{16}) ([0-9a-fA-F]{80}) (-?\d+) ([0-9a-fA-F]{16}) 0 0$"
)


def steamid64(hex16):
    """The clientinfo id is already a full SteamID64 in hex."""
    return int(hex16, 16)


def profile_url(sid):
    return "https://steamcommunity.com/profiles/%d" % sid


# ^ followed by a digit is a Quake/CoD colour code and renders as a colour, not
# as text -- so "^7Bu^4Ky^1JI9I" is really "BuKyJI9I".
COLOUR_RE = re.compile(r"\^[0-9]")

# The connect string is a userinfo string (`\name\%s`), so these would break it.
USERINFO_BAD = set('\\";')


def clean_name(raw):
    """Steam persona name -> a name usable as a bot name, or '' to reject it."""
    s = COLOUR_RE.sub("", raw)
    s = s.rstrip("^")                       # a trailing lone caret is malformed
    # Printable ASCII only: the userinfo string cannot carry anything else.
    s = "".join(c for c in s if c not in USERINFO_BAD and 0x20 <= ord(c) < 0x7F)
    s = " ".join(s.split())                 # collapse runs of whitespace
    # Reject names with no actual name in them (e.g. ".,.,.,.,..,,,,..,..").
    if sum(c.isalnum() for c in s) < 2:
        return ""
    return s[:30]


def scan_demo(path):
    """Return (info, [entry...], [bot...]) for one .demo.

    A clientinfo slot whose id is not an individual Steam account is reported
    rather than silently dropped.

    ⚠ Such a slot is NOT necessarily a bot. Measured: all four private-match
    recordings (airshipdemo / dday / egyptbots / gibraltar) carry the IDENTICAL
    id b941e4ca81fce5ab at slot 266 -- the recording client's own slot -- i.e. an
    offline/private placeholder for the local player, not per-bot data. And
    xbots.demo, an actual bot match, has a valid account and no such slot.

    So the id alone distinguishes "individual Steam account" from "not one", and
    nothing finer. The mod's in-game bot safety does NOT rest on this test: it
    hooks SV_AddBot, which a human connection cannot reach.
    """
    try:
        gs = s2_gamestate.parse(path)
    except Exception as exc:  # a truncated / interrupted recording
        return dict(err=str(exc)), [], []

    if gs.get("err"):
        return gs, [], []

    out = []
    bots = []
    for idx, value in gs.get("cs", []):
        m = CLIENTINFO_RE.match(value.strip())
        if not m:
            continue
        raw_id, blob, team, sess = m.groups()
        sid = steamid64(raw_id)
        # Not an individual account -> a bot or an unfilled slot.
        if (sid >> 32) != STEAM_INDIVIDUAL_HIGH:
            bots.append(dict(slot=idx, raw=raw_id.lower(), blob=blob.lower()))
            continue
        out.append(
            dict(
                demo=os.path.basename(path),
                map=gs.get("map", "?"),
                gametype=gs.get("gametype", "?"),
                slot=idx,
                steamid=sid,
                team=int(team),
                blob=blob.lower(),
                session=sess.lower(),
            )
        )
    return gs, out, bots


def resolve_names(ids, key):
    """Steam Web API GetPlayerSummaries -- max 100 ids per call."""
    names = {}
    ids = list(ids)
    for i in range(0, len(ids), 100):
        chunk = ids[i : i + 100]
        url = (
            "https://api.steampowered.com/ISteamUser/GetPlayerSummaries/v2/"
            "?key=%s&steamids=%s" % (key, ",".join(str(s) for s in chunk))
        )
        try:
            with urllib.request.urlopen(url, timeout=20) as fh:
                data = json.load(fh)
        except Exception as exc:
            print("  ! Steam API call failed: %s" % exc)
            return names
        for p in data.get("response", {}).get("players", []):
            names[int(p["steamid"])] = p.get("personaname", "")
    return names


def dump_blob(entries):
    """Lay each 40-byte blob out as 20 u16s so differing fields stand out.

    This is reference output for the customization work -- it does NOT claim to
    know what any field means. Columns that are identical across every player
    are constants; columns that vary are the per-player cosmetics.
    """
    print()
    print("40-byte customization blob, as 20 little-endian u16 (per player)")
    print("  columns that VARY across players are the interesting ones")
    print()
    hdr = "  %-20s " % "steamid" + " ".join("%4d" % i for i in range(20))
    print(hdr)
    print("  " + "-" * (len(hdr) - 2))
    cols = [[] for _ in range(20)]
    for e in entries:
        b = bytes.fromhex(e["blob"])
        words = [int.from_bytes(b[i : i + 2], "little") for i in range(0, 40, 2)]
        for i, w in enumerate(words):
            cols[i].append(w)
        print("  %-20d " % e["steamid"] + " ".join("%04x" % w for w in words))
    varying = [i for i, c in enumerate(cols) if len(set(c)) > 1]
    print()
    print("  varying u16 fields: %s" % (varying if varying else "none"))
    print("  constant fields   : %s" % [i for i in range(20) if i not in varying])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("demos", nargs="*", help="specific .demo files (default: --dir)")
    ap.add_argument("--dir", default=DEFAULT_DIR, help="directory of .demo files")
    ap.add_argument("--csv", help="write the roster to a CSV file")
    ap.add_argument(
        "--botnames",
        metavar="PATH",
        help="write the resolved names straight out as the mod's botnames.txt "
        "(needs --key, since the demos carry Steam IDs rather than names)",
    )
    ap.add_argument("--key", help="Steam Web API key, to resolve IDs -> names")
    ap.add_argument(
        "--exclude",
        nargs="*",
        type=int,
        default=[],
        metavar="STEAMID64",
        help="drop these accounts (use for your own -- see --whoami)",
    )
    ap.add_argument(
        "--whoami",
        action="store_true",
        help="guess which account is YOURS (the one present in the most of your "
        "own recordings) and exclude it",
    )
    ap.add_argument("--blob", action="store_true", help="lay out the 40-byte blob")
    ap.add_argument("--urls", action="store_true", help="print profile URLs")
    ap.add_argument(
        "--player",
        type=int,
        metavar="STEAMID64",
        help="show EVERY sighting of one player, so two recordings taken either "
        "side of a cosmetic change can be diffed field by field",
    )
    args = ap.parse_args()

    paths = args.demos
    if not paths:
        if not os.path.isdir(args.dir):
            print("no such directory: %s" % args.dir)
            return 1
        paths = sorted(
            os.path.join(args.dir, f)
            for f in os.listdir(args.dir)
            if f.lower().endswith(".demo")
        )
    if not paths:
        print("no .demo files found")
        return 1

    all_entries = []
    skipped = []
    total_bots = 0
    bot_demos = 0
    for p in paths:
        gs, entries, botslots = scan_demo(p)
        if gs.get("err"):
            skipped.append((os.path.basename(p), gs["err"]))
            continue
        all_entries.extend(entries)
        total_bots += len(botslots)
        if botslots:
            bot_demos += 1
        print(
            "  %-28s %-18s %-5s %2d player(s)%s"
            % (
                os.path.basename(p),
                gs.get("map", "?"),
                gs.get("gametype", "?"),
                len(entries),
                "  + %d non-Steam slot(s)" % len(botslots) if botslots else "",
            )
        )

    if total_bots:
        print()
        print(
            "  %d slot(s) across %d demo(s) carry a NON-STEAM id -- excluded."
            % (total_bots, bot_demos)
        )
        print("  These are bots, empty slots, OR an offline/private local player:")
        print("  the id alone cannot tell them apart. (Measured: the four private")
        print("  recordings all carry the same constant b941e4ca81fce5ab at their")
        print("  own slot, so that one is the local player, not a bot.)")

    if skipped:
        print()
        print("  skipped %d file(s) whose gamestate would not decode:" % len(skipped))
        for name, err in skipped:
            print("    %-28s %s" % (name, err))

    if not all_entries:
        print()
        print("No clientinfo found. Nothing to do.")
        return 1

    if args.player:
        mine = [e for e in all_entries if e["steamid"] == args.player]
        if not mine:
            print()
            print("No sighting of %d in these demos." % args.player)
            return 1
        print()
        print("=" * 78)
        print("%d sighting(s) of %d" % (len(mine), args.player))
        print("=" * 78)
        print("  %-28s %-18s %s" % ("demo", "map", "blob as 20 u16"))
        print("  " + "-" * 74)
        rows = []
        for e in mine:
            b = bytes.fromhex(e["blob"])
            rows.append([int.from_bytes(b[i : i + 2], "little") for i in range(0, 40, 2)])
            print(
                "  %-28s %-18s %s"
                % (e["demo"], e["map"], " ".join("%04x" % w for w in rows[-1]))
            )
        changed = [i for i in range(20) if len({r[i] for r in rows}) > 1]
        print()
        if changed:
            print("  fields that CHANGED between these sightings: %s" % changed)
            for i in changed:
                print("    field %-2d : %s" % (i, " -> ".join("%04x" % r[i] for r in rows)))
        else:
            print("  identical in every sighting -- nothing changed.")
        return 0

    # Dedupe by SteamID, keeping the most recent sighting and counting matches.
    seen = {}
    for e in all_entries:
        rec = seen.setdefault(e["steamid"], dict(e, matches=0, maps=set()))
        rec["matches"] += 1
        rec["maps"].add(e["map"])
        rec["blob"] = e["blob"]  # latest sighting wins
        rec["demo"] = e["demo"]

    roster = sorted(seen.values(), key=lambda r: -r["matches"])

    # You appear in EVERY recording you made, so the account with by far the most
    # sightings is yours. Only act on it when the lead is decisive -- if the top
    # two are close, say so and exclude nothing rather than drop a real player.
    drop = set(args.exclude)
    if args.whoami and roster:
        top = roster[0]["matches"]
        second = roster[1]["matches"] if len(roster) > 1 else 0
        if top >= 3 * max(second, 1):
            drop.add(roster[0]["steamid"])
            print()
            print("  --whoami: %d (seen %d times vs %d for the next) looks like YOU "
                  "-- excluded." % (roster[0]["steamid"], top, second))
        else:
            print()
            print("  --whoami: top account seen %d times vs %d -- too close to call, "
                  "excluding nothing." % (top, second))

    if drop:
        before = len(roster)
        roster = [r for r in roster if r["steamid"] not in drop]
        print("  excluded %d account(s)." % (before - len(roster)))

    names = {}
    if args.key:
        print()
        print("Resolving %d Steam ID(s) ..." % len(roster))
        names = resolve_names([r["steamid"] for r in roster], args.key)

    print()
    print("=" * 78)
    print(
        "%d distinct player(s) across %d clientinfo entr(ies)"
        % (len(roster), len(all_entries))
    )
    print("=" * 78)
    hdr = "  %-20s %-5s %-24s %s" % ("steamid64", "seen", "name", "last seen in")
    print(hdr)
    print("  " + "-" * (len(hdr) - 2))
    for r in roster:
        nm = names.get(r["steamid"], "")
        print(
            "  %-20d %-5d %-24s %s (%s)"
            % (r["steamid"], r["matches"], nm[:24], r["demo"], r["map"])
        )

    if args.urls:
        print()
        for r in roster:
            print("  %s" % profile_url(r["steamid"]))

    if not args.key:
        print()
        print("  No --key given, so names are blank.")
        print("  Get a free key at https://steamcommunity.com/dev/apikey and re-run")
        print("  with --key <key>, or use --urls to open the profiles directly.")

    if args.blob:
        dump_blob(roster)

    if args.botnames:
        if not names:
            print()
            print("  --botnames needs --key: the demos carry Steam IDs, not names.")
            return 1
        written = 0
        dropped = []
        dupes = 0
        seen_lower = set()
        lines = []
        for r in roster:
            raw = names.get(r["steamid"], "")
            nm = clean_name(raw)
            if not nm:
                dropped.append(raw)
                continue
            # Two accounts can share a persona name; duplicate bot names in one
            # match would be confusing, so keep the first.
            if nm.lower() in seen_lower:
                dupes += 1
                continue
            seen_lower.add(nm.lower())
            lines.append(nm)
            written += 1

        with open(args.botnames, "w", encoding="utf-8") as fh:
            fh.write("# Generated by tools/s2_players.py from your own recordings.\n")
            fh.write("# %d name(s), from %d account(s) across %d clientinfo entries.\n"
                     % (written, len(roster), len(all_entries)))
            fh.write("# Colour codes (^1 etc) were stripped; add them back by hand if\n")
            fh.write("# you want a coloured bot name -- the mod passes them through.\n")
            fh.write("# Edit freely -- the mod reloads this while the game runs.\n\n")
            fh.write("\n".join(lines) + "\n")

        print()
        print("  wrote %d name(s) to %s" % (written, args.botnames))
        if dupes:
            print("  (%d duplicate name(s) collapsed)" % dupes)
        if dropped:
            print("  (%d rejected as unusable: %s)"
                  % (len(dropped), ", ".join(repr(d)[:24] for d in dropped[:4])))

    if args.csv:
        with open(args.csv, "w", newline="", encoding="utf-8") as fh:
            w = csvmod.writer(fh)
            w.writerow(["steamid64", "name", "matches", "team", "blob", "demo", "map"])
            for r in roster:
                w.writerow(
                    [
                        r["steamid"],
                        names.get(r["steamid"], ""),
                        r["matches"],
                        r["team"],
                        r["blob"],
                        r["demo"],
                        r["map"],
                    ]
                )
        print()
        print("  wrote %s" % args.csv)

    return 0


if __name__ == "__main__":
    sys.exit(main())
