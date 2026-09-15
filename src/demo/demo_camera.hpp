#pragma once

#include <cstdint>

// =====================================================================
//  DEMO CAMERA — framing controls for filming
// =====================================================================
//
// Everything here was recovered from the S2 IDB on 2026-08-31 (see
// CLAUDE.md). Three of the four need no code patching at all; the fourth
// repoints two single instructions using the same technique already
// proven for the free-camera speed.
//
//   FOV          `cg_fov` is a REAL dvar (off_11111B8, flags 0x400001 =
//                user-settable + archived), and the engine additionally
//                ships `cg_fov_override` (off_11111E0, default -1).
//                sub_45760 is the chooser:
//                    intermission?           -> cg_fov_intermission
//                    splitscreen client 1?   -> cg_fov1
//                    per-client scale > 0    -> cg_fov * scale
//                    cg_fov_override > 0     -> the override
//                    else                    -> cg_fov
//                So a slider is just the dvar. No hook, no patch.
//
//   3rd person   CL_Demo_UpdatePlaybackView @0x9135D0 raises the camera by
//                +35.0 (instruction 0x9137C1) and CL_Demo_TraceViewForward
//                @0x913830 pulls it back 85.0 (instruction 0x913939).
//                BOTH constants are SHARED -- dword_B378E8 has 17 xrefs and
//                dword_B2D3A4 has 12 -- so the constants must NOT be
//                patched. We repoint the two INSTRUCTIONS instead, exactly
//                as the free-camera speed already does.
//
//   Roll         both camera movers write roll to cg+2355668 from usercmd
//                angle[2], which the mouse never produces. So the field is
//                plumbed and simply never fed: writing it after the mover
//                runs gives a dutch angle.
//
//   Screenshot   CL_Demo_CaptureScreenshot @0x916740 is the engine's own
//                TILED high-resolution capture (240x180 tiles at 1440). It
//                is action 17, which we block by default because it freezes
//                playback and moves the camera -- which is exactly what a
//                tiled capture does. Exposed here as a deliberate action
//                rather than a surprising key.

namespace demo_camera
{
	void init();

	// ---- field of view ----------------------------------------------
	// Reads the live dvar; -1 when it cannot be read.
	[[nodiscard]] float fov();
	void set_fov(float degrees);          // clamped 45..160
	[[nodiscard]] bool fov_available();

	// ---- third person framing ---------------------------------------
	[[nodiscard]] bool framing_patched();
	[[nodiscard]] float* height();        // stock 35.0, nullptr if unpatched
	[[nodiscard]] float* distance();      // stock 85.0, nullptr if unpatched

	// ---- camera roll -------------------------------------------------
	[[nodiscard]] float roll();
	void set_roll(float degrees);         // clamped -180..180

	// Called from dolly's EXISTING CL_Demo_FreeCameraMove hook, after the
	// engine's own mover and after bonecam. Never installs a hook of its own
	// (RULE A3.1 -- that address must not be hooked twice).
	void apply_after_camera_move();

	// ---- high-resolution screenshot ----------------------------------
	void screenshot();
}
