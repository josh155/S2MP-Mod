import re, sys
READ = re.compile(r"\b(MSG_Read\w+|CL_GetPredicted\w+)\s*\(([^;]*)")
KEEP = re.compile(r"^(if|else|while|do|for|\{|\}|goto|break|LABEL_|return|switch|case|default)")
for line in open(sys.argv[1], encoding="utf-8"):
    l = line.rstrip("\n"); s = l.strip()
    if not s: continue
    m = READ.search(s)
    ind = " " * (len(l) - len(l.lstrip()))
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
        print("%s%s%s(%s)" % (ind, cond, m.group(1), ", ".join(parts[1:])))
    elif KEEP.match(s):
        s = re.sub(r"/\*0x[0-9a-f]+\*/", "", s).strip()
        print(ind + (s[:86] + ".." if len(s) > 88 else s))
