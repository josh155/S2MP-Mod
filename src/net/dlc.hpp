#pragma once
// =============================================================================
//  net/dlc — DLC entitlement toggle
// =============================================================================
//
//  Turning DLC off makes matchmaking search the BASE playlists instead of the
//  DLC ones, which is the practical use: DLC playlists are often empty, so
//  disabling entitlements puts you in the populated pools.
//
//  Recovered from the deleted force_host module (the research there was sound;
//  it was the matchmaking hooks that were the problem, not this).
//
//  Engine state, all PROVEN offsets:
//      g_contentEntitlementCount  IDA 0x0D4EE438 - 0x1000 = 0x0D4ED438
//      g_contentEntitlementLock   IDA 0x0D4EE43C - 0x1000 = 0x0D4ED43C
//      g_contentEntitlements      IDA 0x0D4EEC40 - 0x1000 = 0x0D4EDC40
//      stride 140 { char name[128]; i32 index; i16 enabled; i16 pad; i32 }
//
//  ⚠ NOTHING IS FABRICATED. Disabling only zeroes the COUNT -- the table rows
//  are left untouched -- so enabling restores exactly the entitlements the game
//  itself registered, never an invented list.
//
//  ⚠ It takes the engine's OWN spin lock before touching the count, because the
//  engine does, and a registration can be in flight on another thread.
//
//  ⚠ It must be LATCHED, not one-shot: the game keeps registering entitlements
//  and each registration bumps the count back up.
//
//  NO HOOKS -- a guarded write to a documented global, nothing patched.
// =============================================================================

#include <string>
#include <vector>

namespace dlc
{
	void init();

	// True when the count global is readable AND we have captured a real
	// original value to restore (so "enable" can never invent one).
	bool available();

	bool enabled();          // count > 0
	int  entry_count();      // live count
	int  original_count();   // what the game registered before we touched it

	void set_enabled(bool on);

	// Names from the entitlement table, for display.
	std::vector<std::string> entries();

	// Keeps the original fresh, and re-asserts "off" against the engine's
	// ongoing re-registration. Call once per frame; cheap and rate-limited.
	void tick();
}
