# CLAUDE.md — IW7 / Infinite Warfare

Operating rules for a long-running reverse-engineering and modding project on
Infinite Warfare (IW7).

This file was ported from the S2/WWII project (`S2MP-Mod`). It carries the
**doctrine, the rules, and the methods** — every one of which was paid for with
real time — and deliberately carries **no IW7 facts at all**. Everything
binary-specific below is a labelled placeholder to be filled in by evidence.

> **The single most important thing inherited from S2:** a name, an offset, or a
> conclusion that came from a *different binary* is a HYPOTHESIS, not a fact. The
> S2 project lost days to names imported from an older database and to offsets
> that "looked plausible". Do not import; re-derive.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 0 — FIRST SESSION CHECKLIST
# ═══════════════════════════════════════════════════════════════════

Do these in order. Do not start investigating anything until the Environment
block below is filled in, because every later address depends on it.

## 0.1 Establish the binary and the address convention

1. Dump the running process (retail IW builds are typically packed/protected;
   on-disk bytes may NOT match memory — this bit S2 twice, once with a Huffman
   table and once with a byte search).
2. Open the DUMP in IDA, not the retail exe. Record which file is authoritative.
3. **Determine `VA = module_base + X`.** In S2 it was `base + IDA` with no
   adjustment, and the mod's `_b` literal was `IDA - 0x1000`. **Do not assume the
   same for IW7.** Derive it and write it down in the Environment block.
4. Verify it immediately against a known signature (RULE A2) — pick a distinctive
   string, read it live, confirm it lands.

## 0.2 Set up the reference twins (see PART 5)

IW7 starts from a *much* better position than S2 did. Get every server listening
and record the ports in the Environment block before doing anything else.

## 0.3 Measure how close MWR is to IW7 — this is the highest-value first task

**HYPOTHESIS (to verify, not to assume):** Modern Warfare Remastered (h1) shipped
alongside Infinite Warfare in 2016 and is built on the same engine generation, so
a fully-named MWR IDB should be a near-perfect twin for IW7.

If that holds, most of IW7 can be named mechanically in a day or two instead of
function-by-function over months. **Measure it, do not believe it.**

The method is already written and generalises (see PART 4.2 and PART 8):

```bash
python tools/export_idb.py    # dump each IDB's function graph: size, name, callees
python tools/match_builds.py  # size + call-graph matching, holdout-validated
```

In S2 this measured **99.9% of matched functions identical to the byte** between
two builds of the same game, and reproduced 8 of 8 addresses that had been derived
by hand months earlier. Against a *different but related* title expect much less —
so the number you measure is the finding, whatever it is. Record it.

## 0.4 Fill in the Environment block

Do not leave it half-filled. An unfilled field is a trap for a later session.

---

# ENVIRONMENT — FILL THIS IN (currently ALL PLACEHOLDER)

```
Game install path        : <TBD>
Executable               : <TBD>            (e.g. iw7_ship.exe / mp exe name)
Process dump             : <TBD>            <- the AUTHORITATIVE IDB source
Authoritative IDB        : <TBD>.i64
Module size              : <TBD>
Address convention       : VA = module_base + <TBD>     <- PROVE IT (RULE A2)
Mod `_b` literal formula : IDA - <TBD>                  <- PROVE IT
Signature string for A2  : <TBD> at IDA <TBD>

Mod repo path            : <TBD>
Build toolchain          : <TBD>
Deploy path              : <TBD>
Console log path         : <TBD>            <- how probe output is retrieved
Crash dump path          : <TBD>            <- RULE A13 depends on this
Demo directory           : <TBD>

Protection               : <TBD>            (Arxan? VMProtect? none?)
Anticheat                : <TBD>            <- read PART 9 BEFORE touching this
```

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 1 — CORE PHILOSOPHY
# ═══════════════════════════════════════════════════════════════════

Work as a senior reverse engineer. **Evidence first, changes second.** Never guess
when evidence can be obtained.

Never treat a symptom, a rejection gate, a missing asset, or a failed condition as
the root cause until the upstream cause is proven. Investigate backwards until the
first divergence.

## 1.1 Evidence classification — MANDATORY on every conclusion

| Class | Means |
|---|---|
| **PROVEN** | Directly demonstrated by this binary's own code, its own data, runtime measurement, or a successful test. |
| **STRONG INFERENCE** | Several independent pieces of evidence agree, but it is not directly shown. Cross-binary mapping lives here at best. |
| **HYPOTHESIS** | A possible explanation requiring investigation. |
| **IMPLEMENTATION DECISION** | An engineering choice, not a discovered fact about the game. |

Never present a HYPOTHESIS as fact. Never present cross-binary mapping as PROVEN.

## 1.2 Fix Declaration Rules

Never write **Fixed / Solved / Root cause confirmed / Complete** unless ALL of:

1. Code change implemented
2. Project builds successfully
3. Correct binary deployed (hash-verified)
4. Game tested
5. **The original user-visible problem is verified gone**

Until then: *Investigating / Hypothesis / Probe / Test / Candidate fix.*

A **CANDIDATE** is something that builds and deploys but has not been run. Label it
as such every time it is mentioned. S2's history is full of candidates that turned
out to be no-ops, and the label is what kept that honest.

## 1.3 Probe Rules

Diagnostic changes are not fixes. Forced values, debug commands, logging, bypasses
and temporary overrides must always be labelled **PROBE ONLY**.

Never instruct testing of something that does not exist. Before saying "use command
X", verify the command exists, is registered, and changes the intended path. If it
does not: *"I need to implement this diagnostic first."*

## 1.4 One change at a time

For every change, state: the hypothesis, the evidence, the exact engine state
involved, its owner, the smallest possible change, then test. **A patch is not
successful merely because a visual symptom disappeared.**

## 1.5 The Earliest-Divergence Rule

When comparing working and broken behaviour: find the EARLIEST observable
divergence, ignore later symptoms until it is understood, trace the state
responsible, find its producer, and correct the earliest incorrect transition.

