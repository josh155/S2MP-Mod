#pragma once

// =====================================================================
//  DISPLAY -- frame-rate cap, unlocked past the engine's own ceiling.
// =====================================================================
//
// FOV lives in demo_camera (cg_fov is a plain dvar already; nothing
// here duplicates it). This module owns only the one control that
// genuinely needs a workaround: `com_maxfps`.
//
// Recovered from the S2 IDB (Com_InitDvars @0x93260):
//     off_14DB7B0 = Dvar_RegisterInt("com_maxfps", 85, 0, 250, 0x400001);
// i.e. a HARD 0..250 domain baked in at registration. The console
// setter (and therefore `com_maxfps 500`) clamps to that domain, so
// going past 250 needs the raw current-value slot -- the same
// technique this project already uses for the free-camera speed and
// third-person framing.
//
// Re-registering with a wider domain was investigated and rejected:
// the "dvar already exists" path inside the registrar (sub_B1A70) only
// touches the domain when the FLAGS themselves change, so calling it
// again with the same flags is a genuine no-op for the bounds -- and
// forcing a flag change to reach the domain-update branch runs through
// a Com_Error guard and a string-interning dance this project has not
// proven safe. Poking the storage directly is the proven route.
//
// Storage offset (dvar+16) is S2's established layout (Dvar_SetBool
// @0xB1FD0; reused throughout this project for sv_maxclients and
// others), independent of the fact that com_maxfps's own GETTER
// (sub_AF2D0) is one of this binary's Arxan-obfuscated wrappers -- we
// never call it, only read/write the plain storage it ultimately backs.
//
// ---------------------------------------------------------------------
//  PERSISTENCE -- this is a standing preference, not a per-session toggle
// ---------------------------------------------------------------------
//
// USER REPORT 2026-09-15: the cap "isn't just for demos, it's for online
// play too, all the time" -- i.e. it was reverting between sessions. It
// was never actually gated on demos (tick() already ran from the
// unconditional Present hook, live play included), but nothing ever
// re-applied a value on boot: `com_maxfps` is archived (flags include
// the archive bit), so a value written above 250 by the raw poke gets
// read back through the ENGINE's own config-load path next launch --
// which is a normal domain-clamped setter -- and silently lands back at
// <=250. The only way it stuck before was the user re-opening the GUI
// and re-setting it every single session.
//
// Fixed by making set_fps_cap() the standing preference: it is written
// to <mod dir>/fps_cap.txt, and tick() applies it automatically the
// first moment com_maxfps becomes resolvable (init() runs before the
// dvar is registered, so this cannot happen at init() time). Once
// applied, holding is permanent for the rest of the process -- any
// later value <=250 is also now re-asserted on drift, not just >250,
// since the cause of drift (an archive/reload clamp) is not limited to
// the unlocked range.

namespace demo_display
{
	void init();

	// Per-frame maintenance, called unconditionally from the Present hook
	// (live play and demo playback alike, and while the tool window is
	// closed). Three things happen here, in order, each a no-op once done:
	//   1. the first time com_maxfps is resolvable, apply a saved
	//      preference from disk, if there is one;
	//   2. thereafter, compare-then-write: re-poke the raw value whenever
	//      it has drifted from what was last set, at ANY value, not just
	//      above 250.
	void tick();

	// -1 when the dvar is not registered yet / not readable.
	[[nodiscard]] int fps_cap();
	[[nodiscard]] bool fps_cap_available();

	// Clamped 0..1000. 0 is the engine's own "uncapped" (min of the
	// registered domain), reached through the normal console setter same
	// as every value up to 250. Anything past 250 writes the raw slot.
	// Persists to disk and becomes the value tick() holds from now on,
	// including across future launches.
	void set_fps_cap(int fps);
}
