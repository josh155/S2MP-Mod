#pragma once

#include "structs.h"

class LuiLoader {
public:
	static void dumpLuaFile(const LuaFile* luaFile);
	static bool FindXAssetHeader(XAssetType type, const char* name, int allow_create_default, XAssetHeader& header);
	static bool LUI_CoD_GetRawFile(XAssetHeader& header, const char* name);
	static void init();
};
