import ida_name, ida_funcs, json

EA = 0x73F90
# CORRECTION. An earlier call-graph propagation pass put "MSG_ReadShort" here on
# 2 mapped neighbours. The body disproves it: it reads msg+40 (the BIT cursor),
# resyncs bit := 8*readcount when (bit & 7) == 0, and returns one bit -- that is
# MSG_ReadBit. Corroborated by every call site: CL_ParseSnapshot and
# MSG_ReadDeltaEntity use it exactly where the named PS4 twin calls MSG_ReadBit.
ok = ida_name.set_name(EA, "MSG_ReadBit", ida_name.SN_NOCHECK | ida_name.SN_NOWARN)
back = ida_name.get_name(EA)
f = ida_funcs.get_func(EA)
if f:
    ida_funcs.set_func_cmt(
        f,
        "CORRECTED from MSG_ReadShort (a false positive of the same-game call-graph\n"
        "propagation pass). Body reads the BIT cursor at msg+40 and resyncs to\n"
        "8*readcount, returning a single bit. Call sites match MSG_ReadBit in the\n"
        "named PS4 twin. Basis: own body + call sites.", True)
print(json.dumps({"ea": "0x%X" % EA, "got": back, "ok": bool(ok) and back == "MSG_ReadBit"}))
