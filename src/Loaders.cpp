#include "pch.h"
#include "Loaders.hpp"
#include "Console.hpp"
#include "FontLoader.hpp"
#include "FuncPointers.h"
#include "Hook.hpp"
#include "ImageLoader.hpp"
#include "LuiLoader.hpp"
#include "MapEntLoader.hpp"
#include "RawFileLoader.hpp"
#include "ScriptLoader.hpp"
#include "StringTableLoader.hpp"
#include "DevDef.h"

//dont load from here just dump from here
//also has the waited for xasset print so ya
typedef XAssetHeader(*DB_FindXAssetHeader)(XAssetType type, const char* name, int allow_create_default);
DB_FindXAssetHeader _DB_FindXAssetHeader = nullptr;
typedef bool(*DB_IsXAssetDefault)(XAssetType type, const char* name);
DB_IsXAssetDefault _DB_IsXAssetDefault = nullptr;

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
        headerLoaded = LuiLoader::FindXAssetHeader(type, safeName, allow_create_default, header);
        break;
    }
    case ASSET_TYPE_SCRIPTFILE: {
        headerLoaded = ScriptLoader::FindXAssetHeader(type, safeName, allow_create_default, header);
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

    if (type == ASSET_TYPE_SCRIPTFILE) {
        ScriptLoader::noteScriptFileAsset(header.script);
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

bool hook_DB_IsXAssetDefault(XAssetType type, const char* name) {
    if (ScriptLoader::ShouldForceNonDefault(type, name)) {
        return false;
    }

    if (!_DB_IsXAssetDefault) {
        return false;
    }

    return _DB_IsXAssetDefault(type, name);
}

XAssetHeader Loaders::DB_FindXAssetHeaderOriginal(XAssetType type, const char* name, int allow_create_default) {
    if (!_DB_FindXAssetHeader) {
        return {};
    }

    return _DB_FindXAssetHeader(type, name, allow_create_default);
}


void Loaders::initAssetLoaders() {
	//DB_FindXAssetHeader hook
	Hook::create("DB_FindXAssetHeader", 0xA0080_b, &hook_DB_FindXAssetHeader, &_DB_FindXAssetHeader);
    Hook::create("DB_IsXAssetDefault", 0xA2C90_b, &hook_DB_IsXAssetDefault, &_DB_IsXAssetDefault);

	LuiLoader::init();
	FontLoader::init();
	ScriptLoader::init();
    ImageLoader::init();
    MapEntLoader::init();
}
