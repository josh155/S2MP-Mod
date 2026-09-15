"""RUNS INSIDE IDA (MWR-PS4). Enumerate every place MAX_CLIENTS bounds something.

MWR-PS4 is a DEBUG build, so every bounds check is annotated with an assert that
NAMES the constant and carries the source file and line. That assert set is an
authoritative inventory of "everywhere the 18-client cap bites" - far better than
hunting for the literal 18.

Writes re/mwr_client_sites.json.
"""
import json, os, re

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"


def main():
    import idautils, ida_bytes, ida_segment, ida_funcs, ida_name, idc

    NEEDLES = [b"MAX_CLIENTS", b"MAX_AGENTS", b"MAX_GENTITIES", b"MAX_CLIENT_NUM",
               b"MAX_LOCALCLIENTS", b"MAX_SPLITSCREEN", b"MAX_PARTY_CLIENT_COUNT",
               b"MAX_SNAPSHOT_ENTITIES", b"MAX_PARSE_ENTITIES", b"MAX_HUDELEMS",
               b"MAX_WEAPONS", b"MAX_CONFIGSTRINGS", b"MAX_SCOREBOARD"]

    segs = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        segs.append((seg.start_ea, seg.end_ea))
    lo = min(a for a, _ in segs)
    hi = max(b for _, b in segs)
    buf = ida_bytes.get_bytes(lo, hi - lo) or b""

    # assert text -> referencing functions, plus source file/line when present
    sites = []
    for needle in NEEDLES:
        start = 0
        while True:
            i = buf.find(needle, start)
            if i < 0:
                break
            start = i + 1
            s0 = buf.rfind(b"\x00", max(0, i - 250), i) + 1
            s1 = buf.find(b"\x00", i, min(len(buf), i + 250))
            if s1 < 0:
                continue
            try:
                text = buf[s0:s1].decode("ascii")
            except Exception:
                continue
            addr = lo + s0
            refs = []
            for xr in idautils.XrefsTo(addr, 0):
                f = ida_funcs.get_func(xr.frm)
                if not f:
                    continue
                fname = ida_name.get_name(f.start_ea)
                # MyAssertHandler(file, line, ...) - recover file+line from the
                # nearby constant loads
                src, line = "", 0
                ea = xr.frm
                for _ in range(14):
                    ea = idc.prev_head(ea, f.start_ea)
                    if ea == idc.BADADDR or ea < f.start_ea:
                        break
                    for k in (0, 1):
                        v = idc.get_operand_value(ea, k)
                        if lo <= v < hi:
                            e = buf.find(b"\x00", v - lo, v - lo + 200)
                            if e > 0:
                                try:
                                    t = buf[v - lo:e].decode("ascii")
                                except Exception:
                                    continue
                                if "code_source" in t and t.endswith(".cpp"):
                                    src = t
                        elif 100 < v < 100000 and not line:
                            line = v
                refs.append({"func": fname, "ea": hex(f.start_ea),
                             "src": src, "line": line})
            if refs:
                sites.append({"const": needle.decode(), "text": text,
                              "refs": refs})

    # collapse by (function, constant)
    byfunc = {}
    for s in sites:
        for r in s["refs"]:
            k = (r["func"], s["const"])
            e = byfunc.setdefault(k, {"func": r["func"], "ea": r["ea"],
                                      "const": s["const"], "src": r["src"],
                                      "checks": []})
            t = s["text"].split("\n")[0]
            if t not in e["checks"]:
                e["checks"].append(t)
            if r["src"] and not e["src"]:
                e["src"] = r["src"]

    out = sorted(byfunc.values(), key=lambda e: (e["const"], e["func"]))
    json.dump(out, open(os.path.join(RE_DIR, "mwr_client_sites.json"), "w",
                        encoding="utf-8"))

    from collections import Counter
    byconst = Counter(e["const"] for e in out)
    bysrc = Counter(e["src"].split("\\")[-1] for e in out if e["src"])
    return {"sites": len(out), "by_const": dict(byconst),
            "top_files": bysrc.most_common(18)}


main()
