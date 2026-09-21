"""Same-game call-graph propagation: MWR-PC <- MWR-PS4.

We hold a partial mapping M: pc_ea -> ps4_ea from the string-anchor pass. For an
unmapped PC function X, every mapped NEIGHBOUR constrains what X can be:

    from callees : Y must call M[c] for each mapped callee c of X
                   -> candidates = INTERSECT over c of callers_ps4(M[c])
    from callers : Y must be called by M[p] for each mapped caller p of X
                   -> candidates = INTERSECT over p of callees_ps4(M[p])

Intersecting both and demanding exactly ONE survivor, backed by >= MIN_SUPPORT
independent neighbours, is strong evidence - and it uses no strings at all.

Iterated to a fixed point: every name resolved tightens its neighbours, so
rounds compound WITHOUT loosening the rule.
"""
import json, os, collections

RE_DIR = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE_DIR, n), encoding="utf-8"))

MIN_SUPPORT = 2          # independent mapped neighbours required
MAX_ROUNDS = 12

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

# seed mapping from the anchor pass
M = {}
for r in L("mwrpc_corroborated.json"):
    if r["ps4"]:
        M[r["pc"]] = r["ps4"]
seed_n = len(M)

# names already worn in PC (never reuse), and PS4 names claimed
pc_names = {ea: v[1] for ea, v in pc.items()}
taken = {n for n in pc_names.values()
         if not (n.startswith("sub_") or n.startswith("nullsub_") or n.startswith("j_"))}
used_ps4 = set(M.values())

# PS4 names that are unique (a duplicated name cannot identify anything)
ps4_name_count = collections.Counter(v[1] for v in ps4.values())

new_rows = []
for rnd in range(1, MAX_ROUNDS + 1):
    proposals = {}
    for X in pc:
        if X in M:
            continue
        cands = None
        support = 0
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
        if not cands or support < MIN_SUPPORT:
            continue
        cands = {y for y in cands if y not in used_ps4}
        if len(cands) != 1:
            continue
        Y = cands.pop()
        nm = ps4[Y][1]
        if ps4_name_count[nm] != 1 or nm in taken:
            continue
        if nm.startswith("sub_") or nm.startswith("nullsub_"):
            continue
        proposals[X] = (Y, nm, support)

    # one name, one function
    byname = collections.defaultdict(list)
    for X, (Y, nm, sup) in proposals.items():
        byname[nm].append(X)
    for nm, xs in byname.items():
        if len(xs) > 1:
            for X in xs:
                proposals.pop(X, None)

    if not proposals:
        print(f"round {rnd}: converged")
        break

    for X, (Y, nm, sup) in proposals.items():
        M[X] = Y
        used_ps4.add(Y)
        taken.add(nm)
        pcsz, ps4sz = pc[X][0], ps4[Y][0]
        ratio = max(pcsz, ps4sz) / max(1, min(pcsz, ps4sz))
        new_rows.append({"pc": X, "ps4": Y, "name": nm, "support": sup,
                         "round": rnd, "pc_size": pcsz, "ps4_size": ps4sz,
                         "size_ratio": round(ratio, 2)})
    print(f"round {rnd}: +{len(proposals):,}  (mapping now {len(M):,})")

print(f"\nseeded from anchors : {seed_n:,}")
print(f"propagated          : {len(new_rows):,}")
print(f"total mapping       : {len(M):,}")

sane = [r for r in new_rows if r["size_ratio"] <= 3.0]
print(f"size ratio <= 3.0   : {len(sane):,}  ({100.0*len(sane)/max(1,len(new_rows)):.1f}%)")

json.dump(new_rows, open(os.path.join(RE_DIR, "mwrpc_propagated.json"),
                         "w", encoding="utf-8"))

print("\nsample:")
for r in new_rows[:15]:
    print(f"  0x{r['pc']:<8x} {r['name'][:50]:50} sup={r['support']} "
          f"r{r['round']} size {r['pc_size']}/{r['ps4_size']}")