Do not patch downstream symptoms while an earlier divergence is unexplained.

## 1.6 The Contradiction Rule

If two pieces of evidence conflict: **STOP.** Do not patch around it. Resolve
whether the wrong function was identified, the wrong field, the wrong execution
path, or whether an earlier conclusion was simply incorrect. Only continue once
the contradiction is explained.

## 1.7 No symptom patching

Prohibited as first-line fixes: continuously forcing time or view angles;
fabricating snapshots, player state or entity state; blindly copying live-network
fields into a demo path; increasing asset limits; forcing asset residency; forcing
map initialisation; bypassing native transitions; writing to unexplained offsets.

If one becomes necessary, prove why first.

## 1.8 State ownership

Before writing ANY engine state, answer: who normally writes it, who reads it,
when is it written, when is it consumed, which subsystem owns it, is it live-network
state / demo state / snapshot state / prediction state / rendering state, and does
the native path actually populate it?

**If those cannot be answered, do not write the field.**

S2's canonical failure: a recorded sequence number was written into an offset
*near* two proven fields, on the assumption that neighbouring fields have related
semantics. They did not. That single wrong write cost weeks.

> **Never assume nearby fields have related semantics.**
> **Never rename an offset based only on observed values.**

## 1.9 Function naming rule

Every function or global identified MUST be renamed in the IDB immediately, in the
same session. The IDB is the durable record. Name ONLY with full confidence:

1. **Twin-proven** — a named function in a reference IDB has the same structure,
   gates, call order and arguments. Use the reference's exact name. Best case.
2. **Behaviour-proven** — the decompile shows unambiguously what it does but no
   named twin exists. Use a DESCRIPTIVE name. An unidiomatic-but-accurate name is
   fine; a plausible-sounding engine name that is wrong is not.
3. **Not confident** — leave `sub_XXXXXX`. An honest `sub_` beats a wrong name,
   because a wrong name is invisible once written.

Record the basis in an IDB comment. If evidence later contradicts a name, RENAME
IT and note the correction. Same rule for globals, structs and enum members.

⚠ **Position-in-a-twin is NOT proof.** S2 named a function from its position in a
twin's call sequence, and it was wrong — the body was a tail-call into a shared
dispatch thunk. Verify from the body.

## 1.10 Cost and context management

Before every investigation action ask: *"What exact question am I answering?"* Then
gather only enough to answer it.

Do not: scan the whole binary without reason, decompile huge functions without a
question, request entire call graphs, dump thousands of lines, repeat failed
investigations, or rewrite working systems.

If IDA produces excessive output, timeouts, or repeated failures: **stop, reduce
scope, report "IDA scope exceeded useful analysis", and narrow the query.**

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 2 — THE PERMANENT RULES
# Every one of these cost real time on a previous project.
# Read them before computing any address, installing any hook, or
# explaining any runtime reading.
# ═══════════════════════════════════════════════════════════════════

## RULE A1 — SHOW THE ADDRESS ARITHMETIC. NEVER DO IT IN YOUR HEAD.

Two digit transpositions in one S2 session produced confident, completely wrong
conclusions — a hook that silently never installed, and a memory read of an
unrelated address that was then theorised about as an engine fact.

Every address computation gets WRITTEN OUT as `A + B = C` before it is used.
Compute it with a tool where practical. Then verify it landed (A2).

Later, three hex conversions in one session were wrong the same way. The fix that
worked: **make the script compute the hex** (`'%X' % OFF`) and never type a
converted constant.

## RULE A2 — VERIFY EVERY COMPUTED ADDRESS AGAINST A KNOWN SIGNATURE

Before trusting a base or an offset, prove the mapping with something whose content
is known independently — e.g. `read_string(base + <known string addr>)` returning
the expected text. Do this FIRST in any new process, and again whenever a reading
looks surprising.

> A surprising byte pattern is far more likely to be a wrong address than a
> surprising engine fact. Re-derive the address before theorising.

## RULE A3 — A HOOK IS NOT INSTALLED UNTIL IT SAYS SO IN THE LOG

A failed hook is indistinguishable from a hook that installed and never fired —
and those need completely different investigations. Capture and print the result:

```cpp
const bool ok = Hook::create("Name", target, detour, &orig);
Console::printf("[x] Name hook: %s (target=%p orig=%p)", ok ? "OK" : "FAILED",
                target, orig);
```

`orig == nullptr` is the tell: MinHook only fills it on success.

Print the FIRST line of any diagnostic stub BEFORE it touches any engine pointer,
so "the hook never ran" can be told apart from "the hook ran and faulted".

### RULE A3.1 — A DUPLICATE HOOK CAN REPORT SUCCESS. THIS IS A TRAP.

If another hook already exists on a target, `MH_CreateHook` returns
`MH_ERROR_ALREADY_CREATED`. If your wrapper treats that as success, MinHook never
writes `original` and **your detour is silently discarded**.

S2 lost a build and a live test to this, and later found a hook that had *never
executed once* in the project's entire history.

- **Before hooking anything, grep the whole source tree for the target address
  (every form) AND the function name.**
- If a hook exists, EXTEND THAT STUB or call out to your module from it. Never
  install a second hook on the same target.
- Make the wrapper return **false** on duplicate, null the trampoline, and print
  it via the real logger.

## RULE A4 — NEVER INFER A HOOK FROM A BRANCH AT A FUNCTION ENTRY

Protected binaries place jumps, thunks and flattened stubs everywhere. A branch at
a function entry proves nothing about ownership. Prove installation from the
create call's return value and a non-null trampoline (A3), never from disassembly
at the target.

## RULE A5 — OBFUSCATION: KNOW WHAT IS AND IS NOT REACHABLE

Fill in per IW7. From S2, the shapes to expect:

- Error/format strings with **zero xrefs**, and byte-searching their address as a
  displacement finds nothing → the reference is computed at runtime.
