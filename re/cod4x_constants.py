"""METHOD: constant-set matching. Reaches functions with NO strings.

Anchors and string-sets can only ever touch functions that reference a string
literal - roughly 660 of 8,987 here. Maths, prediction, physics and render code
typically has none, so it is unreachable by any string method no matter how it is
tuned. But it is full of literal constants, and a source literal (0.267, 1.5708,
a magic integer) survives recompilation on any compiler.

Addresses are excluded, because they differ between builds and would be noise.

    python re/cod4x_constants.py [min_shared] [min_score] [margin]
writes re/cod4x_const_proposals.json
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load, clean_ref_name
from mutualbest import match

MIN_SHARED = int(sys.argv[1]) if len(sys.argv) > 1 else 3
MIN_SCORE = float(sys.argv[2]) if len(sys.argv) > 2 else 0.5
MARGIN = float(sys.argv[3]) if len(sys.argv) > 3 else 1.2

ref_c = {int(k, 16): set(v) for k, v in load("cod4_consts.json").items()}
tgt_c = {int(k, 16): set(v) for k, v in load("cod4x_consts.json").items()}
refg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}

# only reference functions with a usable name are worth matching
names = {}
for ea in list(ref_c):
    nm = clean_ref_name(refg.get(ea, [0, "", []])[1], ea)
    if nm:
        names[ea] = nm
    else:
        ref_c.pop(ea, None)

pairs, stats = match(ref_c, tgt_c, MIN_SHARED, MIN_SCORE, MARGIN)

proposals = {}
for t, (r, n, sc) in pairs.items():
    proposals[t] = {"name": names[r], "ref_ea": r, "shared": n,
                    "score": round(sc, 3),
                    "evidence": f"{n} shared literal constants, score {sc:.2f}"}

byname = collections.defaultdict(list)
for t, p in proposals.items():
    byname[p["name"]].append(t)
for nm, ts in byname.items():
    if len(ts) > 1:
        stats["dropped_name_collision"] += len(ts)
        for t in ts:
            proposals.pop(t, None)

print(f"reference funcs with constants+name : {len(ref_c):,}")
print(f"target funcs with constants         : {len(tgt_c):,}")
print(f"MIN_SHARED={MIN_SHARED} MIN_SCORE={MIN_SCORE} MARGIN={MARGIN}")
for k, v in stats.most_common():
    print(f"  {k:26} {v:,}")
print(f"  PROPOSALS                  {len(proposals):,}")

json.dump({str(k): v for k, v in proposals.items()},
          open(os.path.join(RE_DIR, "cod4x_const_proposals.json"), "w",
               encoding="utf-8"))
