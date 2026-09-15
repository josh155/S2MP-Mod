"""RUNS INSIDE IDA (MWR-PC). Export the function graph to re/mwrpc_funcs.json.

Format matches re/mwr_funcs.json:  {"0xEA": [size, name, [callee_ea, ...]]}
Only the real .text (lowest exec segment) is exported; the high exec segment is
the Arxan stub block and is noise.
"""
import json, os

OUT = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\mwrpc_funcs.json"


def main():
    import idautils, ida_funcs, ida_name, ida_segment, ida_xref

    lo = hi = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if seg.perm & ida_segment.SEGPERM_EXEC and lo is None:
            lo, hi = seg.start_ea, seg.end_ea

    out = {}
    for ea in idautils.Functions():
        if not (lo <= ea < hi):
            continue
        f = ida_funcs.get_func(ea)
        size = (f.end_ea - f.start_ea) if f else 0
        name = ida_name.get_name(ea)
        callees = []
        seen = set()
        for item in idautils.FuncItems(ea):
            for xr in idautils.XrefsFrom(item, 0):
                if xr.type in (ida_xref.fl_CN, ida_xref.fl_CF):
                    t = xr.to
                    tf = ida_funcs.get_func(t)
                    if tf and tf.start_ea not in seen:
                        seen.add(tf.start_ea)
                        callees.append(tf.start_ea)
        out[hex(ea)] = [size, name, callees]

    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(out, fh)
    return {"functions": len(out),
            "edges": sum(len(v[2]) for v in out.values()),
            "range": [hex(lo), hex(hi)]}


main()
