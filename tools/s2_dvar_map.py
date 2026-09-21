#!/usr/bin/env python3
"""
s2_dvar_map.py -- work with S2's numeric dvar names, offline.

WHY DVARS ARE NUMERIC
---------------------
S2 registers nearly everything under a numeric name -- "1762" is the cg_drawGun
equivalent, "1766" is the demo record enable, "5816" is cl_demo_pause. The real
names are not in the shipped binary.

CAN A SCRIPT JUST NAME THEM ALL?  NO -- and here is the evidence, measured from the
1259 mappings we already have in src/DvarMappings.hpp:

    ids sorted ascending -> names alphabetical   50.8%   (chance; NOT an alpha index)
    prefix clustering                            none    (cg_* spans ids 35..5860)
    distinct ids / names                    1254 / 1259  (near-collision-free, so it
                                                          is an INDEX or counter,
                                                          not a hash of the name)
    the tail 6017..6021 is IsdlcDivisionEnabled_ARTILLERY / SCOUT / COMMANDO /
    GRENADIER / RESISTANCE -- sequential AND semantically grouped, which is what
    registration order looks like.

A registration index is not invertible: there is no function from "4231" back to a
name. Names can only come from a SOURCE (a dump, another build, or identifying the
dvar by what reads it, as we did for 1762/1766/5816/2669).

So this tool does the parts that ARE possible:
  * report coverage of the existing mapping
  * translate either direction, so a numeric id in a log or decompile becomes a name
  * list which ids are still unnamed, to target the manual work
  * merge newly discovered names back into DvarMappings.hpp format

    python tools/s2_dvar_map.py --stats
    python tools/s2_dvar_map.py 1762 5816 cg_fov      (either direction, mixed)
    python tools/s2_dvar_map.py --unknown 1..200      (ids in a range with no name)
    python tools/s2_dvar_map.py --grep demo           (names matching a substring)
    python tools/s2_dvar_map.py --add 4231=cl_demo_freecamSpeed
"""

import argparse
import os
import re
import sys

HPP = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                   "..", "src", "DvarMappings.hpp")
ROW = re.compile(r'\{\s*"([^"]*)"\s*,\s*"([^"]*)"\s*,\s*"(.*?)"\s*\}', re.S)


def load():
    txt = open(HPP, encoding="utf-8", errors="replace").read()
    rows = ROW.findall(txt)
    by_id, by_name = {}, {}
    for name, eng, desc in rows:
        by_name[name.lower()] = (eng, desc)
        if eng.isdigit():
            by_id[eng] = (name, desc)
    return rows, by_id, by_name


def cmd_stats(rows, by_id, _by_name):
    numeric = [(u, e) for u, e, _d in rows if e.isdigit()]
    ident = [(u, e) for u, e, _d in rows if u == e]
    desc = [r for r in rows if r[2].strip()]
    ids = sorted(int(e) for _u, e in numeric)
    print("DvarMappings.hpp")
    print("  entries                 %d" % len(rows))
    print("  real name -> numeric    %d" % len(numeric))
    print("  already plain-named     %d" % len(ident))
    print("  with a description      %d" % len(desc))
    print("  distinct numeric ids    %d   range %d..%d" % (len(set(ids)), ids[0], ids[-1]))
    unknown = len(range(ids[0], ids[-1] + 1)) - len(set(ids))
    print("  ids in range with NO name  %d" % unknown)
    print()
    print("  The id is a registration index, not a hash or an alphabetical position,")
    print("  so those %d cannot be derived -- they need a source or identification" % unknown)
    print("  by what reads them. See this file's header for the measurements.")
    return 0


def cmd_lookup(terms, by_id, by_name):
    for t in terms:
        key = t.strip()
        if key.isdigit():
            hit = by_id.get(key)
            if hit:
                print("%-8s -> %s%s" % (key, hit[0], ("   // " + hit[1]) if hit[1] else ""))
            else:
                print("%-8s -> UNKNOWN (no name recorded for this id)" % key)
        else:
            hit = by_name.get(key.lower())
            if hit:
                print("%-32s -> %s%s" % (key, hit[0], ("   // " + hit[1]) if hit[1] else ""))
            else:
                print("%-32s -> UNKNOWN (not in the mapping)" % key)
    return 0


def cmd_unknown(spec, by_id):
    m = re.match(r"^(\d+)\.\.(\d+)$", spec)
    if not m:
        raise SystemExit("--unknown takes a range like 1..200")
    lo, hi = int(m.group(1)), int(m.group(2))
    miss = [n for n in range(lo, hi + 1) if str(n) not in by_id]
    print("%d of %d ids in %d..%d have no recorded name" % (len(miss), hi - lo + 1, lo, hi))
    for i in range(0, len(miss), 16):
        print("   " + " ".join("%5d" % n for n in miss[i:i + 16]))
    return 0


def cmd_grep(pat, rows):
    rx = re.compile(pat, re.I)
    hits = [(u, e, d) for u, e, d in rows if rx.search(u)]
    print("%d name(s) matching %r" % (len(hits), pat))
    for u, e, d in sorted(hits):
        print("   %-40s %-8s %s" % (u, e, d))
    return 0


def cmd_add(assignments):
    """Emit DvarMappings.hpp rows for newly identified dvars."""
    out = []
    for a in assignments:
        if "=" not in a:
            raise SystemExit("--add takes id=name, e.g. 4231=cl_demo_freecamSpeed")
        num, name = a.split("=", 1)
        num, name = num.strip(), name.strip()
        if not num.isdigit():
            raise SystemExit("left side must be the numeric id: %r" % a)
        out.append('\t{ "%s", "%s", "" },' % (name, num))
    print("Paste into src/DvarMappings.hpp (keep the file sorted by name):")
    for line in out:
        print(line)
    return 0


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("terms", nargs="*", help="numeric ids and/or dvar names to translate")
    ap.add_argument("--stats", action="store_true")
    ap.add_argument("--unknown", metavar="LO..HI")
    ap.add_argument("--grep", metavar="PATTERN")
    ap.add_argument("--add", nargs="+", metavar="ID=NAME")
    a = ap.parse_args()

    rows, by_id, by_name = load()
    if a.stats:
        return cmd_stats(rows, by_id, by_name)
    if a.unknown:
        return cmd_unknown(a.unknown, by_id)
    if a.grep:
        return cmd_grep(a.grep, rows)
    if a.add:
        return cmd_add(a.add)
    if a.terms:
        return cmd_lookup(a.terms, by_id, by_name)
    ap.print_help()
    return 0


if __name__ == "__main__":
    sys.exit(main())
