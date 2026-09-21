"""Undo the over-broad revert, then redo it correctly.

⛔ MY MISTAKE: cod4x_fix_dupes.py reverted every name matching `base_N` where the
base was also in use. That swept up 22 PRE-EXISTING IDA names which were nothing
to do with this pass - start_0..start_15 (IDA's own numbering of several CRT
entry thunks), and __alloca_probe_8 / _copy_environ_0, which are REAL and
DISTINCT MSVC CRT symbols, not collision artefacts.

Restores every name from the dump taken before that change, then re-reverts ONLY
functions whose comment shows THIS pass applied them (a "Basis:" marker).

Lesson: a cleanup that edits by NAME PATTERN must also check PROVENANCE. Only
touch what this pass wrote.
"""
import os, re, sys, json
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from cod4x_common import RE_DIR, load

dump = load("cod4x_named_dump.json")            # taken BEFORE the bad revert
plan = load("cod4x_dupe_plan.json")             # what was reverted

restore, rerevert = {}, {}
for ea in plan:
    entry = dump.get(ea)
    if not entry:
        continue
    nm, _sz, cmt = entry[0], entry[1], (entry[2] if len(entry) > 2 else "")
    if "Basis:" in cmt:
        rerevert[ea] = (nm, cmt)                # ours -> keep it reverted
    else:
        restore[ea] = nm                        # not ours -> put it back

print(f"to RESTORE (pre-existing IDA names wrongly reverted): {len(restore)}")
for ea, nm in restore.items():
    print(f"   {ea} <- {nm}")
print(f"to stay reverted (applied by this pass): {len(rerevert)}")
for ea, (nm, _c) in rerevert.items():
    print(f"   {ea} was {nm}")

json.dump(restore, open(os.path.join(RE_DIR, "cod4x_restore_plan.json"), "w",
                        encoding="utf-8"))

CODE = r'''
def main():
    import json, ida_name, ida_funcs
    plan = json.load(open(r"__PLAN__", encoding="utf-8"))
    ok = fail = 0
    bad = []
    for k, nm in plan.items():
        ea = int(k, 16)
        if not ida_funcs.get_func(ea):
            fail += 1; continue
        ida_name.set_name(ea, nm, ida_name.SN_NOCHECK | ida_name.SN_FORCE)
        got = ida_name.get_name(ea)
        if got == nm:
            ok += 1
        else:
            bad.append((k, nm, got)); fail += 1
    return {"restored": ok, "failed": fail, "mismatch": bad[:10]}
main()
'''.replace("__PLAN__", os.path.join(RE_DIR, "cod4x_restore_plan.json").replace("\\", "\\\\"))

print("\nIDA:", pyeval(PORTS["cod4x"], CODE, timeout=600))
