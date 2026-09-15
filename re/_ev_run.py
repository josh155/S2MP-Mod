"""Locate an engine's EV_* event-name table (runs inside IDA).

Both CoD4 and MWR keep a contiguous array of event NAME strings for debug output
(CG_EntityEvent prints 'ent:%3i event:%3i params:%3i'). Finding that run of
"EV_..." strings, in address order, recovers the event ENUM - which is the
mapping key between the two engines' event channels.

Writes re/ev_enum_<tag>.json
"""
import json, os

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"


def main():
    import idautils, ida_bytes, ida_segment

    segs = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        segs.append((seg.start_ea, seg.end_ea))
    lo = min(a for a, _ in segs)
    hi = max(b for _, b in segs)

    out = []
    for a, b in segs:
        if b - a > 300 * 1024 * 1024:
            continue
        buf = ida_bytes.get_bytes(a, b - a) or b""
        start = 0
        while True:
            i = buf.find(b"EV_", start)
            if i < 0:
                break
            start = i + 1
            # must be the START of a NUL-terminated string
            if i > 0 and buf[i - 1] not in (0, 0x20):
                continue
            e = buf.find(b"\x00", i, min(len(buf), i + 80))
            if e < 0:
                continue
            s = buf[i:e]
            if not all(32 <= c < 127 for c in s):
                continue
            try:
                out.append((a + i, s.decode("ascii")))
            except Exception:
                pass

    out.sort()
    # group into contiguous runs (a table is a dense address run)
    runs, cur = [], []
    for addr, name in out:
        if cur and addr - (cur[-1][0] + len(cur[-1][1]) + 1) > 8:
            runs.append(cur)
            cur = []
        cur.append((addr, name))
    if cur:
        runs.append(cur)
    runs.sort(key=lambda r: -len(r))

    res = {"total_EV_strings": len(out),
           "runs": [{"start": hex(r[0][0]), "count": len(r),
                     "names": [n for _, n in r]} for r in runs[:4]]}
    with open(os.path.join(RE_DIR, "ev_enum_%s.json" % "mwr"), "w",
              encoding="utf-8") as f:
        json.dump(res, f, indent=1)
    return {"total": len(out),
            "biggest_runs": [(r["start"], r["count"]) for r in res["runs"]]}


main()
