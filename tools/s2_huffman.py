"""S2 Huffman decoder — an offline reimplementation of sub_DCAB0 / sub_665990.

Why this exists
---------------
S2's demo messages are Huffman-compressed unless bit31 of the message sequence is
set (then they are zlib). The zlib half was already decodable offline; this adds
the other half, so a .demo can be fully decoded with no game running.

PROVEN 2026-08-08:
  * sub_DCAB0 @ IDA 0xDCAB0 is the block decoder.
  * sub_665990 @ IDA 0x665990 decodes ONE symbol; the table is unk_F92B80.
  * Table layout: [0..255]   code length for the current 8-bit LSB-first window
                  [256..511] symbol for that window
                  [512..]    tree nodes for codes longer than 8 bits
  * Bits are LSB-first within each byte: `src[bitpos>>3] >> (bitpos & 7)`.

The table is pulled straight out of s2_mp64_ship.exe by RVA, so there is nothing
to transcribe and nothing to keep in sync by hand. IDA addresses in this project
equal RVAs (runtime VA = module_base + IDA), which the self-test relies on.

    python tools/s2_huffman.py --selftest
    python tools/s2_huffman.py <demo.demo> [--packet N] [--offset 4|6]
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

GAME = Path(r"E:\SteamLibrary\steamapps\common\Call of Duty WWII")
EXE = GAME / "s2_mp64_ship.exe"       # retail, Arxan-packed: bytes DIFFER from memory
DUMP = GAME / "s2x_dump.exe"          # process dump; this is what the IDB is built from
HUFF_RVA = 0xF92B80
HUFF_SIZE = 4096

# First 16 bytes of unk_F92B80 as dumped from IDA — used to prove the PE mapping.
IDA_FIRST16 = bytes([0x8, 0x8, 0x5, 0x6, 0x8, 0x6, 0x6, 0x7,
                     0x9, 0x8, 0x5, 0x4, 0x8, 0x9, 0x8, 0x9])


def rva_to_file_offset(blob: bytes, rva: int) -> int:
    """Map an RVA to a file offset using the PE section table."""
    pe = struct.unpack_from("<I", blob, 0x3C)[0]
    if blob[pe:pe + 4] != b"PE\0\0":
        raise ValueError("not a PE file")
    n_sections = struct.unpack_from("<H", blob, pe + 6)[0]
    opt_size = struct.unpack_from("<H", blob, pe + 20)[0]
    sec = pe + 24 + opt_size
    for i in range(n_sections):
        off = sec + i * 40
        va = struct.unpack_from("<I", blob, off + 12)[0]
        vsz = struct.unpack_from("<I", blob, off + 8)[0]
        praw = struct.unpack_from("<I", blob, off + 20)[0]
        rsz = struct.unpack_from("<I", blob, off + 16)[0]
        if va <= rva < va + max(vsz, rsz):
            return praw + (rva - va)
    raise ValueError(f"RVA {rva:#x} not in any section")


def _candidates(rva: int):
    """(label, path, file_offset) candidates for an RVA.

    The RETAIL exe is Arxan-packed, so its on-disk bytes do NOT match memory —
    verified 2026-08-08 when the self-test caught a total mismatch. The IDB is
    built from `s2x_dump.exe`, a process dump, whose bytes DO match runtime. A
    dump may be stored either section-mapped or flat (offset == RVA), so try
    both and let the signature decide (RULE A2).
    """
    for path in (DUMP, EXE):
        if not path.exists():
            continue
        blob = path.read_bytes()
        try:
            yield (f"{path.name} (PE sections)", blob, rva_to_file_offset(blob, rva))
        except Exception:
            pass
        if rva < len(blob):
            yield (f"{path.name} (flat, offset==RVA)", blob, rva)


def load_table(rva: int = HUFF_RVA, size: int = HUFF_SIZE, verbose: bool = False) -> bytes:
    """Return the Huffman table, verified against the IDA-dumped signature."""
    first = None
    for label, blob, off in _candidates(rva):
        data = blob[off:off + size]
        if verbose:
            print(f"  try {label:<34} @0x{off:08X} -> "
                  f"{' '.join(f'{b:02X}' for b in data[:8])}")
        if first is None:
            first = data
        if data[:len(IDA_FIRST16)] == IDA_FIRST16:
            if verbose:
                print(f"  MATCH via {label}")
            return data
    raise RuntimeError(
        "could not locate the Huffman table: no candidate matched the IDA "
        "signature. Is s2x_dump.exe present next to the game exe?")


def _rol8(v: int, n: int) -> int:
    n &= 7
    return ((v << n) | (v >> (8 - n))) & 0xFF if n else v & 0xFF


def decode_symbol(table: bytes, src: bytes, bitpos: int) -> tuple[int, int]:
    """One symbol. Faithful transcription of sub_665990."""
    v3 = bitpos
    v5 = v3 >> 3
    if v5 >= len(src):
        raise IndexError("source exhausted")
    v8 = 8 - (bitpos & 7)
    v9 = (src[v5] >> (bitpos & 7)) & 0xFF
    v10 = table[v9]
    if v10 > v8:
        nxt = src[v5 + 1] if v5 + 1 < len(src) else 0
        v9 = (v9 | (nxt << v8)) & 0xFF
        v10 = table[v9]

    if v10 > 8:
        v13 = v3 + 8
        v14 = v13 >> 3
        v15 = v13 & 7
        v16 = v13 + 1
        bit = 1 if (v14 < len(src) and (src[v14] & (1 << v15))) else 0
        v17 = bit + 512 + table[v9 + 256]
        v18 = table[v17]
        # The engine seeds v19 = ROL1(1, v16) and walks the tree until a node
        # with a zero length is reached.
        if v18:
            v19 = _rol8(1, v16)
            while True:
                v20 = v19
                v21 = v16 >> 3
                v16 += 1
                v19 = _rol8(v19, 1)
                b = 1 if (v21 < len(src) and (src[v21] & v20)) else 0
                v17 = (v18 + b + v17) & 0xFFFFFFFF
                v18 = table[v17]
                if not v18:
                    break
        return table[(v17 + 256) & 0xFFFFFFFF], v16

    return table[v9 + 256], v10 + v3


def huff_decode(table: bytes, src: bytes, src_len: int, dest_max: int) -> bytes:
    """Faithful transcription of sub_DCAB0. Returns the decoded bytes.

    NOTE the engine's signedness bug lives in the CALLER: MSG_ReadShort
    sign-extends, so a length with bit15 set arrives here negative and the
    `if (8 * srcLen <= 0)` early-out returns SUCCESS with zero bytes.
    """
    if src_len > dest_max:
        return b""          # engine: return 0 -> Com_Error "464"
    total_bits = 8 * src_len
    out = bytearray()
    if total_bits <= 0:     # the bug path: negative or zero length
        return bytes(out)
    bitpos = 0
    while len(out) < dest_max:
        try:
            sym, bitpos = decode_symbol(table, src, bitpos)
        except IndexError:
            break
        out.append(sym)
        if bitpos >= total_bits:
            break
    return bytes(out)


def packets(blob: bytes):
    """Yield (index, file_offset, outer_seq, payload) for type 2/3 packets."""
    pos = struct.unpack_from("<I", blob, 4)[0]
    i = 0
    while pos < len(blob):
        t = blob[pos]
        if t == 0:
            return
        if t == 1:
            pos += 185
            i += 1
            continue
        if t not in (2, 3):
            return
        p = pos + 1
        oseq = struct.unpack_from("<I", blob, p)[0]
        p += 4
        if t == 3:
            p += 4
        ln = struct.unpack_from("<I", blob, p)[0]
        p += 4
        yield i, pos, oseq, blob[p:p + ln]
        pos = p + ln
        i += 1


def selftest() -> int:
    print("locating unk_F92B80:")
    try:
        table = load_table(verbose=True)
    except RuntimeError as e:
        print(f"  {e}")
        return 1
    print(f"\nIDA reference  : {' '.join(f'{b:02X}' for b in IDA_FIRST16)}")
    print(f"extracted      : {' '.join(f'{b:02X}' for b in table[:16])}")
    lens = table[:256]
    print(f"code lengths   : min={min(lens)} max={max(lens)} "
          f"(expect 4..11 for a real Huffman table)")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description="S2 Huffman decoder / demo message dumper")
    ap.add_argument("demo", nargs="?")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--packet", type=int, default=0, help="packet index to decode")
    ap.add_argument("--offset", type=int, default=None,
                    help="body offset in payload (default: try both 4 and 6)")
    args = ap.parse_args()

    if args.selftest or not args.demo:
        return selftest()

    table = load_table()
    blob = Path(args.demo).read_bytes()

    for i, off, oseq, pay in packets(blob):
        if i != args.packet:
            continue
        seq = struct.unpack_from("<I", pay, 0)[0]
        use_zlib = seq >> 31
        u16 = struct.unpack_from("<H", pay, 4)[0]
        s16 = struct.unpack_from("<h", pay, 4)[0]
        print(f"packet {i} @0x{off:X} outerSeq={oseq} payload={len(pay)}")
        print(f"  msgSeq={seq & 0x7FFFFFFF} useZlib={use_zlib} "
              f"u16@+4={u16} (0x{u16:04X}) signed={s16}")
        print(f"  ENGINE would call sub_DCAB0(srcLen={s16}) -> "
              f"{'ZERO BYTES (bug path)' if 8 * s16 <= 0 else 'decode'}")

        offsets = [args.offset] if args.offset else [6, 4]
        for body_off in offsets:
            body = pay[body_off:]
            out = huff_decode(table, body, len(body), 0x20000)
            print(f"\n  --- decode from payload+{body_off} "
                  f"(srcLen={len(body)}) -> {len(out)} bytes ---")
            if out:
                print(f"      first nibble (opcode) = {out[0] & 0x0F}  "
                      f"byte0=0x{out[0]:02X}")
                print(f"      hex : {' '.join(f'{b:02X}' for b in out[:24])}")
                printable = "".join(chr(c) if 32 <= c < 127 else "." for c in out[:120])
                print(f"      ascii: {printable}")
        return 0

    print(f"packet {args.packet} not found")
    return 1


if __name__ == "__main__":
    sys.exit(main())
