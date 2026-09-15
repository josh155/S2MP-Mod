"""Reusable applier for ANY method's proposals, with a mandatory basis comment.

    python re/cod4x_apply_method.py <proposals.json> <marker> <headline> [--dry]

  <marker>    structured tag for the audit, e.g. cod4mac-strset
  <headline>  one-line description of the method

Refuses to run unless the method has been MEASURED by cod4x_evaluate.py, and
writes the measured precision into every comment. Never overwrites an existing
name; enforces one-name-one-function against the live IDB; excludes the known
contradictions.
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from cod4x_common import RE_DIR, load, is_named
from cod4x_evaluate import evaluate, current_names

DRY = "--dry" in sys.argv

# A method that only ever proposes for UNNAMED functions cannot be scored by
# overlap with known names - it never lands on one. Such a method must supply its
# own CROSS-VALIDATED figure with --measured; it is never applied unmeasured.
MEASURED_OVERRIDE = None
argv = list(sys.argv[1:])
if "--measured" in argv:
    i = argv.index("--measured")
    MEASURED_OVERRIDE = argv[i + 1]
    del argv[i:i + 2]
args = [a for a in argv if not a.startswith("--")]
if len(args) < 3:
    print(__doc__); sys.exit(2)
PATH, MARKER, HEADLINE = args[0], args[1], " ".join(args[2:])

cur = current_names()
m = evaluate(PATH, cur)
if MEASURED_OVERRIDE:
    m = {"precision": 0.0, "agree": 0, "overlap": 0, "new": m["new"],
         "text": MEASURED_OVERRIDE}
elif m["overlap"] < 20:
    print(f"\nREFUSING: only {m['overlap']} overlapping known names - the method "
          f"is not measurable, so it is not applied.")
    sys.exit(1)
print()

props = load(PATH)
contra = {d["tgt"] for d in load("cod4x_contradictions.json")}
refg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}

taken = {v for v in cur.values() if is_named(v)}
plan, skipped = {}, collections.Counter()
for k, v in props.items():
    ea = int(k)
    nm = v["name"]
    if ea in contra:
        skipped["contradiction"] += 1; continue
    if is_named(cur.get(ea, "")):
        skipped["already_named"] += 1; continue
    if nm in taken:
        skipped["name_in_use"] += 1; continue
    ref_ea = v.get("ref_ea")
    mangled = refg.get(ref_ea, [0, "?", []])[1] if ref_ea else "?"
    plan[str(ea)] = {"name": nm, "comment": (
        f"Basis: {HEADLINE} [{MARKER}]\n"
        f"  reference symbol: {mangled}"
        + (f" @ cod4 0x{ref_ea:x}\n" if ref_ea else "\n") +
        f"  evidence: {v.get('evidence', 'see method')}\n"
        + (f"  METHOD PRECISION MEASURED {m['text']}.\n" if m.get("text") else
           f"  METHOD PRECISION MEASURED {m['precision']:.2f}% "
           f"({m['agree']}/{m['overlap']}) against functions already named by "
           f"independent means (string anchors corroborated by call-graph "
           f"propagation).\n") +
        f"  reference = macOS CoD4 (Mach-O, GCC C++, fully symboled), IDA port "
        f"18337. ADDRESSES DIFFER between builds; only the NAME is ported.")}
    taken.add(nm)

for k, v in skipped.most_common():
    print(f"  skipped, {k:18} {v}")
print(f"  TO APPLY                    {len(plan)}")

out = os.path.join(RE_DIR, "cod4x_method_plan.json")
json.dump(plan, open(out, "w", encoding="utf-8"))
if DRY:
    for k, v in list(plan.items())[:6]:
        print(f"\n0x{int(k):x}  {v['name']}\n" +
              "\n".join("    " + l for l in v["comment"].split("\n")))
    sys.exit(0)

CODE = r'''
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
'''.replace("__PLAN__", out.replace("\\", "\\\\"))
print("IDA:", pyeval(PORTS["cod4x"], CODE, timeout=1800))
