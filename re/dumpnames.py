import json
def main():
    import idautils, ida_name, ida_segment
    lo = hi = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if seg.perm & ida_segment.SEGPERM_EXEC and lo is None:
            lo, hi = seg.start_ea, seg.end_ea
    out = {}
    for ea in idautils.Functions():
        if lo <= ea < hi:
            n = ida_name.get_name(ea)
            if n and not (n.startswith("sub_") or n.startswith("nullsub_") or n.startswith("j_")):
                out[hex(ea)] = n
    p = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\mwrpc_names_now.json"
    json.dump(out, open(p, "w", encoding="utf-8"))
    return len(out)
main()
