#pragma once

#include "structs.h"

class StringTableLoader {
public:
	static void dump(StringTable* table);
	static void loadCustom(StringTable* table);
};
