#pragma once
#include <string>
#include "Structs.h"

class Binds {
public:
	static void execBindForKey(int keyNum, int down);
	static void setupCustomBindFromCmd(int keyNum, const char* command);
	static void unbindCustomBind(int keyNum);
	static void bindCmd();
	static void unbindCmd();
	static void unbindAllCmd();
	static void init();
};
