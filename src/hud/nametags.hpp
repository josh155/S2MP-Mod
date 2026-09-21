#pragma once

// =============================================================================
//  hud/nametags -- UNGATE THE ENGINE'S OWN NAMEPLATES
// =============================================================================
//
//  ⭐ THIS DOES NOT DRAW ANYTHING. The engine already has a complete nameplate
//  system -- bone-tag head positions, names, fonts, distance fade, scaling. It is
//  simply GATED to teammates. We open the gate and let the engine draw.
//
//  ---------------------------------------------------------------------------
//  WHY THE PREVIOUS APPROACH WAS ABANDONED
//  ---------------------------------------------------------------------------
//
//  The first four builds reimplemented the whole thing: enumerate entities,
//  read names, read teams, project, draw. Every one of those needed an offset,
//  and they were wrong in almost every combination -- localised-string ids as
//  names, then player LEVELS, then inf/3.9e17 origins, then zero players. It
//  hung the game once (a VirtualQuery per character, on the render thread).
//
//  The user asked the right question: "there's already an existing one when
//  you're close to an enemy and they're in sight -- can't we unlock the engine
//  one so it's not gated?" Yes. That is this file, and it is ~20 lines of real
//  logic instead of ~400.
//
//  ---------------------------------------------------------------------------
//  THE GATE, read out of S2's own CG_DrawVisibleNames (sub_37F00)
//  ---------------------------------------------------------------------------
//
//      if (v11 < 111) {
//          if (!sub_38F510())  goto LABEL_24;          // <-- NOT a team game:
//                                                      //     draw for EVERYONE
//          if (v11 != myClientNum) {
//              theirTeam = *(DWORD*)(cg + 3878296 + 4704*theirId + 12);
//              myTeam    = *(DWORD*)(cg + 3878296 + 4704*myId    + 12);
//              if (theirValid && myValid && myTeam == theirTeam) {
//      LABEL_24:
//                  ... visibility trace ...
//                  sub_3C9B0(localClient, entity, 1.0, clientNum, 1);   // DRAW
//
//  sub_38F510() is "is this a team-based gametype": it reads the same lobby
//  params field (+56) that sub_38F590 reads, comparing to 2 instead of 1. In a
//  free-for-all it is already FALSE, which is why FFA names everyone.
//
//  So making it return false FOR THIS CALLER ONLY gives every player a nameplate,
//  drawn by the engine, in the right place, with the right name.
//
//  ⚠ IT HAS 23 CALL SITES. Forcing it false globally would affect scoreboards,
//  HUD and spawn logic. The hook is therefore SCOPED BY RETURN ADDRESS to the one
//  call inside sub_37F00 -- the same technique broadcaster.cpp uses to open
//  CL_IsDemoPlaying for exactly one caller. Every other caller gets the truth.
//
//  ---------------------------------------------------------------------------
//  OFFSETS THIS INVESTIGATION CORRECTED (kept because they cost real test runs)
//  ---------------------------------------------------------------------------
//
//    entity +1201    the client id is 1-BASED  (the engine does `v10 - 1`)
//    entity +1340    the hidden/skip flag (&0x20), NOT +1184
//    team            cg + 3878296 + 4704*clientId, +12 team, +4 valid --
//                    indexed by the 1-BASED id, which is why every player read
//                    "team 2" when indexed 0-based
//    clientinfo      cg + 4405240, stride 152: +36 team, +56 1-based id,
//                    +60 NAME (inline), +96 level   [measured live with CE]
//    sub_13A00       MUST be called; qword_8B0DB18 is ENCRYPTED (reads
//                    0xF5A16DA2226E8E90 live, and the memory there is zeros)
// =============================================================================

namespace nametags
{
	void init();

	[[nodiscard]] bool enabled();
	void set_enabled(bool on);

	// Also bypass the line-of-sight trace, so enemies show through walls. Off by
	// default: the engine's own behaviour is "visible only", and that is usually
	// what you want on screen.
	[[nodiscard]] bool through_walls();
	void set_through_walls(bool on);

	// Called from the CL_IsDemoPlaying-style scoped hooks. Returns true when the
	// caller is the nameplate enumerator and the feature is on.
	[[nodiscard]] bool ungate_team(const void* return_address);
	[[nodiscard]] bool ungate_visibility(const void* return_address);
}
