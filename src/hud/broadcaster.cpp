// =============================================================================
//  hud/broadcaster.cpp — minimal HUD via the game's own broadcaster settings
// =============================================================================
//  Read broadcaster.hpp first. It records where every address and offset came
//  from, why cg_draw2D and model-blanking could not do this, and the one piece
//  of manufactured state (the local IsBroadcaster flag) with its justification.
//
//  RULE A14: every engine address is resolved INSIDE a function. Nothing here
//  caches a _b() literal at namespace scope.
//  RULE A18: nothing logs per frame.
//  RULE A3.1: this module installs NO hooks. The once-per-frame latch is a
//  call-out from demo_native's existing CG_PublishHudModel stub.
// =============================================================================

#include "pch.h"
#include "hud/broadcaster.hpp"

#include "demo/demo_game.hpp"

#include "Console.hpp"
#include "DevMode.hpp"
#include "GameUtil.hpp"

#include <cstring>
#include <format>
#include <string>

namespace broadcaster
{
	namespace
	{
		// ---- engine addresses (IDA -> _b literal is IDA - 0x1000) -----------
		//   byte_8BE0A20  gate byte,   stride 6920   0x8BE0A20 - 0x1000 = 0x8BDFA20
		//   0x8BE09F0     DDL data,    stride 6920   0x8BE09F0 - 0x1000 = 0x8BDF9F0
		//   qword_8BDEF18 the DDL def                0x8BDEF18 - 0x1000 = 0x8BDDF18
		//   sub_A1C8E0    make root cursor           0xA1C8E0  - 0x1000 = 0xA1B8E0
		//   sub_A1D010    move to named field        0xA1D010  - 0x1000 = 0xA1C010
		//   sub_A1D4D0    set int                    0xA1D4D0  - 0x1000 = 0xA1C4D0
		//   sub_A1C860    get int                    0xA1C860  - 0x1000 = 0xA1B860
		constexpr std::size_t PROFILE_STRIDE = 6920;

		// RULE A17 — exact return widths, taken from the callee that defines
		// them. sub_A21940 (which sub_A1D010 tail-calls) and sub_A1D6F0 (which
		// sub_A1D4D0 tail-calls) both return `char`, i.e. only AL is defined.
		using DDL_MakeRootCursor_t = void* (__fastcall*)(void* cursor32, void* def);
		using DDL_MoveToName_t = char(__fastcall*)(void* dst, void* src, const char* name);
		using DDL_SetInt_t = char(__fastcall*)(void* cursor, void* buffer, int value);
		using DDL_GetInt_t = int(__fastcall*)(void* cursor, void* buffer);

		// ---- cg offsets, from sub_33E550 / sub_411BE0 -----------------------
		constexpr std::size_t CG_CLIENT_SLOT_BYTE = 22904;    // sub_411BE0
		constexpr std::size_t CG_BC_GATE_BASE = 3878300;      // stride 4704
		constexpr std::size_t CG_BC_GATE_STRIDE = 4704;
		constexpr std::size_t CG_BC_FLAG_BASE = 4405240;      // stride 152 (clientinfo)
		constexpr std::size_t CG_BC_FLAG_STRIDE = 152;

		// ---- state ----------------------------------------------------------
		std::atomic<bool> g_enabled{ false };
		bool g_saved_valid = false;
		std::vector<int> g_saved;          // parallel to settings()
		std::uint64_t g_restore_binds_at[2]{ 0, 0 };
		bool g_warned_no_gate = false;
		bool g_warned_no_cg = false;
		std::atomic<bool> g_logged_theater_gate{ false };

		// ---- safety ---------------------------------------------------------
		// RULE A6 — a null check is not enough in this game; an idle subsystem's
		// global holds junk, not zero.
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
			const auto addr = reinterpret_cast<std::uintptr_t>(p);
			return addr + n <= start + mbi.RegionSize;
		}

		[[nodiscard]] bool writable(const void* p, const std::size_t n)
		{
			if (!readable(p, n))
			{
				return false;
			}
			MEMORY_BASIC_INFORMATION mbi{};
			if (!VirtualQuery(p, &mbi, sizeof(mbi)))
			{
				return false;
			}
			constexpr DWORD wr = PAGE_READWRITE | PAGE_WRITECOPY
				| PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
			return (mbi.Protect & wr) != 0;
		}

