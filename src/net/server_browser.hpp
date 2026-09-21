#pragma once
// =============================================================================
//  net/server_browser — S2 online server browser, READ-ONLY
// =============================================================================
//
//  Shows the lobbies Demonware returns for a matchmaking search, with real
//  player counts and ping, and lets you join one.
//
//  ⭐ THE DESIGN RULE, AND IT IS NOT NEGOTIABLE: **ZERO HOOKS.**
//
//  The previous implementation hooked the search path and broke Find Match. We
//  never isolated which hook did it -- only that removing them all fixed it --
//  so anything that patches that path is off the table. This module reaches the
//  result table by a PURE POINTER WALK instead, and only ever reads:
//
//      L = lobby 0                      (IDA 0x8BE6040)
//      M = *(QWORD*)(L + 16)            the matchmaking object
//          verify *(QWORD*)(M + 31552) == L   <- the engine's own back-pointer
//      R = M + 1712                     the results object   (sub_29A8B0)
//      count = *(u32*)(R + 29808)                            (Search_GetResultCount)
//      entry i lives at R + 8 + 596*i                        (sub_29CEA0)
//
//  Every one of those is an engine accessor decompiled from the IDB, not an
//  inferred offset, and the whole chain was verified against the live process:
//  *(M + 31552) read back as lobby 0 exactly.
//
//  Field offsets come from sub_2A1820, which writes each one to telemetry under
//  the name shown. With p = R + 80 + 596*i:
//
//      p[0]     slots_available_count      p[-2]  occupied  (total = p[0]+p[-2])
//      p[-4]    datacenter (u16)           p[4]   status: 1 or 2 == joinable
//      p[8]     qos_error_code             p[412] lobby_throttle
//      p[416..420] ping_aggregate / median / average / ours / lobby
//      p-64     host address blob
//
//  ⚠ SCOPE, HONESTLY: this is what the SERVICE offered US for the playlist WE
//  searched. It is not a global list of every live lobby -- no client can
//  produce one, because matchmaking is brokered. One search covers one playlist.
// =============================================================================

#include <cstdint>
#include <string>
#include <vector>

namespace server_browser
{
	void init();

	struct Server
	{
		int  index = -1;
		int  players = 0;        // occupied slots
		int  capacity = 0;       // slots_total
		int  ping = 0;           // ping_ours
		int  datacenter = 0;
		int  qos_error = 0;
		bool joinable = false;
		bool throttled = false;
		int  playlist = -1;      // the playlist that was being searched
		std::string playlist_name;
	};

	// The CACHED results, most players first then lowest ping.
	//
	// ⚠ NOT a live read. The engine's table is transient -- sub_29D410 memsets it
	// at the top of every search tick and it is cleared when a search ends -- so
	// reading it directly made the list vanish the instant you stopped searching.
	// tick() polls it every 250ms and merges into our own storage instead, keyed
	// on the host-address blob so the same lobby is not duplicated. Rows survive
	// until clear_cache(), which is what lets a sweep across playlists add up to
	// ONE combined list.
	std::vector<Server> servers();
	void clear_cache();
	int  cached_count();
	int  last_result_ms();     // ms since any result was seen, -1 if never

	// True when the pointer chain resolves AND the back-pointer check passes.

	// The playlist currently set on the lobby (params[11]).
	int  current_playlist();
	std::string playlist_name(int id);

	// Everything the browser knows, for one status line.
	struct Status
	{
		bool reachable = false;
		int  count = 0;
		int  playlist = -1;
		bool searching = false;
	};
	Status status();

	// ---- MANUAL SCAN + MULTI-PLAYLIST SWEEP -------------------------------
	//
	// ⭐ CORRECTION: I previously said a search could only come from Find Match
	// and that a sweep was impossible. BOTH WERE WRONG, and the user was right
	// to push back. The evidence:
	//
	//   sub_29A780(i) = unk_86F3730 + 31672*i     the MM object is a plain
	//                                             indexed array -- no flow needed
	//   sub_2960E0                                a LUI BINDING that does
	//                                               sub_29D9C0(sub_29A8C0(mm))
	//                                             i.e. Lua triggers the search
	//                                             tick with an ordinary CALL
	//   sub_29D9C0                                the tick: issues the query via
	//                                             sub_6FF930 when sub_6FC1C0 is
	//                                             satisfied (measured: it is)
	//   sub_29D410                                clears the result table first,
	//                                             so each scan starts clean
	//
	// And the playlist is a plain lobby param, not the `playlist N` console
	// command that broke matchmaking before:
	//
	//   sub_285DA0 (search-params builder):
	//       v6 = sub_1971A0(lobby + 592);     sub_1971A0(x) = *(u32*)(x + 44)
	//       *(DWORD*)blob = v6;               <- the FIRST dword of the blob
	//
	//   so playlist == params[11] == *(u32*)(lobby + 636)
	//
	// PROVEN by agreement between two independent readings: the dumped search
	// blob began 1F 00 00 00 (= 31) and the live params[11] read 31.
	//
	// So: write params[11], call the tick, wait, read results, restore. All
	// plain calls and writes to a documented field -- still ZERO HOOKS.
	//
	// ⚠ SAFETY, because matchmaking was only just restored:
	//   * never automatic -- always user-triggered
	//   * refuses while connected/in a match
	//   * ALWAYS restores the original playlist, including on abort
	//   * one tick per playlist, spaced out; no spamming
	// nullptr when scanning is possible; otherwise why it will refuse. Shown in
	// the GUI so a button that declines is never a mystery.
	const char* busy_reason();

	void scan_current();     // scan just the playlist currently set
	void sweep_start();      // walk every known playlist, one at a time
	void sweep_stop();       // abort and restore immediately
	bool sweeping();
	std::string sweep_status();

	// Results accumulated across a sweep (per playlist), newest scan wins.

	// ---- WHY THERE IS STILL NO JOIN BUTTON --------------------------------
	// Steering the engine to ONE specific result means hooking
	// Lobby_AcceptSearchResult, i.e. patching the search path -- the exact thing
	// that broke Find Match. Matchmaking already joins the best result itself,
	// so the browser's value here is visibility. If manual join is ever wanted,
	// do it deliberately with a zero-hook control switch in place from the start.

	void tick();
}