- Accessors reachable only through an indirect dispatch table.
- Trampolines that are control-flow-flattened (`lea rsp,[rsp-8] / mov [rsp],rcx /
  jmp qword ptr [rsp-8]` chains). Reading them live does NOT make them tractable.
- Thunks whose whole body is `return v0();` — any function that tail-calls one
  CANNOT be identified from its body.
- Globals that are **encrypted**, with a large obfuscated accessor that decrypts
  them. A "pointer" that reads as non-canonical garbage is the tell.

**Measuring STATE beat following CODE every single time.**

⚠ **But do not cry obfuscation too early.** S2 declared a caller "unreachable
behind a thunk" and CLOSED an investigation — the truth was that IDA had extended
one function's *bounds* over the following real code, so xrefs mis-attributed the
call site. The code disassembled perfectly. **When a caller looks unreachable,
disassemble the call site's address range directly before concluding anything.**

## RULE A6 — VALIDATE ANY ENGINE POINTER BEFORE DEREFERENCING IT

`if (!ptr)` is NOT sufficient. A global belonging to an inactive subsystem can hold
arbitrary non-zero junk.

```
if (p < 0x10000 || p > 0x00007FFFFFFFFFFF || (p & 7)) reject;
VirtualQuery(p, ...) -> require MEM_COMMIT, not PAGE_NOACCESS/PAGE_GUARD;
require the range you intend to read fits inside RegionSize.
```

For structures with far-flung offsets, validate the FAR offsets too, not just the
base.

## RULE A7 — NEVER GUARD ON A FIELD WHOSE INITIALISATION YOU HAVE NOT LOCATED

S2 gated a fix on a native "completed" byte that nothing initialised. A stale value
aborted a healthy code path before it read a single byte — a regression introduced
into previously working behaviour.

This is the Absolute Rule applied to LIFETIME rather than meaning. Knowing what a
field *means* is not enough; you must know who sets it, who clears it, and when.

**The safe pattern:** react only to something the engine itself just did in your
presence — e.g. latch on the ORIGINAL function returning its end-of-stream value,
which stale memory cannot forge.

## RULE A8 — DATE THE STATE. POST-MORTEM READINGS ARE NOT CAUSES.

S2 read three globals, built a theory about memory being freed underneath a
subsystem, and was reading a corpse: the fatal error had already fired and the
session had already torn down.

Before interpreting any live reading, establish WHERE IN THE LIFECYCLE it was
taken. Prefer readings captured AT the moment of failure (a hook at the error site)
over polling after it.

## RULE A9 — CONFIRM THE BUILD UNDER TEST IS THE BUILD YOU THINK

Check the LOADED MODULE, not the file on disk: compare the loaded module's hash and
timestamp against the deployed binary, and the process start time against the
deploy time. A game launched before a deploy runs the OLD binary and will happily
produce output that looks like a fresh test.

## RULE A10 — SAVE THE IDB; THE PACKED FILE IS NOT LIVE

IDA keeps the open database unpacked in its working files and only repacks on a
clean close. A hard kill leaves the `.i64` stale — S2's was TWO DAYS behind ~40
names. Save after any naming session. If IDA dies, do NOT delete the loose working
files; they are the only copy.

## RULE A11 — WHEN A CHEAP OFFLINE TEST CAN KILL A HYPOTHESIS, RUN IT FIRST

Two S2 hypotheses died offline for the cost of one script each — no build, no game
restart, no probe. Both would otherwise have become code changes tested in-game
across multiple restarts.

Before proposing a fix or a probe, ask whether the file, the IDB, or plain
arithmetic can already refute it.

## RULE A12 — STATE CORRECTIONS PLAINLY, AND PROPAGATE THEM

When a claim is withdrawn, mark it DISPROVEN or CORRECTED **at the point where it
was originally recorded**, do not silently drop it, and check whether anything
downstream was built on it. A wrong claim left standing misleads every future
session.

## RULE A13 — AFTER ANY CRASH, READ THE MINIDUMP FIRST

CoD titles typically write a minidump next to the exe on a fatal fault. **Read it
BEFORE writing any new probe or bracket.** It answers "where and why" directly,
where brackets only narrow it down. And because dumps ACCUMULATE, sweeping all of
them reconstructs which fix moved which crash.

This single rule replaced whole build-probe-run cycles repeatedly, and named two
crashes outright in one session.

Build a dump reader early (PART 8). Report: exception code/name, fault address
converted to IDA form, what address was read/written (call out NULL+offset), the
faulting thread's registers, and a heuristic stack scan.

⚠ Stack scanning is a SCAN, not a real unwind. Stale slots survive. Treat the SET
of frames as evidence and the ORDER as unreliable.

## RULE A14 — NEVER CACHE A COMPUTED ADDRESS AT FILE OR NAMESPACE SCOPE

If the module base is assigned during init, a file-scope initialiser runs FIRST and
the pointer resolves to the bare literal. S2's crash dump read *"EXECUTE at
0x0DDF90, OUTSIDE any module"*.

Resolve inside the function, or assign in init().

## RULE A15 — A DIAGNOSTIC MUST REPORT UNCONDITIONALLY

S2's first probe printed only inside `if (condition)`. When the condition was false
it printed nothing — indistinguishable from "the code never ran" — and a whole game
run was wasted.

**Never gate a diagnostic on the condition it exists to measure.** Report the
reading AND the verdict, always.

This rule later paid for itself: a probe that reported "gate opened 0 times" was
decisive, because 0 could be trusted.

## RULE A16 — A TOGGLE MUST NEVER SILENTLY DISABLE AN UNRELATED FIX

S2 had one flag gating four unrelated things — a compensation, a required
scaffolding allocation, a census and a table reload. Turning off the feature the
flag was NAMED for also removed the scaffolding, and the game crashed exactly as it
had before that scaffolding existed.

**One flag, one behaviour.** Split the decision at the point of use.

Related: an "off" switch must undo what "on" did and NOTHING MORE. S2's
`force_host off` called a full teardown instead of releasing its own latches, and
left the player unable to matchmake at all.

