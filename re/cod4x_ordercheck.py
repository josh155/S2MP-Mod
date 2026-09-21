"""Does ADDRESS ORDER survive between the two builds?

Both binaries are compiled from the same source files, and compilers emit
functions in source order within a translation unit. If that survives, then two
matched functions bracket a RUN of functions that correspond in order - which
would reach the string-less, call-poor functions that block every other method.

This measures it before anything is built on it:
  * sort the trusted pairs by reference address
  * ask how often the target address also increases (local monotonicity)
  * measure the length of runs where it holds continuously

A high local-monotonicity rate means the alignment idea is sound. A rate near
50% would mean the link order is scrambled and the idea is dead.
"""
import collections, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import load, clean_ref_name, is_named

tg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
rg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}

ref_by_name = collections.defaultdict(list)
for ea, v in rg.items():
    nm = clean_ref_name(v[1], ea)
    if nm:
        ref_by_name[nm].append(ea)
ref_uniq = {nm: e[0] for nm, e in ref_by_name.items() if len(e) == 1}
tgt_by_name = collections.defaultdict(list)
for ea, v in tg.items():
    if is_named(v[1]):
        tgt_by_name[v[1]].append(ea)

pairs = [(ref_uniq[nm], e[0]) for nm, e in tgt_by_name.items()
         if len(e) == 1 and nm in ref_uniq]
pairs.sort()
print(f"trusted pairs: {len(pairs):,}\n")

# local monotonicity: consecutive in reference order -> target also increases?
inc = dec = 0
runs, cur = [], 1
for i in range(1, len(pairs)):
    if pairs[i][1] > pairs[i - 1][1]:
        inc += 1
        cur += 1
    else:
        dec += 1
        runs.append(cur)
        cur = 1
runs.append(cur)
tot = inc + dec
print(f"consecutive reference pairs where the target address also INCREASES:")
print(f"  {inc:,} / {tot:,} = {100.0*inc/tot:.1f}%   (50% would mean no signal)")

runs.sort(reverse=True)
print(f"\nmonotone RUN lengths (a run = consecutive pairs preserving order):")
print(f"  runs: {len(runs):,}   longest: {runs[0]}   "
      f"top10: {runs[:10]}")
long_runs = [r for r in runs if r >= 5]
print(f"  runs of >=5: {len(long_runs)}  covering {sum(long_runs):,} pairs "
      f"({100.0*sum(long_runs)/len(pairs):.1f}% of all pairs)")

# how much UNNAMED material sits inside those brackets?
named_t = {ea for ea, v in tg.items() if is_named(v[1])}
t_sorted = sorted(tg)
r_sorted = sorted(rg)
gap_t = gap_r = 0
brackets = 0
for i in range(1, len(pairs)):
    r0, t0 = pairs[i - 1]
    r1, t1 = pairs[i]
    if t1 <= t0:
        continue
    nt = sum(1 for ea in t_sorted if t0 < ea < t1 and ea not in named_t)
    nr = sum(1 for ea in r_sorted if r0 < ea < r1)
    if nt and nr:
        brackets += 1
        gap_t += nt
        gap_r += nr
print(f"\nbrackets (an ordered pair of matched functions with material between):")
print(f"  {brackets:,} brackets   unnamed target funcs inside: {gap_t:,}   "
      f"reference funcs inside: {gap_r:,}")
print(f"  brackets where the counts MATCH exactly: ", end="")
exact = 0
for i in range(1, len(pairs)):
    r0, t0 = pairs[i - 1]
    r1, t1 = pairs[i]
    if t1 <= t0:
        continue
    nt = [ea for ea in t_sorted if t0 < ea < t1]
    nr = [ea for ea in r_sorted if r0 < ea < r1]
    if nt and nr and len(nt) == len(nr):
        exact += 1
print(exact)
