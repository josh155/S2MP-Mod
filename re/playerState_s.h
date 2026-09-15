/* ===========================================================================
 * playerState_s -- Call of Duty: WWII (S2), Steam build.  ** PARTIAL **
 * ===========================================================================
 *
 * Derived 2026-08-17. Named only where S2's OWN code proves it, or where AW
 * agrees field-for-field AND width-for-width across a run.
 *
 * WHERE IT LIVES
 *   playerState is the FIRST member of cg_s (AW: cg_s.predictedPlayerState at
 *   offset 0; likewise snapshot_s.ps and gclient_s.ps). So in S2 it is reached as
 *   CG_GetLocalClientGlobals(client) + 0 -- there is no separate accessor.
 *
 * METHOD
 *   139 distinct offsets extracted from all 938 callers of
 *   CG_GetLocalClientGlobals (re/map_struct.py). 103 of them fall in the first
 *   1000 bytes, which is where essentially all playerState traffic is.
 *
 * ⚠ THE SIZE BELOW IS NOT sizeof(playerState_s).
 *   It covers the MAPPED REGION only (through weaponFlags at +1524). AW's is
 *   14,848 and S2's is larger; the real end has not been established.
 *
 * HOW S2 RELATES TO AW
 *   The head matches EXACTLY -- same offsets, same widths -- from 0 through at
 *   least +56, including a run of eight consecutive int16 entity-number fields at
 *   28/30/32/36/40/42/44/46. After that S2 inserts fields, and the shift grows
 *   with depth:
 *
 *       field         S2     AW    shift
 *       pm_type        2      2      +0
 *       origin       132    120     +12
 *       velocity     144    132     +12
 *       vehicleState 268    224     +44
 *       viewangles   576    436    +140
 *
 *   So AW offsets must never be copied below the head; only the ORDER carries.
 *
 * ⭐ origin/velocity are PROVEN, not inferred. CL_GetPredicted (0x462650) does:
 *       archive+4  -> ps+132/136/140     (archive origin,   entry+4)
 *       archive+16 -> ps+144/148/152     (archive velocity, entry+16)
 *       archive+28 -> ps+15   (byte)
 *       archive+32 -> ps+248
 *   The archive layout is independently proven from CL_Demo_ProcessPacket_Type1,
 *   so this confirms demo_game.hpp's PS_ORIGIN/PS_VELOCITY against AW's differing
 *   layout. The project's constants are right.
 *
 * ⭐ RESOLVED -- and it was a MISNAMING. +104 is otherFlags, not eFlags.
 *   sub_5D0C0 (CG_UpdateViewModel) tests THREE consecutive flag dwords:
 *       (cg +  96) & 0x800
 *       (cg + 100) & 0x100
 *       (cg + 104) & 0x3800      <- what demo_game.hpp called PS_EFLAGS
 *   AW has pm_flags@84, eFlags@88, otherFlags@92 -- three consecutive flag words
 *   in exactly that pattern.
 *
 *   The decider is MONOTONICITY: the AW->S2 shift can only INCREASE, because the
 *   difference comes from fields being INSERTED, never removed. The shift is
 *   PROVEN +12 at origin (CL_GetPredicted writes archive+4 -> ps+132, and AW's
 *   origin is at 120). A field at +104 must therefore map to AW >= 92 -- so it is
 *   otherFlags. eFlags is at +100 and pm_flags at +96.
 *
 *   demo_game.hpp and the [vmdraw] probe were corrected accordingly. The OFFSET
 *   and the 0x203800 test were always right; only the label was wrong. NB the MWR
 *   netfield work hit this same misnaming once before (ps+0x5C turned out to be
 *   otherFlags rather than eFlags/pm_flags), so it is a recurring trap in this
 *   struct.
 * =========================================================================== */

#pragma once
#include <cstdint>

