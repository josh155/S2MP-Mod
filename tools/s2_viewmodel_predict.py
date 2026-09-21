#!/usr/bin/env python3
"""
s2_viewmodel_predict.py -- will the local viewmodel appear, and when? Offline.

Works on BOTH demo formats:
  * native engine demos   main/demo/*.demo
  * our custom container  demos/*.dm_s2

WHY THIS PREDICTS ANYTHING
--------------------------
Measured in game, the gun appears exactly when StreamSync list 8 gains a THIRD
entry. Two entries is a base pair every demo carries; the third is the local
player's weapon customization.

    egyptbots   list8 2 -> 3 at t=40550    gun observed 40780   (+230 ms)
    gibraltar   list8 2 -> 3 at t=66050    gun observed 68135   (+2085 ms)
    airship     list8 stays [9569, 198]         gun NEVER   (user-confirmed)
    dday        list8 stays [21234957, 308]     gun NEVER   (predicted)

The small positive delta is the streamer paging the textures in after the
request lands.

THREE MODES ARE REPORTED
  STOCK    what the engine does today: apply each command in order. This is what
           the timings above were measured against.
  REPLAY   our pre-scan fix: every recorded request is replayed at t=0, skipping
           any command whose list 8 would DROP an accumulated item (CommitNewSync
           Data diffs, so a naive replay ends in the demo's FINAL state and loses
           the item -- see s2_ss_decode.py).
  REQUEST  the direct fix: sub_196220(viewmodel, list 8, prio 127, tier 0, fb 5),
           the engine's own customization stream request, issued for the model
           the engine itself selected. Independent of demo contents, so it is the
           only mode that can help a demo that never requests the weapon at all.

    python tools/s2_viewmodel_predict.py [files...]        (defaults to all)
"""

import argparse
import glob
import os
import struct
import sys
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s2_huffman as huff
import s2_svc_walk
import s2_ss_decode as SS
from s2_svc_walk import Msg, decode_payload

NATIVE_DIR = r"E:/SteamLibrary/steamapps/common/Call of Duty WWII/main/demo"
CUSTOM_DIR = r"E:/SteamLibrary/steamapps/common/Call of Duty WWII/demos"

# Observed in game, for grading the predictions.
OBSERVED = {
    "egyptbots.demo": 40780,
    "gibraltar.demo": 68135,
    "airshipdemo.demo": None,      # user-confirmed: never
}


# --------------------------------------------------------------------------
#  .dm_s2 container -- TLV stream, network_data is id 2
# --------------------------------------------------------------------------
def iter_tlvs(blob):
    off, n = 0, len(blob)
    while off < n:
        head = blob[off]
        tlv_id = head & 0x1F
        if head & 0x80:
            if off + 2 > n:
                return
            size = blob[off + 1]
            body = off + 2
        else:
            if off + 5 > n:
                return
            size = struct.unpack_from("<I", blob, off + 1)[0]
            body = off + 5
        if body + size > n:
            return
        yield tlv_id, blob[body:body + size]
        if tlv_id == 31:
            return
        off = body + size


def custom_messages(path):
    """Decoded svc message bodies from a .dm_s2.

    network_data payload (demo_recording.cpp pack_network):
        [u32 seq][u32 flags: low31 = entry readcount, bit31 = useZlib][msg data]
    CL_ParseServerMessage resumes at that readcount, reads an int16 length and
    decodes from there -- the same shape as the native path.
    """
    blob = open(path, "rb").read()
    for tlv_id, payload in iter_tlvs(blob):
        if tlv_id != 2 or len(payload) < 8:
            continue
        flags = struct.unpack_from("<I", payload, 4)[0]
        rc = flags & 0x7FFFFFFF
        use_zlib = bool(flags >> 31)
        data = payload[8:]
        if rc + 2 > len(data):
            continue
        declared = struct.unpack_from("<h", data, rc)[0]
        if 0 < declared <= len(data) - rc - 2:
            body = data[rc + 2: rc + 2 + declared]
        else:
            body = data[rc:]
        if not body:
            continue
        if use_zlib:
            try:
                yield zlib.decompress(body)
            except zlib.error:
                continue
        else:
            out = huff.huff_decode(s2_svc_walk.decode_payload.table,
                                   body, len(body), 0x20000)
            if out:
                yield out


def native_messages(path):
    blob = open(path, "rb").read()
    for _i, _o, _s, payload in huff.packets(blob):
        body, _z = decode_payload(payload)
        if body:
            yield body


