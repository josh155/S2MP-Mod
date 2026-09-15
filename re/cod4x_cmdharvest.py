"""RUNS INSIDE IDA (CoD4X). Harvest {command name -> handler} from the registrar.

Cmd_AddServerCommandInternal @ 0x4f9140 is TIER-1 self-naming evidence: its own
error string is "Cmd_AddServerCommand: %s already defined\n", and it is handed a
name and a handler at each call site. The target binary asserts the pairing.

The name arrives in EDI (__usercall), not on the stack, so a push-only scan finds
nothing - the backward scan here reads EVERY operand of EVERY instruction in the
window and classifies it as string / function-start.

Handlers are named "<command>_f", the engine's own convention. SV_Status_f is
ALREADY named in this IDB from the anchor pass, so if the harvest independently
pairs 'status' with that same function, the method is validated.

    python re/cod4x_cmdharvest.py 0x4f9140 [--apply]
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")
TARGET = sys.argv[1] if len(sys.argv) > 1 else "0x4f9140"
APPLY = "--apply" in sys.argv

CODE = r'''
def main():
    import json, os, idautils, idc, ida_bytes, ida_funcs, ida_name

    T = __TARGET__
    starts = set(idautils.Functions())

    def as_string(ea):
        b = ida_bytes.get_bytes(ea, 128)
        if not b:
            return None
        i = b.find(b"\x00")
        if i < 2:
            return None
        s = b[:i]
        if not all(32 <= c < 127 for c in s):
            return None
        try:
            return s.decode("ascii")
        except Exception:
            return None

    rows = []
    for xr in idautils.XrefsTo(T, 0):
        frm = xr.frm
        if not idc.print_insn_mnem(frm).lower().startswith("call"):
            continue
        owner = ida_funcs.get_func(frm)
        # walk backwards, newest first, collecting operand values
        strings, funcs = [], []
        ea = frm
        for _ in range(24):
            ea = idc.prev_head(ea)
            if ea == idc.BADADDR:
                break
            if idc.print_insn_mnem(ea).lower().startswith("call"):
                break
            for opn in range(3):
                ty = idc.get_operand_type(ea, opn)
                if ty not in (idc.o_imm, idc.o_mem, idc.o_far, idc.o_near):
                    continue
                v = idc.get_operand_value(ea, opn)
                if not v:
                    continue
                if v in starts:
                    if v not in funcs and v != T:
                        funcs.append(v)
                else:
                    s = as_string(v)
                    if s and s not in strings:
                        strings.append(s)
        rows.append({"call": frm,
                     "owner": owner.start_ea if owner else None,
                     "owner_name": ida_name.get_name(owner.start_ea) if owner else "",
                     "name": strings[0] if strings else None,
                     "strings": strings[:3],
                     "handler": funcs[0] if funcs else None,
                     "handler_name": ida_name.get_name(funcs[0]) if funcs else None,
                     "funcs": funcs[:3]})
    path = os.path.join(r"__RE_DIR__", "cod4x_cmds.json")
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(rows, fh)
    return {"sites": len(rows),
            "with_name": sum(1 for r in rows if r["name"]),
            "with_handler": sum(1 for r in rows if r["handler"])}
main()
'''.replace("__TARGET__", TARGET).replace("__RE_DIR__", RE_DIR)

print(pyeval(PORTS["cod4x"], CODE, timeout=900))

rows = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                   "cod4x_cmds.json"), encoding="utf-8"))
print(f"\n{'command':<24} {'handler':<12} current name")
for r in sorted(rows, key=lambda r: (r["name"] or "")):
    print(f"  {str(r['name']):<24} "
          f"{('0x%x' % r['handler']) if r['handler'] else '-':<12} "
          f"{r['handler_name']}")

# ---- validation: does it agree with names already established? ----------
agree = clash = 0
for r in rows:
    hn = r["handler_name"] or ""
    if hn and not hn.startswith(("sub_", "nullsub", "j_", "unknown_")):
        want = f"{r['name']}_f" if r["name"] else None
        if want and hn.lower() == want.lower():
            agree += 1
        else:
            clash += 1
            print(f"  NOTE already-named handler {hn} carries command "
                  f"{r['name']!r} (expected {want})")
print(f"\nalready-named handlers agreeing with <cmd>_f : {agree}")
print(f"already-named handlers differing             : {clash}")

if not APPLY:
    sys.exit(0)

plan = {}
seen = set()
for r in rows:
    if not r["name"] or not r["handler"]:
        continue
    hn = r["handler_name"] or ""
    if hn and not hn.startswith(("sub_", "nullsub", "j_", "unknown_")):
        continue                      # never overwrite
    nm = "".join(c if (c.isalnum() or c == "_") else "_" for c in r["name"]) + "_f"
    if nm in seen:
        continue
    seen.add(nm)
    plan[str(r["handler"])] = {
        "name": nm,
        "comment": (f"Basis: self-naming registrar [cod4x-cmdtable]\n"
                    f"  Cmd_AddServerCommandInternal(\"{r['name']}\", this, ...) "
                    f"at 0x{r['call']:x} in {r['owner_name']}\n"
                    f"  The registrar names itself in its own error string "
                    f"\"Cmd_AddServerCommand: %s already defined\", so the "
                    f"name/handler pairing is asserted by the target binary "
                    f"itself - tier-1 evidence, no cross-binary inference.\n"
                    f"  Convention <command>_f matches SV_Status_f, which was "
                    f"established independently by the anchor pass.")}
print(f"\nto apply: {len(plan)}")
json.dump(plan, open(os.path.join(RE_DIR.replace('\\\\', '\\'),
                                  "cod4x_cmd_plan.json"), "w", encoding="utf-8"))

APPLY_CODE = r'''
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
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_cmd_plan.json").replace("\\", "\\\\"))
print("IDA:", pyeval(PORTS["cod4x"], APPLY_CODE, timeout=600))
