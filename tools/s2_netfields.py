#!/usr/bin/env python3
"""
s2_netfields.py -- extract S2's netfield tables OFFLINE from s2x_dump.exe.

These are the tables the snapshot delta codec walks. They are the foundation for
simulating a snapshot decode offline, which is what is needed to explain
publicmatch's Com_Error "4780" (MSG_ReadMonotonicDeltaIndex: the delta field
index failed to increase, i.e. reader and data disagree on FIELD LAYOUT).

HOW THEY WERE FOUND (all PROVEN, 2026-08-08)
    CG_InterpolatePlayerState_S2 @ IDA 0x668A90 -- the playerstate delta reader,
    called from CL_ParseSnapshot -- loads `off_F931B0` and indexes it as
        mov rax, cs:off_F931B0
        mov r12, [rax+60h]        ; a table pointer
        mov r13, [rax+70h]        ; a table pointer
        movsxd rdi, dword ptr [rax+78h]   ; its entry count
    off_F931B0 holds 0xF93120, and that object is a plain array of
    (qword tablePtr, qword count) pairs -- eight of them.

    RECORD STRIDE IS 10 BYTES, and that is not a guess: every table ends exactly
    where the next begins, to within the alignment padding, for all eight:
        0xF96420 145*10 = 1450 -> ends 0xF969CA, next 0xF969D0   (6 pad)
        0xF969D0  65*10 =  650 -> ends 0xF96C5A, next 0xF96C60   (6 pad)
        0xF96C60 402*10 = 4020 -> ends 0xF97C14, next 0xF97C20  (12 pad)
        0xF97C20  10*10 =  100 -> ends 0xF97C84, next 0xF97C90  (12 pad)
        0xF97C90  48*10 =  480 -> ends 0xF97E70, next 0xF97E70   (0 pad, exact)
        0xF97E70  19*10 =  190 -> ends 0xF97F2E, next 0xF97F30   (2 pad)
        0xF97F30   5*10 =   50 -> ends 0xF97F62, next 0xF97F70  (14 pad)
    Eight independent confirmations of the same stride.

RECORD LAYOUT (5 x u16). Field NAMES are stripped from the ship build, so these
are anonymous -- unlike MWR PS4, whose debug build names all of its netfields.
    +0 u16  offset   byte offset of the field within the struct
    +2 i16  size     observed: 1, 4, -4 (0xFFFC). Signedness/kind marker.
    +4 i16  bits     observed: 1, 2, 8, 16, 32, and NEGATIVE values
                     (-97, -100, -92, -91, -90, -75, -16). In this engine family
                     a negative `bits` selects a special encoding rather than a
                     plain N-bit integer.
    +6 u16  x        nonzero on some entries (seen 0x10)
    +8 u16  y        nonzero on some entries (seen 0x01)
The meaning of `size`, `x` and `y`, and the exact per-encoding bit cost, are
NOT yet established -- see the WHAT REMAINS note at the bottom.

USAGE
    python tools/s2_netfields.py                    summary of all 8 tables
    python tools/s2_netfields.py --table 2          dump one table
    python tools/s2_netfields.py --histogram        bits/size value census
"""

import argparse
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s2_huffman as huff

# ONE flat array of (tablePtr, count) pairs at IDA 0xF92F90, 33 entries, stride 16.
#
# CORRECTION to a first reading: 0xF93120 is NOT a separate descriptor. It is
# &array[25] -- 0xF92F90 + 16*25 = 0xF93120 exactly. Different subsystems simply
# hold pointers to different BASES inside the one array, which is why
# CG_InterpolatePlayerState_S2 loads off_F931B0 (= &array[25]) and then indexes
# [rax+60h] (= array[31]) and [rax+70h]/[rax+78h] (= array[32], count 5).
#
# [0..24] are per-ENTITY-TYPE field lists; [25..32] are the whole-struct lists.
DESCRIPTOR = 0xF92F90
DESCRIPTOR_COUNT = 33
PLAYERSTATE_BASE = 0xF93120     # &array[25]; what off_F931B0 holds

TABLES = [
    (0xF934F0, 68), (0xF93A60, 81), (0xF93DA0, 31), (0xF941E0, 69),
    (0xF95290, 68), (0xF96170, 68), (0xF934F0, 68), (0xF95540, 87),
    (0xF958B0, 17), (0xF95960, 68), (0xF95C10, 68), (0xF95EC0, 68),
    (0xF934F0, 68), (0xF94FD0, 69), (0xF94A60, 69), (0xF94D20, 68),
    (0xF947A0, 69), (0xF934F0, 68), (0xF934F0, 68), (0xF934F0, 68),
    (0xF93F10, 71), (0xF934F0, 68), (0xF944A0, 76), (0xF934F0, 68),
    (0xF937A0, 70),
    # ---- from here the whole-struct lists; [25] is what off_F931B0 points at
    (0xF96420, 145),   # [25] max offset 0x145  -- entityState-sized
    (0xF969D0, 65),    # [26]
    (0xF96C60, 402),   # [27] max offset 0x593C -- playerState-sized
    (0xF97C20, 10),    # [28]
    (0xF97C90, 48),    # [29]
    (0xF97E70, 19),    # [30]
    (0xF934F0, 68),    # [31] = [rax+60h] from the playerstate base
    (0xF97F30, 5),     # [32] = [rax+70h]/[rax+78h] from the playerstate base
]

