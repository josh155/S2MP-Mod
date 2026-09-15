# S2MP-Mod

A demo recorder, player and camera rig for Call of Duty: WWII (S2) multiplayer.

Record a match, play it back, put a camera on it, film it.

---

## Quick start

1. Launch the game with the mod (`tools/Launch-S2.ps1`).
2. Play a match. **It is recorded automatically.**
3. Back at the menu, press **F9** (or **Insert**) to open the tools window.
4. Pick the demo from the list, press **Play**.
5. Press **Free** under Camera and fly.

That is the whole workflow. Nothing else needs turning on.

---

## The window

**F9** or **Insert** opens it. **F2** toggles the on-screen timeline.

| Tab | What it is |
|---|---|
| **Demos** | Recording switch, the demo library, and the playback transport. |
| **Dolly** | A camera path. Fly to a spot, add a point, repeat; the camera then flies the curve. |
| **Bone Cam** | Locks the camera to a player's bone (head, hands, weapon) while you keep mouse look. |

Two demo formats appear in one list:

- **engine** — the game's own `.demo`, in `main/demo`. This is what recording produces.
- **custom** — the mod's own `.dm_s2`, in `demos`.

You do not have to care which is which. Play, Stop, Pause, seek and speed all
work on both — the mod dispatches on the file extension.

---

## Commands

Everything the product does, from the console:

| Command | |
|---|---|
| `demo_list` | list every demo, both formats |
| `demo_play <name>` | play one (the bare name is enough) |
| `demo_stop` | |
| `demo_pause` | |
| `demo_seek <seconds>` | negative rewinds |
| `demo_speed <0.1 .. 4.0>` | slows the HUD and the audio pitch with the picture |
| `demo_record <0\|1>` | auto-record every match (on by default) |
| `demo_camera 1 \| 3 \| free` | first person / third person / free camera |
| `demo_fov <45..160>` | field of view |
| `demo_thirdperson <dist> [height]` | third-person framing (stock 85 35) |
| `demo_roll <-180..180>` | dutch angle on the free camera |
| `demo_screenshot` | the engine's tiled high-resolution capture |
| `demo_autoname <0\|1>` | rename recordings to `<map>_<date>_<time>` (on) |
| `demo_ui` | open the window |

### Clips

While an engine demo is playing, **Mark In** / **Mark Out** record a segment,
**Preview** plays the marked clip and **Clear** discards them. These drive the
game's own clip system (`cl_demo_savesegment`), which ships complete but has no
menu.

Plus `dolly`, `bonecam`, `names`, `crosshair_sway` and `crosshair_dot` for the
camera and overlay tools — each prints its own usage when run with no argument.

### Wii pointer aiming

Aiming exactly the way the Wii Call of Duties did it: the mouse moves a free
reticle, the camera holds still inside a bounding box and turns when the
reticle leaves it, and bullets go where the reticle is. Live play only; it
steps aside whenever either demo system owns the camera. A Dolphinbar-style
Wiimote that presents itself as a mouse works unchanged.

| Command | |
|---|---|
| `wii_aim [0\|1]` | toggle (off by default) |
| `wii_aim_box <w> [h]` | bounding box as a fraction of the half-screen (0.50 0.40) |
| `wii_aim_speed <deg/s>` | camera turn speed with the reticle at the screen edge (180) |
| `wii_aim_curve <1..4>` | how the turn ramps up past the box edge (1.5) |
| `wii_aim_ads <0..1>` | box multiplier while aiming down sights (0.5) |
| `wii_aim_lock_scoped [0\|1]` | scoped weapons pin the reticle to centre (on) |
| `wii_aim_reticle [0\|1]`, `wii_aim_reticle_size <px>` | the drawn reticle |
| `wii_aim_showbox [0\|1]` | draw the bounding box while tuning |
| `wii_aim_status` | live cursor / camera / FOV-ratio readout |

ADS is inferred from the field of view narrowing (`wii_aim_ads_threshold`
tunes it) until the player-state ADS field is proven. The viewmodel still
points at screen centre in this version.

---

## Recording

The game writes the demo itself, from the moment you connect, so there is no
button to press mid-match. Turning auto-record on or off takes effect on the
**next** match — the engine only asks once, at cgame init.

Public-match demos are repaired automatically when recording stops. If the game
is killed mid-match that never runs, and the demo will not play; select it and
press **Repair**. It is safe on anything — a demo that does not need it is left
alone.

---

## Developer mode

The mod is also a reverse-engineering workbench. That half — matchmaking, host
forcing, bots, HUD model internals, and about a hundred diagnostic commands — is
**hidden, not removed**.

```
s2_dev 1
```

or the checkbox at the bottom of the window. It adds the **Servers**, **Host**,
**Bots** and **Players** tabs and registers every diagnostic command. The setting
persists across restarts.

Nothing is deleted when it is off. Commands registered during a session stay
usable for that session.

---

## Layout

```
src/demo/     demo_player   one list, one transport, dispatching to both engines
              demo_native   the game's own .demo system (record + playback)
              demo_playback the custom .dm_s2 theater
              demo_gui      the window
              dolly, bonecam, theater_camera
src/hud/      nametags, crosshair, wii_aim, minimal HUD, broadcaster
src/net/      force_host, server_browser, bots, dlc      (developer mode)
src/DevMode   the product / workbench split
```

`CLAUDE.md` is the engineering record: what is proven, what is disproven, and
which approaches have already failed. Read it before changing engine-facing code.

---

## Building

Visual Studio 2026, `s2mp-mod.sln`, Release / x64. The Release build copies the
DLL to the game directory automatically.
