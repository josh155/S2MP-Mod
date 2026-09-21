"""MEASURE call-graph propagation precision on CoD4X, by hiding known pairs.

The anchor pass gives pairs we believe. Hide a random slice of them, propagate
from the rest using ONLY the call graph, and check whether propagation
rediscovers the hidden pairs and agrees on the name.

    recovered = hidden pairs propagation produced an answer for
    correct   = ...and the answer matched the anchor-derived name

This is the only honest way to quote a precision figure, and it also cross-
validates the anchor pass itself: two independent methods agreeing on the same
pair is far stronger than either alone.

    python re/cod4x_holdout.py [frac] [trials]
"""
import os, sys, random, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import load
from cod4x_propagate import propagate

FRAC = float(sys.argv[1]) if len(sys.argv) > 1 else 0.20
TRIALS = int(sys.argv[2]) if len(sys.argv) > 2 else 5

props = load("cod4x_proposals.json")
pairs = {int(k): (v["ref_ea"], v["name"]) for k, v in props.items()
         if v.get("ref_ea")}
print(f"anchor pairs available: {len(pairs):,}   hiding {FRAC:.0%}, "
      f"{TRIALS} trials\n")

for ms in (2, 3):
    tot_rec = tot_ok = tot_bad = tot_hidden = 0
    bad_examples = []
    for t in range(TRIALS):
        rnd = random.Random(1000 + t)
        keys = sorted(pairs)
        hide = set(rnd.sample(keys, int(len(keys) * FRAC)))
        seed = {k: pairs[k][0] for k in keys if k not in hide}

        rows, _ = propagate(seed, verbose=False, min_support=ms)

        got = {r["tgt"]: r["name"] for r in rows}
        rec = ok = bad = 0
        for k in hide:
            if k in got:
                rec += 1
                if got[k] == pairs[k][1]:
                    ok += 1
                else:
                    bad += 1
                    if len(bad_examples) < 12:
                        bad_examples.append((k, pairs[k][1], got[k]))
        tot_rec += rec; tot_ok += ok; tot_bad += bad; tot_hidden += len(hide)

    prec = 100.0 * tot_ok / tot_rec if tot_rec else 0.0
    rcl = 100.0 * tot_rec / tot_hidden if tot_hidden else 0.0
    print(f"MIN_SUPPORT={ms}: hidden {tot_hidden}  recovered {tot_rec}  "
          f"correct {tot_ok}  wrong {tot_bad}   "
          f"precision {prec:.2f}%   recall {rcl:.1f}%")
    if bad_examples:
        print("   disagreements (anchor name vs propagated name):")
        for k, a, b in bad_examples[:8]:
            print(f"     0x{k:<8x} anchor={a!r}  prop={b!r}")
    print()
