"""Explain why a specific reference function did or did not get mapped.

Targeted diagnostic for the high-value functions propagation could not resolve
(registrars, dispatchers). Reports the candidate set rather than a verdict, so an
ambiguous answer is visible instead of being silently dropped.

    python re/cod4x_explain.py Cmd_AddCommand Dvar_RegisterBool
"""
import os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import load, clean_ref_name, is_named

ref = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}
tgt = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}

ref_clean = {ea: clean_ref_name(v[1], ea) for ea, v in ref.items()}
ref_by_name = collections.defaultdict(list)
for ea, nm in ref_clean.items():
    if nm:
        ref_by_name[nm].append(ea)

r_callees = {ea: set(v[2]) for ea, v in ref.items()}
r_callers = collections.defaultdict(set)
for ea, cs in r_callees.items():
    for c in cs:
        r_callers[c].add(ea)

t_callees = {ea: set(v[2]) for ea, v in tgt.items()}
t_callers = collections.defaultdict(set)
for ea, cs in t_callees.items():
    for c in cs:
        t_callers[c].add(ea)

# name -> target ea (unique names only)
tgt_by_name = collections.defaultdict(list)
for ea, v in tgt.items():
    if is_named(v[1]):
        tgt_by_name[v[1]].append(ea)
tgt_uniq = {n: e[0] for n, e in tgt_by_name.items() if len(e) == 1}

for want in sys.argv[1:]:
    print(f"\n================ {want} ================")
    eas = ref_by_name.get(want)
    if not eas:
        near = sorted(n for n in ref_by_name if want.lower() in n.lower())[:12]
        print(f"  not a unique cleaned reference name. near matches: {near}")
        continue
    if len(eas) > 1:
        print(f"  AMBIGUOUS in the reference: {[hex(e) for e in eas]}")
    R = eas[0]
    print(f"  reference {want} @ 0x{R:x}  ({ref[R][1]})")
    if tgt_by_name.get(want):
        print(f"  already named in target: "
              f"{[hex(e) for e in tgt_by_name[want]]}")

    rc = r_callers.get(R, set())
    print(f"  reference callers: {len(rc)}")
    mapped, cand_counts = 0, collections.Counter()
    for p in rc:
        nm = ref_clean.get(p)
        if not nm or nm not in tgt_uniq:
            continue
        mapped += 1
        for c in t_callees.get(tgt_uniq[nm], ()):
            cand_counts[c] += 1
    print(f"  of those, mapped into the target: {mapped}")
    if not cand_counts:
        print("  no mapped callers -> unreachable by caller intersection")
        continue
    print("  candidate callees, by how many mapped callers call them:")
    for c, n in cand_counts.most_common(8):
        cur = tgt[c][1] if c in tgt else "?"
        flag = "  <-- unnamed" if not is_named(cur) else ""
        print(f"     0x{c:<8x} votes={n:<3} size={tgt.get(c,[0])[0]:<6} "
              f"{cur[:40]}{flag}")
