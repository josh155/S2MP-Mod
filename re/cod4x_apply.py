"""Apply CoD4-Mac -> CoD4X names, each with a recorded basis comment.

Two independent sources, applied together:
  anchors  - a string literal uniquely owned on BOTH sides (cross-binary)
  graph    - call-graph topology only, no strings (a genuinely second source)

Contradictions between the two (re/cod4x_contradictions.json) are EXCLUDED, not
adjudicated.

    python re/cod4x_apply.py [--dry]
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from cod4x_common import RE_DIR, load, is_named

DRY = "--dry" in sys.argv

MEASURED = ("method precision measured 97.6% by k-fold cross-validation against "
            "independent call-graph propagation (4x5 folds, 458 answers, 11 wrong)")
REF_NOTE = ("reference = macOS CoD4 (Mach-O, GCC C++, fully symboled), IDA port "
            "18337. ADDRESSES DIFFER between builds; only the NAME is ported.")

props = load("cod4x_proposals.json")
prop_rows = load("cod4x_propagated.json")
contra = {d["tgt"] for d in load("cod4x_contradictions.json")}
refg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}
tgtg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}

plan = {}      # tgt_ea -> (name, comment)

# ---- anchors -------------------------------------------------------------
skipped_contra = 0
for k, p in props.items():
    ea = int(k)
    if ea in contra:
        skipped_contra += 1
        continue
    ref_ea = p.get("ref_ea")
    mangled = refg.get(ref_ea, [0, "?", []])[1] if ref_ea else "?"
    ex = ", ".join(repr(a) for a in p["anchors"][-3:])
    dom = f"\n  collision winner by dominance: {p['dominance']}" if p.get("dominance") else ""
    cmt = (f"Basis: CoD4-Mac string-anchor port "
           f"[cod4mac-anchor tier={p['tier']} n={p['n_anchors']}]\n"
           f"  reference symbol: {mangled} @ cod4 0x{ref_ea:x}\n"
           f"  anchor string(s) uniquely owned by ONE function on BOTH sides: {ex}"
           f"{dom}\n"
           f"  {MEASURED}\n"
           f"  {REF_NOTE}")
    plan[ea] = (p["name"], cmt)

# ---- call-graph propagation ---------------------------------------------
for r in prop_rows:
    ea = r["tgt"]
    if ea in plan or ea in contra:
        continue
    mangled = refg.get(r["ref"], [0, "?", []])[1]
    cmt = (f"Basis: CoD4-Mac call-graph propagation "
           f"[cod4mac-graph round={r['round']} support={r['support']}]\n"
           f"  reference symbol: {mangled} @ cod4 0x{r['ref']:x}\n"
           f"  {r['support']} independent already-mapped neighbours intersect to "
           f"exactly ONE reference candidate. Uses NO strings.\n"
           f"  {MEASURED}\n"
           f"  {REF_NOTE}")
    plan[ea] = (r["name"], cmt)

# ---- final safety: one name, one function; never overwrite --------------
byname = collections.defaultdict(list)
for ea, (nm, _c) in plan.items():
    byname[nm].append(ea)
dupes = {n: e for n, e in byname.items() if len(e) > 1}
for n, eas in dupes.items():
    for ea in eas:
        plan.pop(ea, None)

existing = {v[1] for v in tgtg.values() if is_named(v[1])}
clash = [ea for ea, (nm, _c) in plan.items() if nm in existing]
for ea in clash:
    plan.pop(ea)
overwrite = [ea for ea in plan if is_named(tgtg.get(ea, [0, "", []])[1])]
for ea in overwrite:
    plan.pop(ea)

print(f"anchors                       : {len(props):,}")
print(f"  excluded, contradiction     : {skipped_contra}")
print(f"propagated                    : {len(prop_rows):,}")
print(f"dropped, duplicate name       : {len(dupes)} names / "
      f"{sum(len(v) for v in dupes.values())} funcs")
print(f"dropped, name already in use  : {len(clash)}")
print(f"dropped, would overwrite      : {len(overwrite)}")
print(f"TO APPLY                      : {len(plan):,}")

json.dump({str(k): {"name": v[0], "comment": v[1]} for k, v in plan.items()},
          open(os.path.join(RE_DIR, "cod4x_applied.json"), "w", encoding="utf-8"))

if DRY:
    print("\n--- dry run, 12 samples ---")
    for ea, (nm, cmt) in list(plan.items())[:12]:
        print(f"\n0x{ea:x}  {nm}\n" + "\n".join("    " + l for l in cmt.split("\n")))
    sys.exit(0)

CODE = r'''
def main():
    import json, ida_name, idc, ida_funcs
    plan = json.load(open(r"__PLAN__", encoding="utf-8"))
    ok = fail = 0
    errs = []
    for k, v in plan.items():
        ea = int(k)
        if not ida_funcs.get_func(ea):
            errs.append((k, "no function")); fail += 1; continue
        if ida_name.set_name(ea, v["name"], ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            idc.set_func_cmt(ea, v["comment"], 0)
            ok += 1
        else:
            errs.append((k, "set_name failed")); fail += 1
    return {"applied": ok, "failed": fail, "errors": errs[:20]}
main()
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_applied.json").replace("\\", "\\\\"))

r = pyeval(PORTS["cod4x"], CODE, timeout=1800)
print("\nIDA:", r)
