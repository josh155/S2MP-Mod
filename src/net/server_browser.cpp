#include "pch.h"
#include "server_browser.hpp"

#include "Console.hpp"
#include "DevMode.hpp"
#include "GameUtil.hpp"

#include <cstdio>

namespace server_browser
{
	namespace
	{
		// ---- the pointer chain, all engine accessors ------------------------
		// Arithmetic written out per RULE A1:
		//   lobby 0   IDA 0x8BE6040 - 0x1000 = 0x8BE5040
		//
		// VERIFIED LIVE before this module was written: with the game running,
		//   L               = 0x7FF62EFF6040
		//   *(QWORD*)(L+16) = 0x7FF62EB03730   (matches the mm= in earlier logs)
		//   *(QWORD*)(M + 31552) read back as 0x7FF62EFF6040 == L
		// i.e. the engine's OWN back-pointer confirms M, so nothing here is an
		// inferred offset.
		constexpr std::size_t ADDR_LOBBY_OBJ0   = 0x8BE5040;
		constexpr std::size_t OFF_LOBBY_MM      = 16;      // L + 16   -> M
		constexpr std::size_t OFF_MM_LOBBY      = 31552;   // M + 31552 -> L (check)
		constexpr std::size_t OFF_MM_RESULTS    = 1712;    // sub_29A8B0(M) = M + 1712
		constexpr std::size_t OFF_RESULT_COUNT  = 29808;   // Search_GetResultCount
		constexpr std::size_t OFF_LOBBY_PARAMS  = 592;     // params base on the lobby
		constexpr std::size_t P_PLAYLIST        = 11;      // params[11]

		// Per-result fields. p = R + 80 + 596*i. Names are sub_2A1820's own
		// telemetry labels, so every offset below is documented by the engine.
		constexpr std::size_t SR_BASE   = 80;
		constexpr std::size_t SR_STRIDE = 596;
		constexpr int         SR_MAX    = 64;

		// ---- THE PLAYLIST TABLE, READ LIVE ----------------------------------
		// TWO bugs were made here; both are corrected below.
		//
		//  1. A hardcoded list of 12 ids. The LIVE table holds 44 playlists, so a
		//     sweep over the hardcoded list missed three quarters of the game.
		//
		//  2. Worse: the TABLE INDEX was used as the playlist id. It is not.
		//     sub_6554E0 is a MAPPING function -- it walks the table counting
		//     valid records and returns the INDEX of the Nth one -- so the id the
		//     game uses is an ORDINAL over valid records, not the array position.
		//
		// ⛔ CORRECTED 2026-08-11, and the old note here was wrong about WHY.
		//
		// The record base is IDA 0xABDE010, not 0xABDE228, proven twice:
		//   sub_6563D0 tail:  Dvar_SetString("playlist_name", 568*row + 0xABDE010)
		//   sub_6554E0 walk:  validity word starts at 0xABDE22E and steps 568
		//                     -> 0xABDE22E - 0xABDE010 = 0x21E = 542 = row+542
		//
		//   row_i     = IDA 0xABDE010 + 568*i,  i in [0,100)
		//   row + 0   display name        row + 480 icon name
		//   row + 512 char* var-rule blob row + 540 u16 map/gametype list index
		//   row + 542 u16 VALIDITY -- non-zero means a real playlist
		//   playlist id = 0-based ordinal over rows whose +542 is non-zero
		//
		// The OLD code read the name at 0xABDE228 + 568*i + 32 = row_{i+1} + 0
		// (the NEXT row's name) while testing validity at +6 = row_i + 542 (THIS
		// row's) -- the two tests were one record apart. It still produced the
		// right ids only because row 0 is empty and named <=> valid, so the two
		// off-by-ones cancelled. That is why the word test "did not match".
		//
		//   IDA 0xABDE010 - 0x1000 = 0xABDD010
		constexpr std::size_t ADDR_PLAYLIST_TABLE = 0xABDD010;
		constexpr std::size_t PLAYLIST_STRIDE     = 568;
		constexpr std::size_t PLAYLIST_COUNT      = 100;
		constexpr std::size_t PLAYLIST_NAME_OFF   = 0;
		constexpr std::size_t PLAYLIST_VALID_OFF  = 542;

