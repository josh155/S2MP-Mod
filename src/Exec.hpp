#pragma once
#include <string>
#include "Structs.h"

class Exec {
public:
	static void init();
	static void execCmd();
	static bool updateAutoexecDvar(const std::string& dvarName, const std::string& value);
};
