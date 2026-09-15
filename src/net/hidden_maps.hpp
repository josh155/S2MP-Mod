#pragma once

// =============================================================================
//  net/hidden_maps — put a compiled-but-hidden map into the GAME'S OWN
//  private-match map picker, not just this mod's Host tab.
// =============================================================================
//
//  USER ASK 2026-09-15: "Groesten House should also show up in the actual map
//  selection screen in private match, not in our menu." force_host.cpp already
//  surfaces mp_house in this mod's own Host tab (a different, engine-adjacent
//  table); this is the harder half -- the game's NATIVE menu.
//
//  ---------------------------------------------------------------------------
//  WHERE THE NATIVE PICKER'S LIST ACTUALLY COMES FROM
//  ---------------------------------------------------------------------------
//
//  The private-match map screen is a LUI "feeder" over the Lua library table
//  at IDA 0xB5F930 (registered "Lobby"): GetMapCount, GetMapFeederCount,
//  GetMapNameByIndex, GetMapLoadNameByIndex, GetMapImageByIndex, GetDLCMapCount.
//  Every one of those is a thin marshaller over ONE in-memory table:
//
//      record array   IDA 0xAB0F8B4          (unk_AB0F8B4)
//      count           IDA 0xAB0F8B0          (dword_AB0F8B0) -- a SEPARATE
//                       global 4 bytes before the array; only adjacent by
//                       coincidence of linker layout, not part of the record.
//      stride          4660 bytes/record
//      cap             128 records (the loader itself stops there)
//
//  and that table is populated by ONE function, found via its own xrefs to
//  the count global:
//
//      GameInfo_UpdateArenas   IDA 0x650A70   -- twin-named from the AW
//      string anchors '.arena files : %s', 'mappack', 'mp/mapLoad.csv'
//
//  Decompiled in full. It is gated on a dirty flag (dword_AB0F8AC, set by
//  sub_6506D0 whenever the menu needs a refresh) and, when dirty, rebuilds the
//  WHOLE table from scratch by loading the CSV asset **"mp/mapLoad.csv"** and,
//  for each row, copying named columns into the record:
//
//      +0     "longname"      display name, 32 bytes
//      +32    "map"           load name (what force_host calls a map), 32 B
//      +64    "description"   32 bytes
//      +96    "mapimage"      32 bytes
//      +2724  "mappack"       int, atoi() of the column, or -1 if blank/absent
//      +2732  "gametype"      int bitmask of allowed gametypes, or -1 if blank
//
//  mp_house has no row in the shipped mp/mapLoad.csv (it is not present in
//  either an offline dump search or the compiled string pool the way the
//  smaller playlist-facing map table's entries are), so GameInfo_UpdateArenas
//  simply never creates a record for it -- there is no gate to disable, the
//  data that would produce one does not exist.
//
//  ---------------------------------------------------------------------------
//  THE mappack FIELD IS THE ONE THAT MUST BE EXACTLY 0
//  ---------------------------------------------------------------------------
//
//  Both consumers that decide "is this map selectable" (sub_74EEC0, the count,
//  and UI_GetMapIdForNum, the index remapper the feeder uses) test the mappack
//  field the SAME way:
//
//      if (!mappack || Content_DoWeHaveContentPack(mappack + 1)) -> included
//
//  `!mappack` is true only for mappack == 0. The CSV parser's OWN "column is
//  blank" sentinel is -1, which is NOT 0 -- a blank column routes through
//  Content_DoWeHaveContentPack(0) instead, unproven to return true. So the
//  synthetic record this module adds sets mappack explicitly to 0 (matching
//  every real base-game map's row), not left at -1.
//
//  ---------------------------------------------------------------------------
//  THE FIX -- append after the real list, never touch the CSV or a fastfile
//  ---------------------------------------------------------------------------
//
//  GameInfo_UpdateArenas is hooked; the original runs FIRST (so the ~50 real
//  maps populate exactly as they always have), then, if the table has no
//  "mp_house" row yet and there is still room before the 128-entry cap, one
//  record is appended with the fields above. This runs every time the native
//  function is called, so it survives the table being rebuilt from scratch
//  whenever the dirty flag fires again -- there is no one-shot state to lose.
//
//  Nothing on disk is modified; no fastfile is touched. This is purely an
//  in-memory append to a table the engine already owns and already walks.
// =============================================================================

namespace hidden_maps
{
	void init();
}
