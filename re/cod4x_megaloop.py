"""THE COMPOUNDING ENGINE: run every method in one loop until convergence.

Measured on this target, the dominant blocker for the graph methods is
`too_little_support` on 7,567 functions - they have fewer than two MAPPED
neighbours. So the binding constraint is not the cleverness of any single method,
it is MAPPING DENSITY. Every name any method lands raises the density and unlocks
neighbours for all the others.

So the methods are not alternatives, they are a ratchet:

    strict propagation  (intersection, exactly one survivor)   ~97.6%
    string-set overlap  (mutual best + margin)                 ~98.1%
    weighted graph vote (dominance over runner-up)             ~98.9%

Each round: refresh the graph from the IDB, run all three, merge them in order of
MEASURED precision (highest wins a tie), apply, repeat. Nothing is loosened - the
gain comes purely from density.

    python re/cod4x_megaloop.py [rounds] [--dry]
"""
import json, os, subprocess, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from cod4x_common import RE_DIR, load, is_named

ROUNDS = 8
for a in sys.argv[1:]:
    if a.isdigit():
        ROUNDS = int(a)
DRY = "--dry" in sys.argv
PY = sys.executable

# (script argv, proposals file, marker, headline, measured precision)
METHODS = [
    (["cod4x_propagate.py", "2"], "cod4x_propagated.json", "cod4mac-graph",
     "CoD4-Mac call-graph propagation (intersection, exactly one survivor)",
     "97.60% (447/458) by k-fold cross-validation against independent anchors"),
    (["cod4x_strsets.py", "2", "0.25", "1.0"], "cod4x_strset_proposals.json",
     "cod4mac-strset",
     "CoD4-Mac string-SET similarity, mutual-best match with margin",
     "98.10% (258/263) against functions named by independent means"),
    (["cod4x_vote.py", "--min-votes", "1.0", "--ratio", "1.3"],
     "cod4x_vote_proposals.json", "cod4mac-vote",
     "CoD4-Mac dominance-weighted graph vote (rarity-weighted neighbours)",
     "98.90% (90/91) by 5-fold cross-validation against STRING-derived names "
     "only, so not self-agreement"),
    (["cod4x_ensemble.py"], "cod4x_ensemble_proposals.json", "cod4mac-ensemble",
     "CoD4-Mac ambiguous-anchor deduction CORROBORATED by an independent "
     "call-graph vote",
     "100.00% (53/53) by 5-fold cross-validation; the deduction alone measures "
     "96.47% and requiring corroboration removes every one of its errors"),
]

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
            idc.set_func_cmt(ea, v["comment"], 0); ok += 1
        else:
            fail += 1
    return {"applied": ok, "failed": fail}
main()
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_mega_plan.json").replace("\\", "\\\\"))

REF_NOTE = ("reference = macOS CoD4 (Mach-O, GCC C++, fully symboled), IDA port "
            "18337. ADDRESSES DIFFER between builds; only the NAME is ported.")

contra = {d["tgt"] for d in load("cod4x_contradictions.json")}
grand = 0
history = []

for rnd in range(1, ROUNDS + 1):
    print(f"\n{'='*66}\nROUND {rnd}\n{'='*66}")
    n = pyeval(PORTS["cod4x"], EXPORT, timeout=1800)
    subprocess.run([PY, "cod4x_dumpnames.py"], cwd=RE_DIR,
                   capture_output=True, text=True)
    tg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
    named_before = sum(1 for v in tg.values() if is_named(v[1]))
    print(f"  graph refreshed: {n} functions, {named_before:,} named")

    refg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}
    taken = {v[1] for v in tg.values() if is_named(v[1])}
    plan, per_method = {}, collections.Counter()

    for argv, out, marker, headline, measured in METHODS:
        r = subprocess.run([PY] + argv, cwd=RE_DIR, capture_output=True,
                           text=True)
        if r.returncode != 0:
            print(f"  {argv[0]:22} FAILED: {r.stderr.strip()[:160]}")
            continue
        try:
            props = load(out)
        except Exception as e:
            print(f"  {argv[0]:22} no output ({e})")
            continue
        # cod4x_propagate.py emits a LIST of rows; the feature methods emit a
        # dict. Normalise so the merge does not care which method produced it.
        if isinstance(props, list):
            props = {str(r["tgt"]): {"name": r["name"], "ref_ea": r.get("ref"),
                                     "evidence": f"support={r.get('support')} "
                                                 f"round={r.get('round')}"}
                     for r in props}
        added = 0
        for k, v in props.items():
            ea = int(k) if not str(k).startswith("0x") else int(k, 16)
            nm = v["name"] if isinstance(v, dict) else v
            if ea in contra or ea in plan:
                continue
            if is_named(tg.get(ea, [0, "", []])[1]):
                continue
            if nm in taken:
                continue
            ref_ea = v.get("ref_ea") if isinstance(v, dict) else None
            mang = refg.get(ref_ea, [0, "?", []])[1] if ref_ea else "?"
            ev = v.get("evidence", "") if isinstance(v, dict) else ""
            plan[ea] = {"name": nm, "comment": (
                f"Basis: {headline} [{marker} megaloop-round={rnd}]\n"
                f"  reference symbol: {mang}"
                + (f" @ cod4 0x{ref_ea:x}\n" if ref_ea else "\n") +
                f"  evidence: {ev}\n"
                f"  METHOD PRECISION MEASURED {measured}.\n  {REF_NOTE}")}
            taken.add(nm)
            added += 1
        per_method[marker] = added
        print(f"  {argv[0]:22} proposals {len(props):<5} new {added}")

    if not plan:
        print("  nothing new - CONVERGED")
        break
    json.dump({str(k): v for k, v in plan.items()},
              open(os.path.join(RE_DIR, "cod4x_mega_plan.json"), "w",
                   encoding="utf-8"))
    if DRY:
        print(f"  (dry run) would apply {len(plan)}")
        break
    res = pyeval(PORTS["cod4x"], APPLY, timeout=1800)
    print(f"  APPLIED: {res}")
    grand += res.get("applied", 0) if isinstance(res, dict) else 0
    history.append((rnd, dict(per_method), named_before))

print(f"\n{'='*66}")
print(f"TOTAL new names from the megaloop: {grand:,}")
for rnd, pm, before in history:
    print(f"  round {rnd}: named {before:,} -> +"
          f"{sum(pm.values())}   " +
          "  ".join(f"{k.split('-')[-1]}={v}" for k, v in pm.items()))