# --------------------------------------------------------------------------
#  Pull StreamSync commands + snapshot times out of decoded messages
# --------------------------------------------------------------------------
def streamsync_events(messages):
    """[(serverTime, payload)] plus the first snapshot time."""
    events, pending, t0, last = [], [], None, None
    for body in messages:
        m = Msg(body)
        for _ in range(512):
            if m.readcount >= len(body) and (m.bitpos >> 3) >= len(body):
                break
            op = m.read_bits(4)
            if op == 7:
                break
            if op == 2:
                m.read_long()
                m.read_string(1024)
            elif op == 3:
                m.read_long()
                ln = m.read_short()
                if ln <= 0 or ln > 0x3FC:
                    break
                d = m._take(ln)
                if d and d[0] == 98:
                    pending.append(d)
            elif op == 4:
                c = m.read_byte()
                if c >= 0x90:
                    break
                for _ in range(c):
                    m.read_int64()
                    m.read_short()
            elif op == 5:
                m.read_string(64)
                m._take(5760)
            elif op == 6:
                st = m.read_long()
                if t0 is None:
                    t0 = st
                last = st
                for d in pending:
                    events.append((st - t0, d))
                pending = []
                break
            elif op == 0:
                break
            else:
                break
            if m.overflow:
                break
    if pending and last is not None and t0 is not None:
        for d in pending:
            events.append((last - t0, d))
    return events


def list8_timeline(events):
    """[(t, list8 set)] as the engine would apply them, in order."""
    out, seen = [], set()
    for t, d in events:
        key = bytes(d)
        if key in seen:
            continue                      # retransmit of the same command
        seen.add(key)
        r = SS.best(d)
        if not r or not r["ok"] or 8 not in r["counts"]:
            continue
        out.append((t, [v for l, v in r["items"] if l == 8]))
    return out


def predict(path):
    name = os.path.basename(path)
    is_native = path.lower().endswith(".demo")
    msgs = native_messages(path) if is_native else custom_messages(path)
    events = streamsync_events(msgs)
    tl = list8_timeline(events)

    print("=" * 78)
    print("%s   [%s]" % (name, "native" if is_native else "custom .dm_s2"))
    if not events:
        print("   no StreamSync commands at all")
    print("   %d StreamSync command(s), %d list-8 state change(s)"
          % (len(events), len(tl)))

    # --- STOCK: first moment list 8 holds more than the 2-entry base pair
    stock = None
    for t, l8 in tl:
        if len(l8) >= 3:
            stock = (t, l8)
            break
    if stock:
        print("   STOCK   : gun at ~%d ms   (list8 reaches %d entries: %s)"
              % (stock[0], len(stock[1]), stock[1]))
    else:
        biggest = max((len(l8) for _t, l8 in tl), default=0)
        print("   STOCK   : NEVER -- list 8 never exceeds %d entries; the demo "
              "never requests the local weapon" % biggest)

    # --- REPLAY: monotone-list8 policy applied up front
    acc = []
    for _t, l8 in tl:
        if all(v in l8 for v in acc):
            for v in l8:
                if v not in acc:
                    acc.append(v)
    if len(acc) >= 3:
        print("   REPLAY  : gun at ~0 ms      (accumulates %d entries: %s)"
              % (len(acc), acc))
    else:
        print("   REPLAY  : NEVER -- accumulates only %d entr%s (%s); there is "
              "nothing in this demo to replay"
              % (len(acc), "y" if len(acc) == 1 else "ies", acc))

    # --- REQUEST: independent of demo contents
    print("   REQUEST : gun at ~0 ms      (direct sub_196220 on the viewmodel; "
          "does not depend on demo contents)")

    if name in OBSERVED:
        obs = OBSERVED[name]
        exp = stock[0] if stock else None
        if obs is None and exp is None:
            verdict = "MATCH (both say never)"
        elif obs is not None and exp is not None:
            verdict = ("MATCH (%+d ms)" % (obs - exp)) if abs(obs - exp) <= 3000 \
                else "MISMATCH by %d ms" % (obs - exp)
        else:
            verdict = "MISMATCH (observed %s, predicted %s)" % (obs, exp)
        print("   observed in game: %s   ->   STOCK prediction %s"
              % ("never" if obs is None else "%d ms" % obs, verdict))
    return stock, acc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("files", nargs="*")
    a = ap.parse_args()
    if s2_svc_walk.decode_payload.table is None:
        s2_svc_walk.decode_payload.table = huff.load_table()
    files = a.files
    if not files:
        files = sorted(glob.glob(os.path.join(NATIVE_DIR, "*.demo"))) + \
                sorted(glob.glob(os.path.join(CUSTOM_DIR, "*.dm_s2")))
    for f in files:
        try:
            predict(f)
        except Exception as e:
            print("=" * 78)
            print("%s\n   ERROR: %s" % (os.path.basename(f), e))
    return 0


if __name__ == "__main__":
    sys.exit(main())
