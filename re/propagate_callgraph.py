#!/usr/bin/env python3
"""
propagate_callgraph.py -- extend S2's naming outward from functions that are
already named, using a named reference build's call graph.

THE IDEA
    If S2 function A and reference function B carry the same name, they are the
    same function. Their callee SETS should then correspond. So line the two sets
    up by the names they already share; if exactly one S2 callee is left unnamed
    and exactly one reference callee name is left unaccounted for, those two are
    each other.

    That is a "set difference of one" -- deliberately the most conservative form.
    Any seed with two or more unknowns on either side is skipped outright rather
    than guessed at.

WHY SETS AND NOT CALL ORDER
    Positional matching drifts: different compilers, different inlining, five
    years apart. Set difference is order-independent, and the export sorts
    callees by address anyway, so call order is not recoverable from it.

THE REAL SAFEGUARD IS CORROBORATION
    One seed proposing a name is a coincidence waiting to happen. The script
    therefore counts how many INDEPENDENT seeds arrive at the same
    (S2 function -> name) pair, and reports the tiers separately so the caller
    can require >= 2. A proposal contradicted by any seed is dropped entirely.

USAGE
    python re/propagate_callgraph.py <s2_funcs.json> <s2_names_now.json>
                                     <ref_funcs.json> <out.json> [ref_label]
"""

from __future__ import annotations

import collections
import json
import sys
from pathlib import Path

UNNAMED = ("sub_", "nullsub", "j_", "unknown_", "loc_")


def is_named(n: str) -> bool:
    return not n.startswith(UNNAMED)


def norm(n: str) -> str:
    """AW writes C++ names with '::', MWR with '__'. Treat them as one."""
    return n.replace("::", "__").rstrip("_").lower()


def main() -> int:
    if len(sys.argv) not in (5, 6):
        print(__doc__)
        return 2

    s2_graph = json.loads(Path(sys.argv[1]).read_text())
    s2_names = json.loads(Path(sys.argv[2]).read_text())
    ref = json.loads(Path(sys.argv[3]).read_text())
    label = sys.argv[5] if len(sys.argv) == 6 else "REF"

    # current S2 names override whatever the graph snapshot held
    for a, n in s2_names.items():
        if a in s2_graph:
            s2_graph[a][1] = n

    ref_by_norm = {}
    for a, (_sz, n, _c) in ref.items():
        if is_named(n):
            ref_by_norm.setdefault(norm(n), a)

    # ITERATE. Every name resolved shrinks the unknown set for its neighbours, so
    # a round that finds nothing new is the fixed point. This compounds coverage
    # WITHOUT loosening the evidence rule -- each round still demands exactly one
    # unknown on each side.
    proposals = []
    claimed: set[str] = set()
    total_contradicted = 0

    for gen in range(1, 9):
        seeds = [(a, ref_by_norm[norm(v[1])])
                 for a, v in s2_graph.items()
                 if is_named(v[1]) and norm(v[1]) in ref_by_norm]

        votes: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
        via: dict[str, list] = collections.defaultdict(list)
        used = 0

        for s2a, refa in seeds:
            s2_callees = s2_graph[s2a][2]
            ref_callees = ref[refa][2]

            s2_named = {norm(s2_graph[hex(c)][1]) for c in s2_callees
                        if hex(c) in s2_graph and is_named(s2_graph[hex(c)][1])}
            s2_unknown = [hex(c) for c in s2_callees
                          if hex(c) in s2_graph and not is_named(s2_graph[hex(c)][1])]

            ref_names = [ref[hex(c)][1] for c in ref_callees
                         if hex(c) in ref and is_named(ref[hex(c)][1])]
            ref_left = [n for n in ref_names if norm(n) not in s2_named]

            if len(s2_unknown) != 1 or len(ref_left) != 1:
                continue
            used += 1
            votes[s2_unknown[0]][ref_left[0]] += 1
            via[s2_unknown[0]].append(s2_graph[s2a][1])

        fresh = []
        for func, c in votes.items():
            if len(c) > 1:
                total_contradicted += 1
                continue
            name = next(iter(c))
            if norm(name) in claimed:
                continue
            fresh.append({"s2_func": func, "name": name, "seeds": c[name],
                          "via": sorted(set(via[func]))[:4],
                          "size": s2_graph[func][0], "gen": gen})

        # one function per name within this round too
        byn = collections.Counter(norm(p["name"]) for p in fresh)
        fresh = [p for p in fresh if byn[norm(p["name"])] == 1]

        print(f"  gen {gen}: seeds={len(seeds):>5} usable={used:>4} new={len(fresh)}")
        if not fresh:
            break

        # feed them back in so the next round can build on them
        for p in fresh:
            s2_graph[p["s2_func"]][1] = p["name"]
            claimed.add(norm(p["name"]))
        proposals.extend(fresh)

    contradicted = total_contradicted

    # a name proposed for two different functions is unusable
    byname = collections.Counter(norm(p["name"]) for p in proposals)
    clean = [p for p in proposals if byname[norm(p["name"])] == 1]

    clean.sort(key=lambda p: (p["gen"], -p["seeds"], -p["size"]))
    Path(sys.argv[4]).write_text(json.dumps(clean, indent=1))

    tiers = collections.Counter("gen%d" % p["gen"] for p in clean)
    print(f"seeds usable (exactly one unknown each side): {used}")
    print(f"proposals: {len(clean)}   (dropped {contradicted} contradicted, "
          f"{len(proposals) - len(clean)} name-collisions)")
    print("by corroboration:", dict(tiers))
    print("\ntop proposals:")
    for p in clean[:20]:
        print(f"  {p['seeds']}x {p['size']:>6}B {p['s2_func']:>9} -> {p['name'][:44]:<44} via {p['via'][0]}")
    print("\nwrote", sys.argv[4])
    return 0


if __name__ == "__main__":
    sys.exit(main())
