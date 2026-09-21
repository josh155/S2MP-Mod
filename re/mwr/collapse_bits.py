"""Collapse the INLINED MSG_ReadBit idiom in a decompile back into one call.

The PC build inlines MSG_ReadBit everywhere, so a decompiled tail is mostly
cursor arithmetic:

    v23 = *(_DWORD *)(v10 + 40) & 7;
    if ( !v23 ) { ...claim the next byte, maybe set overflow... }
    v25 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
    if ( v25 < 0 ) v26 = <split buffer A>; else v26 = <split buffer B>;
    ++*(_DWORD *)(v10 + 40);
    if ( ((v26 >> v23) & 1) != 0 ) goto LABEL_x;

Recognising that whole block and printing `if (ReadBit()) goto LABEL_x;` turns a
600-line tail into something a person can transcribe without losing their place.
Anything the recogniser does not match is printed verbatim, so a missed idiom
shows up as noise rather than as a silently dropped read.
"""
import re
import sys

BIT_START = re.compile(r"^\s*(v\d+) = \*\(_DWORD \*\)\((\w+) \+ 40\) & 7;")
BIT_TEST = re.compile(r"if \( \(\((v\d+) >> (v\d+)\) & 1\) (!=|==) 0 \)")
CURSOR = re.compile(
    r"\*\(_DWORD \*\)\(\w+ \+ (40|36|28|32)\)"
    r"|^\s*\+\+\*\(_DWORD \*\)"
    r"|^\s*v\d+ = \*\(_BYTE \*\)"
    r"|^\s*\*\(_DWORD \*\)\w+ = 1;")
KEEP = re.compile(r"^\s*(if|else|while|do|for|\}|\{|goto|LABEL_|break|return|switch|case)")
READS = re.compile(r"(MSG_Read\w+|sub_4EB510|sub_4ED0E0|sub_4F0780|sub_4EC1F0|Com_Printf)")


def main(path, start, end):
    src = open(path, encoding="utf-8").read().split("\n")
    src = [re.sub(r"/\*0x[0-9a-f]+\*/", "", l).rstrip() for l in src]
    i, out = start, []
    while i < min(end, len(src)):
        m = BIT_START.match(src[i])
        if m:
            var = m.group(1)
            j = i + 1
            hit = None
            # the idiom always resolves within a couple of dozen lines
            while j < min(i + 30, len(src)):
                t = BIT_TEST.search(src[j])
                if t and t.group(2) == var:
                    hit = (j, t)
                    break
                j += 1
            if hit:
                j, t = hit
                tail = src[j].split(")", 1)[-1]
                neg = "!" if t.group(3) == "==" else ""
                indent = " " * (len(src[i]) - len(src[i].lstrip()))
                out.append("%sif (%sReadBit())%s" % (indent, neg, tail))
                i = j + 1
                continue
        s = src[i].strip()
        if s and (READS.search(s) or KEEP.match(src[i])) and not CURSOR.search(src[i]):
            out.append(src[i][:110])
        i += 1
    print("\n".join(out))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))
