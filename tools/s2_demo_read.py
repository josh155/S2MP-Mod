#!/usr/bin/env python3
r"""Offline reader / failure locator for S2 (CoD:WWII) NATIVE .demo files.

Answers, without launching the game:
  * would the engine accept this demo, and if not, at exactly which byte
  * which packet the cursor was on when it died, and what came before it
  * for a given PARSER BUG, which byte the engine would choke on

NOT a reader for our own .dm_s2 container (see tools/dm_s2_scan.py).
Everything is derived from the native parser in the current S2 IDB, correlated
against the shipped demos in main\demo.

--------------------------------------------------------------------------
PROVEN — header (CL_Demo_Play_f)
    +0x00 u32 version      must be 29     -> clc+262760
    +0x04 u32 header size  must be 79384  -> clc+262764 ; BODY STARTS HERE
    +0x08 u32 demo client  -> Dvar_SetInt(cl_demo_client)  (0 private, 7 publicmatch)
    +0x18 u32 exe mode     must be 5      -> clc+262784, else Com_Error "428"

PROVEN — footer (CL_Demo_ReadFooter @ 0x918EC0)
    seek(-8): u32 size, u32 magic ; magic must equal header version
    seek(-8-size): body must start 29, 3984
    records [u16 id][u16 len][ascii], ids sequential from 0

PROVEN — body packets (CL_Demo_ReadDemoMessage @ 0x9188C0)
    one type byte; 0 ends the stream; 1..4 dispatch; anything else raises
    EXE_ERR_PROCESS_DEMO_FILE_FAILED.

    type 1 archive  (0x918640) sizes from `mov edx,N` before each read:
        4 idx | 12 | 12 | 4 | 4 | 4 | 12 | 4 gate
        if gate != 0:  4 | 2        <-- CONDITIONAL, the classic desync trap
        128 tail                    => 184 bytes, or 190 with the gate
    type 2 snapshot     (0x919510): 1 + 4 seq + 4 len + len
    type 3 alt snapshot (0x919510): 1 + 4 seq + 4 extra + 4 len + len
        len > 0x20000 -> engine Com_Error "430"
    type 4 commands     (0x918810): 1-byte sub-tags dispatched to sub_917570
        until a tag of 9 or 10. Sub-tag payload sizes NOT recovered, so this
        reader cannot skip a type-4 block. It does not occur in any shipped demo.

KEY RESULT: all five shipped demos walk to a clean end-of-stream. The shipped
files are not malformed. Therefore EXE_ERR_PROCESS_DEMO_FILE_FAILED in game is a
CURSOR problem — the reader consumed the wrong number of bytes for some packet —
not a file problem. Use --simulate to see which byte a given bug dies on.
--------------------------------------------------------------------------
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

DEMO_DIR = Path(r"E:\SteamLibrary\steamapps\common\Call of Duty WWII\main\demo")

EXPECT_VERSION = 29
EXPECT_HEADER_SIZE = 79384
EXPECT_FOOTER_TAG = 3984
MSG_MAX = 0x20000

PKT_NAMES = {0: "end", 1: "archive", 2: "snapshot", 3: "alt-snapshot", 4: "commands"}

# Deliberate mis-parses, to locate the byte a given bug would die on.
VARIANTS = {
    "correct": "the engine's actual rules",
    "archive-always-extra": "type 1 always reads the conditional 6 bytes",
    "archive-never-extra": "type 1 never reads the conditional 6 bytes",
    "archive-188": "type 1 sized as the 188-byte record instead of 184/190",
    "alt-as-snapshot": "type 3 parsed as type 2 (missing its extra 4-byte field)",
    "no-type-byte": "packet length counted without the leading type byte",
    "ignore-terminator": "does not stop on the type-0 end-of-stream marker",
}


class Failure(Exception):
    def __init__(self, msg: str, offset: int | None = None, byte: int | None = None):
        super().__init__(msg)
        self.offset, self.byte = offset, byte


def u32(b, o): return struct.unpack_from("<I", b, o)[0]
def i32(b, o): return struct.unpack_from("<i", b, o)[0]
def u16(b, o): return struct.unpack_from("<H", b, o)[0]


def hex_window(blob: bytes, centre: int, before: int = 16, after: int = 24) -> list[str]:
    start = max(0, centre - before)
    end = min(len(blob), centre + after)
    lines = []
    for row in range(start & ~0xF, end, 16):
        chunk = blob[row:min(row + 16, len(blob))]
        hx = " ".join(f"{c:02x}" for c in chunk)
        asc = "".join(chr(c) if 32 <= c < 127 else "." for c in chunk)
        mark = " <<<" if row <= centre < row + 16 else ""
        lines.append(f"    {row:08X}: {hx:<47}  {asc}{mark}")
    return lines


# --------------------------------------------------------------------------
# header / footer
# --------------------------------------------------------------------------

def check_header(blob, out):
    if len(blob) < 0x40:
        raise Failure(f"file shorter than header ({len(blob)} < 64)")
    ver, hsize, client, mode = u32(blob, 0), u32(blob, 4), u32(blob, 8), u32(blob, 0x18)
    out.append(f"  version {ver} | header size {hsize} | demo client {client} | exe mode {mode}")
    if ver != EXPECT_VERSION:
        raise Failure(f"rejected at +0x00: version {ver} != {EXPECT_VERSION}", 0, ver)
    if hsize != EXPECT_HEADER_SIZE:
        raise Failure(
            f"rejected at +0x04: header size {hsize} != {EXPECT_HEADER_SIZE} "
            "(recorded by a different build)", 4, hsize)
    if mode != 5:
        raise Failure(f'rejected at +0x18: exe mode {mode} != 5 -> Com_Error "428"', 0x18, mode)
    if client != 0:
        out.append(f"  NOTE recorded from client slot {client} (shipped private demos are 0)")
    return hsize


def check_footer(blob, out):
    size = u32(blob, len(blob) - 8)
    magic = u32(blob, len(blob) - 4)
    if magic != u32(blob, 0):
        raise Failure(f"CL_Demo_ReadFooter: trailing magic {magic} != header version",
                      len(blob) - 4, magic)
    body = len(blob) - 8 - size
    if body < 0x40 or body >= len(blob):
        raise Failure(f"CL_Demo_ReadFooter: footer size {size} puts body at {body}")
    t0, t1 = u32(blob, body), u32(blob, body + 4)
    if t0 != EXPECT_VERSION or t1 != EXPECT_FOOTER_TAG:
        raise Failure(f"CL_Demo_ReadFooter: body tags ({t0},{t1}) != (29,3984)", body, t0)
    out.append(f"  footer @0x{body:X} size {size}")
    return body


# --------------------------------------------------------------------------
# packet walk
# --------------------------------------------------------------------------

def packet_length(blob, pos, limit, variant="correct"):
    """Bytes consumed by the packet at `pos`, including its type byte."""
    t = blob[pos]
    p = pos + 1
    lead = 0 if variant == "no-type-byte" else 1

    if t == 0:
        return 1, "end-of-stream"

    if t == 1:
        fixed = 4 + 12 + 12 + 4 + 4 + 4 + 12          # 52, then the 4-byte gate
        gate_at = p + fixed
        if gate_at + 4 > limit:
            raise Failure("truncated inside archive before the gate field", gate_at)
        gate = i32(blob, gate_at)
        if variant == "archive-always-extra":
            extra = 6
        elif variant == "archive-never-extra":
            extra = 0
        else:
            extra = 6 if gate != 0 else 0
        total = lead + fixed + 4 + extra + 128
        if variant == "archive-188":
            total = lead + 4 + 188
        elif isinstance(variant, tuple) and variant[0] == "archive-size":
            total = variant[1]
        if pos + total > limit:
            raise Failure("truncated inside archive packet", pos)
        return total, f"archive gate={gate}{' +6' if extra else ''}"

    if t in (2, 3):
        hdr = 4 + (4 if (t == 3 and variant != "alt-as-snapshot") else 0)
        if p + hdr + 4 > limit:
            raise Failure("truncated inside snapshot header", p)
        seq = u32(blob, p)
        length = i32(blob, p + hdr)
        if length < 0 or length > MSG_MAX:
            raise Failure(
                f'snapshot length {length} > 0x{MSG_MAX:X} -> engine Com_Error "430"',
                p + hdr, length)
        total = lead + hdr + 4 + length
        if pos + total > limit:
            raise Failure(f"truncated snapshot payload (needs {length})", pos)
        return total, f"{PKT_NAMES[t]} seq={seq} len={length}"

    if t == 4:
        raise Failure(
            "type 4 (commands): sub-tag sizes live in sub_917570 and are not "
            "recovered, so this block cannot be skipped", pos, t)

    raise Failure(
        f"byte 0x{t:02X} ({t}) is not 0-4 -> EXE_ERR_PROCESS_DEMO_FILE_FAILED", pos, t)


def walk(blob, start, limit, variant="correct", keep_history=8):
    """Returns (counts, stop_offset, clean, failure, history)."""
    pos, counts, history = start, {}, []
    while pos < limit:
        try:
            size, desc = packet_length(blob, pos, limit, variant)
        except Failure as exc:
            return counts, pos, False, exc, history
        counts[blob[pos]] = counts.get(blob[pos], 0) + 1
        history.append((pos, blob[pos], size, desc))
        if len(history) > keep_history:
            history.pop(0)
        if blob[pos] == 0 and variant != "ignore-terminator":
            # A real end-of-stream sits immediately before the footer. A 0x00 found
            # anywhere earlier means the cursor drifted onto a zero byte inside a
            # payload — that is a desync, not a clean finish.
            if pos >= limit - 1:
                return counts, pos, True, None, history
            return counts, pos, False, Failure(
                f"hit a 0x00 byte at 0x{pos:X}, but the stream should not end until "
                f"0x{limit - 1:X} — cursor has drifted into a payload", pos, 0), history
        pos += size
    return counts, pos, True, None, history


# NetConstStrings type names, in enum order, decoded from the S2 range table at
# 0xB2E590 plus the type-name blob at 0xB75600. Only a few are firmly identified.
NCS_TYPE_HINT = {0: "models(2048)", 5: "localization", 18: "[315,570)", 24: "[10,138)"}


def parse_netconststrings(blob, footer, out, list_type):
    """Parse the footer's NetConstStrings block.

    Format from CL_Demo_ReadNetConstStringTable @ 0x5DC0E0:
        u16 magic == 0xD311 | u16 version == 1 | u32 total
        26 x u32 per-type counts
        total x { u16 index, u16 length, length bytes }
    """
    end = len(blob) - 8
    magic_at = blob.find(b"\x11\xd3\x01\x00", footer, end)
    if magic_at < 0:
        out.append("  netconststrings: magic 0xD311 not found in the footer")
        return
    total = u32(blob, magic_at + 4)
    counts = [u32(blob, magic_at + 8 + 4 * i) for i in range(26)]
    out.append(f"  netconststrings @0x{magic_at:X}  total={total}  "
               f"(sum of type counts = {sum(counts)})")
    for t, n in enumerate(counts):
        if n:
            hint = NCS_TYPE_HINT.get(t, "")
            out.append(f"    type {t:2}: {n:5} entries  {hint}")

    if list_type is None:
        return
    pos, seen, shown = magic_at + 8 + 26 * 4, 0, 0
    for t, n in enumerate(counts):
        for _ in range(n):
            if pos + 4 > end:
                return
            idx, ln = u16(blob, pos), u16(blob, pos + 2)
            raw = blob[pos + 4:pos + 4 + ln]
            pos += 4 + ln
            if t == list_type and shown < 20:
                out.append(f"      [{idx}] {raw.decode('ascii', 'replace')}")
                shown += 1
            seen += 1


def report_failure(blob, exc, history, out):
    off = exc.offset
    out.append(f"  *** FAILS: {exc}")
    if off is not None:
        out.append(f"  *** at file offset 0x{off:X} ({off})")
        if exc.byte is not None and exc.byte < 256:
            out.append(f"  *** offending byte = 0x{exc.byte:02X} ({exc.byte})")
        out.append("  context:")
        out.extend(hex_window(blob, off))
    if history:
        out.append("  packets immediately before the failure:")
        for hpos, htype, hsize, hdesc in history:
            out.append(f"    @0x{hpos:X} type={htype} size={hsize} {hdesc}")


def inspect(path: Path, args) -> bool:
    blob = path.read_bytes()
    print(f"=== {path.name}   {len(blob)} bytes")
    out: list[str] = []
    try:
        check_header(blob, out)
        footer = check_footer(blob, out)
    except Failure as exc:
        report_failure(blob, exc, [], out)
        print("\n".join(out))
        print()
        return False

    start = args.body_start if args.body_start is not None else u32(blob, 4)
    counts, stop, clean, exc, hist = walk(blob, start, footer)
    total = sum(counts.values())
    if clean:
        breakdown = ", ".join(f"{PKT_NAMES.get(t, t)}={n}" for t, n in sorted(counts.items()))
        out.append(f"  OK: {total} packets, clean end-of-stream @0x{stop:X} ({breakdown})")
    else:
        out.append(f"  walked {total} packets from 0x{start:X} before failing")
        report_failure(blob, exc, hist, out)

    if args.ncs:
        parse_netconststrings(blob, footer, out, args.ncs_list)

    if clean and args.stats:
        gates = {}
        pos = start
        while pos < footer and blob[pos] != 0:
            if blob[pos] == 1:
                gates[i32(blob, pos + 1 + 52)] = gates.get(i32(blob, pos + 1 + 52), 0) + 1
            sz, _ = packet_length(blob, pos, footer)
            pos += sz
        top = sorted(gates.items(), key=lambda kv: -kv[1])[:6]
        out.append("  archive gate values: "
                   + ", ".join(f"{v}x{n}" for v, n in top)
                   + ("" if len(gates) <= 6 else f"  (+{len(gates)-6} more)"))

    if args.sweep_archive:
        out.append("  --- archive-size sweep: which assumed size dies where ---")
        for size in range(args.sweep_lo, args.sweep_hi + 1):
            c, stop_s, ok_s, e, _ = walk(blob, start, footer, ("archive-size", size))
            n = sum(c.values())
            if ok_s:
                out.append(f"    size {size:4}  SURVIVES to EOF ({n} packets)")
            else:
                b = f"0x{e.byte:02X}" if (e.byte is not None and e.byte < 256) else "n/a"
                out.append(f"    size {size:4}  dies @0x{e.offset:X} byte={b} after {n} packets")

    if args.simulate:
        out.append("  --- simulated parser bugs: where each one dies ---")
        for name, desc in VARIANTS.items():
            if name == "correct":
                continue
            # A reader that ignores the terminator keeps going past the packet
            # stream, so let it run to the trailer to show where it lands.
            bound = (len(blob) - 8) if name == "ignore-terminator" else footer
            c2, stop2, clean2, exc2, hist2 = walk(blob, start, bound, name)
            n2 = sum(c2.values())
            if clean2:
                out.append(f"    {name:22} survives to EOF ({n2} packets) - {desc}")
            else:
                b = f"0x{exc2.byte:02X}" if (exc2.byte is not None and exc2.byte < 256) else "n/a"
                out.append(f"    {name:22} dies @0x{exc2.offset:X} byte={b} "
                           f"after {n2} packets")
                out.append(f"    {'':22}   {desc}")
    print("\n".join(out))
    print()
    return clean


def main() -> int:
    ap = argparse.ArgumentParser(
        description="Offline S2 native .demo reader / failure locator")
    ap.add_argument("demos", nargs="*", type=Path)
    ap.add_argument("--simulate", action="store_true",
                    help="also report where each known mis-parse would die")
    ap.add_argument("--body-start", type=lambda s: int(s, 0), default=None,
                    help="force the body offset (default: header size at +0x04)")
    ap.add_argument("--ncs", action="store_true",
                    help="parse the footer NetConstStrings table and report per-type counts")
    ap.add_argument("--ncs-list", type=int, default=None,
                    help="list the first entries of this netconststring type")
    ap.add_argument("--stats", action="store_true",
                    help="report the distribution of archive gate values")
    ap.add_argument("--sweep-archive", action="store_true",
                    help="try each assumed archive size and report where it dies")
    ap.add_argument("--sweep-lo", type=int, default=176)
    ap.add_argument("--sweep-hi", type=int, default=200)
    args = ap.parse_args()

    paths = args.demos or (sorted(DEMO_DIR.glob("*.demo")) if DEMO_DIR.is_dir() else [])
    if not paths:
        print("no .demo files given and none found")
        return 2
    ok = sum(1 for p in paths if p.is_file() and inspect(p, args))
    print(f"--- {ok}/{len(paths)} accepted by the native rules ---")
    return 0


if __name__ == "__main__":
    sys.exit(main())
