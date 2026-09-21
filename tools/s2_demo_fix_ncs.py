#!/usr/bin/env python3
"""
s2_demo_fix_ncs.py -- repair a PUBLIC-match .demo so it plays.

THE DEFECT (proven 2026-08-09, same-map controlled pair on mp_forest_01)
-----------------------------------------------------------------------
    x0147 (PUBLIC) stalls at connstate 9 (PRIMED, never ACTIVE)
    x0335 (LOCAL)  plays
    p3 = public file + LOCAL FOOTER                       -> PLAYS
    p6 = public file + ONLY ncs type 21 spliced in        -> PLAYS

Everything else byte-identical, same map, same build, same recorder. Netconststring
type 21 -- the GSC script-string table -- is causal, not merely correlated.

WHY a public match lacks it: `sub_5DC650`, the footer NCS writer, dumps a REGISTRY of
registered (type, index) pairs. In a local match the client is the server and runs
GSC, so script strings are registered and land in the footer. In a public match
nothing registers them, yet the recorded snapshots still carry type-21 indices, so
playback cannot resolve them.

Why a runtime NetConstStrings_Load on the PLAYBACK side does not fix it: there are
two separate storages, and only the footer fills the one playback needs --

    footer install        -> pointer table  qword_A60D180 + 0x20000 + 8*index
                             (index -> string)          <- what playback resolves through
    NetConstStrings_Load  -> block lists    qword_5A00C30[2*type]
                             (name -> index)            <- all the reload restored

THE TABLE IS GLOBAL, so any local recording is a valid donor
------------------------------------------------------------
type 21 was compared across dday / airshipdemo / egyptbots / gibraltar: all 396
entries and byte-identical listings. It is a GSC string table, not map content. So a
donor recorded on ANY map repairs a demo from ANY other map.

    python tools/s2_demo_fix_ncs.py <public.demo> <local_donor.demo> [out.demo]

The mod also fixes this at the source (it runs NetConstStrings_Load at record time so
the footer captures type 21). This tool is for demos already on disk.
"""

import argparse
import os
import struct
import sys

HEADER_SIZE = 79384
NCS_MAGIC = b"\x11\xd3\x01\x00"          # u16 0xD311, u16 version 1


def split(path):
    b = open(path, "rb").read()
    if len(b) < HEADER_SIZE + 8:
        raise SystemExit("%s: too small to be a .demo" % path)
    fsz = struct.unpack_from("<I", b, len(b) - 8)[0]
    fstart = len(b) - 8 - fsz
    return b[:HEADER_SIZE], b[HEADER_SIZE:fstart], b[fstart:len(b) - 8]


def ncs_split(fb):
    """footer body -> (pre, counts[26], [(type, raw_entries)], tail)

    Layout, from CL_Demo_ReadNetConstStringTable @0x5DC0E0:
        u16 magic 0xD311 | u16 version 1 | u32 total
        26 x u32 per-type counts
        total x { u16 index, u16 length, length bytes }   -- grouped in type order
    """
    at = fb.find(NCS_MAGIC)
    if at < 0:
        raise SystemExit("no NetConstStrings block in this footer")
    counts = [struct.unpack_from("<I", fb, at + 8 + 4 * i)[0] for i in range(26)]
    pos = at + 8 + 26 * 4
    groups = []
    for _t, n in enumerate(counts):
        start = pos
        for _ in range(n):
            ln = struct.unpack_from("<H", fb, pos + 2)[0]
            pos += 4 + ln
        groups.append(fb[start:pos])
    return fb[:at], counts, groups, fb[pos:]


def ncs_build(pre, counts, groups, tail):
    out = bytearray(NCS_MAGIC)
    out += struct.pack("<I", sum(counts))
    for c in counts:
        out += struct.pack("<I", c)
    for raw in groups:
        out += raw
    return pre + bytes(out) + tail


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("demo", help="the public-match .demo to repair")
    ap.add_argument("donor", help="any LOCAL/private .demo carrying type 21")
    ap.add_argument("out", nargs="?", help="output (default: <demo>.fixed.demo)")
    ap.add_argument("--type", type=int, default=21,
                    help="netconststring type to splice (default 21)")
    a = ap.parse_args()

    hdr, body, fb = split(a.demo)
    _dh, _db, dfb = split(a.donor)

    pre, counts, groups, tail = ncs_split(fb)
    _dpre, dcounts, dgroups, _dtail = ncs_split(dfb)

    t = a.type
    if not dcounts[t]:
        raise SystemExit("donor %s has no type %d entries" % (os.path.basename(a.donor), t))
    if counts[t]:
        print("%s already has %d type-%d entries -- nothing to do"
              % (os.path.basename(a.demo), counts[t], t))
        return 0

    print("%-28s type %d: %d  ->  %d   (total %d -> %d)"
          % (os.path.basename(a.demo), t, counts[t], dcounts[t],
             sum(counts), sum(counts) - counts[t] + dcounts[t]))

    counts[t] = dcounts[t]
    groups[t] = dgroups[t]
    new_fb = ncs_build(pre, counts, groups, tail)

    out = a.out or (os.path.splitext(a.demo)[0] + ".fixed.demo")
    with open(out, "wb") as f:
        f.write(hdr)
        f.write(body)
        f.write(new_fb)
        f.write(struct.pack("<II", len(new_fb), 29))   # footer size + magic
    print("wrote %s  (%d bytes)" % (out, os.path.getsize(out)))
    print("validate with:  python tools/s2_demo_read.py \"%s\"" % out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
