#include "pch.h"
#include "Console.hpp"
#include "structs.h"
#include <Hook.hpp>
#include "LogFile.hpp"
#include "DevDef.h"
#include "Arxan.hpp"

HMODULE hm;
//0 - CLI, 1 - GUI, 2 - BOTH
const int EXTERNAL_CONSOLE_MODE = 1;

DWORD WINAPI extConInitWrapper(LPVOID) {
	ExtConsole::extConInit(EXTERNAL_CONSOLE_MODE);
	return 0;
}

void ExternalConsoleGuiInitWrapper() {
	ExternalConsoleGui::init(hm, 0, NULL, 1);
}

DWORD WINAPI modInitWrapper(LPVOID module) {
	hm = static_cast<HMODULE>(module);

	Logfile::init();

#ifdef DEVELOPMENT_BUILD
	Logfile::setEnabled(true); //always log on dev build
#endif

	utils::hook::detour::detour(); //initialize minhook
	DebugPatches::earlyInit();
	if (EXTERNAL_CONSOLE_MODE == 0 || EXTERNAL_CONSOLE_MODE == 2) {
		AllocConsole();
		FILE* pFile = nullptr;
		freopen_s(&pFile, "CONOUT$", "w", stdout);
		freopen_s(&pFile, "CONIN$", "r", stdin);
	}
	if (EXTERNAL_CONSOLE_MODE >= 1) {
		std::thread t1(ExternalConsoleGuiInitWrapper);
		t1.detach();
	}

	HANDLE extConsoleThread = CreateThread(nullptr, 0, extConInitWrapper, nullptr, 0, nullptr);
	if (extConsoleThread) {
		CloseHandle(extConsoleThread);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hModule);
		HANDLE initThread = CreateThread(nullptr, 0, modInitWrapper, hModule, 0, nullptr);
		if (!initThread) {
			return FALSE;
		}

		CloseHandle(initThread);
	}
	return TRUE;
}
