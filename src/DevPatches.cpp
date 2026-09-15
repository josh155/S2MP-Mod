/////////////////////////////////////////////////
//         Development Patches
// Temporary patches for testing stuff
/////////////////////////////////////////////////

#include "pch.h"
#include "DevPatches.hpp"
#include "Console.hpp"
#include "FuncPointers.h"
#include "GameUtil.hpp"
#include "ImageLoader.hpp"
#include "memory.h"
#include <DevDef.h>
#include <xsk/gsc/engine/s2.hpp>
#include <Hook.hpp>
#include <string.h>
#include <atomic>
#include "DvarInterface.hpp"

typedef void* (*BG_GetWorldModel_t)(Weapon* weapon, bool isAlternate, int variation);
static BG_GetWorldModel_t fpBG_GetWorldModel;
static std::atomic<unsigned int> g_weapon_world_model_debug_calls{0};

//force missing world models to use defaultweapon to prevent error 560
void* BG_GetWorldModel_hookfunc(Weapon* weapon, bool isAlternate, int variation) {
    void* model = fpBG_GetWorldModel(weapon, isAlternate, variation);
    const unsigned int n = g_weapon_world_model_debug_calls.fetch_add(1, std::memory_order_relaxed) + 1;
    if (n <= 128 || (n % 256) == 0) {
        Console::printf("[weapon-debug] BG_GetWorldModel n=%u weapon=%p raw=%u alt=%d variation=%d model=%p",
            n, static_cast<void*>(weapon), weapon ? static_cast<unsigned int>(weapon->data) : 0u,
            isAlternate ? 1 : 0, variation, model);
    }
    if (!model) {
        model = Functions::_DB_FindXAssetHeader(ASSET_TYPE_XMODEL, "defaultweapon", 1).data;
    }
    return model;
}

void applyLocalOffset(float origin[3], const float axis[3][3], float x, float y, float z) {
    origin[0] += x * axis[0][0] + y * axis[1][0] + z * axis[2][0];
    origin[1] += x * axis[0][1] + y * axis[1][1] + z * axis[2][1];
    origin[2] += x * axis[0][2] + y * axis[1][2] + z * axis[2][2];
}

typedef void (*CG_AddPlayerWeapon_t)(int localClientNum, const GfxScaledPlacement* placement, void* ps, void* cent, int isViewModel);
static CG_AddPlayerWeapon_t fpCG_AddPlayerWeapon;
static std::atomic<unsigned int> g_weapon_scene_debug_calls{0};

dvar_t* cg_gun_x = nullptr;
dvar_t* cg_gun_y = nullptr;
dvar_t* cg_gun_z = nullptr;

// Live-only gun offset dvars.
void CG_AddPlayerWeapon_hookfunc(int localClientNum, const GfxScaledPlacement* placement, void* ps, void* cent, int isViewModel) {
    const unsigned int n = g_weapon_scene_debug_calls.fetch_add(1, std::memory_order_relaxed) + 1;
    if (n <= 256 || (n % 512) == 0) {
        Console::printf("[weapon-debug] CG_AddPlayerWeapon n=%u source=%s client=%d ps=%p cent=%p placement=%p",
            n, isViewModel ? "local" : "remote", localClientNum, ps, cent, placement);
    }
    fpCG_AddPlayerWeapon(localClientNum, placement, ps, cent, isViewModel);
}

typedef bool (*BG_AISystemEnabled_t)();
static BG_AISystemEnabled_t fpBG_AISystemEnabled;

bool BG_AISystemEnabled_hookfunc() {
    return true;
}

typedef bool (*BG_BotSystemEnabled_t)();
static BG_BotSystemEnabled_t fpBG_BotSystemEnabled;

bool BG_BotSystemEnabled_hookfunc() {
    return true;
}

typedef bool (*BG_AgentSystemEnabled_t)(int a);
static BG_AgentSystemEnabled_t fpBG_AgentSystemEnabled;

bool BG_AgentSystemEnabled_hookfunc(int a) {
    return true;
}

typedef void (*Scr_Error_t)(const char* format, ...);
static Scr_Error_t fpScr_Error;

void Scr_Error_hookfunc(const char* format, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    Console::printf("%s", buffer);

    fpScr_Error(buffer);
}

void DevPatches::init()  {
    DEV_INIT_PRINT();
    // Weapon rendering/switching remains completely native. The diagnostic
    // detour is disabled because a switch crash must not be masked by a probe.

    //Bot Testing
    Hook::create("BG_AISystemEnabled", 0x3869A0_b, &BG_AISystemEnabled_hookfunc, &fpBG_AISystemEnabled);
    Hook::create("BG_BotSystemEnabled", 0x387180_b, &BG_BotSystemEnabled_hookfunc, &fpBG_BotSystemEnabled);
    Hook::create("BG_AgentSystemEnabled", 0x386BC0_b, &BG_AgentSystemEnabled_hookfunc, &fpBG_AgentSystemEnabled);
}