struct playerState_s_partial            /* PARTIAL -- see the size warning above */
{
    /* +0    */ char          clientNum;
    /* +1    */ std::uint8_t  _u001;
    /* +2    */ std::uint8_t  pm_type;              /* PROVEN (project) + AW agree */
    /* +3    */ std::uint8_t  _u003[12];
    /* +15   */ std::uint8_t  bobCycle;             /* PROVEN: CL_GetPredicted writes
                                                       the archive bob byte here; the
                                                       MWR twin writes bobCycle */
    /* +16   */ std::uint8_t  _u010[12];
    /* +28   */ std::int16_t  remoteEyesEnt;        /* the eight-i16 entity block:   */
    /* +30   */ std::int16_t  remoteControlEnt;     /* matches AW by offset AND width */
    /* +32   */ std::int16_t  throwbackGrenadeOwner;
    /* +34   */ std::int16_t  viewlocked_entNum;
    /* +36   */ std::int16_t  groundEntityNum;
    /* +38   */ std::int16_t  linkWeaponEnt;
    /* +40   */ std::int16_t  cursorHintEntIndex;
    /* +42   */ std::int16_t  meleeChargeEnt;
    /* +44   */ std::int16_t  movingPlatformEntity;
    /* +46   */ std::int16_t  groundRefEnt;
    /* +48   */ std::int16_t  loopSound;
    /* +50   */ std::int16_t  linkFlags;
    /* +52   */ std::uint8_t  _u052[44];
    /* +96   */ std::int32_t  pm_flags;             /* sub_5D0C0 tests & 0x800  */
    /* +100  */ std::int32_t  eFlags;               /* sub_5D0C0 tests & 0x100  */
    /* +104  */ std::int32_t  otherFlags;           /* sub_5D0C0 tests & 0x3800 --
                                                       CORRECTED, see header note */
    /* +108  */ std::uint8_t  _u108[24];
    /* +132  */ float         origin[3];            /* PROVEN: CL_GetPredicted */
    /* +144  */ float         velocity[3];          /* PROVEN: CL_GetPredicted */
    /* +156  */ std::uint8_t  _u156[92];
    /* +248  */ std::int32_t  movementDir;          /* PROVEN: CL_GetPredicted */
    /* +252  */ std::uint8_t  _u252[16];
    /* +268  */ std::uint16_t vehicleEntityNum;     /* 2047 = none. NEVER WRITE:
                                                       its caller feeds it straight
                                                       into CG_GetEntity */
    /* +270  */ std::uint8_t  _u270[306];
    /* +576  */ float         viewangles[3];        /* PROVEN: CG_CalcViewValues reads
                                                       ps+0x240. The single most
                                                       load-bearing field in the demo
                                                       work -- the ONLY durable inject
                                                       point, because clientActive is
                                                       overwritten from ps every frame */
    /* +588  */ std::uint8_t  _u588[228];
    /* +816  */ std::int32_t  archiveExtra0;        /* CL_GetDemoViewAnglesFromArchive */
    /* +820  */ std::uint8_t  _u820[252];
    /* +1072 */ std::uint8_t  weapons[180];         /* Weapon[15], stride 12 */
    /* +1252 */ std::uint8_t  weaponSlotMeta[210];  /* 14 * 15; byte[1] = equipped */
    /* +1462 */ std::uint8_t  _u1462[2];
    /* +1464 */ std::int32_t  heldWeaponAlt;        /* used when (weaponFlags & 2) */
    /* +1468 */ std::uint8_t  _u1468[44];
    /* +1512 */ std::int32_t  heldWeapon;
    /* +1516 */ std::uint8_t  _u1516[8];
    /* +1524 */ std::int32_t  weaponFlags;          /* & 0x4000 = left hand */
};

static_assert(sizeof(playerState_s_partial) == 1528, "mapped region only");
static_assert(offsetof(playerState_s_partial, pm_type)     == 2,    "pm_type");
static_assert(offsetof(playerState_s_partial, bobCycle)    == 15,   "bobCycle");
static_assert(offsetof(playerState_s_partial, pm_flags)    == 96,   "pm_flags");
static_assert(offsetof(playerState_s_partial, eFlags)      == 100,  "eFlags");
static_assert(offsetof(playerState_s_partial, otherFlags)  == 104,  "otherFlags");
static_assert(offsetof(playerState_s_partial, origin)      == 132,  "origin");
static_assert(offsetof(playerState_s_partial, velocity)    == 144,  "velocity");
static_assert(offsetof(playerState_s_partial, movementDir) == 248,  "movementDir");
static_assert(offsetof(playerState_s_partial, viewangles)  == 576,  "viewangles");
static_assert(offsetof(playerState_s_partial, heldWeapon)  == 1512, "heldWeapon");
static_assert(offsetof(playerState_s_partial, weaponFlags) == 1524, "weaponFlags");
