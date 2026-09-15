#pragma once
// =============================================================================
//  hud/broadcaster.hpp — minimal HUD via the game's OWN broadcaster settings
// =============================================================================
//
//  GOAL: keep only obituaries, the score popup and hitmarkers.
//
//  This is NOT a new mechanism. Call of Duty: WWII ships a broadcaster/caster
//  HUD whose whole job is hiding HUD furniture per widget, and its granularity
//  happens to match that request exactly. We drive that, rather than inventing
//  another way to hide things.
//
//  ---------------------------------------------------------------------------
//  WHY THE EARLIER ATTEMPTS COULD NOT WORK
//  ---------------------------------------------------------------------------
//    cg_draw2D ("2562")   gates the ENTIRE 2D pass, native AND LUI. It takes
//                         hitmarkers, obituaries and score popups with it.
//                         Confirmed in game.
//    model blanking       CG_GetHudModelValue can only change a model's VALUE.
//                         It zeroes the numbers but leaves the widget frame, so
//                         the score chrome and the splash medals survive.
//    ui_hide_hud omnvar   real, and read by mphud_uc.lua — but it sits next to
//                         GetDvarBool("2562") in the same condition, i.e. it is
//                         the all-or-nothing switch. Cannot keep obituaries.
//
//  ---------------------------------------------------------------------------
//  THE MECHANISM (from ui/s2/mphud_uc.lua in the dumped LUI)
//  ---------------------------------------------------------------------------
//  mphud_uc.lua carries a {SettingName, Function} table feeding
//      broadcasterShowHud(widget, BroadcasterUtils.ProfileVarBool(setting))
//  which is a per-widget setAlpha:
//
//      broadcaster_inventory        -> WeaponInfoWidget0        (ammo)
//      broadcaster_teamscore        -> MatchScoresWidget0       (the score chrome)
//      broadcaster_scorestreaks     -> Scorestreak_List
//      broadcaster_killfeed         -> ObituaryWidget0          <- KEEP
//      broadcaster_objective_status -> PlayerAliveCount/SD/Hardpoint/CTF/Uplink
//      broadcaster_voipdock         -> Talkers_List
//      broadcaster_calloutcards     -> VictimPlayerCardWidget0
//      broadcaster_minimap          (via the broadcaster_minimap_change event)
//      broadcaster_playernotifications / _scorestreaks_notification
//                                   -> SplashesWidget           (splash medals)
//
//  `pointsPopup` is NOT in that table, so the score popup survives, and
//  hitmarkers are native (the sub_E7980 path), so they survive too.
//
//  ---------------------------------------------------------------------------
//  WHERE THE SETTINGS LIVE  (all transcribed from sub_46B760, not inferred)
//  ---------------------------------------------------------------------------
//      ProfileVarValue(n)      = Broadcaster.GetBroadcasterSettings():get(n)
//      SetProfileVarValue(n,v) = Broadcaster.GetBroadcasterSettings():set(n,v)
//
//      GetBroadcasterSettings(c):   sub_340800
//          gate   sub_46B6A0(c,0) = byte_8BE0A20[6920*c]   != 0 or it pushes nil
//          object sub_46ABF0(c,0) = 0x8BE09F0 + 6920*c
//
//      sub_46B760 sets "broadcaster_hasbeenread" with EXACTLY this sequence,
//      so the same sequence sets any field:
//
//          r      = DDL_MakeRootCursor(scratch, *(void**)qword_8BDEF18);
//          cursor = 32 bytes copied from r
//          DDL_MoveToName(cursor, cursor, "<field>");
//          DDL_SetInt(cursor, 0x8BE09F0 + 6920*c, value);
//
//  ---------------------------------------------------------------------------
//  THE ONE PIECE OF MANUFACTURED STATE, AND WHY
//  ---------------------------------------------------------------------------
//  The settings are only consulted while IsBroadcaster is true. From sub_33E550:
//
//      slot = *(BYTE*)(cg + 22904);                       // sub_411BE0
//      if (*(DWORD*)(cg + 3878300 + 4704*slot))           // gate
//          result = *(BYTE*)(cg + 4405240 + 152*slot) != 0;
//
//  That byte is REPLICATED clientinfo: normally the client puts
//  broadcaster_mode=1 in its userinfo (Dvar_InfoString @0x664C62, computed from
//  the lobby member's dword at +1288), the server latches it in
//  SV_UserinfoChanged @0x547A90, and it comes back in clientinfo.
//
//  We set the local copy instead. It is our own client's display flag, it is
//  exactly the value the engine itself would write, and it is latched per frame
//  because clientinfo updates would otherwise clear it. It is still
//  MANUFACTURED STATE and is therefore opt-in and off by default.
//
//  ---------------------------------------------------------------------------
//  KNOWN HAZARD — KEY UNBINDING
//  ---------------------------------------------------------------------------
//  ui/s2/broadcasterlayerhud_uc.lua:
//      CONDITIONS.IsPC -> Engine.ExecNow("exec mp/broadcaster_unbind_keys.cfg")
//  so bringing up the broadcaster layer unbinds keys on PC. We re-issue the
//  engine's own `exec keys_mp.cfg` (a literal the engine uses itself, @0xB33C48)
//  automatically after enabling, and `hud_binds` does it on demand.
//
//  NOT USABLE DURING DEMO PLAYBACK: sub_33E550 returns early when
//  CL_IsDemoPlaying, so broadcaster mode is disabled in theater by design.
// =============================================================================

#include <cstdint>
#include <string>
#include <vector>

namespace broadcaster
{
	struct setting_t
	{
		const char* name{};      // the DDL field / SettingName from broadcaster_utils.lua
		int minimal{};           // what the minimal-HUD preset sets it to
		const char* what{};      // human description, for hud_settings
	};

	void init();

	// The whole mode. Off by default; nothing is written until this is enabled.
	[[nodiscard]] bool enabled();
	void set_enabled(bool on);

	// One setting. Both go through the engine's own DDL cursor API.
	bool set_setting(const char* name, int value);
	bool get_setting(const char* name, int& out);

	// The preset table (also what the GUI would enumerate).
	const std::vector<setting_t>& settings();

	// ---------------------------------------------------------------------
	//  THE THEATER GATE
	// ---------------------------------------------------------------------
	//  sub_33E550 (IsBroadcaster) opens with
	//      if (CL_IsDemoPlaying(client)) return 0;   // pushes nothing -> nil
	//  so the engine disables broadcaster mode during demo playback outright,
	//  and every widget gated on it stays visible in theater. Measured: with the
	//  settings written and the flag latched, the ONLY visible change in a demo
	//  was the minimap player arrows -- i.e. the settings landed and everything
	//  behind IsBroadcaster did nothing.
	//
	//  This is called from demo_playback's EXISTING CL_IsDemoPlaying hook
	//  (RULE A3.1 -- it is already hooked at demo_playback.cpp:3796, so we
	//  extend that stub rather than installing a second one). It returns true
	//  only when the minimal HUD is on AND the caller is inside sub_33E550, so
	//  exactly one call site in the whole engine sees a different answer.
	[[nodiscard]] bool hide_demo_from_isbroadcaster(const void* return_address);

	// Called ONCE PER FRAME from demo_native's existing CG_PublishHudModel hook,
	// on the id that is published outside the connstate gate. Public only so
	// that stub can reach it. Early-outs to a single relaxed atomic load when
	// the mode is off. RULE A3.1 — this deliberately adds NO hook of its own.
	void on_frame();
}
