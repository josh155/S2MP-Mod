import ida_name, ida_funcs, json
EA = 0x4EB890
# CORRECTION. "Com_Printf" here is a false positive of the same-game call-graph
# propagation pass (its own basis comment records pc=9 vs ps4=656 bytes).
# The body is `movsxd r8, [rcx+24h]` -- msg+36, the BYTE cursor -- then a jump
# into the Arxan block, i.e. a 4-byte read primitive taking a msg_t*.  It is
# called three times in MSG_ReadDeltaPlayerstate's tail to fill three
# consecutive playerState dwords followed by a MSG_ReadByte, so it consumes 4
# bytes on the byte cursor.  Whether it is MSG_ReadLong or a float variant is
# NOT established, so the name is descriptive rather than guessed.
ok = ida_name.set_name(EA, "MSG_ReadValue32_ByteCursor",
                       ida_name.SN_NOCHECK | ida_name.SN_NOWARN)
back = ida_name.get_name(EA)
f = ida_funcs.get_func(EA)
if f:
    ida_funcs.set_func_cmt(f,
        "CORRECTED from Com_Printf (call-graph propagation false positive; that\n"
        "pass's own note records a 72x size mismatch). Reads msg+36 (byte cursor)\n"
        "and tail-jumps into the Arxan block. Consumes 4 bytes. Descriptive name:\n"
        "long-vs-float is not established. Basis: own body + call sites in\n"
        "MSG_ReadDeltaPlayerstate's tail.", True)
print(json.dumps({"got": back, "ok": bool(ok) and back == "MSG_ReadValue32_ByteCursor"}))
