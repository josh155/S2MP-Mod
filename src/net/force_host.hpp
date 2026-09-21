#pragma once

// =============================================================================
//  net/force_host — OWN THE LOBBY. Scoped deliberately, 2026-08-15.
// =============================================================================
//
//  WHAT THIS IS: the "semi/half" force host. You become the LOBBY host, so the
//  map, gametype, playlist and player counts are yours, and you can kick.
//
//  WHAT THIS IS NOT, and will not be attempted again: running the match on your
//  own machine. That was chased for days and is CLOSED on evidence, not on
//  effort:
//
//    * public matchmaking PROVISIONS a dedicated server. The search tick forks
//      `if (sessionType == 2 && sub_1FF290()) DS-search else lobby-search`, and
//      the DS FAILURE path (sub_6FF040 -> sub_1FE630) sets state 5 and RESTARTS
//      the search. There is no listen-server branch to fall into.
//    * AreWeHost (lobby + 1598540) is written ONLY by sub_490E70, reachable only
//      from sub_491DE0 (session CREATE) and sub_473BE0 (migration). Hosting is a
//      CREATE-TIME act; no flag converts an existing session into a hosted one.
//    * calling the create path directly (sub_80290, shipped as fh_createhost)
//      was TESTED: it started a search that never counted down, and did not make
//      us host. REMOVED.
//    * blocking the DS search (dvar "3707" = 0) just means no match is found.
//    * the GRIIMS byte pokes (shipped as fh_griim) wrote an address with no name
//      and no xrefs that reads as an allocation-tracking table, and its
//      "oDisableJoining = 0" ENABLES joining -- the opposite of the mechanism.
//      REMOVED rather than left as a loaded gun.
//
//  So the match server is Demonware's and that is expected. Everything below is
//  about the half we can actually own.
//
// ---------------------------------------------------------------------------
//  LOBBY PLAYER LIST + KICK  (see force_host.cpp for the proof of each offset)
//
//  As the LOBBY host you can remove someone with the engine's own
//  PartyHost_KickPlayer -- which is a different thing from SV_KickClient, and
//  the one that applies here: SV_KickClient requires com_sv_running, i.e. that
//  you ARE the server, which you are not when a dedicated server is running the
//  match.
// ---------------------------------------------------------------------------
#include <cstdint>
#include <string>
#include <vector>

namespace force_host
{
	struct member_t
	{
		int           index;      // slot, 0..47 -- what kick() takes
		int           state;      // >= 5 means connected
		std::uint64_t xuid;       // SteamID64 on PC
		std::string   name;
		bool          is_me;
	};

	// Everyone currently in the lobby. Empty if the lobby is unreadable.
	[[nodiscard]] std::vector<member_t> lobby_members();

