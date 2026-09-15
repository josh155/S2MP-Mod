#!/usr/bin/env python3
"""
match_aw_tables.py -- map S2's {name -> function} binding tables onto Advanced
Warfare's, so AW's real engine symbols can be carried across.

WHY TABLE-FIRST, NOT NAME-FIRST
    Matching bindings by string alone across two different games is careless:
    'ping' or 'show' could mean unrelated things in unrelated tables. So the
    match is done at TABLE granularity first -- two tables correspond only when
    their binding-name SETS overlap heavily -- and entries are matched only
    inside a corresponding pair.

    A table whose name set is {mstart, mdata, ping, pinga, mhead, mstate} in both
    binaries is not a coincidence; a lone shared 'ping' is.

OUTPUT
    A proposal file. Nothing is written to any IDB here -- review, then apply.

USAGE
    python re/match_aw_tables.py <s2_bindings.json> <aw_bindings.json> <out.json>
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

# Two tables correspond if EITHER test passes:
#
#   ratio  -- they share this fraction of the smaller table's names. Good for
#             tables that survived between games basically intact.
#   count  -- they share this many names outright. Needed because AW keeps ONE
#             merged party table where S2 splits it into three and adds
#             WWII-specific commands, so the ratio collapses to ~0.24 even
#             though 'kickedFromParty' / 'partystate' / 'notpresent' matching
#             exactly is not something that happens by chance.
#
# Only the SHARED entries are ever proposed, so a table that matches on 6 of 25
# yields 6 proposals and leaves the other 19 alone.
MIN_OVERLAP = 0.60
MIN_ABS_SHARED = 5
MIN_SHARED = 4


def group(entries, slot_key, gap):
    """Group flat {slot, ...} rows into tables by address adjacency."""
    rows = sorted(entries, key=lambda e: int(e[slot_key], 16))
    tables, cur = [], []
    for r in rows:
        if cur and int(r[slot_key], 16) - int(cur[-1][slot_key], 16) > gap:
            tables.append(cur)
            cur = []
        cur.append(r)
    if cur:
        tables.append(cur)
    return [t for t in tables if len(t) >= MIN_SHARED]


def main() -> int:
    if len(sys.argv) != 4:
        print(__doc__)
        return 2

    s2 = json.loads(Path(sys.argv[1]).read_text())
    aw = json.loads(Path(sys.argv[2]).read_text())

    s2_tabs = group(s2, "slot", 0x80)
    aw_tabs = group(aw, "slot", 0x40)

    print(f"S2 tables: {len(s2_tabs)}   AW tables: {len(aw_tabs)}\n")

    proposals, report = [], []
    for st in s2_tabs:
        snames = {e["binding"] for e in st}
        best, best_score, best_shared = None, 0.0, 0
        for at in aw_tabs:
            anames = {e["binding"] for e in at}
            shared = snames & anames
            if len(shared) < MIN_SHARED:
                continue
            score = len(shared) / min(len(snames), len(anames))
            # rank on shared count first: the merged-vs-split party tables score
            # poorly on ratio but are unambiguous on absolute overlap
            if (len(shared), score) > (best_shared, best_score):
                best, best_score, best_shared = at, score, len(shared)
        if not best or (best_score < MIN_OVERLAP and best_shared < MIN_ABS_SHARED):
            report.append((st[0]["table"], len(st), None, 0.0, 0))
            continue

        amap = {e["binding"]: e for e in best}
        hits = 0
        for e in st:
            a = amap.get(e["binding"])
            if not a:
                continue
            hits += 1
            if not e["cur"].startswith(("sub_", "nullsub", "j_")):
                continue          # already named in S2 -- leave it alone
            if e["ambiguous"]:
                continue
            proposals.append({
                "s2_func": e["func"], "s2_cur": e["cur"], "binding": e["binding"],
                "aw_name": a["name"], "aw_func": a["func"],
                "s2_table": e["table"], "aw_table": best[0]["slot"],
                "table_overlap": round(best_score, 3),
            })
        report.append((st[0]["table"], len(st), best[0]["slot"], round(best_score, 3), hits))

    print(f"{'S2 table':>12} {'n':>4}  {'AW table':>12} {'overlap':>8} {'matched':>8}")
    print("-" * 56)
    for t, n, a, sc, h in sorted(report, key=lambda r: -r[1]):
        print(f"{t:>12} {n:>4}  {str(a):>12} {sc:>8} {h:>8}")

    # A name proposed for two different S2 functions is unusable -- drop both.
    seen: dict[str, int] = {}
    for p in proposals:
        seen[p["aw_name"]] = seen.get(p["aw_name"], 0) + 1
    dupes = {k for k, v in seen.items() if v > 1}
    clean = [p for p in proposals if p["aw_name"] not in dupes]

    Path(sys.argv[3]).write_text(json.dumps(clean, indent=1))
    print(f"\nproposals: {len(clean)}  (dropped {len(proposals) - len(clean)} "
          f"colliding across {len(dupes)} duplicated names)")
    print("wrote", sys.argv[3])
    return 0


if __name__ == "__main__":
    sys.exit(main())
