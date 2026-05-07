#pragma once
#include "structs.h"

class Loaders {
public:
	static void initAssetLoaders();
	static XAssetHeader DB_FindXAssetHeaderOriginal(XAssetType type, const char* name, int allow_create_default);
};
