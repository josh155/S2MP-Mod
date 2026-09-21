"""Baseline survey of an IDB: segments, function counts, naming coverage."""
import sys, json
sys.path.insert(0, r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re")
from ida import pyeval

CODE = r'''
def main():
    import idautils, idc, ida_funcs, ida_segment, ida_name
    segs = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        segs.append({
            "name": ida_segment.get_segm_name(seg),
            "start": seg.start_ea, "end": seg.end_ea,
            "size": seg.end_ea - seg.start_ea,
            "exec": bool(seg.perm & ida_segment.SEGPERM_EXEC),
        })
    total = 0; named = 0; sub = 0; big = 0; big_named = 0
    per_prefix = {}
    for ea in idautils.Functions():
        total += 1
        f = ida_funcs.get_func(ea)
        sz = (f.end_ea - f.start_ea) if f else 0
        n = ida_name.get_name(ea)
        isnamed = not (n.startswith("sub_") or n.startswith("nullsub_")
                       or n.startswith("j_") or n.startswith("unknown_"))
        if isnamed:
            named += 1
            p = n.split("_")[0] if "_" in n else n[:12]
            per_prefix[p] = per_prefix.get(p, 0) + 1
        else:
            sub += 1
        if sz >= 256:
            big += 1
            if isnamed: big_named += 1
    top = sorted(per_prefix.items(), key=lambda kv: -kv[1])[:25]
    return {"segs": segs, "total": total, "named": named, "sub": sub,
            "substantial": big, "substantial_named": big_named, "top_prefix": top}
main()
'''

for label, port in (("MWR-PC  (target, 14347)", 14347), ("MWR-PS4 (reference, 9999)", 9999)):
    r = pyeval(port, CODE)
    if isinstance(r, str):
        print(label, "ERROR:", r[:500]); continue
    print(f"===== {label} =====")
    print(f"  functions {r['total']:,}   named {r['named']:,} "
          f"({100.0*r['named']/max(1,r['total']):.2f}%)   sub_ {r['sub']:,}")
    print(f"  >=256 bytes: {r['substantial']:,}   of those named {r['substantial_named']:,} "
          f"({100.0*r['substantial_named']/max(1,r['substantial']):.2f}%)")
    print("  exec segments:")
    for s in r["segs"]:
        if s["exec"] or s["name"] in (".rdata", ".data"):
            print(f"    {s['name']:12} 0x{s['start']:x}-0x{s['end']:x}  {s['size']/1048576:.1f} MB  exec={s['exec']}")
    print("  top name prefixes:", ", ".join(f"{k}({v})" for k, v in r["top_prefix"][:18]))
    print()
