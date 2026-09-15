"""Round 2 propagation: reseed from ALL evidence sources and iterate again.

Propagation compounds - every name resolved tightens the constraints on its
neighbours - so it is worth re-running after any other naming pass. Seeds now:
  * string anchors      (MWR-PS4, ~94% corroborated)
  * round-1 propagation (measured 98.4% precision on a holdout)
  * binding tables      (validated 43/43 against the other two)
"""
import json, os, collections

RE_DIR = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE_DIR, n), encoding="utf-8"))

MIN_SUPPORT = 2
MAX_ROUNDS = 15

pc = {int(k, 16): v for k, v in L("mwrpc_funcs.json").items()}
ps4 = {int(k, 16): v for k, v in L("mwr_funcs.json").items()}
now = {int(k, 16): v for k, v in L("mwrpc_names_now.json").items()}

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
ps4_by_name = {}
for ea, v in ps4.items():
    ps4_by_name.setdefault(v[1], []).append(ea)

# ---- build the seed mapping from every source --------------------------
M = {}
for r in L("mwrpc_corroborated.json"):
    if r["ps4"]:
        M[r["pc"]] = r["ps4"]
for r in L("mwrpc_propagated.json"):
    M[r["pc"]] = r["ps4"]

tbl = L("mwrpc_table_names.json")
ps4_tables = L("ps4_tables.json")
name2ea = {}
for t in ps4_tables:
    for bind, fh, nm in t["pairs"]:
        if nm and not nm.startswith("sub_"):
            name2ea.setdefault(nm, int(fh, 16))
for k, r in tbl.items():
    ea = int(k)
    y = name2ea.get(r["name"])
    if y is not None:
        M[ea] = y

seed_n = len(M)
used = set(M.values())
taken = set(now.values())

new_rows = []
for rnd in range(1, MAX_ROUNDS + 1):
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
        if not cands or support < MIN_SUPPORT:
            continue
        cands = {y for y in cands if y not in used}
        if len(cands) != 1:
            continue
        Y = cands.pop()
        nm = ps4[Y][1]
        if ps4_name_count[nm] != 1 or nm in taken:
            continue
        if nm.startswith("sub_") or nm.startswith("nullsub_"):
            continue
        prop[X] = (Y, nm, support)

    byname = collections.defaultdict(list)
    for X, (Y, nm, s) in prop.items():
        byname[nm].append(X)
    for nm, xs in byname.items():
        if len(xs) > 1:
            for X in xs:
                prop.pop(X, None)

    if not prop:
        print(f"round {rnd}: converged")
        break
    for X, (Y, nm, s) in prop.items():
        M[X] = Y; used.add(Y); taken.add(nm)
        new_rows.append({"pc": X, "ps4": Y, "name": nm, "support": s,
                         "round": rnd, "pc_size": pc[X][0], "ps4_size": ps4[Y][0]})
    print(f"round {rnd}: +{len(prop):,}  (mapping {len(M):,})")

print(f"\nseeds (all sources) : {seed_n:,}")
print(f"NEW this round      : {len(new_rows):,}")
print(f"total mapping       : {len(M):,}")
json.dump(new_rows, open(os.path.join(RE_DIR, "mwrpc_propagated2.json"),
                         "w", encoding="utf-8"))
print("\nsample:")
for r in new_rows[:14]:
    print(f"  0x{r['pc']:<8x} {r['name'][:54]:54} sup={r['support']} r{r['round']}")