STRIDE = 10


def read_table(blob, rva, count):
    off = huff.rva_to_file_offset(blob, rva)
    if off is None:
        raise SystemExit("could not map RVA 0x%X to a file offset" % rva)
    out = []
    for i in range(count):
        rec = blob[off + i * STRIDE: off + (i + 1) * STRIDE]
        if len(rec) < STRIDE:
            break
        o, size, bits, x, y = struct.unpack("<HhhHH", rec)
        out.append(dict(index=i, offset=o, size=size, bits=bits, x=x, y=y))
    return out


def load_all():
    # The RETAIL exe is Arxan-packed and its on-disk bytes do not match memory;
    # the tables must come from s2x_dump.exe, the process dump the IDB is built
    # from. s2_huffman learned this the hard way (see its --selftest).
    blob = open(huff.DUMP, "rb").read()
    return [(rva, cnt, read_table(blob, rva, cnt)) for rva, cnt in TABLES]


def index_width(count):
    """Bits used to index a list of `count` fields.

    MW3's MSG_ReadDeltaFields @0x36DF80 computes `32 - CLZ(numFields)`, i.e.
    count.bit_length(). The SAME width is used for the initial lastChangedField
    read and for every index read, so a wrong count desynchronises the whole
    field loop -- which is what S2's Com_Error "4780" reports.
    """
    return count.bit_length() if count > 0 else 0


def summarise(tables):
    print("S2 netfield lists -- one flat array @ IDA 0x%X, %d entries, record stride %d"
          % (DESCRIPTOR, DESCRIPTOR_COUNT, STRIDE))
    print("off_F931B0 holds 0x%X == &array[25]\n" % PLAYERSTATE_BASE)
    print("%-4s %-12s %-7s %-10s %-6s %s"
          % ("idx", "rva", "entries", "maxOffset", "width", "role"))
    for i, (rva, cnt, recs) in enumerate(tables):
        if not recs:
            print("%-4d 0x%-10X %-7d  <unreadable>" % (i, rva, cnt))
            continue
        mx = max(r["offset"] for r in recs)
        role = "per-entity-type" if i < 25 else "whole-struct"
        if i == 25:
            role += "  (entityState-sized)"
        if i == 27:
            role += "  (playerState-sized)"
        print("%-4d 0x%-10X %-7d 0x%-8X %-6d %s"
              % (i, rva, cnt, mx, index_width(cnt), role))

    from collections import Counter
    widths = Counter(index_width(c) for _, c, _ in
                     [(r, c, x) for r, c, x in tables])
    print("\nindex widths in play: %s"
          % ", ".join("%d bits x%d lists" % (w, n) for w, n in sorted(widths.items())))
    print("Per-entity-type lists are mostly 7 bits (68-87 fields) but TWO are 5 bits")
    print("(31 and 17 fields). Reading an entity with the wrong type therefore shifts")
    print("every subsequent index by two bits -- exactly the 4780 signature.")


def dump(tables, which, limit):
    rva, cnt, recs = tables[which]
    print("table %d @ IDA 0x%X, %d entries" % (which, rva, cnt))
    print("%-5s %-8s %-6s %-6s %-6s %s" % ("i", "offset", "size", "bits", "x", "y"))
    for r in recs[:limit]:
        print("%-5d 0x%-6X %-6d %-6d %-6d %d"
              % (r["index"], r["offset"], r["size"], r["bits"], r["x"], r["y"]))
    if len(recs) > limit:
        print("... %d more (use --limit)" % (len(recs) - limit))


def histogram(tables):
    from collections import Counter
    cb, cs, cxy = Counter(), Counter(), Counter()
    for _, _, recs in tables:
        for r in recs:
            cb[r["bits"]] += 1
            cs[r["size"]] += 1
            cxy[(r["x"], r["y"])] += 1
    print("bits values (all tables):")
    for v, n in sorted(cb.items()):
        note = "  <- negative: special encoding" if v < 0 else ""
        print("   %6d  x%d%s" % (v, n, note))
    print("\nsize values:")
    for v, n in sorted(cs.items()):
        print("   %6d  x%d" % (v, n))
    print("\n(x, y) pairs:")
    for v, n in sorted(cxy.items()):
        print("   %-12s x%d" % (str(v), n))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--table", type=int, help="dump one table by index 0-7")
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--histogram", action="store_true")
    args = ap.parse_args()

    tables = load_all()
    if args.table is not None:
        dump(tables, args.table, args.limit)
    elif args.histogram:
        histogram(tables)
    else:
        summarise(tables)
    return 0


if __name__ == "__main__":
    sys.exit(main())
