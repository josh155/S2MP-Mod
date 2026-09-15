#!/usr/bin/env python3
"""
s2_streamsync.py -- offline StreamSync timeline for a native S2 .demo.

WHY THIS EXISTS
---------------
The local viewmodel appears at a FIXED moment in every playback of a given demo
(egyptbots ~+40.8 s, gibraltar ~+68.1 s), identically on builds that predate any
of our asset changes. A fixed timestamp means the trigger is an event in the
DEMO STREAM, not a streaming race or an asset-residency accident.

Candidate trigger: the binary server command with opcode 98 ==
CL_StreamSync_ParseServerLoadRequest (IDA 0x193B20). Opcode is derived in
CG_ExecuteBinaryServerCommand (IDA 0x431B20) as `firstPayloadByte - 45`, so
0x62 == 98.

This tool extracts every binary command with the snapshot serverTime of the
message carrying it, prints the timeline, finds the longest StreamSync silence,
and marks where the gun is predicted to appear. If that prediction lands on the
measured pop for two independent demos, the mechanism is proven -- offline.

    python tools/s2_streamsync.py <demo.demo> [--pop-ms N] [--all-opcodes]

--pop-ms is the MEASURED viewmodel pop, in ms after CA_ACTIVE, so the tool can
print it alongside its own prediction rather than being graded by hand.

Reader model is s2_svc_walk's, which is bit-exact against the live engine.
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s2_huffman as huff
import s2_svc_walk
from s2_svc_walk import Msg, decode_payload

# CG_ExecuteBinaryServerCommand switches on (firstPayloadByte - 45), and the
# StreamSync arm is case 53. So the RAW byte is 98 (0x62) and the SWITCH value
# is 53; this tool works in switch space.
STREAMSYNC_OPCODE = 53
OPCODE_BIAS = 45


def scan(path):
    """[(serverTime, msgIndex, opcode, length, payload)] for binary commands,
    plus the list of snapshot serverTimes."""
    if s2_svc_walk.decode_payload.table is None:
        s2_svc_walk.decode_payload.table = huff.load_table()
    blob = open(path, "rb").read()
    cmds, snaps = [], []
    pending = []            # commands seen before this message's snapshot
    for idx, _off, _oseq, payload in huff.packets(blob):
        body, _z = decode_payload(payload)
        if not body:
            continue
        m = Msg(body)
        guard = 0
        while guard < 512:
            guard += 1
            if m.readcount >= len(body) and (m.bitpos >> 3) >= len(body):
                break
            op = m.read_bits(4)
            if op == 7:
                break
            if op == 2:
                m.read_long()
                m.read_string(1024)
            elif op == 3:
                seq = m.read_long()
                ln = m.read_short()
                if ln <= 0 or ln > 0x3FC:
                    break
                data = m._take(ln)
                # payload[0] is the opcode byte the engine biases by 45
                opc = (data[0] - OPCODE_BIAS) & 0xFF if data else -1
                pending.append((idx, seq, opc, ln, data))
            elif op == 4:
                cnt = m.read_byte()
                if cnt >= 0x90:
                    break
                for _ in range(cnt):
                    m.read_int64()
                    m.read_short()
            elif op == 5:
                m.read_string(64)
                m._take(5760)
            elif op == 6:
                st = m.read_long()
                snaps.append(st)
                for c in pending:
                    cmds.append((st,) + c)
                pending = []
                break                       # rest is delta-encoded
            elif op == 0:
                break
            else:
                break
            if m.overflow:
                break
    # commands after the last snapshot inherit the last known time
    if pending and snaps:
        for c in pending:
            cmds.append((snaps[-1],) + c)
    return cmds, snaps


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("demo")
    ap.add_argument("--pop-ms", type=int, default=None,
                    help="measured viewmodel pop, ms after CA_ACTIVE")
    ap.add_argument("--all-opcodes", action="store_true")
    a = ap.parse_args()

    cmds, snaps = scan(a.demo)
    if not snaps:
        print("no snapshots decoded -- wrong file?")
        return 1
    t0 = snaps[0]
    print("=" * 76)
    print("%s" % os.path.basename(a.demo))
    print("  first snapshot serverTime = %d   (t0; all times below are relative)" % t0)
    print("  %d snapshots, %d binary commands" % (len(snaps), len(cmds)))

    if a.all_opcodes:
        from collections import Counter
        c = Counter(o for _st, _i, _s, o, _l, _d in cmds)
        print("\n  binary command opcodes: " +
              ", ".join("%d x%d" % (k, v) for k, v in sorted(c.items())))

    ss = [(st - t0, ln, data) for st, _i, _s, o, ln, data in cmds
          if o == STREAMSYNC_OPCODE]
    print("\n  StreamSync (opcode %d) commands: %d" % (STREAMSYNC_OPCODE, len(ss)))
    if not ss:
        print("  NONE -- this demo carries no StreamSync at all.")
        return 0

    print("\n  %-12s %-8s %s" % ("t (ms)", "bytes", "gap since previous"))
    prev = None
    gaps = []
    for t, ln, _d in ss:
        gap = "" if prev is None else "%+d ms" % (t - prev)
        if prev is not None:
            gaps.append((t - prev, t, ln))
        print("  %-12d %-8d %s" % (t, ln, gap))
        prev = t

    if gaps:
        big, at, ln = max(gaps)
        print("\n  LONGEST SILENCE: %d ms, broken by the %d-byte command at t=%d"
              % (big, ln, at))
        print("  " + "-" * 66)
        print("  >>> PREDICTED: THE GUN APPEARS HERE  ~t=%d ms  <<<" % at)
        print("  " + "-" * 66)
        if a.pop_ms is not None:
            d = a.pop_ms - at
            verdict = ("MATCH (within %d ms)" % abs(d)) if abs(d) <= 3000 \
                else "MISMATCH by %d ms -- prediction is wrong" % d
            print("  measured pop = %d ms   ->   %s" % (a.pop_ms, verdict))
    return 0


if __name__ == "__main__":
    sys.exit(main())
