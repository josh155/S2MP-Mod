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
#include "DvarInterface.hpp"

typedef void* (*BG_GetWorldModel_t)(Weapon* weapon, bool isAlternate, int variation);
static BG_GetWorldModel_t fpBG_GetWorldModel;

//force missing world models to use defaultweapon to prevent error 560
void* BG_GetWorldModel_hookfunc(Weapon* weapon, bool isAlternate, int variation) {
    void* model = fpBG_GetWorldModel(weapon, isAlternate, variation);
    if (!model) {
        model = Functions::_DB_FindXAssetHeader(ASSET_TYPE_XMODEL, "defaultweapon", 1).data;
    }
    return model;
}


typedef int (*CG_AddPlayerWeapon_t)(int localClientNum, const GfxScaledPlacement* placement, void* ps, void* cent, bool isViewModel);
static CG_AddPlayerWeapon_t fpCG_AddPlayerWeapon;

void applyLocalOffset(float origin[3], const float axis[3][3], float x, float y, float z) {
    origin[0] += x * axis[0][0] + y * axis[1][0] + z * axis[2][0];
    origin[1] += x * axis[0][1] + y * axis[1][1] + z * axis[2][1];
    origin[2] += x * axis[0][2] + y * axis[1][2] + z * axis[2][2];
}

dvar_t* cg_gun_x = nullptr;
dvar_t* cg_gun_y = nullptr;
dvar_t* cg_gun_z = nullptr;
void CG_AddPlayerWeapon_hookfunc(int localClientNum, const GfxScaledPlacement* placement, void* ps, void* cent, bool isViewModel) {
    if (!cg_gun_x) {
        cg_gun_x = Functions::_Dvar_FindVar("cg_gun_x");
    }

    if (!cg_gun_y) {
        cg_gun_y = Functions::_Dvar_FindVar("cg_gun_y");
    }

    if (!cg_gun_z) {
        cg_gun_z = Functions::_Dvar_FindVar("cg_gun_z");
    }

    if (!placement || !cg_gun_x || !cg_gun_y || !cg_gun_z) {
        fpCG_AddPlayerWeapon(localClientNum, placement, ps, cent, isViewModel);
        return;
    }

    cg_t* globals = GameUtil::CG_GetLocalClientGlobals();
    if (!globals) {
        fpCG_AddPlayerWeapon(localClientNum, placement, ps, cent, isViewModel);
        return;
    }

    GfxScaledPlacement modified = *placement;
    applyLocalOffset(modified.base.origin, globals->viewModelAxis, cg_gun_x->current.value, cg_gun_y->current.value, cg_gun_z->current.value);
    fpCG_AddPlayerWeapon(localClientNum, &modified, ps, cent, isViewModel);
}

void DevPatches::init()  {
    DEV_INIT_PRINT();
    //make weapons without world models work
    Hook::create("BG_GetWorldModel", 0x3BCD30_b, &BG_GetWorldModel_hookfunc, &fpBG_GetWorldModel);

    Hook::create("CG_AddPlayerWeapon", 0x2E1B0_b, &CG_AddPlayerWeapon_hookfunc, &fpCG_AddPlayerWeapon);

   //
   // Hook::create("Crypto_TransformBufferInPlace", 0x15DC0_b, &Crypto_TransformBufferInPlace_hookfunc, &fpCrypto_TransformBufferInPlace);
   // Hook::create("ctr_setiv", 0x92BD90_b, &ctr_setiv_hookfunc, &fpctr_setiv);
   // Hook::create("ctr_start", 0x92BAB0_b, &ctr_start_hookfunc, &fpctr_start);
}
