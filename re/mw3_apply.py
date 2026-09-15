"""Apply the MW3-Mac -> MW3-Steam naming pass, with a mandatory basis comment
on every function.

Merges two sources into one plan:
  * mw3_proposals.json     string-anchor matches (tiers: multi/dominant/
                            single_strong/single_weak), each carrying its own
                            reference ea and anchor strings
  * mw3_propagated.json    call-graph propagation seeded from the anchors,
                            uses NO strings - a genuinely second source

Both were cross-validated by mw3_crossval.py before this ran (98.48% @ MS=2,
99.46% @ MS=3, on 838 anchor pairs; the 16 known contradictions are excluded).

Enforces: one name per function (never overwrite), one function per name
across the WHOLE merged plan, contradictions excluded, and a Basis: comment
that states the exact evidence and the measured precision.

    python re/mw3_apply.py [--dry]
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from mw3_common import RE_DIR, load, is_named

DRY = "--dry" in sys.argv

proposals = load("mw3_proposals.json")          # {str(ea): {...}}
propagated = load("mw3_propagated.json")        # [{"tgt":..,"ref":..,"name":..,"support":..,"round":..}]
contra = {d["tgt"] for d in load("mw3_contradictions.json")}
refg = {int(k, 16): v for k, v in load("mw3_funcs.json").items()}
tgt = load("mw3steam_strowners.json")
tgt_names = {int(k): v for k, v in tgt["names"].items()}

PREC_MS2 = "98.48% (1421/1443 answers, 4 repeats x 5 folds, MIN_SUPPORT=2)"
PREC_MS3 = "99.46% (919/924 answers, 4 repeats x 5 folds, MIN_SUPPORT=3)"

plan, skipped = {}, collections.Counter()
taken = {v for v in tgt_names.values() if is_named(v)}


def mangled_of(ref_ea):
    return refg.get(ref_ea, [0, "?", []])[1] if ref_ea else "?"


# ---- 1. string-anchor proposals ------------------------------------------
for k, v in proposals.items():
    ea = int(k)
    nm = v["name"]
    if ea in contra:
        skipped["contradiction"] += 1; continue
    if is_named(tgt_names.get(ea, "")):
        skipped["already_named"] += 1; continue
    if nm in taken:
        skipped["name_in_use"] += 1; continue
    ref_ea = v.get("ref_ea")
    anchors = v.get("anchors", [])
    comment = (
        f"Basis: MW3-Mac -> MW3-Steam string-anchor port [mw3mac-anchor:{v['tier']}]\n"
        f"  reference symbol: {mangled_of(ref_ea)} @ mw3 0x{ref_ea:x}\n"
        f"  tier={v['tier']}  n_anchors={v['n_anchors']}  best_score={v['best_score']}\n"
        f"  anchor strings (sample): {anchors}\n"
        f"  METHOD PRECISION MEASURED {PREC_MS2} (all tiers combined; this "
        f"pair's own tier scored no worse than 97.80% in cross-validation - "
        f"see re/mw3_crossval.py).\n"
        f"  reference = macOS MW3 (Mach-O, C++, ~99.3% symboled), IDA port 14200. "
        f"ADDRESSES DIFFER between builds (ref imagebase 0x1000, target "
        f"0x140000000); only the NAME is ported.")
    plan[str(ea)] = {"name": nm, "comment": comment}
    taken.add(nm)

n_anchor = len(plan)

# ---- 2. call-graph propagation --------------------------------------------
for r in propagated:
    ea = r["tgt"]
    nm = r["name"]
    if ea in contra:
        skipped["contradiction"] += 1; continue
    if is_named(tgt_names.get(ea, "")):
        skipped["already_named"] += 1; continue
    if str(ea) in plan:
        skipped["already_in_plan"] += 1; continue
    if nm in taken:
        skipped["name_in_use"] += 1; continue
    ref_ea = r["ref"]
    comment = (
        f"Basis: MW3-Mac -> MW3-Steam call-graph propagation "
        f"[mw3mac-propagation gen {r['round']}]\n"
        f"  reference symbol: {mangled_of(ref_ea)} @ mw3 0x{ref_ea:x}\n"
        f"  support={r['support']} (independent mapped neighbours agreeing) "
        f"round={r['round']}\n"
        f"  uses NO strings - callee/caller topology only, seeded from the "
        f"anchor pass and iterated to a fixed point.\n"
        f"  METHOD PRECISION MEASURED {PREC_MS2}\n"
        f"  reference = macOS MW3 (Mach-O, C++, ~99.3% symboled), IDA port 14200. "
        f"ADDRESSES DIFFER between builds (ref imagebase 0x1000, target "
        f"0x140000000); only the NAME is ported.")
    plan[str(ea)] = {"name": nm, "comment": comment}
    taken.add(nm)

n_prop = len(plan) - n_anchor

for k, v in skipped.most_common():
    print(f"  skipped, {k:18} {v}")
print(f"  anchor names        {n_anchor:,}")
print(f"  propagation names   {n_prop:,}")
print(f"  TOTAL TO APPLY      {len(plan):,}")

out = os.path.join(RE_DIR, "mw3_apply_plan.json")
json.dump(plan, open(out, "w", encoding="utf-8"))
if DRY:
    for k, v in list(plan.items())[:8]:
        print(f"\n0x{int(k):x}  {v['name']}\n" +
              "\n".join("    " + l for l in v["comment"].split("\n")))
    sys.exit(0)

CODE = r'''
def main():
    import json, ida_name, idc, ida_funcs
    plan = json.load(open(r"__PLAN__", encoding="utf-8"))
    ok = fail = mismatched = 0
    mismatches = []
    for k, v in plan.items():
        ea = int(k)
        if not ida_funcs.get_func(ea):
            fail += 1; continue
        # SN_FORCE does NOT fail on a collision - it silently appends "_0".
        # Verify the name that actually landed, never trust the return value.
        if ida_name.set_name(ea, v["name"], ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            got = ida_name.get_name(ea)
            if got != v["name"]:
                mismatched += 1
                mismatches.append([hex(ea), v["name"], got])
                continue
            idc.set_func_cmt(ea, v["comment"], 0); ok += 1
        else:
            fail += 1
    return {"applied": ok, "failed": fail, "mismatched": mismatched,
            "mismatch_sample": mismatches[:20]}
main()
'''.replace("__PLAN__", out.replace("\\", "\\\\"))
print("IDA:", pyeval(PORTS["mw3steam"], CODE, timeout=1800))