		struct PlaylistEntry { int id; std::string name; };

		// Defined below; declared here because live_playlists() sits above it.
		[[nodiscard]] bool readable(const void* p, std::size_t n);

		[[nodiscard]] std::vector<PlaylistEntry> live_playlists()
		{
			std::vector<PlaylistEntry> out;
			const auto* base = reinterpret_cast<const std::uint8_t*>(_b(ADDR_PLAYLIST_TABLE));
			if (!readable(base, PLAYLIST_STRIDE * PLAYLIST_COUNT))
			{
				return out;
			}
			for (std::size_t i = 0; i < PLAYLIST_COUNT; ++i)
			{
				const auto* rec = base + PLAYLIST_STRIDE * i;
				// The engine's own validity test, not a name heuristic.
				if (*reinterpret_cast<const std::uint16_t*>(rec + PLAYLIST_VALID_OFF) == 0)
				{
					continue;
				}
				const auto* nm = reinterpret_cast<const char*>(rec + PLAYLIST_NAME_OFF);
				std::string name;
				for (std::size_t k = 0; k < 48; ++k)
				{
					const auto c = static_cast<unsigned char>(nm[k]);
					if (c == 0)
					{
						break;
					}
					if (c >= 0x20 && c < 0x7F)
					{
						name.push_back(static_cast<char>(c));
					}
				}
				// A valid but unnamed row still occupies an ordinal -- dropping it
				// would shift every later id, so it is listed, not skipped.
				if (name.empty())
				{
					name = "(unnamed)";
				}
				// The ID is the ORDINAL (out.size()), NOT the table index i.
				out.push_back({ static_cast<int>(out.size()), std::move(name) });
			}
			return out;
		}

		// RULE A6: a global belonging to an idle subsystem can hold junk, so a
		// null check is not enough before dereferencing.
		[[nodiscard]] bool readable(const void* p, const std::size_t n)
		{
			if (!p)
			{
				return false;
			}
			MEMORY_BASIC_INFORMATION mbi{};
			if (!VirtualQuery(p, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT)
			{
				return false;
			}
			if (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))
			{
				return false;
			}
			const auto start = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress);
			const auto want = reinterpret_cast<std::uintptr_t>(p) + n;
			return want <= start + mbi.RegionSize;
		}

		[[nodiscard]] bool sane_ptr(const std::uintptr_t p)
		{
			return p >= 0x10000 && p <= 0x00007FFFFFFFFFFFull && (p & 7) == 0;
		}

		[[nodiscard]] std::uintptr_t lobby0()
		{
			const auto l = _b(ADDR_LOBBY_OBJ0);
			return readable(reinterpret_cast<const void*>(l), 64) ? l : 0;
		}

		// M, but only if the engine's own back-pointer agrees. That check is
		// free and it turns "we walked into the wrong object" into a refusal
		// instead of a plausible-looking table of nonsense.
		[[nodiscard]] std::uintptr_t mm_object()
		{
			const auto l = lobby0();
			if (!l || !readable(reinterpret_cast<const void*>(l + OFF_LOBBY_MM), 8))
			{
				return 0;
			}
			const auto m = *reinterpret_cast<const std::uintptr_t*>(l + OFF_LOBBY_MM);
			if (!sane_ptr(m) || !readable(reinterpret_cast<const void*>(m + OFF_MM_LOBBY), 8))
			{
				return 0;
			}
			return (*reinterpret_cast<const std::uintptr_t*>(m + OFF_MM_LOBBY) == l) ? m : 0;
		}

