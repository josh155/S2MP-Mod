#pragma once

#include "structs.h"

class ScriptLoader {
public:
	static void dumpScript(ScriptFile* script);
	static void loadCustomScripts();
	static void init();
};
