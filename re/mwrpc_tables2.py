"""RUNS INSIDE IDA (MWR-PC). Clean extraction of self-naming {name, fn} tables.

Fixes two defects in the first pass:
  * find MAXIMAL runs of alternating [string ptr][function ptr] qwords, so the
    table base can never start mid-record (that produced shifted pairings);
  * emit only the canonical luaL_Reg shape (stride 16, name+0, fn+8), which was
    settled empirically: it agrees with independently-derived names, the
    name+8/fn+0 reading agrees 0%.

Each table is then GRADED against names derived from strings / call graph -
evidence sources that know nothing about these tables. A correctly aligned table
agrees; a shifted one does not.

Writes re/mwrpc_tables2.json.
"""
import json, os

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"


def main():
    import idautils, ida_bytes, ida_funcs, ida_segment, ida_name

    code_lo = code_hi = None
    rdata = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if seg.perm & ida_segment.SEGPERM_EXEC and code_lo is None:
            code_lo, code_hi = seg.start_ea, seg.end_ea
        if ida_segment.get_segm_name(seg) == ".rdata":
            rdata = (seg.start_ea, seg.end_ea)

    func_starts = {ea for ea in idautils.Functions() if code_lo <= ea < code_hi}
    lo, hi = rdata
    buf = ida_bytes.get_bytes(lo, hi - lo) or b""
    n = (hi - lo) // 8

    def as_str(addr):
        if not (lo <= addr < hi):
            return None
        o = addr - lo
        end = buf.find(b"\x00", o, min(o + 160, len(buf)))
        if end < 0 or end - o < 2:
            return None
        s = buf[o:end]
        if not all(32 <= c < 127 for c in s):
            return None
        try:
            return s.decode("ascii")
        except Exception:
            return None

    qs = [int.from_bytes(buf[i * 8:i * 8 + 8], "little") for i in range(n)]
    is_fn = [v in func_starts for v in qs]
    strv = [as_str(v) if v and not f else None for v, f in zip(qs, is_fn)]

    # maximal runs of [str][fn] pairs
    tables, i = [], 0
    while i + 1 < n:
        if strv[i] and is_fn[i + 1]:
            j, pairs = i, []
            while j + 1 < n and strv[j] and is_fn[j + 1]:
                pairs.append([strv[j], qs[j + 1]])
                j += 2
            if len(pairs) >= 5:
                tables.append({"base": lo + i * 8, "count": len(pairs),
                               "pairs": pairs})
            i = j
        else:
            i += 1

    # grade each table against independently-derived names
    out = []
    for t in tables:
        tested = agree = 0
        ex = []
        for s, fea in t["pairs"]:
            nm = ida_name.get_name(fea)
            if not nm or nm.startswith("sub_") or nm.startswith("nullsub_"):
                continue
            tested += 1
            if s.lower().replace("_", "") in nm.lower().replace("_", ""):
                agree += 1
            else:
                ex.append([s, nm])
        out.append({"base": hex(t["base"]), "count": t["count"],
                    "tested": tested, "agree": agree,
                    "mismatch": ex[:4],
                    "pairs": [[s, hex(f)] for s, f in t["pairs"]]})

    json.dump(out, open(os.path.join(RE_DIR, "mwrpc_tables2.json"), "w",
                        encoding="utf-8"))
    tot_tested = sum(t["tested"] for t in out)
    tot_agree = sum(t["agree"] for t in out)
    return {"tables": len(out),
            "pairs": sum(t["count"] for t in out),
            "graded_entries": tot_tested,
            "agreeing": tot_agree,
            "agreement_pct": round(100.0 * tot_agree / max(1, tot_tested), 1)}


main()
