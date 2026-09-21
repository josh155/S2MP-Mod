"""Refresh re/cod4x_named_dump.json {ea: [name, size, comment]} from the IDB.

The comment is what lets a method be measured against a SPECIFIC evidence source
(cod4x_evaluate.py --truth=...), which is how circular validation is avoided.
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                   "cod4x_named_dump.json").replace("\\", "\\\\")

CODE = r'''
def main():
    import idautils, ida_funcs, idc, json
    out = {}
    for fea in idautils.Functions():
        nm = ida_funcs.get_func_name(fea)
        if nm.startswith(("sub_", "nullsub", "j_", "unknown_")):
            continue
        f = ida_funcs.get_func(fea)
        c = idc.get_func_cmt(fea, 0) or idc.get_func_cmt(fea, 1) or ""
        out[hex(fea)] = [nm, f.size() if f else 0, c]
    with open(r"__OUT__", "w", encoding="utf-8") as fh:
        json.dump(out, fh)
    return len(out)
main()
'''.replace("__OUT__", OUT)

print("named functions dumped:", pyeval(PORTS["cod4x"], CODE, timeout=900))
