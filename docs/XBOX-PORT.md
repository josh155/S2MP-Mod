# Microsoft Store / Game Pass port

Status as of 2026-08-15. Everything below was established offline — no Store launch
has happened yet. Sections marked **BLOCK** are things to come back to.

---

## Verdict

The address port is **largely mechanical**. The hard part is not the 341 addresses;
it is the loader and the writable-file layout, both of which are now designed but
unverified.

The reason it is mechanical: the two builds are the **same source compiled with the
same settings**. Across 28,428 automatically matched function pairs, **28,391 are
identical in size to the byte (99.9%)**. Only 37 differ, and only **one** of those
is a function the mod touches.

---

## The pipeline

Four offline tools, run in order. All talk to the two IDBs over the ida-pro-mcp
JSON-RPC endpoint (Steam 13337, Store 12346).

| tool | does |
|---|---|
| `tools/s2_export_idb.py` | dumps an IDB's function graph (size, name, callees) to JSON |
| `tools/s2_match_builds.py` | matches the builds: name + unique-size seed, then call-graph propagation |
| `tools/s2_map_globals.py` | resolves data globals via instruction-offset alignment |
| `tools/s2_emit_buildmap.py` | writes `src/BuildMap.Store.inc` |

```
python tools/s2_export_idb.py 13337 <scratch>/steam_funcs.json
python tools/s2_export_idb.py 12346 <scratch>/xbox_funcs.json
python tools/s2_match_builds.py <scratch>/steam_funcs.json <scratch>/xbox_funcs.json --out <scratch>/build_map.json
python tools/s2_map_globals.py  <scratch>/build_map.json <scratch>/globals_map.json
python tools/s2_emit_buildmap.py <scratch>
```

### How functions are matched

Seed on names shared by both IDBs (741) plus sizes unique to exactly one function
in each build (630), then propagate: for a matched pair `(s, x)`, if `s` calls a
function of size *N* and exactly one unmatched callee of `x` also has size *N*, the
pair is forced. Same in the caller direction. Iterate to a fixed point — 11 rounds,
28,428 matches.

**Accuracy is measured, not assumed.** Holdout test: hide half the shared names
from the seed and re-derive them.

```
recovered 310/370 held-out pairs, 2 WRONG, 58 not matched
=> precision 99.36%   recall 83.8%
```

### How data globals are matched

A global has no size, no name and no call graph, so none of the above applies. But
it is *referenced by instructions*, and because the builds share codegen, an
instruction *N* bytes into a Steam function is *N* bytes into its Store twin. So:
find a referencing instruction, take its offset, read the instruction at the same
offset in the twin, use its operand. Guarded by requiring the **mnemonic to match**
and **≥ 2 referencing sites to agree**.

### Independent verification

The pipeline was checked against addresses derived months earlier by hand, by
decompiling the GSC binding table — none of which was fed to the matcher:

```
g_hostingEnabled      steam 0xf9e9d8  -> 0x106ba28   MATCH
Session_CanHostServer steam 0x8534b0  -> 0x849380    MATCH
LobbyParams_GetPrivate            ... -> 0x1947c0    MATCH
LobbyParams_GetRequireOpenNat     ... -> 0x194800    MATCH
Session_IsHostingEnabled          ... -> 0x84ce50    MATCH
Session_GetRequiredUploadForCount ... -> 0x660c00    MATCH
Session_GetRequiredPingForCount   ... -> 0x660c60    MATCH
Playlist_IsAlwaysSearch           ... -> 0x651620    MATCH

8 of 8 correct.
```

`dvar_online` was confirmed separately by decompiling the Store twin of
`Com_IsOnlineGame`, which reads `off_187CDF8` — exactly what the resolver predicted.

---

## Coverage

```
mod addresses                     341
  function starts                 221  ->  219 mapped
  mid-function code                11  ->   10 computed from the owner's match
  data globals                    109  ->  104 resolved (97 strong, 7 single-site)
  ------------------------------------------------------------------
  MAPPED                          334  (98.0%)
  unresolved                        7
```

By module, so nothing can hide:

| module | addresses | mapped |
|---|---|---|
| `demo_native.cpp` | 86 | 86 |
| `demo_game.hpp` | 66 | 65 |
| `demo_playback.cpp` | 32 | 29 |
| `FuncPointers.cpp` | 65 | 65 |
| everything else | — | — |
| **demo subsystem** | **197** | **193 (98.0%)** |
| **whole project** | **389 refs / 341 distinct** | **98.2%** |

The demo system is the single largest consumer of addresses in the mod and it is
covered at the same rate as everything else.

### The seven still unresolved

```
0x16A570   mid-function inside sub_16A450   demo_game.hpp
0x1C04E0   5-byte function, no matched caller
0x189D780  data   demo_playback.cpp
0x28EB110  data   demo_playback.cpp
0x476C191  data   demo_playback.cpp
0xD4EE43C  data   dlc.cpp
0xE464D98  data   DevDraw.cpp
```

