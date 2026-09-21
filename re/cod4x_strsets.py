"""METHOD: string-SET similarity with mutual-best matching.

The anchor method needs a string owned by exactly ONE function on BOTH sides. That
throws away 648 strings with 2+ reference owners and 44 with 2+ target owners, and
worse, it cannot use a function whose strings are each shared by a few functions
even when the SET is unmistakable.

Here the unit of evidence is the whole string set of a function:

    score(R, T) = |strings(R) & strings(T)| / min(|strings(R)|, |strings(T)|)

A pair is accepted only when it is MUTUALLY BEST - R's best target is T and T's
best reference is R - with a minimum overlap count and a clear margin over each
side's runner-up. Mutual-best plus a margin is what stops a big dispatcher
absorbing every small function that shares one of its strings.

    python re/cod4x_strsets.py [min_shared] [min_score] [margin]
writes re/cod4x_strset_proposals.json
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load, clean_ref_name, is_named

MIN_SHARED = int(sys.argv[1]) if len(sys.argv) > 1 else 2
MIN_SCORE = float(sys.argv[2]) if len(sys.argv) > 2 else 0.50
MARGIN = float(sys.argv[3]) if len(sys.argv) > 3 else 1.5   # best/runner-up

ref = load("cod4_strowners.json")
tgt = load("cod4x_strowners.json")
ref_names = {int(k): v for k, v in ref["names"].items()}
tgt_names = {int(k): v for k, v in tgt["names"].items()}

# ---- invert: function -> set of strings ----------------------------------
ref_strs = collections.defaultdict(set)
for s, owners in ref["owners"].items():
    for o in owners:
        ref_strs[o].add(s)
tgt_strs = collections.defaultdict(set)
for s, owners in tgt["owners"].items():
    for o in owners:
        tgt_strs[o].add(s)

# only reference functions with a usable name are worth matching
ref_ok = {ea: clean_ref_name(ref_names.get(ea, ""), ea) for ea in ref_strs}
ref_ok = {ea: nm for ea, nm in ref_ok.items() if nm}

# ---- co-occurrence counts, driven by shared strings ---------------------
shared = collections.defaultdict(collections.Counter)   # ref_ea -> Counter(tgt_ea)
for s, r_owners in ref["owners"].items():
    t_owners = tgt["owners"].get(s)
    if not t_owners:
        continue
    # a string owned by very many functions on either side carries no signal
    if len(r_owners) > 8 or len(t_owners) > 8:
        continue
    for r in r_owners:
        if r not in ref_ok:
            continue
        for t in t_owners:
            shared[r][t] += 1

def score(r, t, n):
    denom = min(len(ref_strs[r]), len(tgt_strs[t])) or 1
    return n / denom

# ---- best target per reference, and vice versa --------------------------
best_t = {}       # ref_ea -> (tgt_ea, score, n, runner_score)
for r, cnt in shared.items():
    ranked = sorted(((t, n, score(r, t, n)) for t, n in cnt.items()),
                    key=lambda x: (-x[2], -x[1]))
    if not ranked:
        continue
    t, n, sc = ranked[0]
    runner = ranked[1][2] if len(ranked) > 1 else 0.0
    best_t[r] = (t, sc, n, runner)

best_r = collections.defaultdict(list)   # tgt_ea -> [(ref_ea, score, n)]
for r, cnt in shared.items():
    for t, n in cnt.items():
        best_r[t].append((r, score(r, t, n), n))
for t in best_r:
    best_r[t].sort(key=lambda x: (-x[1], -x[2]))

proposals, stats = {}, collections.Counter()
for r, (t, sc, n, runner) in best_t.items():
    stats["candidate_pairs"] += 1
    if n < MIN_SHARED:
        stats["too_few_shared"] += 1
        continue
    if sc < MIN_SCORE:
        stats["score_too_low"] += 1
        continue
    if runner and sc < runner * MARGIN:
        stats["no_margin_ref_side"] += 1
        continue
    # mutual best: t's best reference must be r, with its own margin
    tr = best_r[t]
    if tr[0][0] != r:
        stats["not_mutual_best"] += 1
        continue
    if len(tr) > 1 and tr[1][1] and tr[0][1] < tr[1][1] * MARGIN:
        stats["no_margin_tgt_side"] += 1
        continue
    proposals[t] = {"name": ref_ok[r], "ref_ea": r, "shared": n,
                    "score": round(sc, 3),
                    "evidence": f"{n} shared strings, score {sc:.2f}"}

# one name, one function
byname = collections.defaultdict(list)
for t, p in proposals.items():
    byname[p["name"]].append(t)
for nm, ts in byname.items():
    if len(ts) > 1:
        stats["dropped_name_collision"] += len(ts)
        for t in ts:
            proposals.pop(t, None)

print(f"MIN_SHARED={MIN_SHARED} MIN_SCORE={MIN_SCORE} MARGIN={MARGIN}")
for k, v in stats.most_common():
    print(f"  {k:26} {v:,}")
print(f"  PROPOSALS                  {len(proposals):,}")

json.dump({str(k): v for k, v in proposals.items()},
          open(os.path.join(RE_DIR, "cod4x_strset_proposals.json"), "w",
               encoding="utf-8"))
