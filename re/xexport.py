"""RUNS INSIDE IDA. Dump the function graph of one IDB.

    {hex_ea: [size, name, [callee_eas]]}
writes re/<key>_funcs.json  (same shape as mwr_funcs.json / mwrpc_funcs.json)

    python re/xexport.py cod4 cod4x
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, ida_funcs, ida_name, ida_xref
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
        funcs["%x" % ea] = [f.end_ea - f.start_ea,
                            ida_name.get_name(ea) or "",
                            sorted(callees)]
    path = os.path.join(r"__RE_DIR__", "__KEY___funcs.json")
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(funcs, fh)
    edges = sum(len(v[2]) for v in funcs.values())
    return {"functions": len(funcs), "edges": edges, "path": path}
main()
'''

for key in sys.argv[1:]:
    port = PORTS.get(key) or int(key)
    code = CODE.replace("__RE_DIR__", RE_DIR).replace("__KEY__", key)
    r = pyeval(port, code, timeout=1800)
    print(key, "->", r)
