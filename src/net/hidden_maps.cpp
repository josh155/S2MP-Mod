#include "pch.h"
#include "hidden_maps.hpp"

#include "Console.hpp"
#include "DevMode.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"

#include <atomic>
#include <cstdint>
#include <cstring>

namespace hidden_maps
{
	namespace
	{
		// ---- addresses (RULE A1: the arithmetic is written out) -----------
		//
		//   GameInfo_UpdateArenas   IDA 0x650A70 - 0x1000 = 0x64FA70
		//   dword_AB0F8B0 (count)   IDA 0xAB0F8B0 - 0x1000 = 0xAB0E8B0
		//   unk_AB0F8B4 (records)   IDA 0xAB0F8B4 - 0x1000 = 0xAB0E8B4
		constexpr std::uintptr_t ADDR_UPDATE_ARENAS = 0x64FA70;
		constexpr std::uintptr_t ADDR_ARENA_COUNT   = 0xAB0E8B0;
		constexpr std::uintptr_t ADDR_ARENA_TABLE   = 0xAB0E8B4;

		constexpr std::size_t RECORD_STRIDE = 4660;
		// GameInfo_UpdateArenas itself refuses past this; we match it so an
		// append can never write somewhere the engine's own writer would not.
		constexpr int RECORD_CAP = 128;

		// Field offsets within one record, all proven from GameInfo_UpdateArenas's
		// own decompile (see hidden_maps.hpp for the walkthrough).
		constexpr std::size_t OFF_LONGNAME = 0;      // display name, 32 bytes
		constexpr std::size_t OFF_LOADNAME = 32;     // "map" -- the mp_xxx name, 32 bytes
		constexpr std::size_t OFF_DESC     = 64;     // 32 bytes
		constexpr std::size_t OFF_IMAGE    = 96;     // 32 bytes -- blank is safe, see below
		constexpr std::size_t OFF_KEYCOUNT = 2688;   // int, backslash-metadata bookkeeping
		constexpr std::size_t OFF_MAPPACK  = 2724;   // int -- MUST be exactly 0, see hpp
		constexpr std::size_t OFF_GAMETYPE = 2732;   // int bitmask -- -1 == every gametype

		const char* const HIDDEN_LOAD_NAME = "mp_house";
		const char* const HIDDEN_LONG_NAME = "Groesten House";
		const char* const HIDDEN_DESC      = "A hidden base-game MP map.";

		std::atomic<bool> g_enabled{true};
		std::atomic<int>  g_added_index{-1};   // -1 until we have actually appended one

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
			return reinterpret_cast<std::uintptr_t>(p) + n <= start + mbi.RegionSize;
		}

		// I_strncpyz's own semantics: at most 31 characters, always NUL-terminated
		// within the 32-byte field. A field this project cannot widen -- it must
		// fit, same as every real map's row does.
		void write_field(std::uint8_t* record, const std::size_t off, const char* text)
		{
			const auto len = std::strlen(text);
			const auto copy = (std::min)(len, static_cast<std::size_t>(31));
			std::memcpy(record + off, text, copy);
			record[off + copy] = 0;
		}

		[[nodiscard]] std::uint8_t* record_at(std::uint8_t* table, const int index)
		{
			return table + static_cast<std::size_t>(index) * RECORD_STRIDE;
		}

		[[nodiscard]] bool find_load_name(std::uint8_t* table, const int count, const char* load_name)
		{
			for (int i = 0; i < count; ++i)
			{
				auto* record = record_at(table, i);
				if (!readable(record, OFF_LOADNAME + 32))
				{
					// The table runs clean and contiguous up to `count`; hitting
					// unreadable memory before that means the count itself is
					// stale. Stop rather than guess further.
					break;
				}
				if (std::strcmp(reinterpret_cast<const char*>(record + OFF_LOADNAME), load_name) == 0)
				{
					return true;
				}
			}
			return false;
		}

