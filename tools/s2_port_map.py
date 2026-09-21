#!/usr/bin/env python3
"""
s2_port_map.py -- measure (and later build) a Steam -> Xbox address map for the mod.

WHY THIS EXISTS
    The mod hardcodes ~341 addresses of the STEAM build. They are meaningless in
    the Microsoft Store / Game Pass build, whose layout is completely different.
    Porting by hand is 341 separate reverse-engineering jobs; porting by NAME is
    a lookup, because both IDBs are already substantially named (the Xbox one via
    the string-anchor pass that ported 587 names from Steam).

    So the question this answers is: for each address the mod actually uses, is
    the owning function NAMED in Steam, and does that name EXIST in Xbox?

    Tier A  named in both        -> a direct lookup, no analysis
    Tier B  named in Steam only  -> needs a string/twin anchor pass
    Tier C  unnamed (sub_/data)  -> needs real work, one at a time

ADDRESS CONVENTION
    The mod writes `0xNNNN_b`, and `_b` == IDA - 0x1000. Some newer code uses
    `constexpr std::size_t ADDR_X = <already _b-adjusted>`. Both are handled, and
    both are converted back to IDA form before querying.

USAGE
    python tools/s2_port_map.py            # coverage report
    python tools/s2_port_map.py --emit     # write the map we can resolve today
"""

from __future__ import annotations

import argparse
import json
import re
import sys
import urllib.request
from pathlib import Path

STEAM_PORT = 13337
XBOX_PORT = 12346
SRC = Path(__file__).resolve().parent.parent / "src"

# _b literals, and the constexpr form used by the newer modules.
RE_B = re.compile(r"0x([0-9A-Fa-f]+)_b")
RE_ADDR = re.compile(r"ADDR_[A-Z0-9_]+\s*=\s*0x([0-9A-Fa-f]+)")


def rpc(port: int, tool: str, args: dict) -> object:
    """One JSON-RPC call to an ida-pro-mcp server. Returns the decoded payload."""
    body = json.dumps({
        "jsonrpc": "2.0", "id": 1, "method": "tools/call",
        "params": {"name": tool, "arguments": args},
    }).encode()
    req = urllib.request.Request(
        f"http://127.0.0.1:{port}/mcp", body,
        {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=30) as r:
        out = json.load(r)
    if "error" in out:
        raise RuntimeError(out["error"])
    text = out["result"]["content"][0]["text"]
    try:
        return json.loads(text)
    except json.JSONDecodeError:
        return text


def collect_addresses() -> dict[int, list[str]]:
    """Every distinct address the mod uses, in IDA form -> where it appears."""
    found: dict[int, list[str]] = {}
    for path in SRC.rglob("*"):
        if path.suffix not in (".cpp", ".hpp", ".h"):
            continue
        rel = str(path.relative_to(SRC.parent))
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for m in RE_B.finditer(text):
            # `_b` is IDA - 0x1000, so add it back.
            found.setdefault(int(m.group(1), 16) + 0x1000, []).append(rel)
        for m in RE_ADDR.finditer(text):
            found.setdefault(int(m.group(1), 16) + 0x1000, []).append(rel)
    return found


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--emit", metavar="FILE", nargs="?", const="tools/s2_xbox_map.json")
    args = ap.parse_args()

    addrs = collect_addresses()
    print(f"mod uses {len(addrs)} distinct addresses\n")

    # 1. Ask the STEAM idb what each address belongs to.
    steam: dict[int, dict] = {}
    for a in sorted(addrs):
        try:
            info = rpc(STEAM_PORT, "func_query", {"addr": hex(a)})
        except Exception:
            info = None
        steam[a] = info if isinstance(info, dict) else {}

    named = {a: i for a, i in steam.items()
             if i.get("name") and not i["name"].startswith(("sub_", "nullsub_", "loc_"))}
    print(f"  named in the Steam IDB : {len(named)}")
    print(f"  still sub_/data        : {len(addrs) - len(named)}")

    # 2. For each Steam name, does the XBOX idb have it?
    tier_a: dict[int, tuple[str, int]] = {}
    tier_b: list[tuple[int, str]] = []
    for a, info in sorted(named.items()):
        name = info["name"]
        try:
            hit = rpc(XBOX_PORT, "lookup_funcs", {"names": [name]})
        except Exception:
            hit = None
        xa = None
        if isinstance(hit, list) and hit:
            ent = hit[0]
            if isinstance(ent, dict) and ent.get("address"):
                xa = int(str(ent["address"]), 16)
        elif isinstance(hit, dict) and hit.get(name):
            xa = int(str(hit[name]), 16)
        if xa:
            tier_a[a] = (name, xa)
        else:
            tier_b.append((a, name))

    print(f"\n  TIER A  named in BOTH -> direct lookup : {len(tier_a)}")
    print(f"  TIER B  Steam name, not in Xbox yet    : {len(tier_b)}")
    print(f"  TIER C  unnamed, needs real analysis   : {len(addrs) - len(named)}")

    if tier_a:
        print("\n  sample of the direct mappings:")
        for a, (n, xa) in list(sorted(tier_a.items()))[:12]:
            print(f"    {n:<44} steam 0x{a:<9X} -> xbox 0x{xa:X}")

    if tier_b:
        print("\n  needs an anchor pass (named here, not there):")
        for a, n in tier_b[:12]:
            print(f"    {n:<44} steam 0x{a:X}")

    if args.emit:
        out = {f"0x{a:X}": {"name": n, "xbox": f"0x{xa:X}"}
               for a, (n, xa) in sorted(tier_a.items())}
        Path(args.emit).write_text(json.dumps(out, indent=2), encoding="utf-8")
        print(f"\nwrote {len(out)} mappings -> {args.emit}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