	// Remove one by slot index, via PartyHost_KickPlayer. Returns false when we
	// are not the host, or the slot is empty, or it would target ourselves.
	bool kick_member(int index, std::string& why);
}
// =============================================================================
//  net/force_host — host the match, and decide what it plays. No hotkeys.
// =============================================================================
//
//  WHAT WAS WRONG WITH THE OLD APPROACH (GRIIMS-WWII-Tool, read 2026-08-11)
//
//  Its ForceHost() poked six raw bytes and its "playlist spoof" was a HOTKEY:
//
//      F4 -> ApplySpoofedPlaylist()   Cbuf ";ui_mapname <map>", mapvote entries,
//                                     ";mm_skill_enabled 0", ";raidmode 0|1",
//                                     and two raw gametype dwords
//      F5 -> ApplyOriginalPlaylist()  put it back, ";party_maxplayers 18"
//
//  and its own UI told you the procedure: "Change to spoofed playlist when the
//  match is about to begin then change to original playlist when the match has
//  started." That is the timing trickery. Two further defects:
//
//    * the writes are ONE-SHOT, so anything the engine does afterwards (a
//      playlist re-apply, a lobby migration) silently undoes them;
//    * its Gametype1 / Gametype2 offsets are literally 0 in the shipped source,
//      so the gametype half never ran at all;
//    * it never touches the playlist NUMBER, which is what the game displays --
//      hence "the game thinks you're in the playlist you searched for".
//
//  ---------------------------------------------------------------------------
//  WHY THIS ONE NEEDS NO TIMING — the proof, decompiled 2026-08-11
//  ---------------------------------------------------------------------------
//
//  The map spawn reads the lobby params at the moment it spawns. sub_48C0C0:
//
//      v4 = sub_1970E0(lobby);      // ui_mapname   = *(QWORD*)(lobby + 616)
//      v5 = sub_1970A0(lobby);      // ui_gametype  = *(QWORD*)(lobby + 624)
//      ...
//      sub_7CAD0(v4, v5); sub_80DF0(v4, v5);
//      DB_LoadLevelXAssets(v4, 0);  // <- the map that actually loads
//
//  and the matchmaking search-params builder, sub_285DA0, reads ONLY the
//  playlist number:
//
//      v6 = sub_1971A0(lobby + 592);                  // params[11]
//      if (!private && !privateEscape)
//          v6 = sub_6554E0(client, v6);               // ordinal -> table row
//      *(DWORD*)searchBlob = v6;
//
//  ⭐ IT NEVER READS ui_mapname OR ui_gametype. That is the whole finding:
//  the map and gametype can be held at our values PERMANENTLY without touching
//  what matchmaking searches for. So there is no window to hit -- we simply
//  keep them correct, and whenever the engine decides to spawn, they are right.
//
//  ---------------------------------------------------------------------------
//  THE LOBBY PARAMS — every offset proven from its own accessor
//  ---------------------------------------------------------------------------
//      lobby 0                       IDA 0x8BE6040   (sub_470D30(0), stride
//                                                     205030 qwords = 1640240)
//      params base = lobby + 592     (sub_197070 / Party_SetLobbyParamFromCmd)
//
//      +592   params[0]   party_minplayers    set sub_1973E0  get sub_197130
//      +596   params[1]   party_maxplayers    set sub_1973D0  get sub_197110
//      +616   params[6]   ui_mapname   char*  set sub_1973C0  get sub_1970E0
//      +624   params[8]   ui_gametype  char*  set sub_1973A0  get sub_1970A0
//      +632   params[10]  private            get sub_197150
//      +636   params[11]  playlist ordinal    set sub_197460  get sub_1971A0
//      +652   params[15]  allowJoiningListenServer
//      +1598512           0 while there is no session  (LUI IsSearching)
//      +1598540           AreWeHost      (PROVEN BY NAME: Script_AreWeHost)
//      +1598544           dedicated      (Script_IsServerDedicated)
//
//  ⚠ ui_mapname / ui_gametype are INTERNED strings: sub_688B70 refcounts them
//  through the pool at off_ACA1388. They must never be written as raw pointers.
//  We set them the way the console does -- `ui_mapname <x>` through Cbuf, which
//  Cmd_ExecuteString feeds to Party_SetLobbyParamFromCmd -- so the interning is
//  the engine's, on the engine's own thread. (This module ticks from the DXGI
//  Present thread; a refcounted pool must not be touched from there.)
//
//  ---------------------------------------------------------------------------
//  THE PLAYLIST NUMBER — the engine's own rule, and a correction
//  ---------------------------------------------------------------------------
//  sub_6554E0 and sub_6563D0 both walk the same table and both count the same
//  way, so this is not inferred:
//
//      row_i     = IDA 0xABDE010 + 568*i,  i in [0,100)
//      row + 0   playlist display name        (Dvar_SetString "playlist_name")
//      row + 480 icon name                    (Dvar_SetString "1676")
//      row + 512 char* var-rule blob          ("party_maxplayers 32; ...")
//      row + 540 u16 map/gametype list index
//      row + 542 u16 VALIDITY -- non-zero means this row is a real playlist
//
//      playlist number = 0-based ORDINAL over rows whose +542 is non-zero
//
//  ⛔ CORRECTION to server_browser.cpp: it used base IDA 0xABDE228 with the name
//  at +32, i.e. 0xABDE248 + 568*i -- which is row_{i+1} + 0, the NEXT row's
//  name -- while testing validity at +6, i.e. row_i + 542, THIS row's. The two
//  tests were one row apart, which is why the note there says the word test
//  "did not match reality". It produced the right numbers only because row 0 is
//  empty and named <=> valid, so the two off-by-ones cancelled. Fixed here and
//  there; do not reintroduce the +32 name offset.
//
//  ---------------------------------------------------------------------------
//  ---------------------------------------------------------------------------
//  ⛔ DISPROVEN BY TEST 2026-08-11 — "refuse the dedicated-server handover"
//  ---------------------------------------------------------------------------
//  An earlier build hooked sub_1FD110 to keep IsServerDedicated false and make
//  IsServerListen true, on the theory that it would keep the match on this
//  machine. USER TESTED IT: the pre-match countdown completes and the match then
//  never starts. Removed.
//
//  The reading was backwards. sub_1FD110 is
//      (o[0] - 5) <= 2 && (int)o[3] >= 2      on the server-ACQUIRE state object
//  i.e. "the server we went and got is ready" -- NOT "this is a dedicated
//  server". Both IsDedicated and IsListen consume it, which is what misled me.
//  Refusing it does not make us the host; it tells the engine acquisition never
//  finished, so the launch waits forever. That is exactly the observed symptom.
//
//  ⛔ AND THE LARGER FRAME WAS WRONG. WWII's public matchmaking PROVISIONS a
//  server: CanStartAcquiringDSNow -> StartServerAcquire -> dwFindDSSessions ->
//  AssignServer -> launch. There is no client-hosting branch for a public
//  playlist; the shipped `matchmaking_allowJoiningListenServer 1` blobs are the
//  4-player playlists only. Earlier evidence already said so and was underweighted
//  (advertised=1 with AreWeHost=0, and nobody ever arrived).
//
//  THE CORRECT MODEL IS **LOBBY HOST, NOT SERVER HOST**. The match still runs on
//  Demonware's box; what you own is the LOBBY, and the deploy takes its map,
//  gametype and player counts from the lobby host's params. That is the only
//  reason a map spoof does anything at all -- and it is why holding the params
//  removes the timing without ever needing to be the server.
//
//  ---------------------------------------------------------------------------
//  ⛔ AND 18 PLAYERS IS THE CEILING. CLOSED 2026-08-11, do not re-open.
//  ---------------------------------------------------------------------------
//  party_maxplayers is NOT the cap (measured live at 33 while the match ran 18,
//  and sub_7FE60 sets it FROM sv_maxclients, so it is downstream). The cap is
//  svs_clientCount, written only by SV_Init:
//      if (!HIBYTE(word_1BD36F8) || sub_B8CB0()) svs_clientCount = sv_maxclients;
//      else                                      svs_clientCount = 48;   // the hub
//  and every server array is allocated from it.
//
//  Raising sv_maxclients is FATAL. SV_CreateServerHunk reserves g_serverHunkUser
//  IN ADVANCE from a client count, QUADRATICALLY (~33 MB at 18, ~106 MB at 48);
//  SV_Init then allocates past the reservation and Hunk_Alloc aborts with
//  "Fatal Error: Memory Error: 6 161". Tested in game. The reservation's caller is
//  behind an Arxan thunk (DB_Thread @0xACE30 is a JUMPOUT), so it cannot be made
//  to agree. 18 is not an oversight -- the whole server allocation is sized for it.
//
//  So MATCH_MAX_CLIENTS is 18 and the UI does not offer more.
//
//  ⭐ ZERO HOOKS. Everything is a guarded write to a documented field, or a
//  console command the engine already accepts.
// =============================================================================

