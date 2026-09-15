"""Run CoD4X <- CoD4-Mac propagation to a fixed point, reseeding each round.

The anchor pass seeds a mapping, propagation extends it, and every name that
lands makes the mapping denser - which lets propagation resolve neighbours it
could not before. So: refresh names from the IDB, rebuild the mapping from ALL
names that are unique on both sides (not just anchor-derived ones), propagate,
apply, repeat.

This is why the method compounds: each pass strictly increases the seed without
loosening any rule.

    python re/cod4x_nameloop.py [rounds] [--dry]
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from cod4x_common import RE_DIR, load, clean_ref_name, is_named
from cod4x_propagate import propagate

ROUNDS = 4
for a in sys.argv[1:]:
    if a.isdigit():
        ROUNDS = int(a)
DRY = "--dry" in sys.argv

MEASURED = ("method precision measured 97.6% by k-fold cross-validation against "
            "independent call-graph propagation (4x5 folds, 458 answers, 11 wrong)")
REF_NOTE = ("reference = macOS CoD4 (Mach-O, GCC C++, fully symboled), IDA port "
            "18337. ADDRESSES DIFFER between builds; only the NAME is ported.")

EXPORT = r'''
def main():
    import json, idautils, ida_funcs, ida_name, ida_xref
    funcs = {}
    starts = set(idautils.Functions())
    for ea in starts:
        f = ida_funcs.get_func(ea)
        if not f:
            continue
        callees = set()
        for item in idautils.FuncItems(ea):
            for xr in idautils.XrefsFrom(item, 0):
                if xr.type in (ida_xref.fl_CN, ida_xref.fl_CF) and xr.to in starts:
                    callees.add(xr.to)
        funcs["%x" % ea] = [f.end_ea - f.start_ea, ida_name.get_name(ea) or "",
                            sorted(callees)]
    with open(r"__OUT__", "w", encoding="utf-8") as fh:
        json.dump(funcs, fh)
    return len(funcs)
main()
'''.replace("__OUT__", os.path.join(RE_DIR, "cod4x_funcs.json").replace("\\", "\\\\"))

APPLY = r'''
def main():
    import json, ida_name, idc, ida_funcs
    plan = json.load(open(r"__PLAN__", encoding="utf-8"))
    ok = fail = 0
    for k, v in plan.items():
        ea = int(k)
        if not ida_funcs.get_func(ea):
            fail += 1; continue
        if ida_name.set_name(ea, v["name"], ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            idc.set_func_cmt(ea, v["comment"], 0)
            ok += 1
        else:
            fail += 1
    return {"applied": ok, "failed": fail}
main()
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_loop_plan.json").replace("\\", "\\\\"))

contra = {d["tgt"] for d in load("cod4x_contradictions.json")}
total_new = 0

for rnd in range(1, ROUNDS + 1):
    print(f"\n===== loop round {rnd} =====")
    n = pyeval(PORTS["cod4x"], EXPORT, timeout=1800)
    print(f"  refreshed target graph: {n} functions")

    tgt = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
    ref = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}

    # reference: cleaned name -> ea, keeping only names unique in the reference
    ref_by_name = collections.defaultdict(list)
    for ea, v in ref.items():
        nm = clean_ref_name(v[1], ea)
        if nm:
            ref_by_name[nm].append(ea)
    ref_uniq = {nm: eas[0] for nm, eas in ref_by_name.items() if len(eas) == 1}

    # target: named functions, unique in the target
    tgt_by_name = collections.defaultdict(list)
    for ea, v in tgt.items():
        if is_named(v[1]):
            tgt_by_name[v[1]].append(ea)

    seed = {eas[0]: ref_uniq[nm] for nm, eas in tgt_by_name.items()
            if len(eas) == 1 and nm in ref_uniq}
    print(f"  seed from all matching names: {len(seed):,}")

    rows, M = propagate(seed, verbose=True)
    rows = [r for r in rows if r["tgt"] not in contra]
    if not rows:
        print("  nothing new - converged")
        break

    plan = {}
    for r in rows:
        mangled = ref.get(r["ref"], [0, "?", []])[1]
        plan[str(r["tgt"])] = {
            "name": r["name"],
            "comment": (f"Basis: CoD4-Mac call-graph propagation "
                        f"[cod4mac-graph loop={rnd} round={r['round']} "
                        f"support={r['support']}]\n"
                        f"  reference symbol: {mangled} @ cod4 0x{r['ref']:x}\n"
                        f"  {r['support']} independent already-mapped neighbours "
                        f"intersect to exactly ONE reference candidate. "
                        f"Uses NO strings.\n"
                        f"  {MEASURED}\n  {REF_NOTE}")}
    json.dump(plan, open(os.path.join(RE_DIR, "cod4x_loop_plan.json"),
                         "w", encoding="utf-8"))
    print(f"  new names this round: {len(plan):,}")
    for r in rows[:8]:
        print(f"     0x{r['tgt']:<8x} {r['name'][:44]:44} sup={r['support']}")
    if DRY:
        print("  (dry run, not applied)")
        break
    print("  IDA:", pyeval(PORTS["cod4x"], APPLY, timeout=1800))
    total_new += len(plan)

print(f"\nTOTAL new names from the loop: {total_new:,}")
