#include "pch.h"
#include "demo/demo_player.hpp"

#include "Console.hpp"
#include "GameUtil.hpp"
#include "demo/demo_library.hpp"
#include "demo/demo_native.hpp"
#include "demo/demo_playback.hpp"
#include "demo/demo_recording.hpp"
#include "demo/demo_utils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstring>

namespace demo_player
{
	namespace
	{
		std::vector<Entry> g_list;
		int g_selected = 0;

		Kind kind_of(const std::filesystem::path& p)
		{
			const auto ext = p.extension().string();
			if (_stricmp(ext.c_str(), ".demo") == 0)
			{
				return Kind::Engine;
			}
			// DEMO_EXTENSION is a string_view, so give _stricmp a real pointer.
			if (_stricmp(ext.c_str(), std::string(demo_utils::DEMO_EXTENSION).c_str()) == 0)
			{
				return Kind::Custom;
			}
			return Kind::None;
		}

		void scan(const std::optional<std::filesystem::path>& dir, Kind kind)
		{
			if (!dir)
			{
				return;
			}
			std::error_code ec;
			for (const auto& e : std::filesystem::directory_iterator(*dir, ec))
			{
				if (ec)
				{
					break;
				}
				if (!e.is_regular_file(ec) || kind_of(e.path()) != kind)
				{
					continue;
				}
				Entry entry;
				entry.path = e.path();
				entry.name = e.path().filename().string();
				entry.kind = kind;
				entry.size = e.file_size(ec);
				if (ec)
				{
					ec.clear();
					entry.size = 0;
				}
				// Two seeks: header + footer. Cheap enough for every row, and
				// it is what turns "x0147_6a77b6ea" into a map and a date.
				if (kind == Kind::Engine)
				{
					entry.info = demo_library::describe(entry.path);
				}
				g_list.push_back(std::move(entry));
			}
		}

		// Resolve a bare name typed at the console ("dday", "d_day.0000") to a
		// file in either library. Exact filename first, then stem, so
		// `demo_play dday` finds dday.demo without the user knowing the format.
		const Entry* find(const std::string& want)
		{
			if (g_list.empty())
			{
				refresh();
			}
			for (const auto& e : g_list)
			{
				if (_stricmp(e.name.c_str(), want.c_str()) == 0)
				{
					return &e;
				}
			}
			for (const auto& e : g_list)
			{
				if (_stricmp(e.path.stem().string().c_str(), want.c_str()) == 0)
				{
					return &e;
				}
			}
			return nullptr;
		}

		// ---- console commands ---------------------------------------

