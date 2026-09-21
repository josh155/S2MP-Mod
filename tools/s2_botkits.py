#!/usr/bin/env python3
"""
s2_botkits.py -- build the mod's botkits.txt from the GAME'S OWN costume tables.

Offline. No game, no IDA. Reads the CSVs produced by the in-game
`dumpAllCSVFiles` command and emits named kits the mod can use.

WHY THIS EXISTS
    A bot's look travels in its connect string as \\ctz\\ and is SEVEN integers:

        sub_14B820(struct, buf, size) =
            Com_sprintf(buf, size, "%d|%d|%d|%d|%d|%d|%d|",
                        dword@+0, +4, +8, +12, +16, +20, byte@+24);

    The engine's own bot costume table has exactly six labelled rows --
    shirt, head, pants, eyewear, hat, gear -- one per dword, with each COLUMN a
    complete outfit. So a kit is just a column.

    Using the shipped tables means the uniforms are real, coherent and
    developer-authored, rather than guessed or copied off the local player.

⚠ FIELD ORDER IS AN INFERENCE, NOT PROVEN.
    botcostumetable.csv's row order is shirt,head,pants,eyewear,hat,gear and we
    assume the ctz dwords are in that same order. That is consistent but has NOT
    been confirmed against the parser (sub_14CD30). If bots come out wearing the
    wrong pieces, this ordering is the first thing to re-check -- everything else
    here is read straight from the game's data.

    The SEVENTH field (the byte at +24) is NOT in the costume table and its
    meaning is unknown, so it is written as 0 and left alone.

USAGE
    python tools/s2_botkits.py                       # scan the default dump dir
    python tools/s2_botkits.py --dump <dir>
    python tools/s2_botkits.py --out botkits.txt
    python tools/s2_botkits.py --list                # just show what was found
"""

import argparse
import csv
import os
import sys

for _s in (sys.stdout, sys.stderr):
    try:
        _s.reconfigure(encoding="utf-8", errors="replace")
    except Exception:
        pass

DEFAULT_DUMP = (r"E:\SteamLibrary\steamapps\common\Call of Duty WWII"
                r"\S2MP-Mod\dump\mp")
DEFAULT_OUT = (r"E:\SteamLibrary\steamapps\common\Call of Duty WWII"
               r"\S2MP-Mod\botkits.txt")

# The order botcostumetable.csv labels its rows in -- assumed to match the ctz
# dword order. See the caveat at the top of this file.
FIELDS = ["shirt", "head", "pants", "eyewear", "hat", "gear"]

# High byte of a packed costume id -> category, from costumeidtable.csv
# (e.g. eyewear ... 0x6C00004, shirt ... 0x6200001).
PACKED_CATEGORY = {
    0x62: "shirt", 0x63: "head", 0x64: "pants",
    0x6C: "eyewear", 0x66: "hat", 0x67: "gear",
    0x60: "uniform",
}


def rows(path):
    if not os.path.isfile(path):
        return []
    with open(path, newline="", encoding="latin1") as fh:
        return [r for r in csv.reader(fh) if r]


def load_names(dump):
    """(category, index) -> readable item name, from costumeidtable.csv."""
    out = {}
    for r in rows(os.path.join(dump, "costumeidtable.csv")):
        # category,,,?,index,LOOT_NAME,,packedId,unlocked,...
        if len(r) < 6:
            continue
        cat = r[0].strip()
        try:
            idx = int(r[4])
        except ValueError:
            continue
        name = r[5].strip()
        if not name:
            continue
        if name.startswith("LOOT_"):
            name = name[5:]
        if name.endswith("_CAPS"):
            name = name[:-5]
        out[(cat, idx)] = name.replace("_", " ").title()
    return out


