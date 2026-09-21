"""RUNS INSIDE IDA (MWR-PS4). Recover the NAMED netfield tables.

MWR's netfield tables live in .bss and are built at RUNTIME by
GLOBAL__sub_I_sv_msg_write_mp_cpp @0x7446e0, so a static read returns 0xFF.
The initializer is straight-line stores, so emulating it recovers the tables:

    lea  reg, aSomeString      -> reg holds a name pointer
    mov  cs:qword_BASE,   reg  -> record BASE   .name  = string
    mov  cs:word_BASE+8,  imm  -> record BASE+8 .offset
    mov  cs:word_BASE+10, imm  ->              .size
    mov  cs:word_BASE+12, imm  ->              .bits/encoder
    mov  cs:word_BASE+14, imm  ->              .flags

netField_t = 16 bytes {const char* name; u16 offset; i16 size; i16 bits; u16 flags}

Writes re/ps4_named_netfields.json
"""
import json, os

OUT = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\ps4_named_netfields.json"


def main():
    import idautils, idc, ida_funcs, ida_bytes, ida_ua

    def cstr(ea, n=128):
        b = ida_bytes.get_bytes(ea, n) or b""
        i = b.find(b"\x00")
        if i <= 0:
            return None
        s = b[:i]
        if not all(32 <= c < 127 for c in s):
            return None
        return s.decode("ascii")

    f = ida_funcs.get_func(0x7446e0)
    regs = {}          # register name -> string
    names = {}         # address -> name
    vals = {}          # address -> immediate

    for ea in idautils.FuncItems(f.start_ea):
        mnem = idc.print_insn_mnem(ea)
        if mnem == "lea":
            dst = idc.print_operand(ea, 0)
            src = idc.get_operand_value(ea, 1)
            s = cstr(src)
            if s:
                regs[dst] = s
            else:
                regs.pop(dst, None)
        elif mnem == "mov":
            t0 = idc.get_operand_type(ea, 0)
            t1 = idc.get_operand_type(ea, 1)
            if t0 != ida_ua.o_mem:
                # register <- register/imm: keep the shadow map honest
                if t0 == ida_ua.o_reg:
                    d = idc.print_operand(ea, 0)
                    if t1 == ida_ua.o_reg:
                        s = regs.get(idc.print_operand(ea, 1))
                        if s:
                            regs[d] = s
                        else:
                            regs.pop(d, None)
                    else:
                        regs.pop(d, None)
                continue
            addr = idc.get_operand_value(ea, 0)
            if t1 == ida_ua.o_reg:
                s = regs.get(idc.print_operand(ea, 1))
                if s:
                    names[addr] = s
            elif t1 == ida_ua.o_imm:
                vals[addr] = idc.get_operand_value(ea, 1)

    # assemble records: every address that received a NAME is a record base
    recs = []
    for base, nm in names.items():
        def sw(off):
            v = vals.get(base + off)
            return v if v is not None else None
        def sgn(v):
            if v is None:
                return None
            v &= 0xFFFF                      # IDA reports imms 64-bit sign-extended
            return v - 0x10000 if v >= 0x8000 else v
        recs.append({"base": base, "name": nm,
                     "offset": (sw(8) & 0xFFFF) if sw(8) is not None else None,
                     "size": sgn(sw(10)),
                     "bits": sgn(sw(12)),
                     "flags": (sw(14) & 0xFFFF) if sw(14) is not None else None})
    recs.sort(key=lambda r: r["base"])

    # slice by the REGISTRY (dumped separately) - the tables are contiguous in
    # .bss so contiguity alone cannot separate them.
    REG = [("EntityState", 0xbb42a60, 72), ("ArchivedEntity", 0xbb42ee0, 119),
           ("ClientState", 0xbb43650, 56), ("PlayerState", 0xbb439d0, 271),
           ("Objective", 0xbb44ac0, 7), ("HudElem", 0xbb44b30, 44)]
    by_base = {r["base"]: r for r in recs}
    tables = []
    for nm, base, cnt in REG:
        rows = []
        for i in range(cnt):
            r = by_base.get(base + 16 * i)
            rows.append(r if r else {"base": base + 16 * i, "name": "?",
                                     "offset": None, "size": None,
                                     "bits": None, "flags": None})
        rows[0]["_label"] = nm
        tables.append(rows)

    out = {"tables": [{"label": t[0].get("_label", "?"),
                       "base": hex(t[0]["base"]), "count": len(t),
                       "fields": [{"i": i, "name": r["name"], "offset": r["offset"],
                                   "size": r["size"], "bits": r["bits"],
                                   "flags": r["flags"]}
                                  for i, r in enumerate(t)]}
                      for t in tables]}
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(out, fh, indent=1)
    return {"named_slots": len(names), "imm_slots": len(vals),
            "tables": [(t["label"], t["base"], t["count"],
                        sum(1 for f in t["fields"] if f["name"] != "?"))
                       for t in out["tables"]]}


main()