		// ---- the broadcaster settings DDL blob ------------------------------
		// gate: GetBroadcasterSettings pushes nil unless this is non-zero, so a
		// zero here means the profile never parsed broadcastersettings.txt and
		// the data buffer must NOT be written.
		[[nodiscard]] unsigned char* ddl_gate(const int client)
		{
			auto* p = reinterpret_cast<unsigned char*>(0x8BDFA20_b)
				+ PROFILE_STRIDE * static_cast<std::size_t>(client);
			return readable(p, 1) ? p : nullptr;
		}

		[[nodiscard]] void* ddl_buffer(const int client)
		{
			auto* p = reinterpret_cast<unsigned char*>(0x8BDF9F0_b)
				+ PROFILE_STRIDE * static_cast<std::size_t>(client);
			return readable(p, PROFILE_STRIDE) ? p : nullptr;
		}

		[[nodiscard]] void* ddl_def()
		{
			auto* slot = reinterpret_cast<void**>(0x8BDDF18_b);
			if (!readable(slot, sizeof(void*)))
			{
				return nullptr;
			}
			void* def = *slot;
			// The def is an asset pointer; a 64-byte read covers every field the
			// cursor API touches (+24 size, +28 bits, +36 type, +52 unit).
			return readable(def, 64) ? def : nullptr;
		}

		// Build a cursor positioned on `name`. Faithful to sub_46B760:
		//     r = MakeRootCursor(scratch, def);  copy 32 bytes;  MoveToName(cur,cur,name)
		[[nodiscard]] bool cursor_for(const char* name, unsigned char (&cursor)[32])
		{
			void* def = ddl_def();
			if (!def || !name || !*name)
			{
				return false;
			}
			const auto make = reinterpret_cast<DDL_MakeRootCursor_t>(0xA1B8E0_b);
			const auto move = reinterpret_cast<DDL_MoveToName_t>(0xA1C010_b);

			alignas(16) unsigned char scratch[64]{};
			void* r = make(scratch, def);
			if (!r)
			{
				return false;
			}
			std::memcpy(cursor, r, sizeof(cursor));
			return move(cursor, cursor, name) != 0;
		}

		// ---- the local IsBroadcaster flag -----------------------------------
		struct bc_flag_t
		{
			unsigned char* flag{};   // cg + 4405240 + 152*slot
			bool gate_open{};        // cg + 3878300 + 4704*slot != 0
			int slot{ -1 };
		};

		[[nodiscard]] bc_flag_t broadcaster_flag()
		{
			bc_flag_t out{};
			auto* cg = static_cast<unsigned char*>(demo_game::cg_globals_for(0));
			if (!cg || !readable(cg + CG_CLIENT_SLOT_BYTE, 1))
			{
				return out;
			}
			const int slot = *(cg + CG_CLIENT_SLOT_BYTE);
			if (slot < 0 || slot >= 64)
			{
				return out;
			}
			auto* gate = cg + CG_BC_GATE_BASE + CG_BC_GATE_STRIDE * static_cast<std::size_t>(slot);
			auto* flag = cg + CG_BC_FLAG_BASE + CG_BC_FLAG_STRIDE * static_cast<std::size_t>(slot);
			if (!readable(gate, 4) || !writable(flag, 1))
			{
				return out;
			}
			out.slot = slot;
			out.gate_open = *reinterpret_cast<const std::int32_t*>(gate) != 0;
			out.flag = flag;
			return out;
		}

		void queue_bind_restore()
		{
			// `exec keys_mp.cfg` is a literal the ENGINE itself issues (@0xB33C48),
			// so this is its own restore path, not one we invented. The broadcaster
			// layer unbinds on PC when it builds, and that build happens after the
			// flag flips, so re-issue twice on a short delay rather than once.
			const std::uint64_t now = GetTickCount64();
			g_restore_binds_at[0] = now + 1500;
			g_restore_binds_at[1] = now + 4000;
		}

