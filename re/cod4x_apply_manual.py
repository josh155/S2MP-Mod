"""Apply the handful of names established INDIVIDUALLY, each with its own basis.

These did not come from the bulk anchor/graph passes; each was verified on its
own, so each carries its own evidence rather than the pass-level precision
figure.

Deliberately NOT named here:
  0x56c350  the shared Dvar_Register internal. 964 of its call sites pass a dvar
            DESCRIPTION string and it is reached from many different
            Dvar_Register* callers, so naming it after one of them would break
            the shared-callee rule. Commented instead.
  0x4f9950  the command-exists lookup used by the INLINED Cmd_AddCommand. Its
            role is clear but no name is proven. Commented, left as sub_.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__))

NAMES = {
    0x4f9140: ("Cmd_AddServerCommandInternal",
               "Basis: self-naming [cod4x-selfnaming]\n"
               "  The function's OWN error string is \"Cmd_AddServerCommand: %s "
               "already defined\\n\", emitted when the name it was handed is "
               "already in the list it links into (head dword_14099DC).\n"
               "  Signature from its body: (const char *name@<edi>, int fn, "
               "cmd_function_s *slot); writes slot[1]=name, slot[4]=fn, "
               "slot[0]=old head.\n"
               "  Tier-1: the target binary asserts this itself, no cross-binary "
               "inference. NOTE CoD4X INLINES the client-side Cmd_AddCommand, so "
               "that one does not exist as a function."),
    0x4fcbc0: ("Com_Printf",
               "Basis: caller-intersection + argument shape [cod4mac-graph]\n"
               "  97 of the 115 mapped callers of the reference Com_Printf "
               "(__Z10Com_PrintfiPKcz @ cod4 0x16a640) call this function; the "
               "runner-up scores 32.\n"
               "  Corroborated independently by the observed call-site shape: "
               "sub_4FCBC0(16, \"Cmd_AddServerCommand: %s already defined\", name) "
               "and (0x11, fmt, \"Mantle Failed: ...\") - i.e. "
               "(int channel, const char *fmt, ...), which is Com_Printf's "
               "signature.\n"
               "  Further corroboration: Com_DPrintf was placed at 0x4fcc10 by "
               "the anchor pass and independently scores 30/32 for the reference "
               "Com_DPrintf, so the intersection method is self-consistent here."),
    0x462f00: ("goprone_f",
               "Basis: live command list in the process dump [cod4x-cmdtable]\n"
               "  iw3mp_dump.exe is a dump of a RUNNING process, so the client "
               "command list (head off_1410B3C) is populated. This function is "
               "the handler paired with the command name \"goprone\" by the "
               "running game itself.\n"
               "  cmd_function_s layout {next@0, name@4, fn@16} read from "
               "Cmd_AddServerCommandInternal @0x4f9140.\n"
               "  DESCRIPTIVE name using the engine's <command>_f convention "
               "(cf. SV_Status_f, CL_PlayDemo_f, established independently by the "
               "anchor pass) - NOT a recovered engine symbol."),
    0x462df0: ("speed_throw_minus_f",
               "Basis: live command list in the process dump [cod4x-cmdtable]\n"
               "  Handler paired with the command name \"-speed_throw\" by the "
               "running game itself (client command list, head off_1410B3C).\n"
               "  cmd_function_s layout {next@0, name@4, fn@16} read from "
               "Cmd_AddServerCommandInternal @0x4f9140.\n"
               "  DESCRIPTIVE: the leading '-' of a key-release command cannot be "
               "spelled in an identifier, so it is written as the _minus_ suffix. "
               "NOT a recovered engine symbol."),
}

COMMENTS_ONLY = {
    0x56c350: "NOT NAMED. Shared Dvar_Register internal: 964 of its 1028 call "
              "sites pass a dvar DESCRIPTION string, and caller-intersection "
              "reaches it from many different reference Dvar_Register* functions "
              "(Dvar_RegisterBool scores 28/30 here). A shared callee cannot be "
              "named after one of its callers, so this stays sub_ until the "
              "variant is proven. CANDIDATE: the common "
              "Dvar_Register/Dvar_RegisterVariant worker.",
    0x4f9950: "NOT NAMED. Predicate used by the INLINED client-side "
              "Cmd_AddCommand: callers do `if (sub_4F9950()) Com_Printf(16, "
              "\"Cmd_AddCommand: %s already defined\", name)` before open-coding "
              "the list insert. So it reports whether a command name is already "
              "registered, but no proven name. CANDIDATE: a Cmd_FindCommand / "
              "Cmd_Exists style lookup.",
}

plan = {str(k): {"name": v[0], "comment": v[1]} for k, v in NAMES.items()}
plan_c = {str(k): v for k, v in COMMENTS_ONLY.items()}
json.dump({"names": plan, "comments": plan_c},
          open(os.path.join(RE_DIR, "cod4x_manual.json"), "w", encoding="utf-8"))

CODE = r'''
def main():
    import json, ida_name, idc, ida_funcs
    d = json.load(open(r"__PLAN__", encoding="utf-8"))
    ok = fail = 0
    skipped = []
    for k, v in d["names"].items():
        ea = int(k)
        cur = ida_name.get_name(ea) or ""
        if cur and not cur.startswith(("sub_", "nullsub", "j_", "unknown_")):
            skipped.append((k, cur)); continue
        if ida_name.set_name(ea, v["name"], ida_name.SN_NOCHECK | ida_name.SN_FORCE):
            idc.set_func_cmt(ea, v["comment"], 0)
            ok += 1
        else:
            fail += 1
    cm = 0
    for k, c in d["comments"].items():
        ea = int(k)
        if ida_funcs.get_func(ea):
            idc.set_func_cmt(ea, c, 0); cm += 1
    return {"named": ok, "failed": fail, "skipped_already_named": skipped,
            "comments_written": cm}
main()
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_manual.json").replace("\\", "\\\\"))

print(pyeval(PORTS["cod4x"], CODE, timeout=600))