		[[nodiscard]] std::uintptr_t results_object()
		{
			const auto m = mm_object();
			return m ? m + OFF_MM_RESULTS : 0;
		}

		[[nodiscard]] const int* params()
		{
			const auto l = lobby0();
			if (!l)
			{
				return nullptr;
			}
			const auto* p = reinterpret_cast<const int*>(l + OFF_LOBBY_PARAMS);
			return readable(p, sizeof(int) * 20) ? p : nullptr;
		}

		// ---- RAW DIFF: find the real player-count field, by measurement -------
		// The player count reads 1/12 for every result. Two possibilities, and
		// they need opposite responses:
		//   (a) p[-2] is not the occupied count and the real one is elsewhere
		//   (b) the values are correct and these genuinely ARE 1-player lobbies
		//       -- matchmaking returns other searchers' LOBBIES to merge with,
		//       and a solo player searching is a 1-player lobby
		//
		// Rather than guess another offset (the exact mistake this project keeps
		// paying for), dump which bytes DIFFER between results. A field that is
		// identical across every row cannot be a player count; one that varies
		// with what you would expect is a candidate.
		void cmd_raw()
		{
			const auto r = results_object();
			if (!r || !readable(reinterpret_cast<const void*>(r + OFF_RESULT_COUNT), 4))
			{
				Console::printf("[browser] table not reachable");
				return;
			}
			const int n = *reinterpret_cast<const std::int32_t*>(r + OFF_RESULT_COUNT);
			if (n <= 0 || n > SR_MAX)
			{
				Console::printf("[browser] no results to dump (count=%d)", n);
				return;
			}

			// entry i = R + 8 + 596*i   (sub_29CEA0). p sits at entry + 72.
			const auto entry = [r](const int i) -> const std::uint8_t*
			{
				return reinterpret_cast<const std::uint8_t*>(r + 8 + SR_STRIDE * static_cast<std::size_t>(i));
			};
			if (!readable(entry(0), SR_STRIDE * static_cast<std::size_t>(n)))
			{
				Console::printf("[browser] entry span not readable");
				return;
			}

			Console::printf("[browser] RAW: %d result(s), entry = R+8+596*i, p = entry+72", n);

			// Which offsets differ across results?
			std::string varying;
			int shown = 0;
			for (std::size_t off = 0; off < SR_STRIDE; ++off)
			{
				const auto v0 = entry(0)[off];
				bool differs = false;
				for (int i = 1; i < n; ++i)
				{
					if (entry(i)[off] != v0) { differs = true; break; }
				}
				if (differs && shown < 64)
				{
					char b[24];
					// Report BOTH the entry-relative and the p-relative offset,
					// because every documented field is named p-relative.
					_snprintf_s(b, sizeof(b), _TRUNCATE, "%zu(p%+d) ", off,
						static_cast<int>(off) - 72);
					varying += b;
					++shown;
				}
			}
			Console::printf("[browser] offsets that DIFFER between results: %s",
				varying.empty() ? "<none - every row is byte-identical>" : varying.c_str());

			// Hexdump the slot region of the first few rows so the numbers can be
			// read directly. p-8 .. p+16 covers datacenter/occupied/available/status.
			for (int i = 0; i < n && i < 4; ++i)
			{
				const auto* p = entry(i) + 72;
				char line[160]{};
				int w = _snprintf_s(line, sizeof(line), _TRUNCATE, "[browser]  #%d p-8..p+15:", i);
				for (int k = -8; k < 16; ++k)
				{
					w += _snprintf_s(line + w, sizeof(line) - w, _TRUNCATE, " %02X", p[k]);
				}
				Console::printf("%s", line);
				Console::printf("[browser]     -> p[-2]=%u (occupied?)  p[0]=%u (available?)"
					"  total=%u  status=%d",
					p[-2], p[0], static_cast<unsigned>(p[0]) + p[-2],
					*reinterpret_cast<const std::int32_t*>(p + 4));
			}
		}

