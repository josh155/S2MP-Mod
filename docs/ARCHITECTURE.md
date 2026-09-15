# S2MP-Mod — architecture guide

Start here if `src/demo/demo_native.cpp` looked like an indigestible blob. It is 4900
lines, but it is thirteen self-contained sections, and this document says what each
one is for and which order to read them in.

## What this mod is

A client DLL for **Call of Duty: WWII** (engine codename **S2**), injected into
`s2_mp64_ship.exe`. It hooks engine functions with MinHook and adds a console, dev
tools, and — the bulk of recent work — a working **demo (theater) system**.

## The one thing to know before reading any code

Nearly every comment in `src/demo/` records a *measurement*, not an intention. S2 is
Arxan-protected: the call graph is obfuscated, strings have no cross-references, and
many functions are reachable only through indirect dispatch. So findings were won by
bracketing, crash dumps, and offline analysis of demo files — and each one is written
down at the point it is used, because re-deriving it is expensive.

That is why the comment-to-code ratio is high. The comments are the expensive part.

Two conventions worth knowing:

- **`0x912D65_b`** — a literal in `_b` form. The engine's runtime address is
  `module_base + 0x1000 + literal`, so an IDA address of `0x913D65` is written
  `0x912D65_b`. Any address in a comment written as `IDA 0x...` is the IDA address.
- **`sub_XXXXXX`** — an engine function whose purpose is known but whose real name is
  not. These are deliberately not renamed to a guess; a wrong name is worse than none.

## Two demo systems, and why there are two

| | what it is | status |
|---|---|---|
| **theater** (`demo_playback`, `demo_recording`, `theater_camera`) | our own container (`.dm_s2`) and our own playback loop | superseded — being retired |
| **native** (`demo_native`) | drives S2's *own* demo system (`cl_demo_play`, `main/demo/*.demo`) | the one that works |

The native route won because S2 has a complete demo system that simply never worked
in the shipped game. Getting it working meant fixing engine defects rather than
reimplementing them. `demo_native.cpp` is large because it is the accumulation of
those fixes.

## The demo pipeline end to end

```
play a match  ──►  the ENGINE records it        (CL_Demo_StartRecord, gate forced open)
                        │
                   on disconnect                (CL_Demo_StopRecord writes the footer)
                        │
                   auto-repair                  (public matches get ncs type 21 spliced in)
                        │
              cl_demo_play <name>  ──►  playback, with read-side fixes applied
```

## Engine defects this mod works around

These explain most of the odd-looking code. Each was proven before it was fixed.

1. **The gamestate packet has no 2-byte length prefix.** The reader unconditionally
   reads one, gets `0xDAA9`, sign-extends it to `-9559`, and silently decodes zero
   bytes. `repair_gamestate_message()` inserts the real length.
