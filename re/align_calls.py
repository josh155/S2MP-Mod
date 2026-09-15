#!/usr/bin/env python3
"""
align_calls.py -- name unknowns by ALIGNING the call sequences of matched pairs.

WHY
    Caller-intersection cannot bootstrap CL_/SV_/CG_: those functions are mostly
    called by other unnamed CL_/SV_/CG_ functions, so there are no named callers
    to intersect. But a matched pair -- same name in S2 and in the reference --
    calls broadly the same things in broadly the same ORDER, because the two
    binaries share a source lineage.

    So use the callees whose names ALREADY match on both sides as anchors, and
    align what sits between them. If exactly one unnamed S2 callee and exactly one
    unaccounted reference callee sit between the SAME two anchors, they are each
    other.

WHY ANCHORS RATHER THAN RAW POSITION
    Raw positional matching drifts the moment either compiler inlines something.
    Anchors re-synchronise the sequences at every point where both sides agree, so
    drift is contained to the gap it occurs in rather than propagating.

SAFEGUARDS
    - at least MIN_ANCHORS matching callees, so the alignment is constrained
    - only gaps with exactly one unknown on each side are used
    - votes are collected across every pair; a function whose votes disagree is
      dropped, never resolved by majority
    - a name proposed for two different functions is dropped

USAGE
    python re/align_calls.py <s2_ord.json> <ref_ord.json> <pairs.json> <out.json> [label]
"""

from __future__ import annotations

import collections
import json
import sys
from pathlib import Path

UNNAMED = ("sub_", "nullsub", "j_", "unknown_", "loc_")
MIN_ANCHORS = 2


def is_named(n: str) -> bool:
    return not n.startswith(UNNAMED)


def dm(n: str) -> str:
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


def norm(n: str) -> str:
    return dm(n).replace("::", "__").rstrip("_").lower()


def main() -> int:
    if len(sys.argv) not in (5, 6):
        print(__doc__)
        return 2

    s2 = json.loads(Path(sys.argv[1]).read_text())
    ref = json.loads(Path(sys.argv[2]).read_text())
    pairs = json.loads(Path(sys.argv[3]).read_text())
    label = sys.argv[5] if len(sys.argv) == 6 else "REF"

    votes: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    via: dict[str, list] = collections.defaultdict(list)
    stats = collections.Counter()

    for s2a, refa in pairs:
        A, B = s2.get(s2a), ref.get(refa)
        if not A or not B:
            continue
        aseq, bseq = A[2], B[2]
        if not aseq or not bseq:
            continue

        # anchors: a callee name present, named, on BOTH sides
        bpos = {}
        for j, (_ba, bn) in enumerate(bseq):
            if is_named(bn):
                bpos.setdefault(norm(bn), j)

        anchors = []          # (i in aseq, j in bseq)
        last_j = -1
        for i, (_aa, an) in enumerate(aseq):
            if not is_named(an):
                continue
            j = bpos.get(norm(an))
            if j is not None and j > last_j:
                anchors.append((i, j))
                last_j = j

        if len(anchors) < MIN_ANCHORS:
            stats["too few anchors"] += 1
            continue
        stats["aligned"] += 1

        # walk the gaps between consecutive anchors
        for (i0, j0), (i1, j1) in zip(anchors, anchors[1:]):
            aun = [aseq[k] for k in range(i0 + 1, i1) if not is_named(aseq[k][1])]
            anamed = {norm(aseq[k][1]) for k in range(i0 + 1, i1) if is_named(aseq[k][1])}
            bleft = [bseq[k][1] for k in range(j0 + 1, j1)
                     if is_named(bseq[k][1]) and norm(bseq[k][1]) not in anamed]
            if len(aun) == 1 and len(bleft) == 1:
                votes[aun[0][0]][dm(bleft[0])] += 1
                via[aun[0][0]].append(A[1])
                stats["gap resolved"] += 1
            elif aun and bleft:
                stats["gap ambiguous"] += 1

    proposals = []
    for func, c in votes.items():
        if len(c) > 1:
            stats["contradicted"] += 1
            continue
        name = next(iter(c))
        proposals.append({"s2_func": func, "name": name, "votes": c[name],
                          "via": sorted(set(via[func]))[:4]})

    byn = collections.Counter(norm(p["name"]) for p in proposals)
    clean = [p for p in proposals if byn[norm(p["name"])] == 1]
    clean.sort(key=lambda p: -p["votes"])

    Path(sys.argv[4]).write_text(json.dumps(clean, indent=1))
    print(f"reference: {label}")
    print("stats:", dict(stats))
    print(f"proposals: {len(clean)} "
          f"(dropped {len(proposals) - len(clean)} name-collisions)")
    print(f"\n{'votes':>6} {'func':>10}  name")
    print("-" * 70)
    for p in clean[:30]:
        print(f"{p['votes']:>6} {p['s2_func']:>10}  {p['name'][:42]:<42} via {p['via'][0][:20]}")
    print("\nwrote", sys.argv[4])
    return 0


if __name__ == "__main__":
    sys.exit(main())