def kits_from_bot_table(dump):
    """botcostumetable.csv: rows are fields, columns are outfits."""
    r = rows(os.path.join(dump, "botcostumetable.csv"))
    if not r:
        return []
    groups, cur = [], {}
    for row in r:
        field = row[0].strip()
        vals = []
        for v in row[1:]:
            try:
                vals.append(int(v))
            except ValueError:
                vals.append(0)
        if field in cur:                 # a repeated label starts a new group
            groups.append(cur)
            cur = {}
        cur[field] = vals
    if cur:
        groups.append(cur)

    out = []
    for gi, g in enumerate(groups):
        width = min((len(v) for v in g.values()), default=0)
        for col in range(width):
            out.append(("bot%d" % gi, [g.get(f, [0] * width)[col] for f in FIELDS]))
    return out


def kits_from_division_table(dump, fname, tag):
    """Division/costume tables hold PACKED ids; the low 16 bits are the index."""
    r = rows(os.path.join(dump, fname))
    if not r:
        return []
    table = {}
    for row in r:
        field = row[0].strip()
        vals = []
        for v in row[1:]:
            v = v.strip()
            try:
                vals.append(int(v, 16) if v.lower().startswith("0x") else int(v))
            except ValueError:
                vals.append(0)
        table[field] = vals

    width = min((len(v) for v in table.values()), default=0)
    out = []
    for col in range(width):
        vals = []
        for f in FIELDS:
            packed = table.get(f, [0] * width)[col]
            vals.append(packed & 0xFFFF)          # index within the category
        out.append((tag, vals))
    return out


def kits_from_all_uniforms(dump, names):
    """EVERY uniform in costumeidtable, not just the preset columns.

    PROVEN: a uniform reuses ONE index across every category. Index 9 resolves to
    LOOT_BRITISH_DESERT_RAT_UNIFORM in shirt, pants, hat, gear AND eyewear. So a
    complete outfit is (idx, head, idx, idx-if-it-exists, idx, idx), and the
    shirt list is the authoritative set of uniforms.

    This is what makes the list large: the preset tables only ever used a
    handful, but the game ships 54.
    """
    have = {}
    for (cat, idx) in names:
        have.setdefault(cat, set()).add(idx)

    heads = sorted(have.get("head", {51}))
    default_head = heads[0] if heads else 51

    out = []
    for idx in sorted(have.get("shirt", set())):
        vals = [
            idx,                                              # shirt
            default_head,                                     # head
            idx if idx in have.get("pants", set()) else 0,    # pants
            idx if idx in have.get("eyewear", set()) else 0,  # eyewear
            idx if idx in have.get("hat", set()) else 0,      # hat
            idx if idx in have.get("gear", set()) else 0,     # gear
        ]
        out.append(("uniform", vals))
    return out


def kit_name(vals, names, tag, n):
    """Name a kit after its most identifying piece (the shirt), else its index."""
    shirt = names.get(("shirt", vals[0]))
    if shirt and shirt.lower() not in ("none", ""):
        base = shirt
    else:
        base = "%s Outfit %d" % (tag.title(), n)
    return base.replace(" ", "")[:28]