		// =====================================================================
		//  MANUAL SCAN + SWEEP
		// =====================================================================
		//   searchState = M + 1656          sub_29A8C0(M)
		//   tick        = sub_29D9C0        IDA 0x29D9C0 - 0x1000 = 0x29C9C0
		//   playlist    = *(u32*)(lobby + 636)     params[11], per sub_285DA0
		//
		// Calling the tick is exactly what the LUI binding sub_2960E0 does, so it
		// is an ordinary call on an ordinary object -- NOT a hook.
		constexpr std::size_t ADDR_SEARCH_TICK = 0x29C9C0;
		constexpr std::size_t OFF_MM_SEARCH    = 1656;
		constexpr std::size_t OFF_PLAYLIST     = OFF_LOBBY_PARAMS + 44;  // lobby + 636

		// ---- THE RESULT CACHE -----------------------------------------------
		// The engine's table is NOT ours and does not persist: sub_29D410 memsets
		// it (memset(R+8, 0, 0x7468); count = 0) at the top of every tick, and it
		// is cleared when a search ends. Reading it live therefore made the list
		// vanish the moment you stopped searching.
		//
		// So poll it continuously and merge into OUR OWN storage. Rows survive
		// until explicitly cleared, which is what makes a sweep across playlists
		// add up to one list instead of 44 that each disappear.
		//
		// Identity for dedupe: the 64-byte host-address blob at p-64. Two results
		// with the same host are the same lobby, even across playlists.
		struct CacheKey
		{
			std::uint64_t host_hash;
			int playlist;
			bool operator==(const CacheKey& o) const
			{
				return host_hash == o.host_hash && playlist == o.playlist;
			}
		};
		std::vector<std::pair<CacheKey, Server>> g_cache;
		DWORD g_last_poll = 0;
		DWORD g_last_hit = 0;          // when we last saw ANY result

		[[nodiscard]] std::uint64_t hash_host(const std::uint8_t* p)
		{
			// FNV-1a over the host-address blob.
			std::uint64_t h = 1469598103934665603ull;
			for (int i = -64; i < 0; ++i)
			{
				h ^= p[i];
				h *= 1099511628211ull;
			}
			return h;
		}

		// Sweep state
		bool  g_sweeping = false;
		int   g_sweep_idx = 0;
		int   g_saved_playlist = -1;
		DWORD g_sweep_at = 0;
		std::string g_sweep_note = "idle";
		std::vector<Server> g_sweep_results;
		std::vector<PlaylistEntry> g_sweep_list;
		constexpr DWORD SWEEP_DWELL_MS = 2500;   // let the service answer

		[[nodiscard]] int* playlist_ptr()
		{
			const auto l = lobby0();
			if (!l)
			{
				return nullptr;
			}
			auto* p = reinterpret_cast<int*>(l + OFF_PLAYLIST);
			return readable(p, sizeof(int)) ? p : nullptr;
		}

		// Refuse while in a REAL match, but NOT in the hub -- the hub/menu is
		// exactly where you want to browse from.
		//
		// ⚠ CORRECTED: this used to be `connstate >= 9` alone, which refused in the
		// hub too and made the buttons look dead ("refusing to sweep: you are in a
		// match" while sitting in the menu). The virtual lobby loads a BSP, runs a
		// local server (com_sv_running = 1) and reaches connstate ACTIVE, so
		// connstate alone cannot tell hub from game.
		//
		// byte_1BD36F8 is the hub discriminator, measured and corroborated twice:
		//     mp_hub_allies_slim -> 1        real map (shipment/forest) -> 0
		//   clientConnectionState IDA 0x1BAF4E4 - 0x1000 = 0x1BAE4E4
		//   byte_1BD36F8         IDA 0x1BD36F8 - 0x1000 = 0x1BD26F8
		[[nodiscard]] bool in_the_hub()
		{
			const auto* h = reinterpret_cast<const std::uint8_t*>(_b(0x1BD26F8));
			return readable(h, 1) && *h != 0;
		}

