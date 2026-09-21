#!/usr/bin/env python3
"""
propagate_callers.py -- name an unknown S2 function from the INTERSECTION of what
its named callers' reference twins call.

WHY THE CALLER SIDE
    propagate_callgraph.py works from the callee side: take a matched pair and
    hope exactly one callee is unknown on each side. With S2 only ~7% named that
    almost never holds -- it yielded 18 names from 730 seed pairs.

    Turn it around. For an unknown X, collect the S2 functions that CALL it and
    are themselves named. Map each to its twin in the reference. Whatever X is,
    its name must appear in what EVERY one of those twins calls. Intersecting
    three callers' callee-name sets is enormously more constraining than looking
    at one caller's callees, and it gets stronger as coverage grows rather than
    weaker.

    Then subtract every name already worn by some other S2 function that those
    same callers call -- those are accounted for. If exactly one name survives,
    that is X.

EVIDENCE TIERS
    Reported by number of independent named callers. 1 caller is weak (it is just
    the old method wearing a hat); 2 is reasonable; 3+ is strong, because three
    unrelated functions would have to agree by coincidence.

USAGE
    python re/propagate_callers.py <s2_funcs.json> <s2_names_now.json>
                                   <ref_funcs.json> <out.json> [label]
"""

from __future__ import annotations

import collections
import json
import sys
from pathlib import Path

UNNAMED = ("sub_", "nullsub", "j_", "unknown_", "loc_")


def is_named(n: str) -> bool:
    return not n.startswith(UNNAMED)


def demangle_lite(n: str) -> str:
    if n.startswith("??") and len(n) > 3 and n[2].isdigit():
        end = n.find("@@")
        if end > 3:
            parts = [q for q in n[3:end].split("@") if q]
            if parts:
                return "::".join(reversed(parts)) + "::" + parts[0]
    if n.startswith("?"):
        end = n.find("@@")
        if end > 1:
            return "::".join(reversed([p for p in n[1:end].split("@") if p]))
    return n


def norm(n: str) -> str:
    return demangle_lite(n).replace("::", "__").rstrip("_").lower()


def main() -> int:
    if len(sys.argv) not in (5, 6):
        print(__doc__)
        return 2

    s2 = json.loads(Path(sys.argv[1]).read_text())
    names_now = json.loads(Path(sys.argv[2]).read_text())
    ref = json.loads(Path(sys.argv[3]).read_text())
    label = sys.argv[5] if len(sys.argv) == 6 else "REF"

    for a, n in names_now.items():
        if a in s2:
            s2[a][1] = n

    ref_by_norm = {}
    for a, v in ref.items():
        if is_named(v[1]):
            ref_by_norm.setdefault(norm(v[1]), a)

    # every name currently worn by an S2 function -- these are "accounted for"
    s2_taken = {norm(v[1]) for v in s2.values() if is_named(v[1])}

    # reverse the graph: callee -> its callers
    callers = collections.defaultdict(list)
    for a, v in s2.items():
        for c in v[2]:
            callers[hex(c)].append(a)

    proposals = []
    stats = collections.Counter()

    for func, v in s2.items():
        if is_named(v[1]):
            continue
        # named callers that also exist in the reference
        twins = []
        for ca in callers.get(func, []):
            cn = s2[ca][1]
            if not is_named(cn):
                continue
            ra = ref_by_norm.get(norm(cn))
            if ra:
                twins.append((ca, ra))
        if not twins:
            continue

        # intersect what each twin calls
        sets = []
        for _ca, ra in twins:
            sets.append({norm(ref[hex(c)][1]) for c in ref[ra][2]
                         if hex(c) in ref and is_named(ref[hex(c)][1])})
        inter = set.intersection(*sets) if sets else set()
        if not inter:
            stats["empty intersection"] += 1
            continue

        # drop names already worn by an S2 function -- they are spoken for
        left = inter - s2_taken
        if len(left) != 1:
            stats["ambiguous" if len(left) > 1 else "all accounted for"] += 1
            continue

        key = next(iter(left))
        # recover the reference's original spelling
        pretty = None
        for _ca, ra in twins:
            for c in ref[ra][2]:
                if hex(c) in ref and norm(ref[hex(c)][1]) == key:
                    pretty = demangle_lite(ref[hex(c)][1])
                    break
            if pretty:
                break
        proposals.append({"s2_func": func, "name": pretty, "callers": len(twins),
                          "size": v[0],
                          "via": sorted({s2[ca][1] for ca, _ in twins})[:4]})
        stats[f"{min(len(twins), 3)}-caller"] += 1

    # one function per name
    byn = collections.Counter(norm(p["name"]) for p in proposals)
    clean = [p for p in proposals if byn[norm(p["name"])] == 1]
    clean.sort(key=lambda p: (-p["callers"], -p["size"]))

    Path(sys.argv[4]).write_text(json.dumps(clean, indent=1))
    print(f"reference: {label}")
    print("outcome:", dict(stats))
    print(f"proposals: {len(clean)} (dropped {len(proposals) - len(clean)} name-collisions)")
    print(f"\n{'callers':>7} {'size':>7} {'func':>10}  name")
    print("-" * 78)
    for p in clean[:28]:
        print(f"{p['callers']:>7} {p['size']:>7} {p['s2_func']:>10}  {p['name'][:40]:<40} via {p['via'][0][:22]}")
    print("\nwrote", sys.argv[4])
    return 0


if __name__ == "__main__":
    sys.exit(main())
