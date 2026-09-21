#pragma once

// =============================================================================
//  hud/aimassist -- report (and if necessary re-arm) the controller aim assist
// =============================================================================
//
//  ⭐ THE HEADLINE FINDING: AIM ASSIST WAS NEVER REMOVED FROM S2.
//
//  The whole subsystem is present and runs. What was removed is the two OPTIONS
//  TOGGLES, which is why it looks gone from inside the game.
//
//  ---------------------------------------------------------------------------
//  THE EVIDENCE, all static
//  ---------------------------------------------------------------------------
//
//  AimAssist_Init @0x2CDF0 (twin-proven from MW3) still allocates the per-client
//  state and loads all five input curves every session:
//
//      memset(&unk_5C388F0 + 4912*localClient, 0, 0x1330)
//      for i in 0..4:  GraphFloat_Load(&unk_5C3AF50 + 328*i,
//                                      "aim_assist/view_input_%d.graph")
//
//  The RUNTIME is intact too: 20 references to that state block from ~18
//  functions at 0x2B3C0..0x2DDF0, driven per-frame by sub_78AC0, which applies
//  the curves in sub_2BC60. None of it is a stub.
//
//  sub_78AC0 gates the aim-assist chain on the STATE byte:
//
//      state = &unk_5C388F0 + 4912*localClient;
//      if (state[240]) { sub_2DDF0(); sub_2D1A0(); sub_2BC60(); sub_2B3C0(); ... }
//
//  and state[240] is SET TO 1 by sub_2D0F0, which sub_43ADA0 calls
//  UNCONDITIONALLY at cgame init. Nothing in the binary ever clears it -- every
//  function in the cluster was checked for a write of 0 to that byte, and for a
//  second memset of the block. There is none.
//
//  The only other gate is on the PROFILE block:
//
//      profile = &unk_8BDEF20 + 6920*controllerIndex;   (sub_46B230)
//      if (profile[264]) { ...the entire gamepad look path, aim assist included }
//
//  profile[264] is the gamepad flag. It gates STICK LOOK as well, not just aim
//  assist -- so if it were never set, controllers would not turn the camera at
//  all. That is the sense in which aim assist is "controller only": it is the
//  engine's own gate, exactly as the user expected.
//
//  ---------------------------------------------------------------------------
//  WHAT WAS ACTUALLY REMOVED
//  ---------------------------------------------------------------------------
//
//  The profile settings table at 0xB711A0 (24 bytes/entry {name, id, typeinfo})
//  still carries them, beside settings that ARE still in the options menu:
//
//      0xB711A0  autoWeaponSwitch        id 0x111     still in the menu
//      0xB711B8  autoMantle              id 0x112     still in the menu
//      0xB711D0  aimAssistLockon         id 0x113     ORPHANED
//      0xB711E8  aimAssistSlowdown       id 0x114     ORPHANED
//
//  Every function in the aim-assist cluster was scanned for reads of the profile
//  block. It reads ONLY:
//
//      profile[4], [8]    look sensitivity h / v
//      profile[12]        ADS flag
//      profile[16], [20]  ADS sensitivities
//      profile[119]       invert Y  (picks +1.0f / -1.0f)
//
//  It never reads 0x113 or 0x114. So those two settings are registered and
//  stored but consulted by nothing -- the toggles were cut and the feature was
//  left permanently on rather than permanently off.
//
//  In Advanced Warfare (fully symboled) those same settings feed
//  GamerProfile_AimAssistLockon / GamerProfile_AimAssistSlowdown, and there are
//  LUI bindings and console commands to flip them. S2 has none of those.
//
//  ---------------------------------------------------------------------------
//  SO WHAT DOES THIS MODULE DO?
//  ---------------------------------------------------------------------------
//
//  Mostly it TELLS YOU THE TRUTH, because the above is a static argument and the
//  honest way to settle it is to read the two bytes at runtime. `aimassist`
//  prints them plus the sensitivities actually in use.
//
//  It can also re-assert state[240] -- not because anything is known to clear
//  it, but because if the reading ever comes back 0 that is the one byte that
//  would need putting back, and re-asserting a flag the engine itself sets to 1
//  fabricates nothing.
//
//  ⚠ IT DELIBERATELY WILL NOT WRITE profile[264]. That byte turns on the whole
//  gamepad look path; forcing it for a keyboard player would hand stick-look
//  input to someone with no stick. It is REPORTED, never set.
// =============================================================================

#include <string>

namespace aimassist
{
	struct state_t
	{
		bool  readable;
		int   controller;      // controller index for local client 0
		bool  gamepad;         // profile[264] -- the only real gate
		bool  enabled;         // state[240]   -- set by the engine at cgame init
		float sens_h;          // profile[4]
		float sens_v;          // profile[8]
		bool  ads_separate;    // profile[12]
		float ads_h;           // profile[16]
		float ads_v;           // profile[20]
		bool  invert_y;        // profile[119]
	};

	void init();

	[[nodiscard]] state_t read();

	// Re-assert state[240] = 1. Returns false if the state block is unreadable.
	bool rearm();
}
