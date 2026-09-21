"""Find client/entity limit constants in an IDB by their ASSERT / error text.

A debug build states its own limits: "clientNum < MAX_CLIENTS" etc. Rather than
hunting for the numeric literal 18 or 64 (hopelessly noisy), find the strings
that NAME the constant and the functions that reference them.

Run inside IDA. Returns matches; writes nothing.
"""


def main():
    import idautils, ida_bytes, ida_segment, ida_funcs, ida_name

    NEEDLES = [
        "MAX_CLIENTS", "MAX_GENTITIES", "MAX_ENTITIES", "GENTITYNUM",
        "MAX_GPLAYERS", "maxclients", "sv_maxclients", "MAX_CLIENT",
        "MAX_AGENTS", "MAX_SNAPSHOT_ENTITIES", "MAX_PARSE_ENTITIES",
        "clientNum <", "clientnum <", "MAX_LOCALCLIENTS", "MAX_SPLITSCREEN",
        "ENTITYNUM_NONE", "MAX_HUDELEMS", "MAX_WEAPONS", "MAX_CONFIGSTRINGS",
    ]

    segs = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        segs.append((ida_segment.get_segm_name(seg), seg.start_ea, seg.end_ea,
                     bool(seg.perm & ida_segment.SEGPERM_EXEC)))

    hits = []
    for nm, lo, hi, isexec in segs:
        if hi - lo > 80 * 1024 * 1024:
            continue
        buf = ida_bytes.get_bytes(lo, hi - lo) or b""
        for needle in NEEDLES:
            nb = needle.encode()
            start = 0
            while True:
                i = buf.find(nb, start)
                if i < 0:
                    break
                start = i + 1
                # widen to the enclosing NUL-terminated string
                s0 = buf.rfind(b"\x00", max(0, i - 220), i) + 1
                s1 = buf.find(b"\x00", i, min(len(buf), i + 220))
                if s1 < 0:
                    s1 = i + 60
                try:
                    text = buf[s0:s1].decode("ascii")
                except Exception:
                    continue
                if len(text) > 240:
                    continue
                addr = lo + s0
                refs = []
                for xr in idautils.XrefsTo(addr, 0):
                    f = ida_funcs.get_func(xr.frm)
                    if f:
                        refs.append(ida_name.get_name(f.start_ea))
                hits.append({"addr": hex(addr), "text": text,
                             "refs": sorted(set(refs))[:4]})

    # dedupe by text
    seen, out = set(), []
    for h in hits:
        if h["text"] in seen:
            continue
        seen.add(h["text"])
        out.append(h)
    return out[:120]


main()
