"""Split a decompiled switch into per-case bodies, stripped of decompiler noise.

MSG_ReadDeltaField is 1644 lines of XMM/register churn. What matters is the ORDER
and WIDTH of the MSG_Read* calls in each case, plus the control flow around them.
Everything that exists only because IDA models registers is dropped.
"""
import re
import sys

path = sys.argv[1]
lines = open(path, encoding="utf-8").read().split("\n")

start = None
for i, l in enumerate(lines):
    if re.match(r"\s*switch \( \*\(\(_WORD \*\)\w+ \+ 6\) \)", l):
        start = i
        break
if start is None:
    sys.exit("outer switch dispatching on +6 not found")

# Take the case indent from the data, not from an assumed +4: the two builds
# nest the switch differently and a wrong guess silently yields an empty result.
case_indent = None
for l in lines[start + 1:]:
    s = l.strip()
    if s.startswith("case ") or s.startswith("default:"):
        case_indent = len(l) - len(l.lstrip())
        break
if case_indent is None:
    sys.exit("no case labels after the switch")

NOISE = re.compile(
    r"^(_R\w+|_E\w+|_XMM\d|v\d+|LOBYTE|HIBYTE|LODWORD|HIDWORD|WORD\d|BYTE\d)"
    r"\s*(\(\w+\))?\s*=\s*"
    r"(\(.*?\))?\s*[&*]?(_R\w+|_E\w+|v\d+|a\d+|\w+)\s*;$"
)

cur, out, order = None, {}, []
for l in lines[start + 1:]:
    ind = len(l) - len(l.lstrip())
    s = l.strip()
    if not s:
        continue
    if ind == case_indent and (s.startswith("case ") or s.startswith("default:")):
        cur = s.rstrip(":")
        if cur not in out:
            out[cur] = []
            order.append(cur)
        continue
    if ind < case_indent and s == "}":
        break
    if cur is None:
        continue
    s = re.sub(r"/\*0x[0-9a-f]+\*/", "", s).rstrip()
    if not s or NOISE.match(s):
        continue
    out[cur].append((ind, s))

for k in order:
    print("=" * 4, k, "=" * 4)
    for ind, b in out[k]:
        print("  " + " " * max(0, ind - case_indent) + b)
    print()
