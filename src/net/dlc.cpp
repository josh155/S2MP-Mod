#include "pch.h"
#include "dlc.hpp"

#include "Console.hpp"
#include "DevMode.hpp"
#include "GameUtil.hpp"

#include <algorithm>

namespace dlc
{
	namespace
	{
		//   g_contentEntitlementCount IDA 0x0D4EE438 - 0x1000 = 0x0D4ED438
		//   g_contentEntitlementLock  IDA 0x0D4EE43C - 0x1000 = 0x0D4ED43C
		//   g_contentEntitlements     IDA 0x0D4EEC40 - 0x1000 = 0x0D4EDC40
		constexpr std::size_t ADDR_COUNT  = 0xD4ED438;
		constexpr std::size_t ADDR_LOCK   = 0xD4ED43C;
		constexpr std::size_t ADDR_TABLE  = 0xD4EDC40;
		constexpr std::size_t STRIDE      = 140;   // name[128], i32 index, i16 enabled, ...

		int  g_original = -1;      // captured before we ever write
		bool g_forced_off = false;

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

		// The engine spins on this lock with InterlockedCompareExchange before
		// touching the table, so we do the same rather than racing a
		// registration that is in progress on another thread.
		bool lock_acquire()
		{
			auto* lock = reinterpret_cast<volatile long*>(_b(ADDR_LOCK));
			if (!readable(const_cast<long*>(lock), sizeof(long)))
			{
				return false;
			}
			for (int spin = 0; spin < 2000; ++spin)
			{
				if (InterlockedCompareExchange(lock, 1, 0) == 0)
				{
					return true;
				}
				Sleep(0);
			}
			return false;   // busy -- better to do nothing than to race
		}

		void lock_release()
		{
			auto* lock = reinterpret_cast<volatile long*>(_b(ADDR_LOCK));
			if (readable(const_cast<long*>(lock), sizeof(long)))
			{
				InterlockedExchange(lock, 0);
			}
		}

		void cmd_dlc()
		{
			const auto* args = GameUtil::getCmdArgs();
			const auto* cnt = reinterpret_cast<const int*>(_b(ADDR_COUNT));
			if (!readable(cnt, sizeof(int)))
			{
				Console::printf("[dlc] entitlement count not resolvable");
				return;
			}
			if (!args || args->argc[args->nesting] < 2)
			{
				Console::printf("[dlc] DLC is %s (count=%d, original=%d). usage: dlc <0|1>",
					*cnt ? "ON" : "OFF", *cnt, g_original);
				return;
			}
			set_enabled(GameUtil::safeStringToInt(args->argv[args->nesting][1]) != 0);
		}

		void cmd_list()
		{
			const auto e = entries();
			Console::printf("[dlc] %zu entitlement(s) (count=%d, original=%d, %s)",
				e.size(), entry_count(), g_original, enabled() ? "ON" : "OFF");
			for (const auto& s : e)
			{
				Console::printf("[dlc]   %s", s.c_str());
			}
		}
	}

	void init()
	{
		// Capture before anything can zero it. Registration may not have run
		// yet, so tick() keeps this fresh until we first write.
		if (const int n = entry_count(); n > 0)
		{
			g_original = n;
		}
		dev_mode::add_command("dlc", cmd_dlc);
		dev_mode::add_command("dlc_list", cmd_list);
		Console::printf("[dlc] DLC toggle ready — `dlc 0` searches the BASE playlists "
			"(DLC pools are often empty), `dlc 1` restores. No hooks.");
	}

	int entry_count()
	{
		const auto* cnt = reinterpret_cast<const int*>(_b(ADDR_COUNT));
		return readable(cnt, sizeof(int)) ? *cnt : 0;
	}

	bool enabled() { return entry_count() > 0; }
	int  original_count() { return g_original; }

	bool available()
	{
		const auto* cnt = reinterpret_cast<const int*>(_b(ADDR_COUNT));
		return readable(cnt, sizeof(int)) && g_original >= 0;
	}

	void set_enabled(const bool on)
	{
		auto* cnt = reinterpret_cast<int*>(_b(ADDR_COUNT));
		if (!readable(cnt, sizeof(int)))
		{
			Console::printf("[dlc] entitlement count not resolvable");
			return;
		}
		if (!lock_acquire())
		{
			Console::printf("[dlc] skipped: the entitlement lock is busy (a "
				"registration is in flight). Try again in a moment.");
			return;
		}
		if (on)
		{
			// Restore what the GAME registered. The table rows were never
			// touched, so this restores exactly those entitlements -- we never
			// invent entries.
			if (g_original > 0)
			{
				*cnt = g_original;
			}
			g_forced_off = false;
		}
		else
		{
			if (*cnt > 0)
			{
				g_original = *cnt;      // keep the newest real value
			}
			*cnt = 0;
			g_forced_off = true;
		}
		const int now = *cnt;
		lock_release();

		Console::printf("[dlc] DLC %s (count now %d) — %s",
			on ? "ENABLED" : "DISABLED", now,
			on ? "DLC playlists are eligible again"
			   : "matchmaking should now search the base playlists");
	}

	std::vector<std::string> entries()
	{
		std::vector<std::string> out;
		// Show the table even while forced off, so you can see what would come
		// back -- the rows survive, only the count is zeroed.
		const int show = (std::max)(entry_count(), g_original);
		if (show <= 0 || show > 64)
		{
			return out;
		}
		const auto base = _b(ADDR_TABLE);
		for (int i = 0; i < show; ++i)
		{
			const auto* e = reinterpret_cast<const char*>(
				base + static_cast<std::size_t>(i) * STRIDE);
			if (!readable(e, STRIDE))
			{
				break;
			}
			std::string name;
			for (int k = 0; k < 128 && e[k]; ++k)
			{
				const auto c = static_cast<unsigned char>(e[k]);
				if (c >= 0x20 && c < 0x7F)
				{
					name.push_back(e[k]);
				}
			}
			if (!name.empty())
			{
				out.push_back(std::move(name));
			}
		}
		return out;
	}

	void tick()
	{
		// 4 Hz is plenty and keeps this off the per-frame path.
		static DWORD s_last = 0;
		const DWORD now = GetTickCount();
		if (now - s_last < 250)
		{
			return;
		}
		s_last = now;

		const int n = entry_count();
		if (n > 0)
		{
			if (!g_forced_off)
			{
				g_original = n;          // keep the restore value current
			}
			else if (lock_acquire())
			{
				// Re-assert. The game keeps registering entitlements and each
				// registration bumps the count back up, so a one-shot zero does
				// NOT stay off.
				auto* cnt = reinterpret_cast<int*>(_b(ADDR_COUNT));
				if (readable(cnt, sizeof(int)) && *cnt > 0)
				{
					g_original = *cnt;
					*cnt = 0;
				}
				lock_release();
			}
		}
	}
}