None fails silently — each returns poison and names itself in a minidump.

---

## The demo file format is IDENTICAL between builds

Worth more than the address work, because it means demos are cross-compatible and
none of the demo tooling needs changing.

`CL_Demo_Play_f` validates the same constants in both builds:

| gate | Steam | Store |
|---|---|---|
| `clc+262760` version | `== 29` | `== 29` |
| `clc+262764` header size | `== 79384` | `== 0x13618` — **the same number** |
| `clc+262784` exe mode | `== 5` | `== 5` |
| header state blob | `memcpy(…, 0x135FC)` | `memcpy(…, 0x135FC)` |

The Store IDB renders `79384` as `&loc_13618` because that immediate happens to be
a valid code address there. `0x13618 == 79384` exactly — which is also the file
offset the packet stream begins at, already documented.

So `tools/s2_demo_read.py`, `s2_dm_to_demo.py`, `s2_huffman.py`, `s2_svc_walk.py`
and the type-21 footer repair all apply unchanged, and a demo recorded on one build
should play on the other.

---

## The matcher CAN be wrong — and how that is handled

Caught 2026-08-15 while chasing the gaps, and worth stating plainly because it
bounds how much the table can be trusted.

`Com_Error` is **607 bytes on Steam and 552 on Store** — one of the 37 genuinely
divergent functions (Steam vs GDK error reporting). Size matching therefore could
not pair it, and propagation handed Store `0x8CA40` to Steam `sub_82D5F0`, an
unrelated 552-byte function. A real false positive, exactly the 0.64% the holdout
predicted.

It was caught by call-site evidence: `CL_Demo_Play_f` is matched, and both builds
call the error function at the same two positions with the same unique strings —
`"428 %s %s"` and `"EXE_ERR_INVALID_DEMO_FILE"`. So Store `0x8CA40` **is**
`Com_Error`.

That bad pair never reached the emitted table (`sub_82D5F0` is not an address the
mod uses), but it did lock `Com_Error` out of it.

**`tools/s2_overrides.json`** is the fix: hand-verified pairs, applied last, that
beat the matcher. Every entry must carry its evidence — an override with no stated
basis is worse than a gap, because a gap faults loudly and a wrong entry does not.

**Lesson for anyone extending this:** a function whose SIZE CHANGED cannot be
matched by size, and propagation may quietly fill its slot with a same-sized
stranger. Cross-check anything on the 37-function divergent list against a call
site before trusting it.

---

## The translation layer

`_b` is the single funnel every hardcoded address passes through, so the whole port
hooks in at one point rather than 341 call sites:

```cpp
// src/game.cpp
size_t _b(const size_t val) { return build_map::resolve(base, val); }
```

`src/BuildMap.hpp` + the generated `src/BuildMap.Store.inc`.

**Build detection** is by the `EXE_ERR_PROCESS_DEMO_FILE_FAILED` string — the same
signature RULE A2 already uses to verify a Cheat Engine attachment. Steam has it at
IDA `0xBCE9E0`, Store at `0xC6D5B0`. Not a version number and not a module size,
both of which a patch changes.

**Steam is a strict no-op**: one predictable branch, then `base + val`.

**An unmapped address never falls through to the Steam value** — that would point at
arbitrary memory and corrupt it silently. It returns a poison VA instead:
`0x0000DEAD00000000 + (steam_offset & 0xFFFFFF)` — canonical, guaranteed unmapped,
and carrying enough of the offset that a minidump names which entry was missing.
`build_map::unmapped_hits()` counts them.

### Why this is worth having even if the port never ships

All 341 addresses are currently literals scattered across 25 files. **One Steam
patch invalidates every one of them.** With the table and the pipeline,
re-deriving them after a patch is a tool run, not a re-do.

---

## Behavioural differences between the builds

37 of 28,428 matched functions differ in size. A size delta *is* a logic change, so
the matcher finds these for free. The list reads exactly as a Steam→Store port
should:

| function | Steam | Store | note |
|---|---|---|---|
| `bdXHTTP__prepareEndPoint` | 5576 | 357 | Demonware HTTP — XCurl replaces Steam transport |
| `SV_DirectConnect` | 409 | 3644 | **+3235**, the largest addition anywhere |
| `bdHTTPWrapper__startCopy` | 2176 | 1120 | same area |
| `Script_IsSteamSessionBad` | 224 | 80 | Steam-specific, gutted |
| `Friends_GetPresence_Platform` | 540 | 225 | platform social |
| `CL_Disconnect` | 5393 | 5088 | |
| `Session_CanHostServer` | 309 | 264 | already known — Store has no bandwidth-test gate |
| `SV_SpawnServer` | 2654 | 2638 | **the only mod target that differs** |
| `malloc`/`free`/`tolower`/`_stricmp` | 6 | 7 | different CRT stubs, irrelevant |