#include <cstdint>
#include <string>
#include <vector>

namespace force_host
{
	void init();
	void tick();      // call once per frame; cheap, compare-then-write

	// ---- engine-supplied lists (read LIVE, never hardcoded) ----------------
	struct Playlist
	{
		int         id = -1;    // the ordinal params[11] uses
		int         row = -1;   // its index in the table, for diagnostics
		std::string name;
	};
	std::vector<Playlist> playlists();
	std::string playlist_name(int id);

	std::vector<std::string> maps();        // "mp_d_day", ... from the engine table,
	                                         // PLUS anything registered but pulled
	                                         // from matchmaking rotation (e.g. mp_house)
	std::vector<std::string> gametypes();   // "war", "dom", ... deduped

	// ---- configuration ----------------------------------------------------
	bool enabled();
	void set_enabled(bool on);

	// The playlist the match should RUN and REPORT. -1 leaves it alone.
	int  play_playlist();
	void set_play_playlist(int id);

	// Optional: search a DIFFERENT (busier) playlist, then switch to the play
	// playlist once a session exists. -1 = don't; use the play playlist for
	// both, which is the simple case and needs no phase at all.
	int  search_playlist();
	void set_search_playlist(int id);

	// "" leaves the engine's own choice alone.
	std::string map();
	void set_map(const std::string& internal_name);
	std::string gametype();
	void set_gametype(const std::string& gametype);

