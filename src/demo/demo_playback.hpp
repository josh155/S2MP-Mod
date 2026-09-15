#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <utility>

namespace demo_playback
{
	void init();

	// Start / stop / seek the custom (.dm_s2) theater. Exposed so demo_player
	// can dispatch to it -- the console commands live there now, not here, so
	// that one command set drives both demo engines.
	bool play(const std::filesystem::path& path);
	void stop();
	bool seek_to(std::int32_t absolute_ms);

	bool is_playing();
	bool suppress_local_messages();
	bool is_replay_armed();
	// Armed and CA_ACTIVE — theater draw/stream paths may run.
	bool is_active_replay();

	bool paused();
	void toggle_pause();

	std::optional<std::int32_t> current_time();
	std::optional<std::pair<std::int32_t, std::int32_t>> time_bounds();
	const std::filesystem::path& current_path();

	void forward(std::uint32_t msec);
	bool rewind(std::optional<std::uint32_t> msec);
	// Absolute seek in demo serverTime ms. Backward seeks restart the stream and
	// burst-replay forward (S2 demos carry no seek index).
	bool seeking();

	float timescale();
	void set_timescale(float value);


	// Diagnostic chatter gate. OFF by default so the console stays readable.
	// Toggle in game with `demo_verbose 1`. Covers the per-frame probes:
	// [ang] [rate] [vm] [vmdraw] [vmadd] [vmres] [probe], the feed tick lines and
	// the gamestate-capture retry warning. Errors and one-shot state changes are
	// NOT gated — those always print.
	bool verbose();

}
