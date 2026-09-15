"""Fix names that IDA silently MANGLED, and verify the filter on real symbols.

⚠ THE DEFECT THIS FIXES: ida_name.set_name(..., SN_FORCE) does not fail on a
name collision - it appends _0/_1 and reports success. So a duplicate proposal
becomes `CL_InitOnceForAllClients_0`, a name that exists in neither binary. The
audit caught it as a phantom reference.

Any function carrying such a suffix is reverted to sub_ with a comment, because
one-name-one-function means the ambiguous member gets no name at all.

    python re/cod4x_fix_dupes.py [--dry]
"""
import os, re, sys, json
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from cod4x_common import RE_DIR, load, clean_ref_name

DRY = "--dry" in sys.argv

# ---- 1. verify the filter against REAL reference symbols ------------------
rg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}
print("filter check on REAL reference symbols:")
for want in ("SCR_StopCinematic", "SCR_UpdateFrame", "CG_Init", "SV_Frame",
             "UI_Init", "StringTable_Lookup"):
    hits = [(ea, v[1]) for ea, v in rg.items()
            if clean_ref_name(v[1], ea) == want]
    print(f"   {want:24} -> " +
          (f"ok, ref 0x{hits[0][0]:x} {hits[0][1][:40]}" if hits
           else "NOT RECOVERED"))

# ---- 2. find mangled names in the target ---------------------------------
dump = load("cod4x_named_dump.json")
names = {v[0] for v in dump.values()}
bad = {}
for ea, (nm, sz, cmt) in dump.items():
    m = re.match(r"^(.*?)_(\d+)$", nm)
    if not m:
        continue
    base = m.group(1)
    # only a collision artefact if the base name is worn by another function
    if base in names:
        bad[ea] = (nm, base)

print(f"\nnames that look like IDA collision artefacts: {len(bad)}")
for ea, (nm, base) in bad.items():
    holder = [k for k, v in dump.items() if v[0] == base]
    print(f"   {ea} {nm}  (base {base!r} held by {holder})")

if not bad or DRY:
    sys.exit(0)

plan = {ea: (
    f"NOT NAMED. A previous pass proposed the name {base!r} for this function, "
    f"but that name was already worn by another function, and "
    f"ida_name.set_name(SN_FORCE) silently appended a numeric suffix instead of "
    f"failing - producing {nm!r}, a name present in NEITHER binary. Under "
    f"one-name-one-function the ambiguous member gets no name, so this reverts "
    f"to sub_. The evidence pointed at this function OR the one holding {base!r}; "
    f"which of the two is correct is unresolved.")
    for ea, (nm, base) in bad.items()}

json.dump(plan, open(os.path.join(RE_DIR, "cod4x_dupe_plan.json"), "w",
                     encoding="utf-8"))

CODE = r'''
def main():
    import json, ida_name, idc, ida_funcs
    plan = json.load(open(r"__PLAN__", encoding="utf-8"))
    done = []
    for k, cmt in plan.items():
        ea = int(k, 16)
        if not ida_funcs.get_func(ea):
            continue
        ida_name.set_name(ea, "", ida_name.SN_NOCHECK)   # back to sub_
        idc.set_func_cmt(ea, cmt, 0)
        done.append((k, ida_name.get_name(ea)))
    return done
main()
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_dupe_plan.json").replace("\\", "\\\\"))

print("\nIDA:", pyeval(PORTS["cod4x"], CODE, timeout=600))
