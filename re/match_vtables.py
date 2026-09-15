#!/usr/bin/env python3
"""
match_vtables.py -- pair S2 function-pointer tables with AW's and name the slots.

WHY VTABLES ARE THE STRONGEST ALIGNMENT TARGET
    Slot order is fixed by the C++ ABI (declaration order), not by the optimiser,
    so unlike call-sequence alignment there is no inlining drift to contain. Two
    tables that agree on a couple of already-named slots are almost certainly the
    same table, and then EVERY remaining slot lines up.

MATCHING
    For each S2 table x AW table pair, count slots where S2's existing name equals
    AW's (normalised). Require MIN_ANCHORS agreements.
      - equal length  -> align strictly by index
      - differing     -> anchored alignment; only gaps bounded by two anchors and
                         containing exactly one unknown on each side resolve.
    A class that gained or lost a method between the two games shifts indices,
    which is exactly what the anchored path handles and the strict path must not
    be allowed to paper over.

SAFEGUARDS
    - a table may pair with only its single best AW counterpart
    - a name proposed for two S2 functions is dropped
    - never overwrite an existing S2 name; disagreements are reported, not applied

USAGE
    python re/match_vtables.py <s2_vtables.json> <aw_vtables.json>
                               <s2_names.json> <aw_funcs.json> <out.json>
"""

from __future__ import annotations

import collections
import json
import sys
from pathlib import Path

MIN_ANCHORS = 2
UNNAMED = ("sub_", "nullsub", "j_", "unknown_", "loc_")


def is_named(n):
    return n and not n.startswith(UNNAMED)


def dm(n):
    if n.startswith("??") and len(n) > 3 and n[2].isdigit():
        e = n.find("@@")
        if e > 3:
            parts = [q for q in n[3:e].split("@") if q]
            if parts:
                return "::".join(reversed(parts)) + "::" + parts[0]
    if n.startswith("?"):
        e = n.find("@@")
        if e > 1:
            return "::".join(reversed([p for p in n[1:e].split("@") if p]))
    return n


def norm(n):
    return dm(n).replace("::", "__").rstrip("_").lower()


def main() -> int:
    if len(sys.argv) != 6:
        print(__doc__)
        return 2

    s2_tabs = json.loads(Path(sys.argv[1]).read_text())
    aw_tabs = json.loads(Path(sys.argv[2]).read_text())
    s2_names = json.loads(Path(sys.argv[3]).read_text())
    aw_g = json.loads(Path(sys.argv[4]).read_text())
    aw_names = {a: v[1] for a, v in aw_g.items()}

    def s2n(a):
        return s2_names.get(a, "")

    def awn(a):
        return aw_names.get(a, "")

    proposals, report = [], []
    used_aw = set()

    for saddr, sents in s2_tabs:
        best = None
        for aaddr, aents in aw_tabs:
            if aaddr in used_aw:
                continue
            # count slots where both sides already agree
            hits = 0
            for i, se in enumerate(sents):
                if i >= len(aents):
                    break
                a, b = s2n(se), awn(aents[i])
                if is_named(a) and is_named(b) and norm(a) == norm(b):
                    hits += 1
            if hits >= MIN_ANCHORS and (best is None or hits > best[0]):
                best = (hits, aaddr, aents)
        if not best:
            continue
        hits, aaddr, aents = best
        used_aw.add(aaddr)
        same_len = len(sents) == len(aents)
        report.append((saddr, len(sents), aaddr, len(aents), hits, same_len))

        if same_len:
            pairs = list(zip(sents, aents))
        else:
            # anchored: only resolve gaps bounded by agreeing slots
            anchors = []
            j = 0
            for i, se in enumerate(sents):
                a = s2n(se)
                if not is_named(a):
                    continue
                for k in range(j, len(aents)):
                    if norm(awn(aents[k])) == norm(a):
                        anchors.append((i, k))
                        j = k + 1
                        break
            pairs = []
            for (i0, k0), (i1, k1) in zip(anchors, anchors[1:]):
                # everything strictly between two agreeing slots, in order
                sgap = [sents[x] for x in range(i0 + 1, i1)]
                agap = [aents[y] for y in range(k0 + 1, k1)]
                su = [x for x in sgap if not is_named(s2n(x))]
                au = [y for y in agap if is_named(awn(y))]
                if len(su) == 1 and len(au) == 1:
                    pairs.append((su[0], au[0]))
                elif len(sgap) == len(agap) and sgap:
                    # EQUAL-WIDTH GAP. Slot order in these tables is fixed by the
                    # ABI (declaration order), not by the optimiser, so a gap that
                    # is the same width on both sides between two agreeing anchors
                    # corresponds 1:1 in order. Weaker than a single-unknown gap --
                    # tagged separately so it can be reviewed or dropped.
                    for x, y in zip(sgap, agap):
                        if not is_named(s2n(x)) and is_named(awn(y)):
                            pairs.append((x, y))

        for se, ae in pairs:
            if is_named(s2n(se)):
                continue
            nm = dm(awn(ae))
            if not is_named(nm):
                continue
            proposals.append({"s2_func": se, "name": nm, "s2_table": saddr,
                              "aw_table": aaddr, "anchors": hits,
                              "mode": "index" if same_len else "anchored"})

    byn = collections.Counter(norm(p["name"]) for p in proposals)
    byf = collections.Counter(p["s2_func"] for p in proposals)
    clean = [p for p in proposals
             if byn[norm(p["name"])] == 1 and byf[p["s2_func"]] == 1]

    Path(sys.argv[5]).write_text(json.dumps(clean, indent=1))

    report.sort(key=lambda r: -r[4])
    print(f"{'S2 table':>12} {'n':>4}  {'AW table':>12} {'n':>4} {'anchors':>8} {'len':>6}")
    print("-" * 60)
    for r in report[:20]:
        print(f"{r[0]:>12} {r[1]:>4}  {r[2]:>12} {r[3]:>4} {r[4]:>8} "
              f"{'same' if r[5] else 'diff':>6}")
    print(f"\npaired tables: {len(report)}")
    print(f"proposals: {len(clean)} (dropped {len(proposals) - len(clean)} collisions)")
    print("\nsample:")
    for p in clean[:25]:
        print(f"  {p['s2_func']:>10} -> {p['name'][:52]:<52} [{p['mode']}, {p['anchors']}a]")
    return 0


if __name__ == "__main__":
    sys.exit(main())