2. **`CL_Demo_WriteGameState` writes ONE bit where `CL_ParseGamestate` reads TWO.**
   A recording bug — every shipped demo is affected. Compensated by hooking
   `MSG_ReadBit`, and auto-detected per demo (see `demo_native.cpp` "gamestate
   framing"): a demo whose gamestate is the *first* record in its message needs it,
   one where it is a later record does not.
3. **The priming loop in `CL_SetCGameTime` ignores end-of-stream**, so a demo that
   never primes gets read past its terminator into the footer.
4. **Public-match recordings omit netconststring type 21** (the GSC script-string
   table), because the footer writer only emits strings *registered* during the
   session and a public match never registers them. Without it playback cannot
   resolve the type-21 indices its own snapshots carry. The table is embedded in
   `demo_ncs21.inc` and spliced in automatically.
5. **`CL_Demo_Play_f` performs no asset releases**, so the frontend (~36,890 of the
   40,192 image slots) stays resident and heavy maps overflow the pool. Fixed by
   issuing the same releases the live map paths issue, with the engine's own masks.

## Reading order

1. **`src/demo/demo_native.hpp`** — the public surface, ~135 lines. Read this first.
2. **`src/demo/demo_native.cpp`, the `init()` at the bottom** — every hook is
   installed there, each with a printed OK/FAILED line. It is the table of contents
   for what the file actually does.
3. Then whichever section below interests you.

### `demo_native.cpp` section map

| line | section | what it does |
|---|---|---|
| 204 | viewmodel `hide` watcher | probe only; polls the byte that gates the gun model |
| 387 | the viewmodel fix | lets the engine's own demo StreamSync path run |
| 452 | StreamSync pre-scan | replays the connect-time load request a demo never recorded |
| 1249 | direct viewmodel stream request | asks the streamer for the local weapon's textures |
| 1323 | remote players | same, for other players' world models |
| 1423 | asset census + tally | per-type allocation accounting; how the image limit was solved |
| 1896 | asset release fix | gives the demo path the releases the live paths perform |
| 2762 | `CL_Demo_StartRecord` | the engine's own recorder — it runs on live connects |
| 2920 | enabling the recorder | opens the gate that config closes |
| 3007 | public-match repair | splices ncs type 21 into the footer after recording |
| 3235 | `CL_Demo_HandleAction` | the demo's key actions (pause / camera / seek / speed) |
| 3285 | free camera speed | makes the engine's baked-in constant adjustable |
| 3723 | `4780` probe | delta-index history, for diagnosing snapshot desyncs |

### The other files

| file | lines | what it is |
|---|---|---|
| `demo_playback.cpp` | 3927 | the theater's own playback. Superseded; being retired |
| `demo_utils.cpp` | 875 | the `.dm_s2` container format (TLV records) |
| `demo_gui.cpp` | 823 | ImGui overlay — demo list, playback controls, freecam speed |
| `demo_game.hpp` | 681 | engine addresses and struct offsets, with the evidence for each |
| `demo_recording.cpp` | 415 | theater-side capture at `CL_ParseServerMessage` |
| `demo_timescale.cpp` | 181 | scales HUD/LUI animation to demo speed, freezes it on pause |
| `demo_ncs21.inc` | generated | the 396-entry GSC script-string table (8141 bytes) |

## `tools/` — offline analysis, no game needed

These are how most of the hard problems were solved. All are standalone Python.

| tool | what it does |
|---|---|
| `s2_demo_read.py` | validates a `.demo` against every rule the engine's parser applies |
| `s2_demo_fix_ncs.py` | repairs a public-match demo (the type-21 splice) |
| `s2_dm_to_demo.py` | converts our `.dm_s2` container into a native `.demo` |
| `s2_svc_walk.py` | walks a demo's svc opcode stream; bit-exact against the engine |
| `s2_huffman.py` | the engine's Huffman decoder, table extracted from the exe |
| `s2_capture_diff.py` | diffs two recordings of the same match |
| `s2_crash_dump.py` | reads the game's minidumps, reports the fault as an IDA address |
| `s2_asset_log.py` | asset/zone accounting from a saved console log |
| `s2_dvar_map.py` | translates S2's numeric dvar names (`"1762"` ⇄ `cg_drawGun`) |
| `s2_netfields.py` | extracts the 33 netfield lists |
| `s2_viewmodel_predict.py` | predicts, offline, whether a demo will show the viewmodel |

**Note:** tools that read the executable use `s2x_dump.exe` (a process dump), not the
retail exe. Retail is Arxan-packed and its on-disk bytes do not match memory.

## Building

Requires **Visual Studio 2026** (toolset v145) and the submodules in `deps/`, which
are already populated in this archive.

```
generate.bat        # premake generates the .sln and project files
```

then build **Release | x64**. Output is `bin/Release/s2mp-mod.dll`.

## Console commands worth knowing

```
cl_demo_play <name>      play a demo from main/demo (no server running)
demo_record              toggle native recording           (default ON)
demo_autofix             toggle the automatic type-21 repair (default ON)
demo_block_action <ids>  swallow demo key actions (17/169 = the screenshot capture)
demo_zones               list loaded asset zones
demo_asset_census        per-type asset pool occupancy
demo_native_state        demo playback state dump
```

There is also an ImGui overlay on **F9** / **Insert** with the demo list, playback
controls, a "Fix Selected Demo" button and the freecam speed slider.