		[[nodiscard]] bool in_a_match()
		{
			const auto* cs = reinterpret_cast<const std::int32_t*>(_b(0x1BAE4E4));
			if (!readable(cs, 4) || *cs < 9)     // 9 = PRIMED, 10 = ACTIVE
			{
				return false;
			}
			return !in_the_hub();                // hub = fine to browse from
		}

		// Issue one search on whatever playlist is currently set.
		bool issue_tick()
		{
			const auto m = mm_object();
			if (!m)
			{
				return false;
			}
			const auto state = m + OFF_MM_SEARCH;
			if (!readable(reinterpret_cast<const void*>(state), 32))
			{
				return false;
			}
			// RULE A17: sub_29D9C0 returns `char`. Do not widen.
			using tick_t = char(__fastcall*)(std::uintptr_t);
			reinterpret_cast<tick_t>(_b(ADDR_SEARCH_TICK))(state);
			return true;
		}

		// Read the LIVE table and merge into the cache. Safe to call often; the
		// engine's table is transient, ours is not.
		void poll_and_merge()
		{
			const auto r = results_object();
			if (!r || !readable(reinterpret_cast<const void*>(r + OFF_RESULT_COUNT), 4))
			{
				return;
			}
			const int n = *reinterpret_cast<const std::int32_t*>(r + OFF_RESULT_COUNT);
			if (n <= 0 || n > SR_MAX)
			{
				return;
			}
			const int pl = current_playlist();
			const auto name = playlist_name(pl);

			for (int i = 0; i < n; ++i)
			{
				const auto pa = r + SR_BASE + SR_STRIDE * static_cast<std::size_t>(i);
				if (!readable(reinterpret_cast<const void*>(pa - 64), 64 + 421))
				{
					break;
				}
				const auto* p = reinterpret_cast<const std::uint8_t*>(pa);

				Server s;
				s.index      = i;
				s.players    = p[-2];
				s.capacity   = static_cast<int>(p[0]) + p[-2];
				s.ping       = p[419];
				s.datacenter = *reinterpret_cast<const std::uint16_t*>(p - 4);
				s.qos_error  = *reinterpret_cast<const std::int32_t*>(p + 8);
				s.throttled  = *reinterpret_cast<const std::int32_t*>(p + 412) != 0;
				const auto stv = *reinterpret_cast<const std::int32_t*>(p + 4);
				s.joinable   = (static_cast<unsigned>(stv - 1) <= 1u);
				s.playlist   = pl;
				s.playlist_name = name;

				const CacheKey k{ hash_host(p), pl };
				auto it = std::find_if(g_cache.begin(), g_cache.end(),
					[&k](const auto& e) { return e.first == k; });
				if (it == g_cache.end())
				{
					g_cache.emplace_back(k, std::move(s));
				}
				else
				{
					it->second = std::move(s);   // refresh players/ping in place
				}
				g_last_hit = GetTickCount();
			}
		}

		void restore_playlist()
		{
			if (g_saved_playlist >= 0)
			{
				if (int* p = playlist_ptr())
				{
					*p = g_saved_playlist;
				}
				g_saved_playlist = -1;
			}
		}

		void cmd_playlists()
		{
			const auto pls = live_playlists();
			const int cur = current_playlist();
			Console::printf("[browser] %zu live playlists (id = ordinal, which is what "
				"params[11] holds). Current: %d = %s",
				pls.size(), cur, playlist_name(cur).c_str());
			for (const auto& e : pls)
			{
				Console::printf("[browser]  %3d  %s%s", e.id, e.name.c_str(),
					e.id == cur ? "   <- current" : "");
			}
		}

		void cmd_scan()
		{
			scan_current();
		}

