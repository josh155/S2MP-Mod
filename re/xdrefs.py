"""RUNS INSIDE IDA. Dump per-function referenced GLOBAL (writable data) sets.

A third feature dimension, independent of both strings and the call graph:
which globals a function touches. Two functions that both touch `cg`, `cl` and
`cgs` are almost certainly twins, and this works for functions that print
nothing and call nothing distinctive.

Only WRITABLE data segments are collected (.data/.bss/__data/__common), because
read-only data is strings and float literals, which the other methods already
cover.

    python re/xdrefs.py cod4 cod4x
writes re/<key>_drefs.json  {func_ea_hex: [global_ea, ...]}
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, ida_segment

    WRITABLE = (".data", ".bss", "__data", "__bss", "__common", ".tls")
    rng = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if ida_segment.get_segm_name(seg) in WRITABLE:
            rng.append((seg.start_ea, seg.end_ea))

    def is_global(ea):
        for a, b in rng:
            if a <= ea < b:
                return True
        return False

    out = {}
    for f in idautils.Functions():
        gs = set()
        for ea in idautils.FuncItems(f):
            for dr in idautils.DataRefsFrom(ea):
                if is_global(dr):
                    gs.add(dr)
        if gs:
            out["%x" % f] = sorted(gs)

    path = os.path.join(r"__RE_DIR__", "__KEY___drefs.json")
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(out, fh)
    return {"functions_with_globals": len(out),
            "distinct_globals": len({g for v in out.values() for g in v})}
main()
'''

for key in sys.argv[1:]:
    port = PORTS.get(key) or int(key)
    code = CODE.replace("__RE_DIR__", RE_DIR).replace("__KEY__", key)
    print(key, "->", pyeval(port, code, timeout=1800))
