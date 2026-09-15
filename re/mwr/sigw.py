import re, sys
READ = re.compile(r"\b(MSG_(?:Read|Write)\w+)\s*\(([^;]*)")
KEEP = re.compile(r"^\s*(if|else|while|do|for|\{|\}|goto|break|LABEL_|return|switch|case|default)")
for line in open(sys.argv[1], encoding="utf-8"):
    l = line.rstrip("\n")
    if l.startswith("===="):
        print(); print(l); continue
    s = l.strip()
    if not s: continue
    m = READ.search(s)
    if m:
        args = m.group(2); depth = 0; out = ""
        for ch in args:
            if ch == "(": depth += 1
            elif ch == ")":
                if depth == 0: break
                depth -= 1
            out += ch
        parts = [p.strip() for p in out.split(",")]
        cond = "IF " if s.startswith("if ") or " if (" in s else ""
        print("  %s%s(%s)" % (cond, m.group(1), ", ".join(parts[1:]) or ""))
    elif KEEP.match(s):
        s = re.sub(r"\s+", " ", s)
        print("  " + " " * (len(l) - len(l.lstrip())) + (s[:88] + ".." if len(s) > 90 else s))
