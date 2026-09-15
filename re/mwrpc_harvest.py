"""RUNS INSIDE IDA (MWR-PC, port 14347).

Harvest, for every MWR-PS4 anchor string, which MWR-PC function references it.

Method: extract printable NUL-terminated runs from the non-executable segments
once, build string -> [addresses], then look up each anchor. Never calls
idautils.Strings() (forces a strlist rebuild and times out on a dump this size).

Writes re/mwrpc_anchor_hits.json.
"""
import json, os

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"
OUT = os.path.join(RE_DIR, "mwrpc_anchor_hits.json")
MIN_LEN = 4


def main():
    import idautils, idaapi, ida_bytes, ida_funcs, ida_segment, ida_name, ida_xref

    # ---- 1. segment map -------------------------------------------------
    data_segs, code_lo, code_hi = [], None, None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        nm = ida_segment.get_segm_name(seg)
        if seg.perm & ida_segment.SEGPERM_EXEC:
            # first (lowest) exec segment is the real code; the high one is Arxan
            if code_lo is None:
                code_lo, code_hi = seg.start_ea, seg.end_ea
        else:
            data_segs.append((nm, seg.start_ea, seg.end_ea))

    # ---- 2. extract string runs from data segments ----------------------
    # str -> list of addresses. Skip .data if it is enormous unless asked.
    strmap = {}
    scanned = []
    for nm, lo, hi in data_segs:
        size = hi - lo
        if size > 64 * 1024 * 1024:
            # a process dump's .data is mostly heap; strings there carry no
            # lea-from-code xrefs, so they cannot identify an owner anyway.
            scanned.append((nm, size, "SKIPPED (too large)"))
            continue
        buf = ida_bytes.get_bytes(lo, size) or b""
        scanned.append((nm, size, "scanned"))
        start = None
        for i, b in enumerate(buf):
            if 32 <= b < 127 or b in (9,):
                if start is None:
                    start = i
            else:
                if start is not None and b == 0 and i - start >= MIN_LEN:
                    s = buf[start:i].decode("ascii", "replace")
                    strmap.setdefault(s, []).append(lo + start)
                start = None

    # ---- 3. load anchors, resolve xrefs ---------------------------------
    anchors = json.load(open(os.path.join(RE_DIR, "mwr_anchors.json"),
                             encoding="utf-8"))

    hits = {}          # anchor -> {"ps4": name, "pc": [func_ea, ...]}
    present = 0
    for anchor, meta in anchors.items():
        addrs = strmap.get(anchor)
        if not addrs:
            continue
        present += 1
        funcs = set()
        for a in addrs:
            for xr in idautils.XrefsTo(a, 0):
                f = ida_funcs.get_func(xr.frm)
                if f and code_lo <= f.start_ea < code_hi:
                    funcs.add(f.start_ea)
        if funcs:
            hits[anchor] = {"ps4_name": meta["name"],
                            "ps4_ea": meta.get("func"),
                            "pc": sorted(funcs)}

    # ---- 4. current PC names, so we never overwrite -----------------------
    pc_named = {}
    for ea in idautils.Functions():
        n = ida_name.get_name(ea)
        if n and not (n.startswith("sub_") or n.startswith("nullsub_")
                      or n.startswith("j_")):
            pc_named[str(ea)] = n

    out = {
        "code_lo": code_lo, "code_hi": code_hi,
        "segments_scanned": scanned,
        "distinct_strings": len(strmap),
        "anchors_total": len(anchors),
        "anchors_present_in_pc": present,
        "anchors_with_pc_xref": len(hits),
        "hits": hits,
        "pc_already_named": pc_named,
    }
    with open(OUT, "w", encoding="utf-8") as f:
        json.dump(out, f)
    return {k: v for k, v in out.items() if k not in ("hits", "pc_already_named")}


main()
