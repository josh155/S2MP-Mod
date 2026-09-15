import ida_lines, ida_bytes
START, END = 0x4EB890, 0x4EB89A
out = []
ea = START
while ea < END:
    txt = ida_lines.generate_disasm_line(ea, 0)
    txt = ida_lines.tag_remove(txt) if txt else "?"
    out.append("%06x  %s" % (ea, txt))
    n = ida_bytes.get_item_size(ea)
    ea += n if n > 0 else 1
print("\n".join(out))
