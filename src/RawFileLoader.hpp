#pragma once

#include "structs.h"

class RawFileLoader {
public:
	static void dump(RawFile* rawfile);
	static void loadCustom(RawFile* rawfile);
};
