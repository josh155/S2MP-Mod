"""Collapse the INLINED MSG_ReadBit idiom in a DISASSEMBLY into one line each.

The PC build inlines MSG_ReadBit everywhere, so a gated tail reads as ~20
instructions of cursor arithmetic per gate and the structure disappears.  The
idiom is fixed, which makes it mechanical to recognise:

    mov  r8d, [rXX+28h]      ; bit
    and  r8d, 7
    jnz  short <skip>        ; rem != 0 -> no byte claim
    mov  eax, [rXX+20h]      ; splitSize
    add  eax, [rXX+1Ch]      ; + size
    mov  ecx, [rXX+24h]      ; readcount
    cmp  ecx, eax
    jl   <ok>
    mov  dword ptr [rXX], 1  ; overflow
    ...
  <ok>/<skip>:
    ...fetch the byte, shr by rem...
    and  eax, 1
    jz/jnz <target>          ; THE GATE

Everything between `and rNd, 7` and the `and eax, 1` is bookkeeping.  Printing
`ReadBit -> jz loc_X` in its place turns 3.6 KB of tail into something a person
can transcribe without losing the thread.

Anything not recognised is printed verbatim, so a missed idiom shows up as noise
rather than as a silently dropped read -- which is the whole point: a dropped
read is a desync, and a desync is invisible until it is far too late.

    python bitflow.py <file.asm> [lo] [hi]
"""
from __future__ import annotations

import re
import sys

# the first and last instruction of the inlined idiom
BIT_START = re.compile(r"^\s*and\s+(r\d+d|e[a-z]{2}),\s*7$")
BIT_END = re.compile(r"^\s*and\s+(eax|edx|ecx),\s*1$")
COND_JMP = re.compile(r"^\s*(j[a-z]{1,3})\s+(?:short\s+)?(\S+)")

# noise the idiom leaves behind that is never worth printing on its own
NOISE = re.compile(
    r"^\s*(mov|lea|add|sub|cmp|movzx|movsxd|sar|shr|inc|nop|test|setnz|setnle|xor)\b"
    r".*(\+1Ch|\+20h|\+24h|\+28h|\+8\]|\+10h\]|ds:0\[)")

# reads and structure we always keep
KEEP = re.compile(r"\bcall\b|\bloc_|\bj[a-z]{1,3}\b|\bretn\b")


def parse(path):
    out = []
    for line in open(path, encoding="utf-8"):
        line = line.rstrip("\n")
        parts = line.split("  ", 1)
        if len(parts) != 2:
            continue
        ea, ins = parts[0].strip(), parts[1].strip()
        try:
            out.append((int(ea, 16), ea, ins))
        except ValueError:
            continue
    return out


def main():
    rows = parse(sys.argv[1])
    lo = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0
    hi = int(sys.argv[3], 16) if len(sys.argv) > 3 else 1 << 62

    # every address that is jumped to, so sections can be stitched together
    targets = set()
    for _, _, ins in rows:
        m = re.search(r"loc_([0-9A-Fa-f]+)", ins)
        if m:
            targets.add(m.group(1).lower())

    i = 0
    while i < len(rows):
        addr, ea, ins = rows[i]
        if not (lo <= addr < hi):
            i += 1
            continue
        mark = ">>" if ea.lower() in targets else "  "

        if BIT_START.match(ins):
            # scan forward for the extract + the branch on it
            j = i + 1
            end = None
            while j < min(i + 40, len(rows)):
                if BIT_END.match(rows[j][2]):
                    end = j
                    break
                # a nested read means this was not the idiom after all
                if "call" in rows[j][2]:
                    break
                j += 1
            if end is not None:
                k = end + 1
                tail = ""
                if k < len(rows):
                    m = COND_JMP.match(rows[k][2])
                    if m:
                        tail = "  -> %s %s" % (m.group(1), m.group(2))
                        k += 1
                print("%s %s  ReadBit()%s" % (mark, ea, tail))
                i = k
                continue

        if KEEP.search(ins) or not NOISE.match(ins):
            print("%s %s  %s" % (mark, ea, ins[:88]))
        i += 1


if __name__ == "__main__":
    main()
