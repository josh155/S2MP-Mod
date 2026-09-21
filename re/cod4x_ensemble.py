"""METHOD: ENSEMBLE AGREEMENT - accept only where two methods independently agree.

Constraint deduction on ambiguous anchors measures 96.47%, below the ~98% bar the
other applied methods cleared, and tightening its own guards did not help (the
three errors survive every tightening and even gain witnesses, so they are
systematically wrong rather than thinly supported).

So instead of loosening the bar, require CORROBORATION: a deduced pair is applied
only when the graph's weighted vote independently ranks the SAME reference
function top for that target. Two methods that share no evidence - one uses string
ownership, the other call-graph topology - agreeing on the same answer is a
stronger tier than either alone.

Cross-validated the same way: hide known names, rebuild, and see what survives.

    python re/cod4x_ensemble.py [--crossval]
writes re/cod4x_ensemble_proposals.json
"""
import json, os, sys, collections, random
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load, clean_ref_name, is_named
import cod4x_ambiguous as AMB
import cod4x_vote as VOTE

CROSSVAL = "--crossval" in sys.argv


def vote_top(M):
    """Top graph-vote candidate per target, with NO dominance requirement.

    Used purely as a second opinion, so it is deliberately permissive - the
    agreement itself is the filter.
    """
    g = VOTE.graphs()
    used = set(M.values())
    top = {}
    for X in g["tg"]:
        if X in M:
            continue
        votes, support = collections.Counter(), 0
        for c in g["t_callees"].get(X, ()):
            if c in M:
                fam = g["r_callers"].get(M[c], set())
                if len(fam) > 60:
                    continue
                support += 1
                for y in fam:
                    votes[y] += VOTE.w(len(fam))
        for p in g["t_callers"].get(X, ()):
            if p in M:
                fam = g["r_callees"].get(M[p], set())
                if len(fam) > 60:
                    continue
                support += 1
                for y in fam:
                    votes[y] += VOTE.w(len(fam))
        if not votes:
            continue
        ranked = [(y, s) for y, s in votes.most_common() if y not in used]
        if ranked:
            top[X] = ranked[0][0]
    return top


def ensemble(M):
    amb, _ = AMB.deduce(M)
    top = vote_top(M)
    out = {}
    for t, p in amb.items():
        if top.get(t) == p["ref_ea"]:
            q = dict(p)
            q["evidence"] = (p["evidence"] +
                             "; INDEPENDENTLY CORROBORATED - the call-graph "
                             "weighted vote ranks the same reference function "
                             "top for this target")
            out[t] = q
    return out, len(amb), len(top)


if CROSSVAL:
    tg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
    truth = {ea: v[1] for ea, v in tg.items() if is_named(v[1])}
    keys = sorted(truth)
    random.Random(23).shuffle(keys)
    rec = ok = bad = 0
    wrong = []
    for i in range(5):
        hide = set(keys[i::5])
        M = AMB.build_M(exclude=hide)
        props, na, nv = ensemble(M)
        for h in hide:
            if h in props:
                rec += 1
                if props[h]["name"] == truth[h]:
                    ok += 1
                else:
                    bad += 1
                    wrong.append((h, truth[h], props[h]["name"]))
    print(f"ENSEMBLE crossval, 5 folds over {len(keys)} known names:")
    print(f"  recovered {rec}  correct {ok}  wrong {bad}  "
          f"PRECISION {100.0*ok/rec if rec else 0:.2f}%")
    for h, t, p in wrong[:8]:
        print(f"    0x{h:<8x} truth={t!r} ensemble={p!r}")
    sys.exit(0)

M = AMB.build_M()
props, na, nv = ensemble(M)
print(f"trusted mapping      {len(M):,}")
print(f"ambiguous deductions {na:,}")
print(f"graph top candidates {nv:,}")
print(f"BOTH AGREE           {len(props):,}")
json.dump({str(k): v for k, v in props.items()},
          open(os.path.join(RE_DIR, "cod4x_ensemble_proposals.json"), "w",
               encoding="utf-8"))
for t, p in list(props.items())[:15]:
    print(f"  0x{t:<8x} {p['name'][:44]}")
