#!/usr/bin/env python3
"""
s2_svc_walk.py -- OFFLINE walk of the svc opcode stream inside a native .demo.

No game. Decodes every type-2/3 demo packet (zlib or Huffman, via s2_huffman),
then walks the server-message opcodes with a FAITHFUL model of S2's msg_t
reader, and prints the snapshot headers.

Built to answer one question: why does publicmatch die with Com_Error "4780"
(MSG_ReadMonotonicDeltaIndex: the delta index failed to increase) while the
private demos do not.

THE READER MODEL IS NOT GUESSED -- it is transcribed from MSG_ReadBits
@ IDA 0xDC910:

    if bits == 32: return MSG_ReadLong(msg)       # byte path!
    if bits == 64: return MSG_ReadInt64(msg)
    rem = bitpos & 7
    if rem != 0:
        val   = data[bitpos >> 3] >> rem
        shift = 8 - rem
        if bits <= 8 - rem:
            bitpos += bits            # <-- readcount is NOT touched
            return val & mask
        bits -= 8 - rem
    # byte-aligned continuation
    bitpos = bits + 8 * readcount     # jump to the BYTE cursor
    consume whole bytes from readcount, updating readcount

So a 4-bit opcode read at a byte boundary consumes a whole byte and leaves
bitpos mid-byte; the NEXT 4-bit opcode is taken from the high nibble of that
same byte without moving the byte cursor. Byte reads (Long/Short/Byte/String)
advance readcount only and never touch bitpos. That mixed cursor is the whole
subtlety of this format, and it is what makes byte0 = 0x22 mean "two svc 2s"
and byte0 = 0x33 mean "two svc 3s".

USAGE
    python tools/s2_svc_walk.py <demo.demo> [--max N] [--packets N] [--verbose]
    python tools/s2_svc_walk.py <a.demo> <b.demo> ...      compare demos
"""

import argparse
import os
import struct
import sys
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s2_huffman as huff

# svc opcodes, from CL_ParseServerMessage_Internal @ IDA 0x4636E0
SVC = {
    0: "gamestate",
    2: "cmd_text",
    3: "cmd_binary",
    4: "table_upload",
    5: "matchdata",
    6: "snapshot",
    7: "EOF",
}


class Msg:
    """S2 msg_t reader. Byte cursor (+36) and bit cursor (+40) are separate."""

    def __init__(self, data):
        self.data = data
        self.cursize = len(data)
        self.readcount = 0
        self.bitpos = 0
        self.overflow = False

    def _byte(self, i):
        if i < 0 or i >= len(self.data):
            self.overflow = True
            return 0xFF
        return self.data[i]

    def read_bits(self, n):
        if n == 32:
            return self.read_long()
        if n == 64:
            return self.read_int64()
        mask = (1 << n) - 1
        bits = n
        val = 0
        shift = 0
        rem = self.bitpos & 7
        if rem:
            val = self._byte(self.bitpos >> 3) >> rem
            shift = 8 - rem
            if bits <= 8 - rem:
                self.bitpos += bits
                return val & mask
            bits -= 8 - rem
        rc = self.readcount
        self.bitpos = bits + 8 * rc
        while True:
            val |= self._byte(rc) << shift
            rc += 1
            bits -= 8
            if bits <= 0:
                self.readcount = rc
                return val & mask
            shift += 8

    def read_bit(self):
        return self.read_bits(1)

    def _take(self, n):
        i = self.readcount
        if i + n > len(self.data):
            self.overflow = True
            self.readcount = len(self.data)
            return b"\0" * n
        self.readcount = i + n
        return self.data[i:i + n]

    def read_byte(self):
        return self._take(1)[0]

    def read_short(self):
        return struct.unpack("<h", self._take(2))[0]

    def read_long(self):
        return struct.unpack("<i", self._take(4))[0]

    def read_int64(self):
        return struct.unpack("<q", self._take(8))[0]

    def read_string(self, limit=1024):
        out = bytearray()
        while len(out) < limit:
            if self.readcount >= len(self.data):
                self.overflow = True
                break
            c = self.data[self.readcount]
            self.readcount += 1
            if c == 0:
                break
            out.append(c)
        return bytes(out)

    def remaining(self):
        return len(self.data) - self.readcount


def decode_payload(payload):
    """(body, useZlib) for one type-2/3 packet payload, with the prefix repair.

    PROVEN discriminator: a body carries a 2-byte length prefix iff
        0 < int16(u16 @ payload+4) <= len(payload) - 6
    Packet 0 of every shipped demo fails that test -- the writer omitted the
    prefix -- which is the defect repair_gamestate_message() fixes at runtime.
    """
    if len(payload) < 6:
        return None, False
    seq = struct.unpack_from("<I", payload, 0)[0]
    use_zlib = bool(seq >> 31)
    declared = struct.unpack_from("<h", payload, 4)[0]
    if 0 < declared <= len(payload) - 6:
        body = payload[6:6 + declared]
    else:
        body = payload[4:]          # prefix-less: body starts right after the seq
    if use_zlib:
        try:
            return zlib.decompress(body), True
        except zlib.error:
            return None, True
    table = decode_payload.table
    return huff.huff_decode(table, body, len(body), 0x20000), False