		void cmd_play()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] < 2)
			{
				Console::printf("usage: demo_play <name>   (see demo_list)");
				return;
			}
			const std::string want = args->argv[args->nesting][1];

			if (const Entry* e = find(want))
			{
				play(e->path);
				return;
			}
			// Not in either library, so treat it as a path and let the
			// extension pick the engine.
			const std::filesystem::path p(want);
			if (kind_of(p) != Kind::None && std::filesystem::exists(p))
			{
				play(p);
				return;
			}
			Console::printf("[demo] no demo called '%s'. Try demo_list.", want.c_str());
		}

		void cmd_stop() { stop(); }
		void cmd_pause() { toggle_pause(); }

		void cmd_seek()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] < 2)
			{
				Console::printf("usage: demo_seek <seconds>   (negative rewinds)");
				return;
			}
			const double sec = std::atof(args->argv[args->nesting][1]);
			seek_relative(static_cast<std::int32_t>(sec * 1000.0));
		}

		void cmd_speed()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] < 2)
			{
				Console::printf("playback speed: %.2fx   (demo_speed <0.1 .. 4.0>)",
					timescale());
				return;
			}
			set_timescale(static_cast<float>(std::atof(args->argv[args->nesting][1])));
		}

		void cmd_list()
		{
			refresh();
			if (g_list.empty())
			{
				Console::printf("[demo] no demos found.");
				if (const auto d = demo_native::native_demos_directory())
				{
					Console::printf("[demo]   engine demos: %s", d->string().c_str());
				}
				if (const auto d = demo_utils::demos_directory())
				{
					Console::printf("[demo]   custom demos: %s", d->string().c_str());
				}
				return;
			}
			Console::printf("[demo] %zu demo(s):", g_list.size());
			for (const auto& e : g_list)
			{
				Console::printf("  %-40s %s  %.1f MB",
					e.name.c_str(),
					e.kind == Kind::Engine ? "engine" : "custom",
					static_cast<double>(e.size) / (1024.0 * 1024.0));
			}
		}

		void cmd_record()
		{
			const auto* args = GameUtil::getCmdArgs();
			bool on = !auto_record();
			if (args && args->argc[args->nesting] >= 2)
			{
				on = args->argv[args->nesting][1][0] != '0';
			}
			set_auto_record(on);
			Console::printf("[demo] auto-record every match: %s%s",
				on ? "ON" : "off",
				on ? "  (takes effect on the next connect)" : "");
		}

	}

	// =================================================================

	void refresh()
	{
		g_list.clear();
		scan(demo_native::native_demos_directory(), Kind::Engine);
		scan(demo_utils::demos_directory(), Kind::Custom);

		// Newest first: the demo you just recorded is the one you want.
		std::error_code ec;
		std::stable_sort(g_list.begin(), g_list.end(),
			[&](const Entry& a, const Entry& b)
			{
				const auto ta = std::filesystem::last_write_time(a.path, ec);
				const auto tb = std::filesystem::last_write_time(b.path, ec);
				return ta > tb;
			});

		if (g_selected >= static_cast<int>(g_list.size()))
		{
			g_selected = g_list.empty() ? 0 : static_cast<int>(g_list.size()) - 1;
		}
	}

	const std::vector<Entry>& list() { return g_list; }
	int selected() { return g_selected; }

	void set_selected(int index)
	{
		if (index >= 0 && index < static_cast<int>(g_list.size()))
		{
			g_selected = index;
		}
	}

	const Entry* selected_entry()
	{
		if (g_selected < 0 || g_selected >= static_cast<int>(g_list.size()))
		{
			return nullptr;
		}
		return &g_list[static_cast<std::size_t>(g_selected)];
	}

	Kind active()
	{
		if (demo_native::native_playing())
		{
			return Kind::Engine;
		}
		if (demo_playback::is_playing())
		{
			return Kind::Custom;
		}
		return Kind::None;
	}

	bool playing() { return active() != Kind::None; }

	const char* blocked_reason()
	{
		// The engine wraps CL_Demo_Play_f in !com_sv_running, so with a server
		// up it is a SILENT no-op. Say so rather than letting the button look
		// dead.
		const Entry* e = selected_entry();
		if (e && e->kind == Kind::Engine && demo_native::server_running())
		{
			return "Leave the match first - engine demos will not start while a "
				"server is running.";
		}
		return nullptr;
	}

	bool play(const std::filesystem::path& path)
	{
		stop();

		switch (kind_of(path))
		{
		case Kind::Engine:
			if (demo_native::server_running())
			{
				Console::printf("[demo] cannot play an engine demo while a server is "
					"running - disconnect to the menu first.");
				return false;
			}
			return demo_native::play(path);

		case Kind::Custom:
			return demo_playback::play(path);

		default:
			Console::printf("[demo] '%s' is not a demo (.demo or %s).",
				path.filename().string().c_str(),
				std::string(demo_utils::DEMO_EXTENSION).c_str());
			return false;
		}
	}

	bool play_selected()
	{
		if (const Entry* e = selected_entry())
		{
			return play(e->path);
		}
		return false;
	}

	void stop()
	{
		if (demo_playback::is_playing())
		{
			demo_playback::stop();
		}
		// The engine has no "stop demo" command; disconnecting is how playback
		// ends, and doing that unconditionally would kick the user out of a live
		// match. So only disconnect when a native demo is actually running.
		if (demo_native::native_playing())
		{
			GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "disconnect");
		}
	}

	bool paused()
	{
		switch (active())
		{
		case Kind::Engine: return demo_native::engine_paused();
		case Kind::Custom: return demo_playback::paused();
		default:           return false;
		}
	}

	void toggle_pause()
	{
		switch (active())
		{
		case Kind::Engine: demo_native::toggle_pause(); break;
		case Kind::Custom: demo_playback::toggle_pause(); break;
		default: break;
		}
	}

	float progress()
	{
		switch (active())
		{
		case Kind::Engine:
			return demo_native::playback_progress();

		case Kind::Custom:
		{
			const auto now = demo_playback::current_time();
			const auto bounds = demo_playback::time_bounds();
			if (!now || !bounds || bounds->second <= bounds->first)
			{
				return -1.0f;
			}
			const float f = static_cast<float>(*now - bounds->first)
				/ static_cast<float>(bounds->second - bounds->first);
			return std::clamp(f, 0.0f, 1.0f);
		}

		default:
			return -1.0f;
		}
	}

	float timescale()
	{
		switch (active())
		{
		case Kind::Engine: return demo_native::engine_timescale();
		case Kind::Custom: return demo_playback::timescale();
		default:           return 1.0f;
		}
	}

	void set_timescale(float value)
	{
		const float v = std::clamp(value, 0.1f, 4.0f);
		switch (active())
		{
		case Kind::Engine: demo_native::set_timescale(v); break;
		case Kind::Custom: demo_playback::set_timescale(v); break;
		default:
			Console::printf("[demo] nothing is playing.");
			break;
		}
	}

	void seek_relative(std::int32_t ms)
	{
		if (ms == 0)
		{
			return;
		}
		switch (active())
		{
		case Kind::Engine:
		{
			// Forward is a cheap realtime skip; backward has to land on a
			// keyframe, so route it through seek_to_time, which picks one and
			// then trims the remainder.
			const int now = demo_native::demo_time();
			if (ms > 0)
			{
				demo_native::skip_forward_ms(ms);
			}
			else
			{
				demo_native::seek_to_time((std::max)(0, now + ms));
			}
			break;
		}

		case Kind::Custom:
		{
			const auto now = demo_playback::current_time();
			if (!now)
			{
				return;
			}
			demo_playback::seek_to((std::max)(0, *now + ms));
			break;
		}

		default:
			Console::printf("[demo] nothing is playing.");
			break;
		}
	}

	const demo_library::Info& selected_details()
	{
		static demo_library::Info cached;
		static std::filesystem::path cached_for;

		const Entry* e = selected_entry();
		if (!e)
		{
			cached = demo_library::Info{};
			cached_for.clear();
			return cached;
		}
		if (e->path != cached_for)
		{
			cached_for = e->path;
			// describe_full walks the packet stream for the duration, so it
			// runs once per selection change, never per frame and never for
			// the whole list.
			cached = (e->kind == Kind::Engine)
				? demo_library::describe_full(e->path)
				: e->info;
		}
		return cached;
	}

	int tidy_names(std::string& summary)
	{
		int renamed = 0, skipped = 0;
		// Copy the paths first: renaming invalidates the list we are walking.
		std::vector<std::filesystem::path> targets;
		for (const auto& e : g_list)
		{
			if (e.kind == Kind::Engine)
			{
				targets.push_back(e.path);
			}
		}
		for (const auto& p : targets)
		{
			std::string why;
			if (demo_library::auto_rename(p, why))
			{
				++renamed;
			}
			else
			{
				++skipped;
			}
		}
		refresh();
		summary = std::format("renamed {}, left alone {}", renamed, skipped);
		return renamed;
	}

	bool auto_record() { return demo_native::auto_record(); }
	void set_auto_record(bool on) { demo_native::set_auto_record(on); }
	bool capturing() { return demo_recording::is_recording(); }

	void init()
	{
		// The whole product-level command set. Everything else is developer
		// mode - see DevMode.hpp.
		GameUtil::addCommand("demo_play", cmd_play);
		GameUtil::addCommand("demo_stop", cmd_stop);
		GameUtil::addCommand("demo_pause", cmd_pause);
		GameUtil::addCommand("demo_seek", cmd_seek);
		GameUtil::addCommand("demo_speed", cmd_speed);
		GameUtil::addCommand("demo_list", cmd_list);
		GameUtil::addCommand("demo_record", cmd_record);

		refresh();
	}
}
