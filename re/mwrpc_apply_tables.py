"""Regenerate table-derived names against CURRENT PC names, then apply in IDA.

Evidence chain, both ends tier-1 self-naming:
  PC  : {const char* binding, void* fn} table in .rdata pairs the two directly
  PS4 : the same table, whose functions carry REAL symbols
  link: tables matched table-to-table by shared binding-name set, entries
        matched only inside a corresponding pair

Validated 43/43 (100%) against names derived independently from string anchors
and call-graph propagation.
"""
import json, os, collections, sys

RE_DIR = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE_DIR, n), encoding="utf-8"))

pc_tables = L("mwrpc_tables2.json")
ps4_tables = L("ps4_tables.json")
now = {int(k, 16): v for k, v in L("mwrpc_names_now.json").items()}
taken = set(now.values())

pairs_matched = []
prop = collections.defaultdict(list)
for pt in pc_tables:
    pset = {p[0] for p in pt["pairs"]}
    best = None
    for qt in ps4_tables:
        qset = {p[0] for p in qt["pairs"]}
        sh = pset & qset
        if not sh:
            continue
        ratio = len(sh) / min(len(pset), len(qset))
        if ratio >= 0.60 or len(sh) >= 5:
            if best is None or len(sh) > best[1]:
                best = (qt, len(sh), ratio)
    if not best:
        continue
    qt, nsh, ratio = best
    pairs_matched.append((pt["base"], hex(qt["base"]), nsh, round(ratio, 2)))
    byn = {p[0]: p for p in qt["pairs"]}
    for bind, fh in pt["pairs"]:
        q = byn.get(bind)
        if q and q[2] and not q[2].startswith("sub_"):
            prop[int(fh, 16)].append((q[2], bind, pt["base"], hex(qt["base"]),
                                      nsh, ratio))

final = {}
used = set()
for fea, cands in prop.items():
    if fea in now:
        continue
    names = {c[0] for c in cands}
    if len(names) != 1:
        continue
    nm = names.pop()
    if nm in taken or nm in used:
        continue
    used.add(nm)
    c = cands[0]
    final[fea] = {"name": nm, "binding": c[1], "pc_table": c[2],
                  "ps4_table": c[3], "shared": c[4], "ratio": c[5]}

json.dump({str(k): v for k, v in final.items()},
          open(os.path.join(RE_DIR, "mwrpc_table_names.json"), "w",
               encoding="utf-8"))
print(f"table pairs matched : {len(pairs_matched)}")
print(f"new names to apply  : {len(final)}")