		void cmd_sweep()
		{
			if (g_sweeping) { sweep_stop(); }
			else            { sweep_start(); }
		}

		void cmd_servers()
		{
			const auto st = status();
			if (!st.reachable)
			{
				Console::printf("[browser] result table not reachable — the lobby/"
					"matchmaking object did not resolve, or its back-pointer did not "
					"match. Join a lobby first.");
				return;
			}
			const auto list = servers();
			Console::printf("[browser] playlist %d (%s) — %zu result(s)",
				st.playlist, playlist_name(st.playlist).c_str(), list.size());
			if (list.empty())
			{
				Console::printf("[browser] nothing yet. This fills while the GAME is "
					"searching (Find Match) — it shows what the service returned for "
					"that search. Nothing here starts a search.");
				return;
			}
			for (const auto& s : list)
			{
				Console::printf("[browser]  #%-2d  %d/%-3d players  ping %-4d  dc %-5d %s%s",
					s.index, s.players, s.capacity, s.ping, s.datacenter,
					s.joinable ? "joinable" : "NOT joinable",
					s.throttled ? " throttled" : "");
			}
		}
	}

	void init()
	{
		// NO Hook::create anywhere in this file. See the header: the previous
		// implementation broke Find Match by patching this exact path.
		dev_mode::add_command("browser", cmd_servers);
		dev_mode::add_command("net_servers", cmd_servers);
		dev_mode::add_command("browser_raw", cmd_raw);
		dev_mode::add_command("browser_playlists", cmd_playlists);
		dev_mode::add_command("browser_scan", cmd_scan);
		dev_mode::add_command("browser_sweep", cmd_sweep);
		Console::printf("[browser] online server browser ready (read-only, NO hooks) "
			"— `browser` lists what matchmaking returned for the current search.");
	}


	int current_playlist()
	{
		const auto* p = params();
		return p ? p[P_PLAYLIST] : -1;
	}

	std::string playlist_name(const int id)
	{
		for (const auto& e : live_playlists())
		{
			if (e.id == id)
			{
				return e.name;
			}
		}
		return id < 0 ? "none" : ("playlist " + std::to_string(id));
	}

	Status status()
	{
		Status s;
		const auto r = results_object();
		s.reachable = (r != 0);
		s.playlist = current_playlist();
		if (!r || !readable(reinterpret_cast<const void*>(r + OFF_RESULT_COUNT), 4))
		{
			return s;
		}
		const int n = *reinterpret_cast<const std::int32_t*>(r + OFF_RESULT_COUNT);
		s.count = (n > 0 && n <= SR_MAX) ? n : 0;
		s.searching = s.count > 0;
		return s;
	}

	std::vector<Server> servers()
	{
		// The CACHE, not the engine's transient table. See poll_and_merge().
		std::vector<Server> out;
		out.reserve(g_cache.size());
		for (const auto& e : g_cache)
		{
			out.push_back(e.second);
		}
		// Most players first, then lowest ping -- the order you actually want.
		std::sort(out.begin(), out.end(), [](const Server& a, const Server& b)
		{
			if (a.players != b.players) { return a.players > b.players; }
			return a.ping < b.ping;
		});
		return out;
	}

	void clear_cache()
	{
		g_cache.clear();
		Console::printf("[browser] cache cleared");
	}

	int cached_count() { return static_cast<int>(g_cache.size()); }

	int last_result_ms()
	{
		return g_last_hit ? static_cast<int>(GetTickCount() - g_last_hit) : -1;
	}


	const char* busy_reason()
	{
		if (in_a_match())
		{
			return "In a match — back out to the menu to scan.";
		}
		if (!mm_object())
		{
			return "Matchmaking object not resolvable yet (not at the menu?).";
		}
		return nullptr;
	}

	void scan_current()
	{
		if (in_a_match())
		{
			Console::printf("[browser] refusing to scan: you are in a real match. "
				"Back out to the menu/hub first.");
			return;
		}
		if (!issue_tick())
		{
			Console::printf("[browser] scan failed: the matchmaking object did not "
				"resolve. Are you at the menu?");
			return;
		}
		const int pl = current_playlist();
		Console::printf("[browser] scan issued for playlist %d (%s). Results are "
			"merged into the cache as they arrive and are KEPT when the search ends.",
			pl, playlist_name(pl).c_str());
	}

	bool sweeping() { return g_sweeping; }
	std::string sweep_status() { return g_sweep_note; }

	void sweep_start()
	{
		if (g_sweeping)
		{
			return;
		}
		if (in_a_match())
		{
			Console::printf("[browser] refusing to sweep: you are in a real match. "
				"Back out to the menu/hub and try again.");
			return;
		}
		int* p = playlist_ptr();
		if (!p || !mm_object())
		{
			Console::printf("[browser] cannot sweep: the lobby/matchmaking object did "
				"not resolve — are you at the menu?");
			return;
		}
		g_sweep_list = live_playlists();
		if (g_sweep_list.empty())
		{
			Console::printf("[browser] cannot sweep: the playlist table read empty");
			return;
		}
		g_saved_playlist = *p;          // ALWAYS restored, including on abort
		g_sweeping = true;
		g_sweep_idx = 0;
		g_sweep_at = 0;                 // fire the first immediately
		Console::printf("[browser] sweep started over %zu playlists, %.1fs each "
			"(~%.0fs). Results ACCUMULATE — the cache is not cleared between "
			"playlists, so this builds one combined list. Playlist %d (%s) will be "
			"restored at the end.",
			g_sweep_list.size(), SWEEP_DWELL_MS / 1000.0f,
			g_sweep_list.size() * SWEEP_DWELL_MS / 1000.0f,
			g_saved_playlist, playlist_name(g_saved_playlist).c_str());
	}

	void sweep_stop()
	{
		if (!g_sweeping)
		{
			return;
		}
		g_sweeping = false;
		restore_playlist();
		g_sweep_note = "stopped";
		Console::printf("[browser] sweep stopped; playlist restored. %d row(s) cached.",
			cached_count());
	}

	void tick()
	{
		// ALWAYS poll and merge, sweeping or not. The engine's table is wiped at
		// the top of every search tick (sub_29D410) and when a search ends, so
		// anything not captured here is lost -- that is exactly why the list used
		// to vanish the moment you stopped searching.
		const DWORD tnow = GetTickCount();
		if (tnow - g_last_poll >= 250)
		{
			g_last_poll = tnow;
			poll_and_merge();
		}

		if (!g_sweeping)
		{
			return;
		}

		// Bail out safely if the world changed under us.
		if (in_a_match() || !mm_object())
		{
			Console::printf("[browser] sweep aborted (entered a match, or the lobby "
				"went away). Restoring playlist.");
			sweep_stop();
			return;
		}

		if (g_sweep_at != 0 && (tnow - g_sweep_at) < SWEEP_DWELL_MS)
		{
			return;
		}

		if (g_sweep_idx >= static_cast<int>(g_sweep_list.size()))
		{
			g_sweeping = false;
			restore_playlist();
			g_sweep_note = "done";
			Console::printf("[browser] sweep complete — %d row(s) cached across %zu "
				"playlists. Playlist restored.", cached_count(), g_sweep_list.size());
			return;
		}

		const auto& e = g_sweep_list[g_sweep_idx];
		if (int* p = playlist_ptr())
		{
			*p = e.id;      // params[11] -- the field sub_285DA0 builds the blob from
		}
		issue_tick();
		g_sweep_note = std::string("scanning ") + e.name
			+ " (" + std::to_string(g_sweep_idx + 1) + "/"
			+ std::to_string(g_sweep_list.size()) + ")";
		g_sweep_at = tnow;
		++g_sweep_idx;
	}
}
