#include "pch.h"
#include "demo/demo_display.hpp"

#include "Console.hpp"
#include "GameUtil.hpp"
#include "ModPaths.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <string>

namespace demo_display
{
	namespace
	{
		// ---- addresses (RULE A1: the arithmetic is written out) ---------
		//
		//   com_maxfps dvar ptr    IDA 0x14DB7B0 - 0x1000 = 0x14DA7B0
		//
		// off_14DB7B0 is a POINTER to the dvar (Com_InitDvars assigns the
		// registrar's return value straight into it), same shape as
		// demo_camera's cg_fov pointer. The value sits at dvar+16.
		//
		// RULE A14: the _b literal is resolved inside a function, never at
		// namespace scope.
		constexpr std::uintptr_t MAXFPS_DVAR_LITERAL = 0x14DA7B0;

		[[nodiscard]] std::uintptr_t maxfps_dvar_ptr_addr()
		{
			return _b(MAXFPS_DVAR_LITERAL);
		}

		// Duplicated rather than shared -- see demo_camera.cpp's note on why.
		bool readable(const void* p, const std::size_t n)
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
			const auto end = start + mbi.RegionSize;
			const auto want = reinterpret_cast<std::uintptr_t>(p);
			return want >= start && want + n <= end;
		}

		// Resolves the dvar_t* the pointer variable holds, or nullptr.
		[[nodiscard]] std::uintptr_t resolve_dvar()
		{
			auto* slot = reinterpret_cast<std::uintptr_t*>(maxfps_dvar_ptr_addr());
			if (!readable(slot, sizeof(std::uintptr_t)))
			{
				return 0;
			}
			const auto dvar = *slot;
			if (!readable(reinterpret_cast<void*>(dvar), 20))
			{
				return 0;
			}
			return dvar;
		}

		// Bypasses the dvar's own (Arxan-obfuscated) getter entirely and
		// reads the plain storage, same as demo_camera::fov().
		bool write_raw(const int fps)
		{
			const auto dvar = resolve_dvar();
			if (!dvar)
			{
				return false;
			}
			*reinterpret_cast<std::int32_t*>(dvar + 16) = fps;
			return true;
		}

		int g_target = -1;
		bool g_holding = false;
		// Guards the ONE-TIME "apply whatever was saved last session" step
		// in tick() -- set the first time com_maxfps becomes resolvable,
		// whether or not a saved preference actually existed, so it is
		// never retried once answered.
		bool g_tried_persisted = false;

		[[nodiscard]] std::string prefs_path()
		{
			return mod_paths::mod_dir() + "/fps_cap.txt";
		}

		void save_target(const int fps)
		{
			if (FILE* f = nullptr; fopen_s(&f, prefs_path().c_str(), "wb") == 0 && f)
			{
				std::fprintf(f, "%d\n", fps);
				std::fclose(f);
			}
		}

		// -1 when there is no saved preference (or it is unreadable/nonsense).
		[[nodiscard]] int load_target()
		{
			FILE* f = nullptr;
			if (fopen_s(&f, prefs_path().c_str(), "rb") != 0 || !f)
			{
				return -1;
			}
			int v = -1;
			const bool ok = std::fscanf(f, "%d", &v) == 1;
			std::fclose(f);
			return (ok && v >= 0 && v <= 1000) ? v : -1;
		}

		void cmd_fps()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] < 2)
			{
				const int v = fps_cap();
				if (v < 0)
				{
					Console::printf("fps cap: unavailable (com_maxfps not registered yet)");
				}
				else
				{
					Console::printf("fps cap: %d   (demo_fps <0..1000>; 0 = uncapped, "
						"250 is the engine's own ceiling -- higher writes the raw dvar. "
						"Whatever you set here is remembered and re-applied on every "
						"future launch, in live play as well as demos.)", v);
				}
				return;
			}
			set_fps_cap(std::atoi(args->argv[args->nesting][1]));
		}
	}

	// =====================================================================

	int fps_cap()
	{
		const auto dvar = resolve_dvar();
		if (!dvar)
		{
			return -1;
		}
		const int v = *reinterpret_cast<std::int32_t*>(dvar + 16);
		// An unregistered dvar reads as junk -- sanity check rather than
		// handing the GUI a slider position of a billion.
		return (v >= 0 && v <= 100000) ? v : -1;
	}

	bool fps_cap_available()
	{
		return fps_cap() >= 0;
	}

	void set_fps_cap(int fps)
	{
		fps = std::clamp(fps, 0, 1000);
		g_target = fps;
		// Hold at ANY value now, not just above 250: `com_maxfps` is an
		// archived dvar, and the engine re-applies the archived value
		// through its own domain-clamped setter on every boot, which is
		// the "reverts on its own" behaviour this whole persistence layer
		// exists to fix. Re-asserting below 250 too closes that gap
		// instead of only closing it for the unlocked range.
		g_holding = true;

		if (fps <= 250)
		{
			// Inside the engine's own domain -- through the console, so its
			// setter runs on the client thread and any change callback fires.
			// Exactly demo_camera::set_fov()'s reasoning.
			GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, std::format("com_maxfps {}", fps));
		}
		else
		{
			// Past the registered ceiling the console setter clamps to 250,
			// so the raw slot is the only way past it.
			write_raw(fps);
		}

		// This is now the standing preference -- every future launch should
		// come up already at this value, not just this session.
		save_target(fps);
	}

	void tick()
	{
		if (!g_holding)
		{
			// Nothing chosen yet THIS session. The moment the dvar becomes
			// resolvable (never true at init() -- Com_InitDvars has not run
			// yet), try once to pick up whatever was set last time, so the
			// cap is applied with no GUI interaction and no console command
			// required. If there is nothing saved, this simply never fires
			// again for the rest of the process.
			if (!g_tried_persisted && fps_cap_available())
			{
				g_tried_persisted = true;
				const int saved = load_target();
				if (saved >= 0)
				{
					set_fps_cap(saved);   // re-enters; sets g_holding and g_target
				}
			}
			return;
		}
		// Compare-then-write: com_maxfps is archived, so a config reload,
		// map change, or anything else touching it through the normal
		// setter can clamp it back into the registered 0..250 domain. This
		// costs one int compare per frame and closes that gap unconditionally.
		if (fps_cap() != g_target)
		{
			write_raw(g_target);
		}
	}

	void init()
	{
		GameUtil::addCommand("demo_fps", cmd_fps);
	}
}
