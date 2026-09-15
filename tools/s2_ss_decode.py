#!/usr/bin/env python3
"""
s2_ss_decode.py -- decode StreamSync (opcode 53) command payloads, offline.

Transcribed from CL_StreamSync_ParseServerLoadRequest @0x193B20 and
CL_StreamSync_DataList_ParseRequiredData @0x6608D0.

ALIGNMENT (proven, not assumed): CG_ExecuteBinaryServerCommand does
    MSG_Init(msg, cmd+4, *(u16*)(cmd+2)); MSG_BeginReading(msg);
    opcode = (char)MSG_ReadByte(msg) - 45;
MSG_ReadByte advances ONLY the byte cursor; the inline bit reader then resyncs
bitpos = 8*readcount. So the bitstream starts at byte 1 of the payload.

PER-LIST TABLES, read from the IDB:
    index width  asc_B419D8 (u16[6]) = {9, 9, 8, 8, 12, 9}
    max count    word_B419F8(u16[6]) = {389, 150, 100, 120, 3000, 386}
Every width's range covers its max, which is the consistency check that the
char-typed array is really u16.

sub_B8C40() picks the count width and is a runtime value we cannot read offline,
so BOTH are tried and the one that consumes the payload cleanly wins. That is a
self-check, not a guess: a wrong model overruns or leaves bits.
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from s2_svc_walk import Msg

IDX_BITS = [9, 9, 8, 8, 12, 9]
MAX_CNT  = [389, 150, 100, 120, 3000, 386]


def count_bits(lst, wide):
    if lst >= 6:
        if lst == 6:
            return 9 if wide else 7
        return 3
    return 6 if wide else 5


def parse_list(m, lst, wide, items):
    n = m.read_bits(count_bits(lst, wide))
    for _ in range(n):
        if lst >= 6 and lst != 7:
            v = m.read_bits(10)
            if m.read_bit():
                v |= m.read_bits(6) << 10
                if m.read_bit():
                    v |= m.read_bits(6) << 16
                    if m.read_bit():
                        v |= m.read_bits(6) << 22
                        if m.read_bit():
                            m.read_bits(6)
                            if m.read_bit():
                                m.read_bits(6)
                                if m.read_bit():
                                    m.read_bits(6)
            m.read_bits(2); m.read_bits(3)
            items.append((lst, v))
        elif lst == 7:
            idx = m.read_bits(13) + 1
            m.read_bits(2); m.read_bits(2)
            items.append((lst, idx))
        else:
            idx = m.read_bits(IDX_BITS[lst]) + 1
            m.read_bits(2); m.read_bits(2)
            if lst == 1:
                m.read_bits(6)
            items.append((lst, idx))
            if idx > MAX_CNT[lst]:
                return False, n          # engine bails here
    return True, n


def decode(payload, wide):
    m = Msg(payload)
    op = (m.read_byte() - 45) & 0xFF
    if op != 53:
        return None
    items, counts, ok = [], {}, True
    for lst in range(9):
        if m.read_bit():
            good, n = parse_list(m, lst, wide, items)
            counts[lst] = n
            if not good:
                ok = False
                break
    used = max(m.bitpos, m.readcount * 8)
    total = len(payload) * 8
    return dict(ok=ok and not m.overflow, items=items, counts=counts,
                used=used, total=total, slack=total - used)


def best(payload):
    """Try both sub_B8C40 outcomes; keep the clean one."""
    cands = []
    for wide in (False, True):
        r = decode(payload, wide)
        if r:
            r["wide"] = wide
            cands.append(r)
    if not cands:
        return None
    good = [c for c in cands if c["ok"] and 0 <= c["slack"] < 8]
    return (good or sorted(cands, key=lambda c: abs(c["slack"])))[0]
