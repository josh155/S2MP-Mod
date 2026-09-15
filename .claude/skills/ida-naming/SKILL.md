---
name: ida-naming
description: Rules for naming functions, globals, structs and fields in the S2/WWII IDB (or any reference IDB). Use whenever applying a name, porting names from a reference build (AW / MWR-PS4 / MW3 / S2-Xbox), running a bulk naming pass, resolving a name conflict, or deciding whether evidence is strong enough to write a name. Also use before trusting an existing name.
---

# Naming rules for this project

A wrong name is invisible once written. Every future decompile shows it, and
every later session builds on it. That asymmetry — cheap to write, expensive to
detect — is why these rules are strict.

## The one hard rule

**No name without a recorded basis.** When you write a name, write a function
comment saying *how you know*. If you cannot state the basis in a sentence, you
do not have a name — you have a hypothesis, and it belongs in a comment as
`CANDIDATE, NOT APPLIED`.

Run `python re/audit_names.py` after any naming pass. It fails on names with no
basis.

## Evidence tiers, strongest first

**1. Self-naming** — the target binary itself pairs the name with the pointer.
Strongest tier available; stronger than any twin, because no cross-binary
inference is involved.
- `{const char* name, void* fn}` tables in `.rdata`
- registrar calls that pass both: `Cmd_AddCommandInternal(name, fn, ...)`,
  `hksI_openlib(L, libname, table, ...)`, `Dvar_Register*(name, ...)`
- Record: the table address, the registrar, and the call that pairs them.

**2. Twin-proven** — a *named* function in a reference IDB has the same
structure, gates, call order and arguments. Use the reference's exact name.
- Record: which reference, its address, and what made the match unambiguous.

**3. Behaviour-proven** — the decompile shows unambiguously what it does, with no
named twin. Use a DESCRIPTIVE name derived from observed behaviour.
- A merely unidiomatic name is fine. A plausible-sounding *engine* name that
  turns out wrong is not.
- Record: the specific literals, calls or writes the name is derived from.
- Mark it clearly as descriptive, e.g. "descriptive, NOT a known engine name".

**4. Not confident** — leave `sub_XXXXXX`. Add a comment with what you suspect
and why it is not proven. An honest `sub_` beats a wrong name.

## Rules that were each paid for in lost time

**Match tables to tables before matching entries.** Matching a bare string across
two binaries is careless — `ping`, `show`, `hide` mean different things in
different tables. Establish that two *tables* correspond (by shared name-set),
then match only within a corresponding pair.

**Accept on absolute overlap as well as ratio.** Engines split and merge tables
between versions. AW keeps one merged party table where S2 splits it into three,
collapsing the ratio to 0.24 while 6 exact protocol-token matches are
unmistakable. Require ratio ≥ 0.60 **or** absolute shared ≥ 5.

**Normalise notation before declaring a conflict.** `Foo::bar` (AW) and
`Foo__bar` (MWR) are the same name. Normalise `::` → `__`, strip trailing `_`,
lowercase, *then* compare. Skipping this turns agreements into false conflicts.

**Drop contradictions; never pick a winner.** If two references disagree after
normalisation, that is a Contradiction — leave the function unnamed and record
both claims. Resolving it needs new evidence, not a preference.

**One name, one function.** A name proposed for two functions is unusable —
drop both, or keep only the one with strictly stronger evidence and say why.
Check the name is not already in use before writing it.

**Distinctiveness, not length.** A short protocol token (`%idoqos`) is gold; a
long generic template (`%s%s%llu/%s/%llu/tokens/?client=%s`) is noise. Score
anchors on whether an identifier survives after stripping format specifiers.

**Prefer the bigger contiguous body when two candidates abut.** If A ends exactly
where B begins, they are contiguous and one is likely a split-off chunk. Give the
name to the one the evidence points at; revert the other to `sub_` with a comment
noting the contiguity.

**A shared callee cannot be named after one of its callers.** Before propagating
a name from caller to callee, check how many callers reach that callee. If more
than one, the name is wrong.

**Never verify a claim using the value you just wrote.** If a fix forces a field,
do not confirm the fix by reading that field. Verify the *consequence* instead.

## Reference builds

| port | binary | notes |
|---|---|---|
| 13337 | `s2x_dump.exe` | **the target.** Authoritative. |
| 12345 | `default_mp.pe` (AW) | Sledgehammer, same studio. FULLY symboled, PPC BE 32-bit. |
| 9999 | `2-h1_mp.elf` (MWR-PS4) | DEBUG build: real symbols, asserts with source paths + field names. |
| 12346 | `s2_mp64_ship_dump.exe` | S2 Microsoft Store build. Same source, 99.9% identical sizes. |
| 14200 | `COD_MW3_MPsub` (MW3, Mac reference) | macOS Mach-O, imagebase 0x1000, 99.31% symboled, Itanium-mangled C++. Same shape as the CoD4-Mac reference. Sometimes down. |
| 13999 | `iw5mp_dumpx64.exe` (MW3-Steam) | the new 64-bit Steam client — a TARGET, named from port 14200. No ASLR: addresses are fixed per build, but imagebases differ (0x1000 vs 0x140000000) — cross-reference by RVA/name, never a raw literal. |
| 18337 | macOS CoD4 | Mach-O, GCC C++, 100% symboled reference for the CoD4X pass. |
| 19337 | `iw3mp_dump.exe` (CoD4X) | target for the CoD4X pass, imagebase 0x400000. |

Health-probe with a timeout **≥ 10 s** — AW answers at ~6 s and a 4 s probe
wrongly reports it down.

## Operational traps

- `py_eval` runs under `exec` with split globals/locals: a nested `def` cannot
  see names bound at the top level of your snippet. **Wrap everything in one
  `def main(): ...` and call it.**
- **Never call `idautils.Strings()` on S2** — it forces a strlist rebuild and
  times out the MCP. Read `.rdata` bytes and index in Python.
- `idb_save` on S2 exceeds the MCP timeout but **succeeds**. Do not blind-retry a
  mutating op; verify by `.i64`/`.id0` mtime, or issue it via curl with `-m 600`.
- Save the IDB after any naming session. The `.i64` is stale until an explicit
  save (RULE A10).
- Generate file content with the Write tool, not a shell heredoc.
- Before calling any engine function from the mod, read its body for a `retaddr`
  check (RULE A22). Declare the exact return width *and* parameter list (A17/A23).

## When you finish a pass

1. Apply names with basis comments.
2. `python re/audit_names.py` — fix anything it reports.
3. Save the IDB.
4. Record the method and any corrections in CLAUDE.md. A withdrawn claim gets
   marked at the point it was made, not silently dropped.
