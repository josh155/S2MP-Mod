/////////////////////////////////////////////////
//         Development Patches
// Temporary patches for testing stuff
/////////////////////////////////////////////////

#include "pch.h"
#include "DevPatches.hpp"
#include "Console.hpp"
#include "FuncPointers.h"
#include "GameUtil.hpp"
#include "memory.h"
#include <DevDef.h>
#include <xsk/gsc/engine/s2.hpp>
#include <Hook.hpp>
#include <string.h>

typedef void*(*Image_Setup)(GfxImage* image, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipCount, uint32_t imageFlags, DXGI_FORMAT imageFormat, const char* name, const void* initData);
Image_Setup _Image_Setup = nullptr;

void* hook_Image_Setup(GfxImage* image, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipCount, uint32_t imageFlags, DXGI_FORMAT imageFormat, const char* name, const void* initData) {
    //Console::printf("Image_Setup: %s, width: %d, height: %d, depth: %d, mipCount: %d, imageFlags: %d", name, width, height, depth, mipCount, imageFlags);
    return _Image_Setup(image, width, height, depth, mipCount, imageFlags, imageFormat, name, initData);
 
}

void imageThing() {
    MH_CreateHook(reinterpret_cast<void*>(0x8978C0_b), &hook_Image_Setup, reinterpret_cast<void**>(&_Image_Setup));
    MH_EnableHook(reinterpret_cast<void*>(0x8978C0_b));
}


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

void BG_GetWorldModel_setup() {
    MH_CreateHook(reinterpret_cast<void*>(0x3BCD30_b), &BG_GetWorldModel_hookfunc, reinterpret_cast<void**>(&fpBG_GetWorldModel));
    MH_EnableHook(reinterpret_cast<void*>(0x3BCD30_b));
}


void DevPatches::init()  {
    DEV_INIT_PRINT();
    //imageThing();
    BG_GetWorldModel_setup();
}