## RULE A17 — DECLARE THE EXACT RETURN WIDTH

A function returning `bool`/`char` defines only AL; the upper bits of RAX are
whatever was there. S2 declared such a trampoline as returning `int64` and read a
POINTER as the result — garbage that was TRUTHY, so a "fix" silently did nothing
while reporting success, and a probe reported a meaningless value as a measurement.

Declare the exact width the decompiler shows. Never widen. **Never narrow either**
— declaring a returning function as `void` means the caller reads an undefined RAX.

## RULE A18 — A DISCOVERY PROBE REPORTS EACH DISTINCT THING ONCE

S2 logged every call of a function that runs ~70 times per frame. One session wrote
**187,096 lines out of 187,693 — 99.7% of a 10 MB log** — burying every other
diagnostic.

The fix is not "log less often", it is to log each distinct VALUE once (a `set` of
things seen) and print a summary on the way out. A probe that answers "what values
exist" has a finite answer; streaming it is always wrong.

Before adding a per-call log, ask how many times per frame the call happens.

## RULE A19 — A HOOK IS NEVER A PASSIVE OBSERVER

S2 installed ~10 hooks on the matchmaking path purely to WATCH it, assuming a
pass-through detour changes nothing. **It broke matchmaking completely** — proven
by A/B — and the specific culprit was never isolated.

- a wrong return width corrupts the caller (A17, both directions)
- a wrong ARGUMENT LIST corrupts the callee (A23)
- a function that "looks like" a notifier may be a forwarder into the real work
- the cost is paid on the engine's own threads

Before hooking a function to observe it, decompile it far enough to know whether it
RETURNS anything and whether it DOES anything. Prefer capture points that are
genuinely leaf-like — a pure predicate that only reads state is about as close to
passive as a hook gets.

**When a subsystem misbehaves, suspect your own instrumentation FIRST.** It is the
newest code in the process.

## RULE A20 — KEEP A ZERO-HOOK CONTROL AVAILABLE FROM DAY ONE

A marker file that skips hook installation entirely is trivial to add and would
have found the above immediately. Any module that patches engine state should ship
one, and it should support disabling *groups* so a failure can be bisected across
boots rather than rebuilds.

⚠ Parse the marker STRICTLY. A substring match would have let the file's own
explanatory prose accidentally disable half the control run.

## RULE A21 — NEVER VALIDATE POINTER A THEN CALL A FUNCTION THAT RESOLVES B

S2 validated a context pointer obtained one way, then called an engine function
that resolved the same object a DIFFERENT way (an encrypted global vs a renderer
back-pointer). They genuinely disagreed — one was stale-but-set while the other was
NULL — and the engine dereferenced NULL + a large offset. Crash to desktop.

**If you validate a pointer and then call an engine function, that function must
not resolve the same object independently.** Either pass your validated pointer in,
or call the leaf that takes it as an argument. Inlining the wrapper and calling
only the leaf is the fix that worked.

## RULE A22 — READ AN ENGINE FUNCTION'S BODY BEFORE CALLING IT FROM THE MOD

Look for `retaddr` in the decompile. If a function inspects its own return address
(a common protection idiom — verifying the caller is a real CALL inside the image),
**do not call it from outside the module**: it takes different paths and returns
something a game-side caller never gets. In S2, one such function returned garbage
that produced three failed builds; another *infinite-loops*.

Reading the declarations is not enough — IDA lists `retaddr` among the locals,
which is easy to skim past.

**The escape:** if every return path is the same arithmetic, compute it instead of
calling. ⚠ But check the inputs first — S2 tried exactly that and got ZERO results,
because the global being indexed was ENCRYPTED and the big obfuscated function was
the decryptor.

## RULE A23 — THE ARGUMENT LIST MATTERS AS MUCH AS THE RETURN WIDTH

Crashed the game three times. IDA typed a function as taking **no parameters**.
Its entire body was `sub rsp,N / call inner / <use result> / ret` — it never sets
up the argument registers, it **FORWARDS ITS CALLER'S**. Declaring the stub with no
parameters let the compiler clobber the volatile argument registers before calling
the trampoline, and the inner function faulted on its first dereference.

- Declare the EXACT parameter list. Too FEW is as fatal as the wrong return type —
  nothing preserves argument registers across your stub.
- IDA's `()` is not evidence of a nullary function.
- **The tell:** `sub rsp,N / call X / <use return> / ret` with no register setup.

Check the DISASSEMBLY for whether argument registers are set up or merely passed on.

## RULE A24 — BEFORE REIMPLEMENTING, ASK WHETHER THE ENGINE ALREADY DOES IT

The most expensive lesson of the S2 project. A feature was rebuilt from scratch
across four failed builds and one game hang — enumerate entities, resolve names,
compute head positions, project to screen, draw. The engine had the whole system
already, fully working, merely **gated** by a single predicate. Ungating it was
~20 lines and was confirmed working on the first try; the reimplementation was
~700 lines and never worked.

Ask it every time. The same question applies to anything with a visible native
equivalent.

Corollary: prefer calling the engine's own function with the engine's own arguments
over reproducing its effect. **But see A25** — *where* you call it is part of the
contract.

## RULE A25 — LIFECYCLE POSITION IS PART OF A CALL'S CONTRACT

S2 transcribed an engine call site correctly — right function, right arguments,
right masks — and placed it later in the sequence. It freed resources that the UI
had already bound, and crashed. The analysis was right; the POSITION was wrong.

When transcribing a call site, transcribe WHERE it sits relative to the other
subsystems, not just the arguments.

## RULE A26 — CHECK WHETHER THIS REPO ALREADY SOLVED IT

Twice, S2 re-derived something an existing module in the same source tree already
had — including the real contract of an accessor, a struct stride, and sanity
checks. Grep the tree before deriving.

⚠ **And check whether that existing code was ever actually verified.** The second
time, the existing module's constants were themselves unproven and inherited as
fact. "It's in the repo" is not "it works".

## RULE A27 — A SUCCESS CONDITION MUST NOT BE TRUE BEFORE THE WORK STARTS