`Session_CanHostServer` appearing here is another cross-check: that difference was
found by hand on 2026-08-12 and the matcher flagged it independently.

**`SV_SpawnServer` is benign.** The signature is identical
(`__int64 __fastcall(__int64, int, unsigned int, unsigned int)`), the −16 bytes is
one eliminated local, and the mod only hooks its *entry* to print. A body change
cannot affect a prologue hook.

---

## The loader

### Why the Steam launcher cannot be reused — measured, not assumed

```
exe              C:\Program Files\WindowsApps\38985CA0.CallofDutyWWIIPCMS_
                 2.0.18.0_x64_WW_5bkah9njm3e9g\s2_mp64_ship.exe
Test-Path        True            <- the path is enumerable
[IO.File]::Open  ACCESS DENIED   <- but the file is not even readable
```

`CreateProcessW(CREATE_SUSPENDED)` needs read+execute, so it fails. Even if it
didn't, a process created that way has no package identity, which a GDK title
checks for.

**IFEO does not rescue it.** IFEO keys are per image *name*, and the Store
executable is called `s2_mp64_ship.exe` — **the same name as the Steam build**, so
one key would intercept both. And the stub it launched would hit the same ACL.

### What `tools/Launch-S2-Store.ps1` does instead

`IPackageDebugSettings::EnableDebugging` — the documented mechanism packaged-app
debuggers use. With a null debugger command line it tells the OS: next activation
starts **suspended**. The OS performs the activation, so the process gets correct
package identity, and the "nothing has run yet" guarantee the mod depends on is
preserved.

```
EnableDebugging(pfn, null, null)      arm
ActivateApplication(aumid) -> pid     OS launches it, suspended
inject                                CreateRemoteThread -> LoadLibraryW
Resume(pfn)                           run
DisableDebugging(pfn)                 ALWAYS, even on failure
```

Package facts, read from the installed manifest:

```
Name        38985CA0.CallofDutyWWIIPCMS   version 2.0.18.0
AUMID (MP)  38985CA0.CallofDutyWWIIPCMS_5bkah9njm3e9g!GameMP
AUMID (SP)  ...!GameSP
Executable  s2_mp64_ship.exe / s2_sp64_ship.exe
```

**Verified live:** the package resolves, `IPackageDebugSettings` QueryInterfaces,
and `DisableDebugging` actually executes against the real package. Both COM
interfaces are IUnknown-only with no IDispatch, so PowerShell cannot late-bind to
them — every call is made from C#, which is what `-Disarm` exercises end to end.

If a run ever dies between arming and disarming, **every later launch will hang
waiting for a debugger**. Recovery: `.\tools\Launch-S2-Store.ps1 -Disarm`.

### BLOCK — unverified, needs one real launch

1. That `EnableDebugging` actually suspends *this* title.
2. That `OpenProcess(PROCESS_ALL_ACCESS)` succeeds against it.
3. That the mod survives GDK licensing / package-integrity checks once loaded.
4. Whether `EnableDebugging` needs elevation here.

---

## File layout

### DONE 2026-08-15

`src/ModPaths.hpp` gives a per-build writable directory. **Steam behaviour is
byte-identical**, so the 128 bot names and 115 uniforms already on disk keep
working with no migration; the branch only fires on a build we have never run.

| what | Steam (unchanged) | Store |
|---|---|---|
| `botnames.txt`, `botkits.txt`, … | `<exe dir>\S2MP-Mod\` | `…\LocalState\S2MP-Mod\` |
| markers (`s2mp_nojoingate.txt`, `s2mp_netlog.txt`) | `<exe dir>\` | `…\LocalState\S2MP-Mod\` |
| console log | `main\s2mp_console.log` | `…\LocalState\S2MP-Mod\s2mp_console.log` |

The Steam log path is deliberately untouched — it is baked into how probe output
is retrieved from this project.

### BLOCK — still open

The **demo directory** (`main\demo`) is the engine's own path, not the mod's, so
it may already resolve somewhere writable on Store. Not investigated. Anything
that reads or writes demos needs checking on the first real run.

## BLOCK — Arxan at runtime

Static analysis is solved: the Store dump exists (`F:\WWII XBOX Dump\`, 322 MB) and
587 functions are named in it. What is **unknown** is runtime behaviour on that
build — return-address checks, control-flow flattening, and whether it tolerates
the mod's ~60 MinHook detours the way the Steam build does. Same product, so likely
similar. Not measured.

---

## What to do on the first real attempt

1. Build. Deploy nothing to the Store package — the launcher injects from the repo.
2. `.\tools\Launch-S2-Store.ps1`
3. Read the first console line: `[build] detected: Microsoft Store (322 addresses …)`.
   If it says **UNKNOWN**, the signature offset is wrong and everything downstream
   is using Steam addresses — stop there.
4. Watch for poison faults. A minidump whose fault address begins `0000DEAD` names
   an unmapped entry directly (RULE A13).
5. If it dies before the console appears, the block is the loader, not the map.
