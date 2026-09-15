#pragma once

// =============================================================================
//  hud/wii_aim -- Wii-style pointer aiming (MW Reflex / WaW / Black Ops Wii)
// =============================================================================
//
//  The mouse drives a free RETICLE on screen instead of the camera. Inside the
//  bounding box the camera holds still and only the reticle moves. Past the
//  box edge the camera turns, faster the further out the reticle is. Bullets go
//  where the reticle is, not screen centre, and the engine's own crosshair /
//  hitmarkers ride along with it.
//
//  ---------------------------------------------------------------------------
//  HOW IT WORKS -- two angle sets the engine already keeps apart
//  ---------------------------------------------------------------------------
//
//  AIM angles    clientActive+25900 (CA_CMD_VIEWANGLES). CL_CreateCmd adds the
//                mouse to these and packs them into the usercmd. The SERVER
//                fires along them. We make these point at the reticle.
//
//  CAMERA angles ps+576 (PS_VIEWANGLES). Prediction rebuilds them from the
//                usercmd every frame, then CG_CalcViewValues copies them into
//                the refdef. We subtract the reticle's angular offset from them
//                AFTER prediction, at the exact boundary the theater already
//                proved reaches the camera (CG_UpdateLocalPlayerState stub in
//                demo_playback.cpp).
//
//  Nothing server-side changes and the usercmd stream stays honest, so it
//  works on any server.
//
//  ---------------------------------------------------------------------------
//  WHERE IT RUNS -- call-outs only, no new Hook::create (RULE A3.1)
//  ---------------------------------------------------------------------------
//
//    before_create_cmd / after_create_cmd   demo_playback's CL_CreateCmd stub
//    after_update_local_player_state        demo_playback's UpdateLocalPlayerState stub
//    override_crosshair                     dynamic_crosshair's CalcCrosshairPosition stub
//    render_reticle                         InternalConsole's R_EndFrame stub
//
//  ---------------------------------------------------------------------------
//  EVIDENCE STATUS
//  ---------------------------------------------------------------------------
//
//  PROVEN (earlier sessions, demo_game.hpp): CA_CMD_VIEWANGLES, PS_VIEWANGLES,
//    the tan-half-fov pair at cg+1993776, CL_CreateCmd(void* cmd, int) signature,
//    the post-prediction ps write reaching CG_CalcViewValues.
//  LIKELY (decompile note in demo_game.hpp, verified at RUNTIME by this module
//    before it writes anything): usercmd angles at +0x10/+0x14/+0x18 as
//    ANGLE2SHORT of CA_CMD_VIEWANGLES. If the check fails the feature turns
//    itself off and says so.
//  HEURISTIC: ADS detection. There is no proven ADS field yet, so ADS is
//    inferred from the refdef FOV shrinking relative to the widest FOV seen
//    (wii_aim_status shows the live ratio). Replace once ps ADS state is found.
//
//  KNOWN LIMITATIONS (v1): the viewmodel points at screen centre, not the
//  reticle; the killcam inherits the reticle offset for its duration.
// =============================================================================

namespace wii_aim
{
	void init();

	[[nodiscard]] bool enabled();
	void set_enabled(bool on);

	// Client thread. Wrap the engine's CL_CreateCmd: snapshot the live angles
	// before, apply the pointer model and repack the usercmd after.
	void before_create_cmd(int local_client_num);
	void after_create_cmd(void* cmd, int local_client_num);

	// Client thread, after CG_UpdateLocalPlayerState (post-prediction, before
	// CG_CalcViewValues). Turns the predicted aim angles into camera angles.
	void after_update_local_player_state(int local_client_num);

	// Client thread, from the CG_CalcCrosshairPosition stub. Moves the engine's
	// crosshair to the reticle. Returns true when it wrote x/y (640x480 units).
	bool override_crosshair(float* x, float* y);

	// Render thread, once per frame from R_EndFrame. Draws the reticle and,
	// optionally, the bounding box.
	void render_reticle();
}