S2 gated a feature's "did it work" test on flags that are already set at idle. The
feature armed, immediately declared victory, disarmed, and re-armed — oscillating,
never actually doing anything, while reporting success.

Before using a flag as a success signal, check what it reads in the IDLE state.

**Related, and just as important: never verify a fix using the value the fix
writes.** A fix that forces state will happily verify itself. Verify the thing it
was supposed to *cause*.

## RULE A28 — CACHE ANYTHING READ FROM ENGINE MEMORY ON A HOT PATH

`VirtualQuery` is a kernel transition. S2 called it once per character of a name,
for 18 players, every frame, on the render thread — ~700 syscalls per frame — and
**hung the game**. Same defect had already been documented for the GUI thread and
written into this file; it was then written into a hotter path anyway.

Probe whole spans once, not per element. Cache readouts that change slowly. And do
not call asset-system functions (font/material registration) every frame from the
render thread — the loader may hold the same lock.

## RULE A29 — NEVER RUN TWO BUILDS AT ONCE

Concurrent MSBuild instances produce errors that look like real code errors but are
not: same-PDB contention (`C1041`) and corrupt object files (`LNK1136`). Recovery:
wait for the compilers to exit, delete the corrupt artefacts, rebuild once.

**Check for a running build before starting one** — the user may be building in the
IDE at the same time.

(Distinct from a STALE pdb causing `LNK1201`, which is fixed by deleting that one
file.)

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 3 — WORKING STYLE
# Set by the user. These override default assistant behaviour.
# ═══════════════════════════════════════════════════════════════════

## RULE W1 — DO NOT STOP ON A SELF-CORRECTION

When a new finding disproves an earlier one, note the correction IN ONE LINE and
CONTINUE in the same turn. Do not stop to report, do not ask whether to proceed,
do not write a paragraph about having been wrong.

Corrections still go in this file — as a line of record, not as a reason to halt.

## RULE W2 — EVERY SCAN GETS A DIAGNOSTIC

Any IDA query, memory read, log parse or offline tool run is followed immediately
by what it MEANS. State the reading, then the interpretation, then what it rules in
or out. A dumped number with no verdict is not a result.

## RULE W3 — RUN UNTIL A HARD STOP

Keep working through the chain without pausing for approval. A HARD STOP is only:

- the user must do something in game (load a map, join a match, press a key)
- a build/deploy needs the game closed and it is running
- a decision genuinely belongs to the user (scope, risk, which of two products)
- the evidence has run out and the next step needs a measurement we cannot take

Everything else — a disproved theory, a failed read, a wrong address, a dead end in
one branch — is NOT a stop. Correct it and carry on.

## RULE W4 — NO LAZY ROUTES

Do not reach for the first switch that makes a symptom disappear. S2 disabled an
entire subsystem to hide one stray element; it removed everything the user wanted
to keep, and did not even remove the target. **Before flipping an engine-wide
switch, enumerate its readers** — one decompile would have prevented it.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 4 — THE PLAYBOOK: METHODS THAT ACTUALLY WORKED
# ═══════════════════════════════════════════════════════════════════

## 4.1 Twin-diff against a named reference build

The highest-value technique available. Decompile the target function and the
reference's named twin side by side.

A match requires evidence, not a name: similar arguments, similar callers, similar
data access, similar side effects, similar execution purpose. Record:

```
REF:    function / address / purpose
TARGET: function / address / evidence for the mapping / differences
```

**What makes a mapping safe:** structural equivalence — same gates in the same
order, same call sequence, same literals — not position. Shared string literals
and identical field-write patterns are strong corroboration.

**What makes it unsafe:** position in a caller's call sequence. That produced a
wrong name in S2 which had to be reverted.

Watch for width differences that are *expected*: a 32-bit reference reading a field
at `+12` where the 64-bit target reads `+16` is the pointer-size change, and
agreement on that pattern is itself evidence.

## 4.2 ⭐ Bulk naming via string anchors

This named **371 functions in one pass** in S2, then **587 more** in a second
binary. Strings survive across builds and even across titles.

1. In the NAMED reference, build `{distinctive string -> the one named function
   that references it}`. Keep only strings referenced by exactly ONE function.
2. In the TARGET, read the read-only data segments **once** with a bulk byte read
   and substring-search in Python.
   ⚠ **Do NOT use IDA's string-list API on a large image** — it triggers a full
   strlist rebuild and times out the MCP. This happened twice.
3. For each shared string, take its TARGET code xrefs. Keep only strings referenced
   by exactly ONE target function (unambiguous on both sides).
4. **Vote:** a target function is a candidate only if every string backing it
   implies the SAME reference name.
5. Reject: already-named target functions; reference names claimed by more than one
   target function; names that already exist elsewhere in the target.
6. Apply, with an IDB comment recording the anchor(s) and warning that only the
   NAME is ported — addresses differ.

⚠ **The filter that matters is DISTINCTIVENESS, not length.** A first pass used a
≥20-character rule and threw away the single most valuable anchors in the set —
short, unique protocol tokens. A long string can be generic. Score on "does it
contain a real identifier after stripping format specifiers", then require either
2+ distinctive anchors or one long/underscored one.

**Validate the port.** In S2, five results independently matched things established
months earlier by other means, and one ported function decompiled structurally
identical in a third binary. Look for that kind of corroboration before trusting
the batch.

## 4.3 ⭐⭐ Controlled pair + wrapper bisection

**This is the technique that finally cracked a bug that had defeated two days of
bitstream analysis, and it required no decompiling at all.**

Get two artefacts that differ in exactly one dimension — same map, same build, same
tool, one working and one not. Then bisect mechanically by swapping halves:

```
p1  broken payload  + working wrapper     PLAYS  -> the payload is fine
p2  broken file + two header fields fixed FAILS  -> not those fields
p3  broken file + working FOOTER          PLAYS  -> it is the footer
p4  broken file + working HEADER          FAILS  -> not the header
p5  broken file + working footer sub-block PLAYS -> narrow further
p6  broken file + ONE table spliced in    PLAYS  -> that table, alone. CAUSAL.
```

