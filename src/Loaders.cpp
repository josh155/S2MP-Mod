#include "pch.h"
#include "Loaders.hpp"
#include "Console.hpp"
#include "FontLoader.hpp"
#include "FuncPointers.h"
#include "Hook.hpp"
#include "ImageLoader.hpp"
#include "LuiLoader.hpp"
#include "RawFileLoader.hpp"
#include "ScriptLoader.hpp"
#include "StringTableLoader.hpp"
#include "DevDef.h"

//dont load from here just dump from here
//also has the waited for xasset print so ya
typedef XAssetHeader(*DB_FindXAssetHeader)(XAssetType type, const char* name, int allow_create_default);
DB_FindXAssetHeader _DB_FindXAssetHeader = nullptr;

static bool IsDvarEnabled(const char* name) {
    dvar_t* dvar = Functions::_Dvar_FindVar(name);
    if (!dvar) {
        DEV_PRINTF("Dvar '%s' was not found during asset load", name);
        return false;
    }

    return dvar->current.enabled;
}

XAssetHeader hook_DB_FindXAssetHeader(XAssetType type, const char* name, int allow_create_default) {
    XAssetHeader header{};

    //these will never call findxassetheader
    bool headerLoaded = false;
    const char* safeName = (name && name[0]) ? name : "<null>";
    switch (type) {
    case ASSET_TYPE_LUA_FILE: {
        headerLoaded = LuiLoader::LUI_CoD_GetRawFile(header, safeName);
        break;
    }
    }

    if (!headerLoaded) {
        auto start = std::chrono::high_resolution_clock::now();
        
        header = _DB_FindXAssetHeader(type, name, allow_create_default);
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (dur > 100) {
            Console::printf("Waited %i msec for asset '%s'", dur, safeName);
        }

    }

    switch (type) {
    case ASSET_TYPE_STRINGTABLE: {
        if (IsDvarEnabled("g_dumpStringTables")) {
            StringTableLoader::dump(header.table);
        }
        break;
    }
    case ASSET_TYPE_RAWFILE: {
        if (IsDvarEnabled("g_dumpRawfiles")) {
            RawFileLoader::dump(header.rawfile);
        }
        break;
    }
    default: { 
        break;
    }
    }

    return header;
}


void Loaders::initAssetLoaders() {
	//DB_FindXAssetHeader hook
	Hook::create("DB_FindXAssetHeader", 0xA0080_b, &hook_DB_FindXAssetHeader, &_DB_FindXAssetHeader);

	LuiLoader::init();
	FontLoader::init();
	ScriptLoader::init();
    ImageLoader::init();
}