	int  max_players();
	void set_max_players(int n);
	int  min_players();
	void set_min_players(int n);

	// Run the ENGINE's own playlist applier, sub_6563D0: map, gametype, display
	// name, icon and the playlist's var-rule blob, exactly as the menu does it.
	// CONFIRMED IN GAME 2026-08-11.
	//
	// apply_playlist_now() is the implementation and MUST run on the client
	// thread (it execs config files and touches the interned-string pool), so
	// anything on the Present thread calls queue_apply_playlist() instead, which
	// goes through the command buffer.
	void apply_playlist_now();
	void queue_apply_playlist();

	// Run it automatically whenever the Play playlist changes, rather than only
	// from a button. Change-triggered, never in a loop. Default on.
	bool auto_apply();
	void set_auto_apply(bool on);

	// ---- BOTS -------------------------------------------------------------
	// Per-team bot count, straight through the engine's own setter/getter --
	// sub_38E350 / sub_3882C0, the pair the LUI SetBotsTeamLimit and
	// GetBotsTeamLimit bindings sit on.
	//
	// ⭐ There is NO UPPER CLAMP in native code: sub_38E350's only guard is
	// `if (count <= 0) count = 0`, and the value is one byte per team at
	// settingsObject + 47 + team. Any cap the private-match menu enforces is in
	// the LUI slider (Lua), so calling the native setter goes under it.
	// BotsAreAllowed (sub_388210) is literally `return 1`.
	//
	// team: 0 or 1. Clamped to 17, because a match has 18 client slots and one of
	// them is you -- which is why a "24 per team" request shows up as 9v9.
	void set_bots_team_limit(int team, int count);
	int  bots_team_limit(int team);

	// ---- readout ----------------------------------------------------------
	struct Status
	{
		bool        lobby_ok = false;
		bool        we_host = false;
		bool        dedicated = false;
		bool        priv = false;
		bool        have_session = false;   // lobby+1598512 != 0
		int         playlist = -1;
		std::string playlist_disp;
		std::string cur_map;
		std::string cur_gametype;
		int         cur_min = 0;
		int         cur_max = 0;
		bool        allow_listen = false;
		bool        hosting_enabled = false;
		const char* phase = "";             // "search" / "deploy" / "off"
	};
	Status status();
}
