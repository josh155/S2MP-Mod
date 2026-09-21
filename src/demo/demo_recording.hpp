#pragma once

namespace demo_recording
{
	void init();
	// True once a .dm_s2 file is actually being written.
	bool is_recording();
	// True as soon as recording has been requested, even before a match
	// exists to write from -- lets the UI show "on" without flickering
	// back off while it waits for a connect.
	bool is_armed();
	void start();
	void stop();
	// Disarm AND stop (what `demo_stop_record` does). Used to enforce one
	// recorder at a time when native auto-record is switched on.
	void cancel();

	// On-screen notice ("Recording demo: <file>" / "Saved demo: <file>"),
	// shown for a few seconds. Called from the existing R_EndFrame stub.
	void render_notice();
}