decode_payload.table = None


def walk_message(body, verbose=False):
    """Walk svc opcodes. Returns (list of (op,name,detail), stop_reason)."""
    m = Msg(body)
    ops = []
    guard = 0
    while guard < 512:
        guard += 1
        if m.readcount >= len(body) and (m.bitpos >> 3) >= len(body):
            return ops, "ran off the end"
        op = m.read_bits(4)
        name = SVC.get(op, "UNKNOWN(%d)" % op)
        detail = ""

        if op == 7:
            ops.append((op, name, ""))
            return ops, "EOF"

        if op == 2:
            seq = m.read_long()
            s = m.read_string(1024)
            detail = "seq=%d %r" % (seq, s[:60].decode("latin1", "replace"))
        elif op == 3:
            seq = m.read_long()
            ln = m.read_short()
            if ln > 0x3FC or ln < 0:
                ops.append((op, name, "len=%d BAD (engine Com_Error 460)" % ln))
                return ops, "bad binary command length"
            m._take(ln)
            detail = "seq=%d len=%d" % (seq, ln)
        elif op == 4:
            cnt = m.read_byte()
            if cnt >= 0x90:
                ops.append((op, name, "count=%d BAD" % cnt))
                return ops, "bad table count"
            for _ in range(cnt):
                m.read_int64()
                m.read_short()
            detail = "count=%d" % cnt
        elif op == 5:
            s = m.read_string(64)
            m._take(5760)
            detail = "name=%r" % s[:32].decode("latin1", "replace")
        elif op == 6:
            # CL_ParseSnapshot's header, in order (IDA 0x464C00):
            #   long serverTime, long messageNum, byte deltaNum, byte snapFlags
            st = m.read_long()
            num = m.read_long()
            dn = m.read_byte()
            fl = m.read_byte()
            base = (num - dn) if dn else -1
            detail = ("serverTime=%d msgNum=%d deltaNum=%d -> baseline=%s "
                      "flags=0x%02X%s" %
                      (st, num, dn, base if dn else "NONE(full)", fl,
                       "  [bit7 = archived/alt path]" if fl & 0x80 else ""))
            ops.append((op, name, detail))
            # The rest is delta-encoded against the netfield tables, which we do
            # not model; CL_ParseSnapshot consumes the remainder anyway.
            return ops, "snapshot (rest is delta-encoded, stop)"
        elif op == 0:
            ops.append((op, name, "gamestate"))
            return ops, "gamestate (stop)"
        else:
            ops.append((op, name, "unknown opcode -- stream is out of phase"))
            return ops, "unknown opcode %d" % op

        ops.append((op, name, detail))
        if m.overflow:
            return ops, "msg overflow"
    return ops, "guard limit"


def report(path, max_msgs, verbose):
    blob = open(path, "rb").read()
    print("=" * 78)
    print("DEMO  %s" % os.path.basename(path))
    print("=" * 78)

    n_pkt = 0
    n_snap = 0
    shown = 0
    first_delta_seen = False
    for i, off, oseq, payload in huff.packets(blob):
        body, z = decode_payload(payload)
        n_pkt += 1
        if body is None:
            print("  pkt#%-5d DECODE FAILED (zlib=%s)" % (i, z))
            continue
        ops, why = walk_message(body, verbose)
        has_snap = any(o[0] == 6 for o in ops)
        if has_snap:
            n_snap += 1

        interesting = (shown < max_msgs) or ("out of phase" in why) or \
                      ("UNKNOWN" in why) or ("bad " in why)
        if interesting:
            shown += 1
            print("  pkt#%-5d @0x%-8X seq=%-6d %s %5dB  -> %s"
                  % (i, off, oseq, "zlib" if z else "huff", len(body), why))
            for op, name, detail in ops[:12]:
                print("        svc %-2d %-12s %s" % (op, name, detail))
            if len(ops) > 12:
                print("        ... %d more opcodes" % (len(ops) - 12))

        for op, name, detail in ops:
            if op == 6 and "deltaNum=" in detail and not first_delta_seen:
                if "deltaNum=0" not in detail:
                    first_delta_seen = True
                    print("  >>> FIRST DELTA-CODED SNAPSHOT: pkt#%d  %s" % (i, detail))

        if n_pkt > 4000:
            break

    print("  ---")
    print("  packets walked %d, messages containing a snapshot %d" % (n_pkt, n_snap))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("demos", nargs="+")
    ap.add_argument("--max", type=int, default=6,
                    help="how many messages to print per demo (default 6)")
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()

    decode_payload.table = huff.load_table()
    for d in args.demos:
        report(d, args.max, args.verbose)
    return 0


if __name__ == "__main__":
    sys.exit(main())
