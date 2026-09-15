"""Extract the string vocabulary a function references (runs inside IDA).

Used to enumerate a server-command dispatcher's command names: the dispatcher
compares the first token of each command against a set of literals, so the
literals it references ARE the vocabulary.

Set TARGET before exec.
"""
import json, os

OUT = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\cmd_vocab_out.json"


def main():
    import idautils, idc, ida_funcs, ida_bytes, ida_segment

    segs = [(ida_segment.getseg(s).start_ea, ida_segment.getseg(s).end_ea)
            for s in idautils.Segments()]
    lo = min(a for a, _ in segs)
    hi = max(b for _, b in segs)

    def cstr(ea, maxn=96):
        b = ida_bytes.get_bytes(ea, maxn) or b""
        i = b.find(b"\x00")
        if i <= 0:
            return None
        s = b[:i]
        if not all(32 <= c < 127 for c in s):
            return None
        return s.decode("ascii")

    res = {}
    for target in TARGETS:
        f = ida_funcs.get_func(target)
        if not f:
            res[hex(target)] = []
            continue
        found = []
        for ea in idautils.FuncItems(f.start_ea):
            for k in (0, 1, 2):
                v = idc.get_operand_value(ea, k)
                if v and lo <= v < hi:
                    s = cstr(v)
                    if s and 1 <= len(s) <= 48 and s not in found:
                        found.append(s)
            # also follow data refs (rip-relative lea often lands here)
            for r in idautils.DataRefsFrom(ea):
                s = cstr(r)
                if s and 1 <= len(s) <= 48 and s not in found:
                    found.append(s)
        res[hex(target)] = found
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(res, fh)
    return {k: len(v) for k, v in res.items()}


main()
