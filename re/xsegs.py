"""RUNS INSIDE IDA. Dump segment bounds for one IDB.

Needed to tell ENGINE code from IMPORT STUBS in the Mach-O reference: system
APIs (_glFogi, _atoi, _CFArrayGetTypeID) live in __symbol_stub / __la_symbol_ptr,
which is evidence, unlike guessing from the name.

    python re/xsegs.py cod4 cod4x
writes re/<key>_segs.json
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, ida_segment
    segs = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        segs.append([ida_segment.get_segm_name(seg), seg.start_ea, seg.end_ea,
                     bool(seg.perm & ida_segment.SEGPERM_EXEC)])
    path = os.path.join(r"__RE_DIR__", "__KEY___segs.json")
    with open(path, "w", encoding="utf-8") as f:
        json.dump(segs, f)
    return len(segs)
main()
'''

for key in sys.argv[1:]:
    port = PORTS.get(key) or int(key)
    code = CODE.replace("__RE_DIR__", RE_DIR).replace("__KEY__", key)
    print(key, "segments:", pyeval(port, code, timeout=300))
