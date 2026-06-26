#pragma once

#include "structs.h"

class ScriptLoader {
public:
	static void dumpScript(ScriptFile* script);
	static void loadCustomScripts();
	static void init();

	// STUBS: referenced by Loaders.cpp, not yet implemented
	static bool FindXAssetHeader(XAssetType type, const char* name, int allow_create_default, XAssetHeader& header);
	static void noteScriptFileAsset(ScriptFile* script);
	static bool ShouldForceNonDefault(XAssetType type, const char* name);
};
