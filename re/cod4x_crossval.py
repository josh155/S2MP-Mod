"""K-fold cross-validation of the anchor pass against call-graph propagation.

Every anchor pair is hidden exactly once per repeat, so this both measures
precision AND finds disagreements between two independent methods (strings vs
graph topology). Disagreements are Contradictions: per the skill they are
dropped, not adjudicated.

Contradiction detection is SEED-DEPENDENT - whether propagation can answer for a
hidden pair depends on which of its neighbours are also hidden. So several
independent shuffles are run and the contradictions are UNIONed.

Writes re/cod4x_contradictions.json (target eas to exclude from the apply).

    python re/cod4x_crossval.py [folds] [repeats]
"""
import json, os, sys, random
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load
from cod4x_propagate import propagate

FOLDS = int(sys.argv[1]) if len(sys.argv) > 1 else 5
REPEATS = int(sys.argv[2]) if len(sys.argv) > 2 else 4

props = load("cod4x_proposals.json")
pairs = {int(k): (v["ref_ea"], v["name"]) for k, v in props.items()
         if v.get("ref_ea")}
tier_of = {int(k): v["tier"] for k, v in props.items()}
allkeys = sorted(pairs)

all_contra = {}
for ms in (2, 3):
    rec = ok = bad = 0
    contra = {}
    checked = set()
    import collections as _c
    per_tier = _c.defaultdict(lambda: [0, 0])   # tier -> [answers, correct]
    for rep in range(REPEATS):
        keys = list(allkeys)
        random.Random(7 + rep * 101).shuffle(keys)
        for i in range(FOLDS):
            hide = set(keys[i::FOLDS])
            seed = {k: pairs[k][0] for k in allkeys if k not in hide}
            rows, _ = propagate(seed, verbose=False, min_support=ms)
            got = {r["tgt"]: r["name"] for r in rows}
            for k in hide:
                if k in got:
                    rec += 1
                    checked.add(k)
                    t = tier_of.get(k, "?")
                    per_tier[t][0] += 1
                    if got[k] == pairs[k][1]:
                        ok += 1
                        per_tier[t][1] += 1
                    else:
                        bad += 1
                        contra[k] = {"tgt": k, "anchor": pairs[k][1],
                                     "propagated": got[k]}
    prec = 100.0 * ok / rec if rec else 0.0
    print(f"MIN_SUPPORT={ms}: {REPEATS} repeats x {FOLDS} folds over "
          f"{len(allkeys)} pairs")
    print(f"  answers {rec}  correct {ok}  wrong {bad}  precision {prec:.2f}%")
    print(f"  distinct pairs independently checked: {len(checked)} "
          f"({100.0*len(checked)/len(allkeys):.1f}% of the anchor set)")
    print("  precision BY ANCHOR TIER (answers / correct):")
    for t in ("multi", "dominant", "single_strong", "single_weak"):
        a, c = per_tier.get(t, [0, 0])
        if a:
            print(f"     {t:14} {c:4}/{a:<4} = {100.0*c/a:6.2f}%")
        else:
            print(f"     {t:14}    -/-    (no independent answers)")
    print(f"  CONTRADICTIONS (union over repeats): {len(contra)}")
    for d in contra.values():
        print(f"    0x{d['tgt']:x}: anchor={d['anchor']!r} "
              f"prop={d['propagated']!r}")
    for k, v in contra.items():
        all_contra.setdefault(k, v)
    print()

# Union across BOTH support levels: a contradiction found at either level is a
# contradiction. Excluding it costs one name; keeping a wrong one costs trust.
json.dump(sorted(all_contra.values(), key=lambda d: d["tgt"]),
          open(os.path.join(RE_DIR, "cod4x_contradictions.json"),
               "w", encoding="utf-8"))
print(f"TOTAL contradictions to exclude from the apply: {len(all_contra)}")
