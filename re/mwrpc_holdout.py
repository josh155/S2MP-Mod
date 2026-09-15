"""Measure propagation precision by hiding known-good pairs.

The anchor pass produced 727 (pc -> ps4) pairs validated independently at ~94%.
Hide a random slice of them, propagate from the rest, and check whether
propagation rediscovers the hidden pairs correctly. That is a real precision
number, not an assertion.
"""
import json, os, random, collections

RE_DIR = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE_DIR, n), encoding="utf-8"))

pc = {int(k, 16): v for k, v in L("mwrpc_funcs.json").items()}
ps4 = {int(k, 16): v for k, v in L("mwr_funcs.json").items()}

pc_callees = {ea: set(v[2]) for ea, v in pc.items()}
pc_callers = collections.defaultdict(set)
for ea, cs in pc_callees.items():
    for c in cs:
        pc_callers[c].add(ea)
ps4_callees = {ea: set(v[2]) for ea, v in ps4.items()}
ps4_callers = collections.defaultdict(set)
for ea, cs in ps4_callees.items():
    for c in cs:
        ps4_callers[c].add(ea)

ps4_name_count = collections.Counter(v[1] for v in ps4.values())
seeds = {r["pc"]: r["ps4"] for r in L("mwrpc_corroborated.json") if r["ps4"]}


def propagate(M0, min_support, rounds=12, size_gate=None):
    M = dict(M0)
    used = set(M.values())
    got = {}
    for _ in range(rounds):
        prop = {}
        for X in pc:
            if X in M:
                continue
            cands, support = None, 0
            for c in pc_callees.get(X, ()):
                if c in M:
                    s = ps4_callers.get(M[c], set())
                    cands = s.copy() if cands is None else (cands & s)
                    support += 1
            for p in pc_callers.get(X, ()):
                if p in M:
                    s = ps4_callees.get(M[p], set())
                    cands = s.copy() if cands is None else (cands & s)
                    support += 1
            if not cands or support < min_support:
                continue
            cands = {y for y in cands if y not in used}
            if len(cands) != 1:
                continue
            Y = cands.pop()
            if ps4_name_count[ps4[Y][1]] != 1:
                continue
            if size_gate is not None:
                a, b = pc[X][0], ps4[Y][0]
                if max(a, b) / max(1, min(a, b)) > size_gate:
                    continue
            prop[X] = Y
        byname = collections.defaultdict(list)
        for X, Y in prop.items():
            byname[ps4[Y][1]].append(X)
        for nm, xs in byname.items():
            if len(xs) > 1:
                for X in xs:
                    prop.pop(X, None)
        if not prop:
            break
        for X, Y in prop.items():
            M[X] = Y; used.add(Y); got[X] = Y
    return got


random.seed(1234)
keys = sorted(seeds)
print(f"{'min_sup':>7} {'size_gate':>9} {'recovered':>10} {'correct':>8} {'wrong':>6}  precision  recall")
for min_support in (2, 3):
    for gate in (None, 3.0):
        tot_rec = tot_ok = tot_bad = tot_hidden = 0
        for trial in range(5):
            random.shuffle(keys)
            n = len(keys) // 5
            hidden = set(keys[:n])
            M0 = {k: v for k, v in seeds.items() if k not in hidden}
            got = propagate(M0, min_support, size_gate=gate)
            rec = {k: v for k, v in got.items() if k in hidden}
            ok = sum(1 for k, v in rec.items() if v == seeds[k])
            tot_rec += len(rec); tot_ok += ok; tot_bad += len(rec) - ok
            tot_hidden += len(hidden)
        prec = 100.0 * tot_ok / tot_rec if tot_rec else 0.0
        rcl = 100.0 * tot_rec / tot_hidden if tot_hidden else 0.0
        g = "none" if gate is None else f"{gate}"
        print(f"{min_support:>7} {g:>9} {tot_rec:>10,} {tot_ok:>8,} {tot_bad:>6,}"
              f"  {prec:8.2f}%  {rcl:5.1f}%")
