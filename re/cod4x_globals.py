"""METHOD: global/data cross-reference matching. A third, independent dimension.

Two stages, and the first is worth as much as the second:

  STAGE 1 - MAP THE GLOBALS. For every function pair we already trust, the
  globals the two functions touch must correspond. Vote over (target_global,
  reference_global) across all matched pairs: a real pair like `cg` co-occurs in
  dozens of matched functions, a coincidental pair co-occurs once. Keep
  mutually-best pairs with >= MIN_SUPPORT independent matched functions behind
  them.

  STAGE 2 - USE THEM. Translate each unnamed target function's global set through
  that mapping and mutual-best it against reference functions' global sets. This
  reaches functions with no strings and no distinctive calls, which is the
  population that blocks everything else (7,567 functions had too few mapped
  neighbours for the graph methods).

Stage 2's precision is measurable with the usual harness, and that measurement
VALIDATES STAGE 1 INDIRECTLY: if a global mapping built this way reproduces
hundreds of independently-established function names, the global mapping is sound.

    python re/cod4x_globals.py [min_support] [min_shared] [margin]
writes re/cod4x_global_map.json and re/cod4x_globals_proposals.json
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load, clean_ref_name, is_named
from mutualbest import match

MIN_SUPPORT = int(sys.argv[1]) if len(sys.argv) > 1 else 3
MIN_SHARED = int(sys.argv[2]) if len(sys.argv) > 2 else 3
MARGIN = float(sys.argv[3]) if len(sys.argv) > 3 else 1.3

tg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
rg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}
t_dref = {int(k, 16): set(v) for k, v in load("cod4x_drefs.json").items()}
r_dref = {int(k, 16): set(v) for k, v in load("cod4_drefs.json").items()}

ref_clean = {}
for ea, v in rg.items():
    nm = clean_ref_name(v[1], ea)
    if nm:
        ref_clean[ea] = nm

# ---- the trusted function mapping, from names agreeing on both sides -----
ref_by_name = collections.defaultdict(list)
for ea, nm in ref_clean.items():
    ref_by_name[nm].append(ea)
ref_uniq = {nm: e[0] for nm, e in ref_by_name.items() if len(e) == 1}
tgt_by_name = collections.defaultdict(list)
for ea, v in tg.items():
    if is_named(v[1]):
        tgt_by_name[v[1]].append(ea)
M = {e[0]: ref_uniq[nm] for nm, e in tgt_by_name.items()
     if len(e) == 1 and nm in ref_uniq}
print(f"trusted function pairs: {len(M):,}")

# ---- STAGE 1: vote global <-> global over those pairs --------------------
votes = collections.defaultdict(collections.Counter)   # tgt_g -> Counter(ref_g)
pair_support = collections.defaultdict(set)            # (tg,rg) -> {func pairs}
for t, r in M.items():
    Gt, Gr = t_dref.get(t), r_dref.get(r)
    if not Gt or not Gr:
        continue
    # a function touching a huge number of globals gives a noisy ballot
    if len(Gt) > 40 or len(Gr) > 40:
        continue
    for gt in Gt:
        for gr in Gr:
            votes[gt][gr] += 1
            pair_support[(gt, gr)].add(t)

gmap, gstats = {}, collections.Counter()
best_rev = collections.defaultdict(list)
for gt, cnt in votes.items():
    for gr, n in cnt.items():
        best_rev[gr].append((gt, n))
for gr in best_rev:
    best_rev[gr].sort(key=lambda x: -x[1])

for gt, cnt in votes.items():
    ranked = cnt.most_common()
    gr, n = ranked[0]
    runner = ranked[1][1] if len(ranked) > 1 else 0
    if n < MIN_SUPPORT:
        gstats["below_support"] += 1; continue
    if runner and n < runner * MARGIN:
        gstats["no_margin"] += 1; continue
    if best_rev[gr][0][0] != gt:
        gstats["not_mutual_best"] += 1; continue
    gmap[gt] = {"ref": gr, "support": n,
                "via": sorted(pair_support[(gt, gr)])[:5]}

print(f"global candidates      : {len(votes):,}")
for k, v in gstats.most_common():
    print(f"  {k:20} {v:,}")
print(f"GLOBAL MAPPING         : {len(gmap):,}")
json.dump({str(k): v for k, v in gmap.items()},
          open(os.path.join(RE_DIR, "cod4x_global_map.json"), "w",
               encoding="utf-8"))

# ---- STAGE 2: match functions by translated global sets ------------------
G = {k: v["ref"] for k, v in gmap.items()}
tgt_feats = {}
for ea, gs in t_dref.items():
    f = {G[g] for g in gs if g in G}
    if f:
        tgt_feats[ea] = f
ref_feats = {ea: set(gs) for ea, gs in r_dref.items() if ea in ref_clean}

pairs, stats = match(ref_feats, tgt_feats, MIN_SHARED, 0.5, MARGIN,
                     max_owners=12)
proposals = {}
for t, (r, n, sc) in pairs.items():
    proposals[t] = {"name": ref_clean[r], "ref_ea": r,
                    "evidence": f"{n} shared globals (via the derived global "
                                f"mapping), score {sc:.2f}"}
byname = collections.defaultdict(list)
for t, p in proposals.items():
    byname[p["name"]].append(t)
for nm, ts in byname.items():
    if len(ts) > 1:
        for t in ts:
            proposals.pop(t, None)

print(f"\nstage-2 feature funcs  : target {len(tgt_feats):,} "
      f"reference {len(ref_feats):,}")
for k, v in stats.most_common():
    print(f"  {k:20} {v:,}")
print(f"PROPOSALS              : {len(proposals):,}")
json.dump({str(k): v for k, v in proposals.items()},
          open(os.path.join(RE_DIR, "cod4x_globals_proposals.json"), "w",
               encoding="utf-8"))
