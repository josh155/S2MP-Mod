#pragma once

// =============================================================================
//  ModPaths -- where the mod is allowed to keep its own files, per build
// =============================================================================
//
//  THE PROBLEM, measured 2026-08-15. Every file the mod owns currently lives
//  beside the game executable:
//
//      <exe dir>\S2MP-Mod\botnames.txt, botkits.txt, botemblems.txt, ...
//      <exe dir>\s2mp_nojoingate.txt and the other marker files
//      main\s2mp_console.log                        (relative to the CWD)
//
//  On Steam that is fine. On the Microsoft Store build it is not: the game lives
//  in C:\Program Files\WindowsApps\..., which is ACL'd to TrustedInstaller. The
//  path is enumerable but the files are not even READABLE by the user, let alone
//  writable -- verified on this machine:
//
//      Test-Path         True
//      [IO.File]::Open   ACCESS DENIED
//
//  So on Store the mod's data has to live somewhere else. The natural home is the
//  package's own writable state folder, which is exactly what it is for:
//
//      %LOCALAPPDATA%\Packages\<PackageFamilyName>\LocalState\S2MP-Mod
//
//  ⚠ STEAM BEHAVIOUR IS DELIBERATELY UNCHANGED. mod_dir() returns the same
//  <exe dir>\S2MP-Mod it always did, so the 128 bot names and 115 uniforms
//  already on disk keep working with no migration. The branch only fires on a
//  build we have never run.
// =============================================================================

#include <string>

#include "BuildMap.hpp"

namespace mod_paths
{
	namespace detail
	{
		// The Store package this mod targets. From the installed manifest:
		//   Name  38985CA0.CallofDutyWWIIPCMS   version 2.0.18.0
		//   AUMID 38985CA0.CallofDutyWWIIPCMS_5bkah9njm3e9g!GameMP
		inline constexpr char PACKAGE_FAMILY[] = "38985CA0.CallofDutyWWIIPCMS_5bkah9njm3e9g";

		inline std::string exe_dir()
		{
			char exe[MAX_PATH]{};
			if (GetModuleFileNameA(nullptr, exe, MAX_PATH) == 0)
			{
				return ".";
			}
			std::string dir(exe);
			const auto slash = dir.find_last_of("\\/");
			return (slash == std::string::npos) ? std::string(".") : dir.substr(0, slash);
		}

		inline std::string local_state()
		{
			char buf[MAX_PATH]{};
			DWORD n = GetEnvironmentVariableA("LOCALAPPDATA", buf, MAX_PATH);
			if (n == 0 || n >= MAX_PATH)
			{
				return exe_dir();          // no worse than today
			}
			std::string p(buf, n);
			p += "\\Packages\\";
			p += PACKAGE_FAMILY;
			p += "\\LocalState";
			return p;
		}

		// mkdir -p, because LocalState\S2MP-Mod may be two levels deep.
		inline void ensure(const std::string& path)
		{
			for (std::size_t i = 3; i <= path.size(); ++i)
			{
				if (i == path.size() || path[i] == '\\' || path[i] == '/')
				{
					CreateDirectoryA(path.substr(0, i).c_str(), nullptr);
				}
			}
		}
	}

	// Where the mod keeps ITS OWN data (bot names, uniforms, emblems, kits).
	// Created if missing. Steam: <exe dir>\S2MP-Mod, exactly as before.
	[[nodiscard]] inline std::string mod_dir()
	{
		const std::string dir =
			(build_map::current() == build_map::Build::Store)
			? detail::local_state() + "\\S2MP-Mod"
			: detail::exe_dir() + "\\S2MP-Mod";
		detail::ensure(dir);
		return dir;
	}

	// Where a marker/flag file lives (s2mp_nojoingate.txt and friends). These sit
	// beside the exe on Steam; on Store that directory cannot be written, so they
	// move next to the rest of the mod's data.
	[[nodiscard]] inline std::string marker_dir()
	{
		return (build_map::current() == build_map::Build::Store)
			? mod_dir()
			: detail::exe_dir();
	}

	[[nodiscard]] inline bool marker_present(const char* name)
	{
		const std::string a = marker_dir() + "\\" + name;
		if (GetFileAttributesA(a.c_str()) != INVALID_FILE_ATTRIBUTES)
		{
			return true;
		}
		// Also honour a bare relative name, which is how these were checked
		// before and how someone dropping one in the CWD would expect it to work.
		return GetFileAttributesA(name) != INVALID_FILE_ATTRIBUTES;
	}
}
