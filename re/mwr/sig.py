"""Compress each case body down to its READ SHAPE: branches + MSG_Read* widths.

A codec is defined by which bits it consumes in which order. Assignments,
masks and prints do not change the cursor, so they are dropped -- what is left
is exactly what a decoder has to reproduce.
"""
import re
import sys

READ = re.compile(r"\b(MSG_Read\w+)\s*\(([^;]*)")
KEEP = re.compile(r"^\s*(if|else|while|do|for|\{|\}|goto|break|LABEL_|return|switch|case|default)")

cur = None
for line in open(sys.argv[1], encoding="utf-8"):
    l = line.rstrip("\n")
    if l.startswith("===="):
        print()
        print(l)
        continue
    s = l.strip()
    if not s:
        continue
    m = READ.search(s)
    if m:
        args = m.group(2)
        depth, out = 0, ""
        for ch in args:                       # arg list only, stop at the close paren
            if ch == "(":
                depth += 1
            elif ch == ")":
                if depth == 0:
                    break
                depth -= 1
            out += ch
        parts = [p.strip() for p in out.split(",")]
        cond = "IF " if s.startswith("if ") or " if (" in s else ""
        print("  %s%s(%s)" % (cond, m.group(1), ", ".join(parts[1:]) or ""))
    elif KEEP.match(s):
        s = re.sub(r"\s+", " ", s)
        if len(s) > 90:
            s = s[:88] + ".."
        print("  " + " " * (len(l) - len(l.lstrip())) + s)
