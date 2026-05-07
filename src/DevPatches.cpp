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

typedef void (*Dvar_SetVariant_t)(dvar_t* dvar, DvarValue* value, int source);
static Dvar_SetVariant_t fpDvar_SetVariant;
void Dvar_SetVariant_hookfunc(dvar_t* dvar, DvarValue* value, int source) {
    if (!strcmp(dvar->name, "3078")) {
        //DEV_PRINTF("cg_fovscale set to %f from source %d", value->value, source);
        if (source != 1) {
            return;
        }
    }

    fpDvar_SetVariant(dvar, value, source);
}


void DevPatches::init()  {
    DEV_INIT_PRINT();
    //make weapons without world models work
    Hook::create("BG_GetWorldModel", 0x3BCD30_b, &BG_GetWorldModel_hookfunc, &fpBG_GetWorldModel);
    Hook::create("Dvar_SetVariant", 0xB20C0_b, &Dvar_SetVariant_hookfunc, &fpDvar_SetVariant);


}
