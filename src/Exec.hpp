#pragma once
#include <string>
#include "Structs.h"

class Exec {
public:
	static void init();
	static void execCmd();
	static bool updateAutoexecDvar(const std::string& dvarName, const std::string& value);

	// Strip leftover native/demo auto-play lines left behind while testing theater
	// (cl_demo_play / demo_play / connect demo). Safe no-op if autoexec is clean.
	static void scrubDemoAutostartFromAutoexec();
};