		void tick_bind_restore()
		{
			const std::uint64_t now = GetTickCount64();
			for (auto& at : g_restore_binds_at)
			{
				if (at != 0 && now >= at)
				{
					at = 0;
					GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "exec keys_mp.cfg\n");
				}
			}
		}

		// ---- the preset ------------------------------------------------------
		// Names are the SettingName values from ui/utility/mp/broadcaster_utils.lua,
		// which are also the DDL field names (broadcaster_hasbeenread is set the
		// same way natively by sub_46B760).
		const std::vector<setting_t> g_settings = {
			// keep
			{ "broadcaster_killfeed",                  1, "obituaries / killfeed  (KEPT)" },
			// the HUD furniture
			{ "broadcaster_teamscore",                 0, "score panel + blue/red chrome" },
			{ "broadcaster_inventory",                 0, "ammo / weapon info" },
			{ "broadcaster_minimap",                   0, "minimap" },
			{ "broadcaster_scorestreaks",              0, "scorestreak list" },
			{ "broadcaster_scorestreaks_notification", 0, "scorestreak splashes" },
			{ "broadcaster_playernotifications",       0, "splash medals" },
			{ "broadcaster_objective_status",          0, "SD / hardpoint / CTF / alive count" },
			{ "broadcaster_calloutcards",              0, "victim callout cards" },
			{ "broadcaster_voipdock",                  0, "voice chat dock" },
			{ "broadcaster_announcement",              0, "announcement feed" },
			{ "broadcaster_toolbar",                   0, "caster toolbar" },
			{ "broadcaster_team_identity",             0, "custom team identity" },
			// caster-only panels and cameras — off so broadcaster mode does not
			// bring its own UI or move the camera.
			{ "broadcaster_qs_playerhud",              0, "caster player HUD" },
			{ "broadcaster_qs_playerlist",             0, "caster player list" },
			{ "broadcaster_qs_skycam_playerlist",      0, "caster skycam player list" },
			{ "broadcaster_qs_scorepanel",             0, "caster score panel" },
			{ "broadcaster_qs_playercard",             0, "caster player card" },
			{ "broadcaster_qs_playernumbers",          0, "player numbers" },
			{ "broadcaster_qs_thirdperson",            0, "caster third person" },
			{ "broadcaster_qs_ballcam",                0, "caster ball cam" },
			{ "broadcaster_qs_listen_in",              0, "listen-in" },
			{ "broadcaster_qs_xray",                   0, "xray" },
			{ "broadcaster_xray_firstperson",          0, "xray, first person" },
			{ "broadcaster_xray_skycam",               0, "xray, skycam" },
			{ "broadcaster_lo_full",                   0, "loadout panel" },
		};

		[[nodiscard]] std::string status_line()
		{
			const int client = 0;
			const auto* gate = ddl_gate(client);
			const auto flag = broadcaster_flag();
			return std::format(
				"mode {} | settings blob {} | cg slot {} | engine gate {} | local flag {}",
				g_enabled.load(std::memory_order_relaxed) ? "ON" : "off",
				gate ? (*gate ? "loaded" : "NOT LOADED") : "unreadable",
				flag.slot,
				flag.flag ? (flag.gate_open ? "open" : "CLOSED") : "?",
				flag.flag ? (*flag.flag ? "1" : "0") : "?");
		}
	}

	// =====================================================================
	//  public
	// =====================================================================

	bool enabled()
	{
		return g_enabled.load(std::memory_order_relaxed);
	}

	const std::vector<setting_t>& settings()
	{
		return g_settings;
	}

	bool set_setting(const char* name, const int value)
	{
		void* buf = ddl_buffer(0);
		const auto* gate = ddl_gate(0);
		if (!buf || !gate || !*gate)
		{
			return false;
		}
		alignas(16) unsigned char cursor[32]{};
		if (!cursor_for(name, cursor))
		{
			return false;
		}
		const auto set = reinterpret_cast<DDL_SetInt_t>(0xA1C4D0_b);
		return set(cursor, buf, value) != 0;
	}

	bool get_setting(const char* name, int& out)
	{
		void* buf = ddl_buffer(0);
		const auto* gate = ddl_gate(0);
		if (!buf || !gate || !*gate)
		{
			return false;
		}
		alignas(16) unsigned char cursor[32]{};
		if (!cursor_for(name, cursor))
		{
			return false;
		}
		const auto get = reinterpret_cast<DDL_GetInt_t>(0xA1B860_b);
		out = get(cursor, buf);
		return true;
	}

	void set_enabled(const bool on)
	{
		if (on == g_enabled.load(std::memory_order_relaxed))
		{
			Console::printf("[hud] minimal HUD already %s. %s",
				on ? "on" : "off", status_line().c_str());
			return;
		}

		const auto* gate = ddl_gate(0);
		if (!gate || !*gate)
		{
			// RULE A15 — say why, do not fail silently.
			Console::printf("[hud] cannot %s: the broadcaster settings blob is not "
				"loaded (byte_8BE0A20 = %s). Nothing was written.",
				on ? "enable" : "disable",
				gate ? "0" : "unreadable");
			return;
		}

		if (on)
		{
			// Snapshot first, so disabling restores rather than guessing.
			if (!g_saved_valid)
			{
				g_saved.assign(g_settings.size(), -1);
				for (std::size_t i = 0; i < g_settings.size(); ++i)
				{
					int v = 0;
					if (get_setting(g_settings[i].name, v))
					{
						g_saved[i] = v;
					}
				}
				g_saved_valid = true;
			}

			int applied = 0;
			int failed = 0;
			for (const auto& s : g_settings)
			{
				if (set_setting(s.name, s.minimal))
				{
					++applied;
				}
				else
				{
					++failed;
					Console::printf("[hud]   setting \"%s\" not found in the DDL "
						"(skipped)", s.name);
				}
			}
			g_enabled.store(true, std::memory_order_relaxed);
			g_warned_no_gate = false;
			g_warned_no_cg = false;
			g_logged_theater_gate.store(false, std::memory_order_relaxed);
			queue_bind_restore();
			GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "updategamerprofile\n");

			Console::printf("[hud] BROADCASTER (caster) HUD ON — %d setting(s) applied%s.",
				applied, failed ? std::format(", {} skipped", failed).c_str() : "");
			// MEASURED IN GAME, so say it rather than promise the opposite: this
			// is the caster HUD. It removes the minimap AND the score popup, and
			// draws the killfeed as a white box because the broadcaster materials
			// are not loaded for a normal client.
			Console::printf("[hud]   NOTE: this is the tournament CASTER HUD, not a "
				"filtered player HUD. No score popup, killfeed may draw as a white "
				"box. `hud_broadcaster_off` undoes it.");
			Console::printf("[hud]   keys are re-bound automatically (exec keys_mp.cfg); "
				"`hud_binds` repeats it.");
			Console::printf("[hud]   %s", status_line().c_str());
			return;
		}

		// off — restore the saved values, then drop the local flag.
		int restored = 0;
		if (g_saved_valid)
		{
			for (std::size_t i = 0; i < g_settings.size(); ++i)
			{
				if (g_saved[i] >= 0 && set_setting(g_settings[i].name, g_saved[i]))
				{
					++restored;
				}
			}
		}
		g_enabled.store(false, std::memory_order_relaxed);
		if (const auto flag = broadcaster_flag(); flag.flag)
		{
			*flag.flag = 0;
		}
		queue_bind_restore();
		GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "updategamerprofile\n");
		Console::printf("[hud] minimal HUD OFF — %d setting(s) restored. %s",
			restored, status_line().c_str());
	}

	// The theater gate. See the header for why this exists and why it is scoped
	// to one call site. Cost when the mode is off: one relaxed atomic load.
	bool hide_demo_from_isbroadcaster(const void* return_address)
	{
		if (!g_enabled.load(std::memory_order_relaxed) || !return_address)
		{
			return false;
		}
		// RULE A1, written out: game.cpp defines base = GetModuleHandle(NULL)
		// + 0x1000 and _b(v) = base + v with every literal being (IDA - 0x1000),
		// so VA = module_base + IDA and therefore IDA = VA - module_base, with
		// NO 0x1000 adjustment. Getting this wrong lands in the next function.
		const auto base = reinterpret_cast<std::uint64_t>(GetModuleHandleA(nullptr));
		const auto addr = reinterpret_cast<std::uint64_t>(return_address);
		if (!base || addr < base)
		{
			return false;
		}
		const std::uint64_t ida = addr - base;

		// sub_33E550 (IsBroadcaster): start 0x33E550, size 0x19EC,
		// so the range is [0x33E550, 0x33E550 + 0x19EC) = [0x33E550, 0x33FF3C).
		constexpr std::uint64_t IS_BROADCASTER_LO = 0x33E550;
		constexpr std::uint64_t IS_BROADCASTER_HI = 0x33FF3C;
		if (ida < IS_BROADCASTER_LO || ida >= IS_BROADCASTER_HI)
		{
			return false;
		}

		if (!g_logged_theater_gate)
		{
			g_logged_theater_gate = true;
			Console::printf("[hud] theater gate opened: IsBroadcaster no longer "
				"early-returns during demo playback (this one call site only).");
		}
		return true;
	}

	// Once per frame, client thread, cg known valid (the caller is mid-publish).
	void on_frame()
	{
		tick_bind_restore();

		if (!g_enabled.load(std::memory_order_relaxed))
		{
			return;
		}

		const auto flag = broadcaster_flag();
		if (!flag.flag)
		{
			if (!g_warned_no_cg)
			{
				g_warned_no_cg = true;
				Console::printf("[hud] minimal HUD: cg clientinfo not readable yet — "
					"waiting. This resolves once you are in a match.");
			}
			return;
		}
		g_warned_no_cg = false;

		if (!flag.gate_open)
		{
			if (!g_warned_no_gate)
			{
				g_warned_no_gate = true;
				Console::printf("[hud] minimal HUD: cg+%zu (slot %d) is 0, so "
					"IsBroadcaster stays false no matter what we write. The HUD "
					"will not change until that opens.",
					CG_BC_GATE_BASE + CG_BC_GATE_STRIDE * static_cast<std::size_t>(flag.slot),
					flag.slot);
			}
			return;
		}
		g_warned_no_gate = false;

		// The latch. Clientinfo replication would otherwise clear this.
		if (*flag.flag != 1)
		{
			*flag.flag = 1;
		}
	}

	void init()
	{
		// NOT named hud_on / hud_minimal. MEASURED IN GAME: this does not hide
		// bits of the player HUD, it switches the game into the CASTER HUD --
		// minimap gone, killfeed replaced by a white box (its broadcaster
		// materials are not loaded for a normal client), no score popup. It is
		// a different HUD, not a filtered one. Kept only as an explicitly
		// labelled experiment so the name cannot mislead anyone again.
		dev_mode::add_command("hud_broadcaster", []
		{
			const auto* args = GameUtil::getCmdArgs();
			const int argc = args ? args->argc[args->nesting] : 0;
			if (argc < 2)
			{
				Console::printf("[hud] usage: hud_broadcaster 1 | hud_broadcaster 0");
				Console::printf("[hud] WARNING: this is the CoD tournament caster HUD, "
					"not a filtered player HUD. It removes the score popup and draws "
					"the killfeed as a white box (missing caster materials).");
				Console::printf("[hud] %s", status_line().c_str());
				return;
			}
			set_enabled(GameUtil::safeStringToInt(args->argv[args->nesting][1]) != 0);
		});

		dev_mode::add_command("hud_broadcaster_off", [] { set_enabled(false); });

		dev_mode::add_command("hud_binds", []
		{
			GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "exec keys_mp.cfg\n");
			Console::printf("[hud] re-issued `exec keys_mp.cfg` (the engine's own "
				"bind restore).");
		});

		dev_mode::add_command("hud_settings", []
		{
			Console::printf("[hud] %s", status_line().c_str());
			Console::printf("[hud] name                                  now  minimal  what");
			for (const auto& s : g_settings)
			{
				int v = -1;
				const bool ok = get_setting(s.name, v);
				Console::printf("[hud]   %-38s %3s  %5d    %s",
					s.name, ok ? std::to_string(v).c_str() : "?", s.minimal, s.what);
			}
			Console::printf("[hud] `hud_set <name> <0|1>` changes one.");
		});

		dev_mode::add_command("hud_set", []
		{
			const auto* args = GameUtil::getCmdArgs();
			const int argc = args ? args->argc[args->nesting] : 0;
			if (argc < 3)
			{
				Console::printf("[hud] usage: hud_set <broadcaster_xxx> <0|1>  "
					"(hud_settings lists them)");
				return;
			}
			const char* name = args->argv[args->nesting][1];
			const int value = GameUtil::safeStringToInt(args->argv[args->nesting][2]);
			if (set_setting(name, value))
			{
				int back = -1;
				get_setting(name, back);
				Console::printf("[hud] %s = %d (read back %d)", name, value, back);
				GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "updategamerprofile\n");
			}
			else
			{
				Console::printf("[hud] \"%s\" is not a field in "
					"mp/ddl/broadcastersettings.ddl, or the blob is not loaded. "
					"Nothing written.", name ? name : "?");
			}
		});

		Console::printf("[hud] broadcaster (caster HUD) available but OFF -- it is a "
			"DIFFERENT HUD, not a filtered one. Use demo_hud_only for a clean HUD.");
	}
}