def write_id_list(dump, src, out_path, header, id_col=0, name_col=2):
    """Emit `id  # Name` lines from a simple id/name table.

    Used for patches.csv (emblems) and callingcards.csv. These are NOT part of
    the ctz costume struct -- SV_UserinfoChanged reads them as their OWN userinfo
    keys, `patch` and `callingcard`, which is exactly why a bot with no such keys
    ends up on the default emblem.
    """
    r = rows(os.path.join(dump, src))
    if not r:
        return 0
    lines = []
    for row in r:
        if len(row) <= max(id_col, name_col):
            continue
        try:
            i = int(row[id_col])
        except ValueError:
            continue
        nm = (row[name_col] or row[1] or "").strip()
        for pre in ("LOOT_", "CALLINGCARDS_", "LUA_MP_FRONTEND_"):
            if nm.startswith(pre):
                nm = nm[len(pre):]
        nm = nm.replace("_", " ").title()
        lines.append("%d  # %s" % (i, nm))
    with open(out_path, "w", encoding="utf-8") as fh:
        fh.write(header)
        fh.write("\n".join(lines) + "\n")
    return len(lines)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dump", default=DEFAULT_DUMP)
    ap.add_argument("--out", default=DEFAULT_OUT)
    ap.add_argument("--list", action="store_true")
    args = ap.parse_args()

    if not os.path.isdir(args.dump):
        print("no dump directory: %s" % args.dump)
        print("run `dumpAllCSVFiles` in game first")
        return 1

    names = load_names(args.dump)
    print("  %d named costume item(s) from costumeidtable.csv" % len(names))

    collected = []
    # EVERY shipped uniform first, so the good names win the dedupe.
    collected += kits_from_all_uniforms(args.dump, names)
    collected += kits_from_bot_table(args.dump)
    for fname, tag in (
        ("alliesdivisioncostumetable.csv", "allies"),
        ("axisdivisioncostumetable.csv", "axis"),
        ("axiscostumetable.csv", "axis"),
        ("hardcorecostumetable.csv", "hardcore"),
        ("practiceroundcostumetable.csv", "practice"),
        ("e3costumetable.csv", "e3"),
    ):
        got = kits_from_division_table(args.dump, fname, tag)
        if got:
            print("  %-34s %2d outfit(s)" % (fname, len(got)))
        collected += got

    # Dedupe identical outfits -- the tables repeat columns a lot.
    seen, kits = set(), []
    for tag, vals in collected:
        key = tuple(vals)
        if key in seen or not any(vals):
            continue
        seen.add(key)
        kits.append((tag, vals))

    print()
    print("  %d distinct outfit(s) after dedupe" % len(kits))

    lines, used = [], set()
    for i, (tag, vals) in enumerate(kits):
        nm = kit_name(vals, names, tag, i)
        base, k = nm, 2
        while nm.lower() in used:
            nm = "%s%d" % (base, k)
            k += 1
        used.add(nm.lower())
        # 7th field unknown -> 0
        lines.append("%s = %s|0" % (nm, "|".join(str(v) for v in vals)))
        if args.list:
            desc = ", ".join(
                "%s=%s" % (f, names.get((f, v), v)) for f, v in zip(FIELDS, vals))
            print("    %-28s %s" % (nm, desc))

    if args.list:
        return 0

    with open(args.out, "w", encoding="utf-8") as fh:
        fh.write("# Generated by tools/s2_botkits.py from the game's OWN costume\n")
        fh.write("# tables (dumpAllCSVFiles). Format: Name = shirt|head|pants|"
                 "eyewear|hat|gear|0\n")
        fh.write("#\n")
        fh.write("# The 7th field is not in the costume tables and its meaning is\n")
        fh.write("# unknown, so it is 0. Field ORDER is inferred from\n")
        fh.write("# botcostumetable.csv's row labels -- if bots wear the wrong\n")
        fh.write("# pieces, that ordering is the thing to re-check.\n")
        fh.write("#\n")
        fh.write("# `bot_look random 50` gives each bot a 50%% chance of one of these.\n\n")
        fh.write("\n".join(lines) + "\n")

    print("  wrote %d kit(s) to %s" % (len(lines), args.out))

    # Emblems and calling cards are SEPARATE userinfo keys (patch / callingcard),
    # not part of the ctz costume struct -- which is why a bot that carries
    # neither ends up on the default emblem.
    base = os.path.dirname(args.out)
    n = write_id_list(args.dump, "patches.csv", os.path.join(base, "botemblems.txt"),
                      "# Emblem ids from the game's own patches.csv.\n"
                      "# One id per line; text after # is ignored.\n"
                      "# Bots pick from these at random so they are not all on\n"
                      "# the default emblem.\n\n")
    print("  wrote %d emblem(s) to botemblems.txt" % n)

    n = write_id_list(args.dump, "callingcards.csv", os.path.join(base, "botcards.txt"),
                      "# Calling card ids from the game's own callingcards.csv.\n"
                      "# One id per line; text after # is ignored.\n\n")
    print("  wrote %d calling card(s) to botcards.txt" % n)
    return 0


if __name__ == "__main__":
    sys.exit(main())
