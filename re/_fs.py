"""Find strings by substring and report their referencing functions (inside IDA).

Set [b"pointsPopup",b"PointsPopup",b"earnedXp",b"scoreEvent",b"splashTable",b"ui_player_splash",b"MP_XP",b"xpPopup",b"ScoreEvent",b"scoreInfo"] (list of bytes) before exec.
"""
import json, os

OUT = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\find_str_out.json"


def main():
    import idautils, ida_bytes, ida_segment, ida_funcs, ida_name

    segs = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        segs.append((seg.start_ea, seg.end_ea))

    hits = []
    seen = set()
    for a, b in segs:
        if b - a > 300 * 1024 * 1024:
            continue
        buf = ida_bytes.get_bytes(a, b - a) or b""
        for nd in [b"pointsPopup",b"PointsPopup",b"earnedXp",b"scoreEvent",b"splashTable",b"ui_player_splash",b"MP_XP",b"xpPopup",b"ScoreEvent",b"scoreInfo"]:
            start = 0
            while True:
                i = buf.find(nd, start)
                if i < 0:
                    break
                start = i + 1
                s0 = buf.rfind(b"\x00", max(0, i - 160), i) + 1
                s1 = buf.find(b"\x00", i, min(len(buf), i + 160))
                if s1 < 0:
                    continue
                try:
                    text = buf[s0:s1].decode("ascii")
                except Exception:
                    continue
                if not text or text in seen or len(text) > 150:
                    continue
                seen.add(text)
                addr = a + s0
                refs = []
                for xr in idautils.XrefsTo(addr, 0):
                    f = ida_funcs.get_func(xr.frm)
                    if f:
                        refs.append(ida_name.get_name(f.start_ea))
                hits.append({"addr": hex(addr), "text": text,
                             "refs": sorted(set(refs))[:5]})
    with open(OUT, "w", encoding="utf-8") as f:
        json.dump(hits, f, indent=1)
    return len(hits)


main()