		// One extra "arena", built the same way a real mp/mapLoad.csv row would
		// be -- every field GameInfo_UpdateArenas itself writes, at the same
		// offsets, with the values a blank CSV column would leave EXCEPT
		// mappack, which must be the engine's own "no DLC pack" value (0), not
		// the CSV parser's "column was blank" sentinel (-1) -- see hidden_maps.hpp.
		void write_hidden_entry(std::uint8_t* record)
		{
			std::memset(record, 0, RECORD_STRIDE);
			write_field(record, OFF_LONGNAME, HIDDEN_LONG_NAME);
			write_field(record, OFF_LOADNAME, HIDDEN_LOAD_NAME);
			write_field(record, OFF_DESC, HIDDEN_DESC);
			// OFF_IMAGE left blank: GetMapImageByIndex's native worker returns an
			// empty string for an unregistered/missing image name, not a crash
			// (checked from its own body before shipping this).
			*reinterpret_cast<std::int32_t*>(record + OFF_KEYCOUNT) = 0;
			*reinterpret_cast<std::int32_t*>(record + OFF_MAPPACK) = 0;
			*reinterpret_cast<std::int32_t*>(record + OFF_GAMETYPE) = -1;
		}

		using UpdateArenas_t = std::int64_t(__fastcall*)();
		UpdateArenas_t UpdateArenas_orig = nullptr;
		std::atomic<bool> g_installed{false};

		std::int64_t __fastcall update_arenas_stub()
		{
			// RULE A3: the very first thing, so "the hook never ran" is never
			// confused with "it ran and chose not to add anything".
			const auto result = UpdateArenas_orig();

			if (!g_enabled.load(std::memory_order_relaxed))
			{
				return result;
			}

			auto* cnt = reinterpret_cast<std::int32_t*>(_b(ADDR_ARENA_COUNT));
			auto* table = reinterpret_cast<std::uint8_t*>(_b(ADDR_ARENA_TABLE));
			if (!readable(cnt, sizeof(std::int32_t)) || !readable(table, RECORD_STRIDE))
			{
				return result;
			}

			const int count = *cnt;
			if (count < 0 || count >= RECORD_CAP)
			{
				// Either garbage (don't touch it) or genuinely full -- 128 real
				// maps would be a very different game than the ~50 this table
				// holds today, so this is a defensive cap, not an expected path.
				return result;
			}
			if (find_load_name(table, count, HIDDEN_LOAD_NAME))
			{
				// Already there -- either we added it on an earlier call and the
				// dirty flag has not fired since, or a future patch adds it for
				// real. Either way, nothing to do.
				g_added_index.store(-2, std::memory_order_relaxed);   // "present, not by us this call"
				return result;
			}

			auto* record = record_at(table, count);
			if (!readable(record, RECORD_STRIDE))
			{
				return result;
			}
			write_hidden_entry(record);
			*cnt = count + 1;
			g_added_index.store(count, std::memory_order_relaxed);

			Console::printf("[maps] added %s (\"%s\") to the private-match map list "
				"-- %d entries now", HIDDEN_LOAD_NAME, HIDDEN_LONG_NAME, *cnt);
			return result;
		}

		void cmd_maps_hidden()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (args && args->argc[args->nesting] >= 2)
			{
				g_enabled = GameUtil::safeStringToInt(args->argv[args->nesting][1]) != 0;
				Console::printf("[maps] hidden-map injection %s. It takes effect the "
					"next time the map list rebuilds (open the private-match map "
					"screen again).", g_enabled.load() ? "ON" : "OFF");
				return;
			}

			const auto* cnt = reinterpret_cast<const std::int32_t*>(_b(ADDR_ARENA_COUNT));
			const int count = readable(cnt, sizeof(std::int32_t)) ? *cnt : -1;
			Console::printf("[maps] hook: %s (orig=%p), enabled=%s, arena count=%d, "
				"mp_house index=%d (-1 = never appeared, -2 = present but not from us)",
				g_installed.load() ? "OK" : "FAILED",
				reinterpret_cast<void*>(UpdateArenas_orig),
				g_enabled.load() ? "yes" : "no", count, g_added_index.load());
		}
	}

	void init()
	{
		g_installed = Hook::create("GameInfo_UpdateArenas", _b(ADDR_UPDATE_ARENAS),
			&update_arenas_stub, &UpdateArenas_orig) && UpdateArenas_orig != nullptr;

		Console::printf("[maps] native map-list hook: %s (orig=%p) -- Groesten House "
			"should now appear in the game's own private-match map picker",
			g_installed.load() ? "OK" : "FAILED",
			reinterpret_cast<void*>(UpdateArenas_orig));

		dev_mode::add_command("maps_hidden", cmd_maps_hidden);
	}
}
