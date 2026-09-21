"""RUNS INSIDE IDA (MWR-PS4, port 9999). Extract self-naming {name, fn} tables.

Same maximal-run method as the PC side so the two are directly comparable.

PERF: the MCP plugin enforces a hard 60s internal timeout. A per-qword string
test over 2.4M qwords blows it, so both the qword decode (one struct.unpack) and
the "is this a string start" test (a precomputed set) are done in bulk.

Writes re/ps4_tables.json.
"""
import json, os, struct

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"
PRINTABLE = bytes(range(32, 127))


def main():
    import idautils, ida_bytes, ida_segment, ida_name

    bounds = [(ida_segment.getseg(s).start_ea, ida_segment.getseg(s).end_ea)
              for s in idautils.Segments()]
    lo = min(a for a, _ in bounds)
    hi = max(b for _, b in bounds)

    func_starts = set(idautils.Functions())
    name_of = {ea: ida_name.get_name(ea) for ea in func_starts}

    buf = ida_bytes.get_bytes(lo, hi - lo) or b""
    n = len(buf) // 8
    qs = struct.unpack_from("<%dQ" % n, buf, 0)

    # string START addresses: NUL-terminated printable runs of length >= 3
    ok = bytearray(256)
    for c in PRINTABLE:
        ok[c] = 1
    strstart = set()
    pos = 0
    blen = len(buf)
    find = buf.find
    while pos < blen:
        e = find(b"\x00", pos)
        if e < 0:
            break
        ln = e - pos
        if 2 < ln < 160:
            chunk = buf[pos:e]
            if all(ok[c] for c in chunk):
                strstart.add(lo + pos)
        pos = e + 1

    tables, i = [], 0
    while i + 1 < n:
        if qs[i] in strstart and qs[i + 1] in func_starts:
            j, pairs = i, []
            while j + 1 < n and qs[j] in strstart and qs[j + 1] in func_starts:
                pairs.append((qs[j], qs[j + 1]))
                j += 2
            if len(pairs) >= 5:
                recs = []
                for sa, fa in pairs:
                    o = sa - lo
                    e = buf.find(b"\x00", o)
                    recs.append([buf[o:e].decode("ascii", "replace"),
                                 hex(fa), name_of.get(fa, "")])
                tables.append({"base": lo + i * 8, "count": len(pairs),
                               "pairs": recs})
            i = j
        else:
            i += 1

    json.dump(tables, open(os.path.join(RE_DIR, "ps4_tables.json"), "w",
                           encoding="utf-8"))
    return {"tables": len(tables), "pairs": sum(t["count"] for t in tables)}


main()
