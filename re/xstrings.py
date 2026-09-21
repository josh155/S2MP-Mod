"""RUNS INSIDE IDA. Dump {string: [owning function eas]} for one IDB.

Generic replacement for the one-off mwrpc_harvest step. Extracts printable
NUL-terminated runs from every initialised, reasonably-sized segment, then maps
each string address to the function that references it via IDA's data xrefs.

Never calls idautils.Strings() (forces a strlist rebuild; times out on a dump).

    python re/xstrings.py cod4 cod4x
writes re/<key>_strowners.json
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, ida_bytes, ida_segment, ida_funcs, ida_name
    MIN_LEN = 4
    SKIP = ("__bss", "__common", "UNDEF", "ABS", ".tls", "HEADER", "extern")

    strmap = {}
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        nm = ida_segment.get_segm_name(seg)
        size = seg.end_ea - seg.start_ea
        if nm in SKIP or size > 64 * 1024 * 1024:
            continue
        buf = ida_bytes.get_bytes(seg.start_ea, size)
        if not buf:
            continue
        start = None
        for i, b in enumerate(buf):
            if 32 <= b < 127 or b == 9:
                if start is None:
                    start = i
            else:
                if start is not None and b == 0 and i - start >= MIN_LEN:
                    strmap.setdefault(buf[start:i].decode("ascii", "replace"),
                                      []).append(seg.start_ea + start)
                start = None

    owners = {}
    for s, addrs in strmap.items():
        fs = set()
        for a in addrs:
            for xr in idautils.XrefsTo(a, 0):
                f = ida_funcs.get_func(xr.frm)
                if f:
                    fs.add(f.start_ea)
        if fs:
            owners[s] = sorted(fs)

    names = {}
    for ea in idautils.Functions():
        names[str(ea)] = ida_name.get_name(ea) or ""

    out = {"owners": owners, "names": names,
           "distinct_strings": len(strmap), "with_owner": len(owners)}
    path = os.path.join(r"__RE_DIR__", "__KEY___strowners.json")
    with open(path, "w", encoding="utf-8") as f:
        json.dump(out, f)
    return {"distinct_strings": len(strmap), "with_owner": len(owners),
            "functions": len(names), "path": path}
main()
'''

for key in sys.argv[1:]:
    port = PORTS.get(key) or int(key)
    code = CODE.replace("__RE_DIR__", RE_DIR).replace("__KEY__", key)
    r = pyeval(port, code, timeout=900)
    print(key, "->", r)
