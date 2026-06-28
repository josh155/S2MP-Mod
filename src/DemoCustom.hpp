#pragma once
#include <string>

// Clean rebuild of the working "V055" custom demo system (originally a huge
// ChatGPT prototype). Approach: hook the engine's demo message parsers, record
// the parsed gamestate/snapshot/dispatch messages to a .w2dr file, and play them
// back by loading the map and re-feeding the recorded messages through the same
// parsers.
//
//   Recording: auto-starts on a real (non virtual-lobby) match, stops on return.
//   Playback : DemoCustom::play("file.w2dr") - loads the map then replays.
//
// Files live in the "demos" folder. Stripped of the prototype's diagnostics and
// dead experiments; only the load-bearing mechanism remains.
namespace demo_custom
{
	void init();

	// Start playback of a recorded .w2dr (filename only, looked up in demos/).
	// Runs on the game thread (call from a command / Cbuf).
	bool play(const std::string& file);
	void stop();

	bool is_recording();
	bool is_playing();
}
