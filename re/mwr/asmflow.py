"""Reduce a disassembly to its READ FLOW: calls, gate tests, jumps, targets.

The inlined MSG_ReadBit in this build is a fixed idiom:
    mov  eXX, [rYY+28h]   ; bit & 7 via  and eXX, 7
    ...claim a byte when zero...
    bt / shr+and 1        ; extract
so the only lines that matter for transcription are the reads, the branches on
their results, and the jump targets that stitch the sections together.
"""
import re
import sys

KEEP = re.compile(
    r"\bcall\b|\bj[a-z]{1,3}\b|\bbt\b|\bloc_|"
    r"mov +e[a-z]{2}, +[0-9A-F]+h?$|and +e[a-z]{2}, +7$")
TARGET = re.compile(r"loc_([0-9A-F]+)")

lines = [l.rstrip("\n") for l in open(sys.argv[1], encoding="utf-8")]
lo = int(sys.argv[2], 16)
hi = int(sys.argv[3], 16)

targets = set()
for l in lines:
    for m in TARGET.finditer(l):
        targets.add(m.group(1).lower())

for l in lines:
    parts = l.split("  ", 1)
    if len(parts) != 2:
        continue
    ea, ins = parts[0].strip(), parts[1].strip()
    try:
        a = int(ea, 16)
    except ValueError:
        continue
    if not (lo <= a < hi):
        continue
    mark = ">>" if ea in targets else "  "
    if KEEP.search(ins):
        print("%s %s  %s" % (mark, ea, ins[:90]))
