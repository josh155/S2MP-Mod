"""Same-game call-graph propagation: MW3-Steam <- MW3-Mac.

Given a partial mapping M: tgt_ea -> ref_ea from the string-anchor pass, an
unmapped target function X is constrained by every mapped neighbour:

    from callees : Y must call M[c] for each mapped callee c of X
                   -> candidates = INTERSECT over c of callers_ref(M[c])
    from callers : Y must be called by M[p] for each mapped caller p of X
                   -> candidates = INTERSECT over p of callees_ref(M[p])

Demanding exactly ONE survivor backed by >= MIN_SUPPORT independent neighbours
is strong evidence, and it uses NO strings - a genuinely second source.

Iterated to a fixed point: each name resolved tightens its neighbours, so
rounds compound WITHOUT loosening the rule.

Function SIZE is deliberately never used as a filter (cross-compiler).

    python re/mw3_propagate.py [min_support]
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mw3_common import RE_DIR, load, clean_ref_name, is_named

MIN_SUPPORT = 2          # independent mapped neighbours required
MAX_ROUNDS = 12


def build(fn):
    g = {int(k, 16): v for k, v in load(fn).items()}
    callees = {ea: set(v[2]) for ea, v in g.items()}
    callers = collections.defaultdict(set)
    for ea, cs in callees.items():
        for c in cs:
            callers[c].add(ea)
    return g, callees, callers


def propagate(seed, verbose=True, min_support=None):
    """seed: {tgt_ea: ref_ea}. Returns (new_rows, mapping)."""
    min_support = MIN_SUPPORT if min_support is None else min_support
    tg, t_callees, t_callers = build("mw3steam_funcs.json")
    rg, r_callees, r_callers = build("mw3_funcs.json")

    M = dict(seed)
    used_ref = set(M.values())

    ref_clean = {}
    for ea, v in rg.items():
        nm = clean_ref_name(v[1], ea)
        if nm:
            ref_clean[ea] = nm
    name_count = collections.Counter(ref_clean.values())

    taken = {v[1] for v in tg.values() if is_named(v[1])}
    taken |= {ref_clean.get(r, "") for r in M.values()}

    new_rows = []
    for rnd in range(1, MAX_ROUNDS + 1):
        proposals = {}
        for X in tg:
            if X in M:
                continue
            cands, support = None, 0
            for c in t_callees.get(X, ()):
                if c in M:
                    s = r_callers.get(M[c], set())
                    cands = set(s) if cands is None else (cands & s)
                    support += 1
            for p in t_callers.get(X, ()):
                if p in M:
                    s = r_callees.get(M[p], set())
                    cands = set(s) if cands is None else (cands & s)
                    support += 1
            if not cands or support < min_support:
                continue
            cands = {y for y in cands if y not in used_ref}
            if len(cands) != 1:
                continue
            Y = cands.pop()
            nm = ref_clean.get(Y)
            if not nm or name_count[nm] != 1 or nm in taken:
                continue
            proposals[X] = (Y, nm, support)

        byname = collections.defaultdict(list)
        for X, (Y, nm, sup) in proposals.items():
            byname[nm].append(X)
        for nm, xs in byname.items():
            if len(xs) > 1:
                for X in xs:
                    proposals.pop(X, None)

        if not proposals:
            if verbose:
                print(f"round {rnd}: converged")
            break

        for X, (Y, nm, sup) in proposals.items():
            M[X] = Y
            used_ref.add(Y)
            taken.add(nm)
            new_rows.append({"tgt": X, "ref": Y, "name": nm, "support": sup,
                             "round": rnd,
                             "tgt_size": tg[X][0], "ref_size": rg[Y][0]})
        if verbose:
            print(f"round {rnd}: +{len(proposals):,}  (mapping now {len(M):,})")

    return new_rows, M


if __name__ == "__main__":
    if len(sys.argv) > 1:
        MIN_SUPPORT = int(sys.argv[1])
    props = load("mw3_proposals.json")
    seed = {int(k): v["ref_ea"] for k, v in props.items() if v.get("ref_ea")}
    print(f"seed from anchors: {len(seed):,}   MIN_SUPPORT={MIN_SUPPORT}")
    rows, M = propagate(seed)
    print(f"\npropagated : {len(rows):,}")
    print(f"total map  : {len(M):,}")
    json.dump(rows, open(os.path.join(RE_DIR, "mw3_propagated.json"),
                         "w", encoding="utf-8"))
    print("\nsample:")
    for r in rows[:20]:
        print(f"  0x{r['tgt']:<8x} {r['name'][:46]:46} sup={r['support']} "
              f"r{r['round']} size {r['tgt_size']}/{r['ref_size']}")