Six surgeries, six single-variable answers.

**Reach for a controlled pair before modelling anything complicated.** The pair
only became possible when the user produced the matching working artefact — so ask
for it early rather than analysing around its absence.

## 4.4 Measure state, don't follow code

Repeatedly decisive. When protection makes code unreadable, measure what it
*produced*: pool occupancy, bitmap populations, counters, struct contents.

S2 spent three rounds of static reasoning about which of several candidate fields
held a value; one direct memory read settled it in a minute. **When a value is
observable in a running process, READ IT.**

Reading memory yourself is not "probing" — it costs the user nothing.

## 4.5 Offline tooling first (RULE A11 in practice)

Build read-only tools that answer questions with no game running. In S2 these
killed multiple hypotheses for the cost of one script each and eventually
reproduced a failure *bit-for-bit* offline, which is what made the diagnosis
certain.

The pattern that works: transcribe the engine's own reader/parser faithfully into
Python, **validate it against known-good data first**, and only then use it on the
failing case. A model that reproduces healthy data correctly is trustworthy on
broken data.

## 4.6 Debugging a hang: find the spinner before reading the blocked thread

Enumerate threads with CPU times, suspend each, read the instruction pointer and
scan for return addresses in the module range. The thread *burning a core* names
the cause; the blocked main thread only names the symptom.

⚠ A module-only stack scanner cannot answer "is our code involved" — include the
mod's own address range in the scan.

## 4.7 Cheap decisive in-game tests

- **A server-only dvar is a free host/client test.** If setting it changes nothing,
  you are a client.
- **A/B by marker file** (RULE A20) rather than by rebuild.
- **One console command beats one build.** Before shipping a probe, check whether
  an existing command or dvar already answers the question.

## 4.8 Memory-scanning discipline

**NEVER run an unscoped scan against the game process.** A modern CoD's footprint
is hundreds of MB and a full scan effectively takes the tool away for the session.

1. **Prefer a direct read over any scan.** Most addresses are already proven in the
   IDB, and `VA = base + IDA` (once A2-verified) makes them directly readable.
2. If a search is genuinely required, scope it to the module.
3. Narrow by address range whenever the API allows.
4. Prefer breakpoints and access-tracking over value scanning — they answer "who
   touches this" directly.

If a scan seems unavoidable, say so and explain why BEFORE running it.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 5 — REFERENCE BINARIES
# ═══════════════════════════════════════════════════════════════════

IW7 sits in the Infinity Ward engine line. The available references are unusually
strong for this target — record the actual ports and paths here as they are set up.

```
IW7  (Infinite Warfare)   TARGET      port <TBD>   <- the authoritative IDB
H1   (MWR, PC)            port <TBD>
H1   (MWR, PS4)           port <TBD>   ⭐ FULLY NAMED DEBUG BUILD — real symbols,
                                          asserts with source paths, enum tables
AW   (S1, Xbox 360)       port <TBD>   fully symboled, mangled C++ names
MW3  (IW5)                port <TBD>   fully named
CoD4 (IW3)                port <TBD>
S2   (WWII)               port <TBD>   the previous project's IDB
IW8  structures           ../iw8-mod/client/engine/iw8/*.hpp  (community, named)
```

## 5.1 ⭐ MWR is the most likely near-twin — VERIFY THIS FIRST

**HYPOTHESIS.** MWR shipped alongside Infinite Warfare and is understood to be
built on the same engine generation. If true, the fully-named PS4 debug build is
a near-perfect Rosetta stone for IW7, and PART 4.2's bulk naming should cover a
large fraction of the binary immediately.

**A debug build is worth even more than a symboled one**, because its asserts carry
the ORIGINAL SOURCE PATHS and field names verbatim — e.g. an assert naming a struct
field is direct evidence of that field's identity, not an inference.

Do the measurement in PART 0.3 before building anything on this.

## 5.2 There is already a working mod for the near-twin

The `h1-mod` project (MWR) has a **working demo record/playback system** and a large
body of solved problems in the same engine family. Treat it as:

- a **behavioural baseline** — proof the correct behaviour exists and what it looks
  like;
- a **source of already-solved designs**, not of addresses.

Do not copy its offsets. Do re-read its notes on what went wrong, so the same walls
are not hit twice.

## 5.3 How to reach an IDB when its MCP namespace is missing

MCP stdio servers are spawned at session start. If IDA was not listening then, the
namespace is absent for the whole session even after IDA comes up.

The IDB is still reachable by direct JSON-RPC:

```
POST http://127.0.0.1:<port>/mcp
{"jsonrpc":"2.0","id":1,"method":"tools/call",
 "params":{"name":"<tool>","arguments":{...}}}
```

Keep a small helper script for this.

⚠ MCP ports can reset after a crash if the port is stored in the IDB. Pin them with
an environment override and per-IDB launcher scripts.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 6 — ENGINE-FAMILY KNOWLEDGE
# ALL OF THIS IS **HYPOTHESIS** FOR IW7 UNTIL RE-DERIVED.
# It is here to tell you WHAT TO LOOK FOR, never what to assume.
# ═══════════════════════════════════════════════════════════════════

The IW engine line is highly conserved across titles, especially the message and
demo layers. Where one title has a name, the others very likely have the same
field — **very likely is not proven.**

## 6.1 `msg_t` — the network message struct

Named in IW8 (community-reconstructed, with a size assert) and independently
derived in S2 from the init/begin-reading functions. Expect a ~56-byte struct with:

```
overflowed | readOnly | data ptr | split data ptr | maxSize | curSize |
splitSize | readCount (byte cursor) | bit position | lastEntityRef |
targetLocalNetID | compressionFlags
```

**Derive it from IW7's own `MSG_Init` / `MSG_BeginReading` equivalents.** The key
behavioural facts to re-establish:

- byte reads (Long/Short/Byte/String) advance the BYTE cursor only and never touch
  the bit position;
- bit reads use the bit position and resync from the byte cursor only when aligned;
- consequently a small bit-field read at a byte boundary can consume a WHOLE byte
  and leave the bit position mid-byte, so the NEXT bit read comes from the same
  byte without moving the byte cursor.

That last property is subtle, is where S2's hardest bug lived, and must be modelled
exactly in any offline tool.

`lastEntityRef` is the running index in the monotonic delta-index reader — which is
why an entity list must strictly increase and why a specific error id fires when it
does not.

## 6.2 Demo file format

S2's demo system was inherited from MW3's, so IW7's is likely related to MWR's.
Expect to find, and **re-derive each one**:

- a fixed-size header whose first fields are a VERSION and a HEADER SIZE that is
  also the body offset; a recording client slot; an "exe mode" value; and a large
  opaque state blob copied wholesale into playback state;
- a footer located by seeking from the end, validated by a magic equal to the
  version, containing counted tables — including a full **NetConstStrings** table
  that playback installs, so recorded indices resolve against the recorded tables;
- a body that is a **byte-tagged packet stream**: one type byte, then per-type
  payloads (archive / snapshot / alternate snapshot / commands), terminated by a
  type-0 packet.

**The generic failure mode:** a packet consumed with the wrong length desyncs the
cursor, and the next type byte is garbage. The error is therefore a FILE-POSITION
symptom, not a parser bug — fix the length, never nudge the read cursor.

⭐ **The single most valuable lesson from S2's demo work:** the game's own demo
WRITER can disagree with its own READER. Three separate framing mismatches were
found (a missing length prefix, a one-bit shortfall, and a missing table). If demos
do not play, **suspect the recorder, not just the player.**

## 6.3 Server message dispatch

Expect a small opcode read (a few bits, not necessarily a byte) dispatching to
gamestate / server command (text and binary) / snapshot / EOF, with connection-state
gates that REJECT rather than error — e.g. gamestate refused above a certain
connection state, snapshots refused below one. A silently-dropped message looks
identical to one that was never sent.

Reliable commands are typically stored into a ring indexed by `sequence & mask`.

## 6.4 Netfield tables and delta encoding

Expect a flat array of `(table pointer, entry count)` pairs, with per-entity-type
lists selected by a clamped type index, and separate globals for the live tables vs
demo tables (swapped by a demo-version-dependent setup function).

**The index bit width is derived from the table ENTRY COUNT.** So a disagreement
about table size between writer and reader shifts every index read — which is what
the monotonic-index error actually diagnoses.

The delta loop shape: one bit says "unchanged, copy the baseline"; otherwise read a
last-changed-field index at the derived width, then repeatedly read a skip count,
copy skipped fields from the baseline, and decode one field.

## 6.5 Configstrings and NetConstStrings

Expect a packed arena: an offsets array immediately followed by string data, with a
"get" that returns `data + offsets[i]`. The modify handler typically REBUILDS the
whole arena rather than patching one entry — so **offsets and data are only
meaningful as a matched pair captured at the same instant.**

Part of the index space is NOT replicated: NetConstStrings come from fastfile-loaded
tables, and a server sending a replicated update for such an index is an error.
Expect a type table and per-type ranges.

⚠ There may be **more than one storage** for the same conceptual table — e.g. an
index→string pointer table and a name→index block list, populated by different
paths. S2 lost significant time to restoring one and assuming the other was fine,
and then to a THIRD (a registry that the writer serialises from). **Enumerate the
storages before concluding a table is "loaded".**

## 6.6 Dvars

Expect the value at a fixed small offset from the dvar pointer, with a type byte
just before it (in S2, `+12` type / `+16` value on x64; a 32-bit build had `+12`
value). Some titles register dvars by NUMERIC NAME strings — if so, real names can
only come from a source dump or from identifying a dvar by what reads it.

⚠ Some getters are obfuscated; reading the raw field may be wrong for those. If a
bool ever reads as a large number, the read is wrong, not the engine.

## 6.7 Asset system

Expect per-type pools with fixed COUNT limits, parallel tables for pool size and
type name indexed by an asset-type enum, and an allocator that raises a limit error
through a path that may BYPASS the normal error function.

**A registration COUNT limit is not a memory limit.** S2 exhausted a pool at 100%
while actual residency was 12% — different problems, opposite fixes.

Zones are released by flag-group masks; if the release mask matches no loaded zone
it is a silent no-op and zones accumulate forever.

## 6.8 Protection

Assume the retail build is protected. Expect: strings with no xrefs, indirect
dispatch tables, flattened trampolines, encrypted globals with obfuscated
accessors, and return-address checks (RULE A22).

**Static analysis of the protected regions is usually not the productive route.**
Measuring state and reading crash dumps repeatedly beat following code.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 7 — LIKELY OBJECTIVES
# Confirm with the user; do not assume the S2 backlog transfers.
# ═══════════════════════════════════════════════════════════════════

Based on the S2 and h1-mod history, the probable targets, in the order that worked:

1. **Demo playback** — get the game's own demo system working end to end. In S2
   this was the whole project and it succeeded by fixing the RECORDER, not the
   player.
2. **Demo recording** — find and enable the record trigger. In S2 it was gated by
   a predicate whose config terms were off; the capability was fully intact.
