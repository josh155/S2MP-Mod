"""Apply the console-command naming plan (mw3steam_cmd_plan.json) to MW3-Steam."""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__))
plan_path = os.path.join(RE_DIR, "mw3steam_cmd_plan.json").replace("\\", "\\\\")

CODE = r'''
def main():
    import json, ida_name, idc, ida_funcs
    plan = json.load(open(r"__PLAN__", encoding="utf-8"))
    named = commented = fail = mismatched = 0
    mismatches = []
    for k, v in plan.items():
        ea = int(k, 16)
        if not ida_funcs.get_func(ea):
            fail += 1; continue
        if v.get("dispatcher_only"):
            idc.set_func_cmt(ea, v["comment"], 0)
            commented += 1
            continue
        if ida_name.set_name(ea, v["name"], ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            got = ida_name.get_name(ea)
            if got != v["name"]:
                mismatched += 1
                mismatches.append([k, v["name"], got])
                continue
            idc.set_func_cmt(ea, v["comment"], 0)
            named += 1
        else:
            fail += 1
    return {"named": named, "commented": commented, "failed": fail,
            "mismatched": mismatched, "mismatch_sample": mismatches[:20]}
main()
'''.replace("__PLAN__", plan_path)

print(pyeval(PORTS["mw3steam"], CODE, timeout=900))
