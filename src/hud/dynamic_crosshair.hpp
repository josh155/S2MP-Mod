#pragma once

// =============================================================================
//  hud/dynamic_crosshair -- MWII-style crosshair sway
// =============================================================================
//
//  The crosshair lags behind camera rotation and leans with camera movement,
//  then settles smoothly back to centre. Any direction (full 360), driven by
//  how fast you are turning and moving.
//
//  ---------------------------------------------------------------------------
//  ⭐ IT IS PURELY COSMETIC. THIS IS PROVEN, NOT ASSUMED.
//  ---------------------------------------------------------------------------
//
//  We hook CG_CalcCrosshairPosition and add an offset to its two output floats.
//  Every one of that function's five callers is a DRAW path:
//
//      sub_3E00C0, sub_3E0800, sub_3E1800  <- sub_E7980 (the cg_draw2D 2D HUD)
//      sub_3E2FB0                          <- nested under sub_3E1800
//      sub_3E3570                          <- CG_DrawActiveFrame
//
//  None of them is an entity scan or gameplay path -- the crosshair ENTITY scan
//  (what turns the reticle red, what a nametag targets) traces from the view
//  independently and never consults this function. So this cannot affect aim,
//  bullet direction, hit detection or targeting. It moves pixels only.
//
//  ---------------------------------------------------------------------------
//  THE TARGET, twin-proven against Advanced Warfare
//  ---------------------------------------------------------------------------
//
//  AW (fully symboled) has:
//      ?CG_CalcCrosshairPosition@@YAXPBUcg_s@@PAM1@Z  @0x8267D918 (0x16c)
//      void CG_CalcCrosshairPosition(const cg_s*, float* x, float* y)
//
//  S2's twin is CG_CalcCrosshairPosition @IDA 0x3E10A0 (0x17b), found by its
//  constant pool: -240.0f at 0xB6ADD4 immediately followed by -320.0f at
//  0xB6ADD8, the only such pair in the image. Confirmed three ways:
//
//    1. same signature -- (cg, float* x, float* y)
//    2. same output constants -- *x = proj * -320.0, *y = proj * -240.0
//    3. it reads the EXACT refdef fields this project already proved
//       independently during the dolly work (tan-half-fov at cg+1993776/+1993780,
//       view axis at cg+1993808)
//
//  ⭐ THE OUTPUT IS AN OFFSET FROM SCREEN CENTRE, in 640x480 virtual units.
//  That is why this needs no draw-path surgery: adding to those two floats IS
//  the sway, in the engine's own coordinate space and sign convention.
//
//  ---------------------------------------------------------------------------
//  WHY THE STUB USES ITS OWN ARGUMENT FOR cg
//  ---------------------------------------------------------------------------
//
//  RULE A21 exists because validating one cg pointer and then calling a function
//  that resolves cg independently is how dolly crashed. Here the stub is HANDED
//  the exact cg the engine is using, as argument 1. We read that and nothing
//  else, so there is no second source to disagree with.
// =============================================================================

namespace dynamic_crosshair
{
	void init();

	[[nodiscard]] bool enabled();
	void set_enabled(bool on);

	// Tunables. All are safe to change live; the effect is cosmetic.
	//   rot_gain   virtual pixels of lag per rad/sec of turn      (default 6.0)
	//   move_gain  virtual pixels of lean per world-unit/sec      (default 0.02)
	//   tau_ms     smoothing time constant; higher = laggier      (default 90)
	//   max_radius clamp on the total offset, in 640x480 units    (default 26)
	[[nodiscard]] float rot_gain();
	[[nodiscard]] float move_gain();
	[[nodiscard]] float tau_ms();
	[[nodiscard]] float max_radius();

	// -----------------------------------------------------------------------
	//  CENTRE DOT
	// -----------------------------------------------------------------------
	//
	//  A small MWII-style dot that rides the crosshair. It does NOT recompute
	//  the sway -- the stub captures CG_CalcCrosshairPosition's FINAL output
	//  (engine position + our offset) once per frame, so the dot tracks the
	//  reticle exactly, including any engine-side offset we never modelled
	//  (third person, vehicles, turrets).
	//
	//  It works with the sway off too; it simply sits at centre then.
	//
	//  Drawn from the EXISTING R_EndFrame hook in InternalConsole.cpp -- a
	//  proven engine-2D draw context (drawConsole and dolly::render use it) and
	//  NOT a second Hook::create on that target (RULE A3.1).
	[[nodiscard]] bool dot_enabled();
	void set_dot_enabled(bool on);
	[[nodiscard]] float dot_size();

	// Called once per frame from R_EndFrame. Draws nothing unless the dot is on
	// AND a crosshair was actually positioned this frame -- so it disappears in
	// menus, on the scoreboard and while dead, exactly as the reticle does.
	void render_dot();
}
