#!/usr/bin/env python3
"""
s2_match_builds.py -- match functions between the Steam and Store builds.

WHY A HAND-ROLLED MATCHER AND NOT BinDiff/Diaphora
    Neither is installed, and the conditions here are unusually easy: the two
    builds are the same source with the same compiler settings, so 21 of 22
    known-good pairs are IDENTICAL in size. Size is therefore a real signal, not
    a heuristic -- it just is not UNIQUE on its own (measured: 5209 bytes -> one
    match, 183 bytes -> 91 candidates). So size seeds it and the CALL GRAPH
    disambiguates.

THE ALGORITHM
    seed        functions with the same non-generic NAME in both builds, plus
                any size that is unique to exactly one function in EACH build
    propagate   for every matched pair (s, x): if s calls a function of size N,
                and exactly one unmatched callee of x has size N, and exactly one
                unmatched callee of s has size N, that pair is forced. Same in
                the caller direction. Iterate to a fixed point.
    verify      HOLDOUT: hide half the name matches from the seed, propagate,
                and check how many are recovered and whether they are recovered
                CORRECTLY. That produces a real precision number instead of a
                claim.

USAGE
    python tools/s2_match_builds.py <steam.json> <xbox.json> [--out map.json]
"""

from __future__ import annotations

import argparse
import json
import random
from collections import defaultdict
from pathlib import Path

GENERIC = ("sub_", "loc_", "nullsub_", "j_", "unknown_libname_", "SEH_", "TlsCallback")


def load(path: str) -> dict[int, tuple[int, str, list[int]]]:
    raw = json.loads(Path(path).read_text())
    return {int(k, 16): (v[0], v[1], [int(c) if isinstance(c, int) else c for c in v[2]])
            for k, v in raw.items()}


def real_name(n: str) -> bool:
    return bool(n) and not n.startswith(GENERIC)


class Matcher:
    def __init__(self, s: dict, x: dict):
        self.s, self.x = s, x
        self.s2x: dict[int, int] = {}
        self.x2s: dict[int, int] = {}
        # reverse edges, for caller-direction propagation
        self.s_callers = defaultdict(list)
        self.x_callers = defaultdict(list)
        for a, (_, _, cs) in s.items():
            for c in cs:
                self.s_callers[c].append(a)
        for a, (_, _, cs) in x.items():
            for c in cs:
                self.x_callers[c].append(a)

    def link(self, a: int, b: int) -> bool:
        if a in self.s2x or b in self.x2s:
            return False
        self.s2x[a] = b
        self.x2s[b] = a
        return True

    def seed_names(self, skip: set[str] | None = None) -> int:
        skip = skip or set()
        sn = defaultdict(list)
        xn = defaultdict(list)
        for a, (_, n, _) in self.s.items():
            if real_name(n):
                sn[n].append(a)
        for a, (_, n, _) in self.x.items():
            if real_name(n):
                xn[n].append(a)
        got = 0
        for n, sa in sn.items():
            # unique on BOTH sides, or the name proves nothing
            if n in skip or len(sa) != 1 or len(xn.get(n, [])) != 1:
                continue
            got += self.link(sa[0], xn[n][0])
        return got

    def seed_unique_sizes(self) -> int:
        ss, xs = defaultdict(list), defaultdict(list)
        for a, (sz, _, _) in self.s.items():
            ss[sz].append(a)
        for a, (sz, _, _) in self.x.items():
            xs[sz].append(a)
        got = 0
        for sz, sa in ss.items():
            xa = xs.get(sz, [])
            if len(sa) == 1 and len(xa) == 1:
                got += self.link(sa[0], xa[0])
        return got

    def _step(self, s_adj, x_adj) -> int:
        """One propagation sweep across one edge direction."""
        added = 0
        for sa, xa in list(self.s2x.items()):
            sn = [c for c in s_adj.get(sa, ()) if c not in self.s2x]
            xn = [c for c in x_adj.get(xa, ()) if c not in self.x2s]
            if not sn or not xn:
                continue
            sb, xb = defaultdict(list), defaultdict(list)
            for c in sn:
                sb[self.s[c][0]].append(c)
            for c in xn:
                xb[self.x[c][0]].append(c)
            for sz, group in sb.items():
                other = xb.get(sz, [])
                # forced only when the size is unambiguous on BOTH sides
                if len(group) == 1 and len(other) == 1:
                    added += self.link(group[0], other[0])
        return added

    def propagate(self, verbose: bool = True) -> None:
        s_call = {a: v[2] for a, v in self.s.items()}
        x_call = {a: v[2] for a, v in self.x.items()}
        rnd = 0
        while True:
            rnd += 1
            n = self._step(s_call, x_call) + self._step(self.s_callers, self.x_callers)
            if verbose:
                print(f"    round {rnd:>2}: +{n:<6} total {len(self.s2x)}")
            if n == 0:
                break


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("steam")
    ap.add_argument("xbox")
    ap.add_argument("--out")
    args = ap.parse_args()

    s, x = load(args.steam), load(args.xbox)
    print(f"steam {len(s)} functions   xbox {len(x)} functions\n")

    # ---- HOLDOUT: measure precision before trusting the full run -------------
    shared = {n for a, (_, n, _) in s.items() if real_name(n)} & \
             {n for a, (_, n, _) in x.items() if real_name(n)}
    rnd = random.Random(1234)
    holdout = set(rnd.sample(sorted(shared), max(1, len(shared) // 2)))
    truth = {}
    for a, (_, n, _) in s.items():
        if n in holdout:
            for b, (_, m, _) in x.items():
                if m == n:
                    truth[a] = b
                    break

    print(f"HOLDOUT TEST: hiding {len(holdout)} of {len(shared)} shared names from the seed")
    m = Matcher(s, x)
    print(f"  seed by name       : {m.seed_names(skip=holdout)}")
    print(f"  seed by uniq size  : {m.seed_unique_sizes()}")
    m.propagate()
    ok = bad = miss = 0
    for a, b in truth.items():
        got = m.s2x.get(a)
        if got is None:
            miss += 1
        elif got == b:
            ok += 1
        else:
            bad += 1
    tried = ok + bad
    print(f"  recovered {ok}/{len(truth)} held-out pairs, {bad} WRONG, {miss} not matched")
    if tried:
        print(f"  => precision {100 * ok / tried:.2f}%   recall {100 * ok / len(truth):.1f}%")

    # ---- the real run --------------------------------------------------------
    print("\nFULL RUN (all names seeded):")
    m = Matcher(s, x)
    print(f"  seed by name       : {m.seed_names()}")
    print(f"  seed by uniq size  : {m.seed_unique_sizes()}")
    m.propagate()
    print(f"\n  MATCHED {len(m.s2x)} / {len(s)} steam functions "
          f"({100 * len(m.s2x) / len(s):.1f}%)")

    if args.out:
        Path(args.out).write_text(json.dumps(
            {hex(a): hex(b) for a, b in sorted(m.s2x.items())}, indent=0))
        print(f"  wrote {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
