#!/usr/bin/env python3
"""
s2_gamestate.py -- decode a native .demo's gamestate configstrings, offline.

Applies the PROVEN one-bit fix: CL_Demo_WriteGameState @0x91D190 writes ONE bit
where CL_ParseGamestate @0x462B00 reads TWO, so the reader here consumes one.
That is the defect the runtime MSG_ReadBit hook corrects; modelling it the same
way makes this tool agree with the patched engine.

Field order, transcribed from the disassembly of CL_ParseGamestate (not from the
decompiler's statement order):
    MSG_ReadLong    serverCommandSequence
    MSG_ReadString  mapname     (dest size 32)
    MSG_ReadLong
    MSG_ReadString  gametype    (dest size 32)
    MSG_ReadBit     v9          <-- the writer emits only THIS one
    [MSG_ReadBit    v10]        <-- never written; we skip it
    MSG_ReadLong    v11
    MSG_ReadBits(4) v12         == 1 -> configstrings follow, == 7 -> EOF
    MSG_ReadShort   count
    per entry: 1 bit set -> index = last+1; clear -> index = MSG_ReadBits(13)
               then a NUL-terminated string

    python tools/s2_gamestate.py <demo.demo> [--grep TEXT] [--index N]
"""
import argparse, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s2_huffman as huff, s2_svc_walk
from s2_svc_walk import Msg, decode_payload


def parse(path):
    if s2_svc_walk.decode_payload.table is None:
        s2_svc_walk.decode_payload.table = huff.load_table()
    blob = open(path, "rb").read()
    for _i, _o, _s, payload in huff.packets(blob):
        body, _z = decode_payload(payload)
        if not body:
            continue
        m = Msg(body)
        if m.read_bits(4) != 0:
            continue                        # not the gamestate packet
        cmdseq = m.read_long()
        mapname = m.read_string(32).decode("latin1", "replace")
        m.read_long()
        gametype = m.read_string(32).decode("latin1", "replace")
        m.read_bit()                        # v9  (ONE bit -- the fix)
        v11 = m.read_long()
        v12 = m.read_bits(4)
        if v12 != 1:
            return dict(err="v12=%d (expected 1)" % v12, map=mapname)
        count = m.read_short() & 0xFFFF
        out, last = [], -1
        for _ in range(count):
            if m.read_bit():
                idx = last + 1
            else:
                idx = m.read_bits(13)
            s = m.read_string(4096)
            out.append((idx, s.decode("latin1", "replace")))
            last = idx
        return dict(map=mapname, gametype=gametype, cmdseq=cmdseq, v11=v11,
                    count=count, cs=out)
    return dict(err="no gamestate packet found")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("demo"); ap.add_argument("--grep"); ap.add_argument("--index", type=int)
    ap.add_argument("--range", nargs=2, type=int)
    a = ap.parse_args()
    g = parse(a.demo)
    print("=" * 76)
    print(os.path.basename(a.demo))
    if "err" in g:
        print("  ERROR:", g["err"]); return 1
    print("  map=%s gametype=%s cmdSeq=%d  %d configstrings"
          % (g["map"], g["gametype"], g["cmdseq"], g["count"]))
    for idx, s in g["cs"]:
        if a.index is not None and idx != a.index: continue
        if a.range and not (a.range[0] <= idx <= a.range[1]): continue
        if a.grep and a.grep.lower() not in s.lower(): continue
        printable = "".join(c if 32 <= ord(c) < 127 else "." for c in s)
        print("  cs[%-5d] len=%-5d %s" % (idx, len(s), printable[:200]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