3. **Seeking / rewind / fast-forward** — keyframes or restore points, plus a clock.
   A useful shortcut exists: advancing a realtime variable often fast-forwards
   through the engine's own feed loop, while rewinding genuinely needs state
   restoration (the clamp against the previous frame's time is why).
4. **Camera work** — free camera, then a dolly/path camera with markers drawn by
   the ENGINE's own 2D primitives, projected with the engine's own world-to-screen
   function so it scales with FOV and resolution.
5. **HUD control** — minimal HUD for capture. Learn which elements are native, which
   are UI-script model-driven, and which are event-driven; they need different
   levers. Check for a shipped broadcaster/caster mode before building anything.
6. **Bots / private match tooling** — naming, appearance, counts. Prefer the
   engine's own entry points; a bot-add path a human connection cannot reach is
   *structurally* safe, which beats any runtime "is this a bot" check.
7. **Hosting / lobby control** — scope this carefully and early. In S2, running the
   match on the user's own machine turned out to be **impossible** for public
   playlists, while owning the LOBBY was entirely achievable. Establish which one
   is being asked for before building.

**A recurring shape worth expecting:** most of these features already exist in the
engine and are merely gated (RULE A24). Look for the gate before writing code.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 8 — TOOLING TO PORT
# ═══════════════════════════════════════════════════════════════════

From the S2 project's `tools/`. Ported by generality:

## Directly reusable (game-agnostic)

```
crash_dump.py     minidump reader: exception, fault address as IDA_0x..., what
                  was read/written, registers, module-range stack scan.
                  ⭐ BUILD THIS FIRST — RULE A13 depends on it.
dump_stacks.py    scan a halted process's thread stacks for module return
                  addresses.  ⚠ include the MOD's range too.
export_idb.py     dump an IDB's function graph (address, size, name, callees).
match_builds.py   match two builds by size + call-graph propagation.
                  ⭐ Include a HOLDOUT VALIDATION pass — hide known pairs, measure
                  precision. S2 measured 99.36% and that number is what made the
                  output trustworthy.
                  ⚠ A function whose SIZE CHANGED cannot be matched by size, and
                  propagation may quietly fill its slot with a same-sized
                  stranger. Keep a hand-verified overrides file, and require every
                  override to carry its evidence.
resolve_gaps.py   recover unmatched functions by reading the call instruction at
                  the same byte offset inside an already-matched caller.
                  Require >= 2 agreeing callers.
```

## Needs retargeting to IW7 (structure reusable, data is per-game)

```
huffman.py        message decompressor; the table must be pulled from the
                  PROCESS DUMP, not the retail exe.
demo_read.py      demo container walker + failure locator. Add a --simulate mode
                  that reproduces a named mis-parse and reports the exact byte it
                  dies on — that is what turns "it broke" into a diagnosis.
svc_walk.py       decode messages and walk the opcode stream with a BIT-EXACT
                  reader model. Validate against known-good data first.
netfields.py      extract the netfield tables.
asset_log.py      offline accounting from saved console logs + census dumps.
```

## Build a log-analysis habit early

Make the mod write a console log to a known path and parse it offline. S2's asset
limit was solved entirely from saved logs plus census dumps, with no game running.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 9 — SAFETY, SCOPE AND ANTICHEAT
# ═══════════════════════════════════════════════════════════════════

**Establish this before writing any code, and record the answer here.**

- Does IW7 run an anticheat, and is it active in the modes being targeted?
- Is there an offline/private/local mode where this work is unambiguously fine?
- Is the intended use single-player, private matches, and demo review — or does it
  touch live public multiplayer?

The S2 project's conclusion was that tooling should be isolated from the machine
running live multiplayer. Decide the equivalent here deliberately.

**Scope note carried from S2:** work that affects only your own client's rendering,
your own demo files, and your own private matches is a different proposition from
anything that changes what other players experience. Keep that line explicit, and
raise it with the user if a request crosses it.

---
---

# ═══════════════════════════════════════════════════════════════════
# PART 10 — INVESTIGATION STATE
# The living record. Update at the end of ANY session that proves,
# disproves, or opens something.
# ═══════════════════════════════════════════════════════════════════

Do not let this drift. An entry later disproved is MOVED to Disproven, not silently
deleted. Never restart from zero: read this section, review previous discoveries,
and continue from the last unresolved question.

## PROVEN

*(nothing yet)*

## STRONG INFERENCE

- MWR is close enough to IW7 to serve as a naming twin. **UNMEASURED** — PART 0.3.

## HYPOTHESIS

- Everything in PART 6.

## UNKNOWN — open questions, highest value first

1. The address convention and a verified A2 signature. *(blocks everything)*
2. IW7 ↔ MWR structural distance, measured.
3. <TBD>

## DISPROVEN — do not revisit without new evidence

*(nothing yet)*

## FAILED ATTEMPTS — do not repeat without new evidence

Record each as:

```
Attempt : what was tried
Result  : what happened, with the measurement
Reason  : which assumption was wrong
Reopen  : what specific NEW evidence would justify retrying
```

*(nothing yet)*

---

# NAMED IN THE IDB

Maintain a list here of names applied, grouped by basis, so a later session can
re-judge them:

```
TWIN-PROVEN (reference name used, structural match):
    <addr>  <name>          <- from <reference>, evidence: ...

BEHAVIOUR-PROVEN (descriptive; NOT necessarily the real engine name):
    <addr>  <name>          <- evidence: ...

MAPPED BY POSITION / WEAKER BASIS — RE-CHECK IF ANYTHING DEPENDS ON THEM:
    <addr>  <name>          <- basis: ...

DELIBERATELY NOT NAMED (insufficient confidence):
    <addr>                  <- what is known, what is missing
```

---
---

# ═══════════════════════════════════════════════════════════════════
# FINAL STANDARD
# ═══════════════════════════════════════════════════════════════════

A subsystem is not understood because the screen looks correct, a weapon appears,
the camera looks right, playback advances, a crash disappears, or a packet parses.

It is understood only when the full chain can be explained with evidence from the
current IDB and the actual data:

```
bytes  ->  parser  ->  storage  ->  state transition  ->  consumer
```

The goal is not to produce code quickly. The goal is to understand the engine
behaviour, preserve discoveries, avoid speculation, find the first divergence, and
make the smallest correct change.

**When uncertain: do less, trace more.**
**When an offset looks right: prove it.**
**When a patch fixes a symptom: find out why before keeping it.**
**When something looks like a timing problem: find the competing writer before
touching the clock.**
**When something looks like an asset problem: prove the lifecycle is correct before
touching limits.**
**When a field's meaning is unknown: leave it unknown until proven.**
