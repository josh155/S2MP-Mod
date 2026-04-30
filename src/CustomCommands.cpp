//////////////////////////////////////
//       Custom Commands
//	Functions for custom commands
//////////////////////////////////////
#include "pch.h"
#include "Console.hpp"
#include "FuncPointers.h"
#include <array>
#include "DvarInterface.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"
#include "DevDef.h"
#include "Noclip.hpp"
#include "Loaders.hpp"
#include "ConfigManager.h"

#define ASSET_ENTRY_SIZE 32
uintptr_t CustomCommands::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;
uintptr_t CustomCommands::rawBase = (uintptr_t)GetModuleHandle(NULL);
bool CustomCommands::isGodmode = false;

void CustomCommands::toggleGodmode() {
	if (!GameUtil::areWeHost()) {
		Console::print("Must be host to use this command");
		return;
	}
	int* health = (int*)0x9ED370C_b;
	if (CustomCommands::isGodmode) {
		*health = 100;
		Console::print("God (and Notarget ig): OFF");
		Functions::_SV_SendServerCommand(0i64, 0, "%c \"God (and Notarget ig): ^1OFF\"", 101i64);
	}
	else {
		*health = -1;
		Console::print("God (and Notarget ig): ON");
		Functions::_SV_SendServerCommand(0i64, 0, "%c \"God (and Notarget ig): ^2ON\"", 101i64);
	}
	CustomCommands::isGodmode = !CustomCommands::isGodmode;
}



void CustomCommands::dumpAllLuaFiles() {
	unsigned int count = 0;
	unsigned int totalSize = 0;
	auto g_assetNames = (const char**)0xF88A60_b;
	auto db_hashTable = (uint32_t*)0x27D0110_b;
	auto g_assetEntryPool = (uint8_t*)0x50F50E0_b;
	constexpr uint32_t HASH_SIZE = 0x48800; //this looks right from ida
	constexpr uint32_t MAX_ENTRIES = 0x200000; //placeholder
	const char* typeName = g_assetNames[ASSET_TYPE_LUA_FILE];
	for (uint32_t hash = 0; hash < HASH_SIZE; ++hash) {
		uint32_t index = db_hashTable[hash];

		while (index) {
			if (index >= MAX_ENTRIES) {
				break;
			}

			uint8_t* entry = g_assetEntryPool + (index * 32);

			uint32_t assetType = *(uint32_t*)(entry + 0);
			uint32_t nextIndex = *(uint32_t*)(entry + 20); //entry[5]

			if (assetType == ASSET_TYPE_LUA_FILE) {
				const char* assetName = Functions::_DB_GetXAssetName(entry);
				if (assetName) {
					XAsset* a = (XAsset*)entry;
					LuiLoader::dumpLuaFile(a->header.luafile);
				}

				++count;
				totalSize += Functions::_DB_GetXAssetTypeSize(assetType);
			}

			if (nextIndex >= MAX_ENTRIES) {
				break;
			}

			index = nextIndex;
		}
	}
	Console::printf("Dumped %u lua files", count);
}

void CustomCommands::dumpAllCSVFiles() {
	unsigned int count = 0;
	unsigned int totalSize = 0;
	auto g_assetNames = (const char**)0xF88A60_b;
	auto db_hashTable = (uint32_t*)0x27D0110_b;
	auto g_assetEntryPool = (uint8_t*)0x50F50E0_b;
	constexpr uint32_t HASH_SIZE = 0x48800; //this looks right from ida
	constexpr uint32_t MAX_ENTRIES = 0x200000; //placeholder
	const char* typeName = g_assetNames[ASSET_TYPE_STRINGTABLE];
	for (uint32_t hash = 0; hash < HASH_SIZE; ++hash) {
		uint32_t index = db_hashTable[hash];

		while (index) {
			if (index >= MAX_ENTRIES) {
				break;
			}

			uint8_t* entry = g_assetEntryPool + (index * 32);

			uint32_t assetType = *(uint32_t*)(entry + 0);
			uint32_t nextIndex = *(uint32_t*)(entry + 20); //entry[5]

			if (assetType == ASSET_TYPE_STRINGTABLE) {
				const char* assetName = Functions::_DB_GetXAssetName(entry);
				if (assetName) {
					XAsset* a = (XAsset*)entry;
					StringTableLoader::dump(a->header.table);
				}

				++count;
				totalSize += Functions::_DB_GetXAssetTypeSize(assetType);
			}

			if (nextIndex >= MAX_ENTRIES) {
				break;
			}

			index = nextIndex;
		}
	}
	Console::printf("Dumped %u stringtables", count);
}

void DB_ListAssetPool(unsigned int targetType, bool saveToFile) {
	unsigned int count = 0;
	unsigned int totalSize = 0;

	auto g_assetNames = (const char**)0xF88A60_b;
	auto db_hashTable = (uint32_t*)0x27D0110_b;
	auto g_assetEntryPool = (uint8_t*)0x50F50E0_b;

	constexpr uint32_t HASH_SIZE = 0x48800; //this looks right from ida
	constexpr uint32_t MAX_ENTRIES = 0x200000; //placeholder

	if (targetType >= 0x53) {
		Console::printf("Invalid asset type %u", targetType);
		return;
	}

	const char* typeName = g_assetNames[targetType];

	std::ofstream outFile;
	if (saveToFile) {
		std::string filename = "assetpool_" + std::to_string(targetType) + ".txt";
		outFile.open(filename, std::ios::out);
		if (!outFile.is_open()) {
			Console::printf("Failed to open file %s for writing.", filename.c_str());
			saveToFile = false;
		}
	}

	if (!saveToFile) {
		Console::printf("Listing assets in %s pool.", typeName);
	}

	for (uint32_t hash = 0; hash < HASH_SIZE; ++hash) {
		uint32_t index = db_hashTable[hash];

		while (index) {
			if (index >= MAX_ENTRIES) {
				break;
			}

			uint8_t* entry = g_assetEntryPool + (index * 32);

			uint32_t assetType = *(uint32_t*)(entry + 0);
			uint32_t nextIndex = *(uint32_t*)(entry + 20); //entry[5]

			if (assetType == targetType) {
				const char* assetName = Functions::_DB_GetXAssetName(entry);
				if (assetName) {
					if (saveToFile) {
						outFile << assetName << std::endl;
					}
					else {
						Console::printf("%s", assetName);
					}
				}

				++count;
				totalSize += Functions::_DB_GetXAssetTypeSize(assetType);
			}

			if (nextIndex >= MAX_ENTRIES) {
				break;
			}

			index = nextIndex;
		}
	}

	if (saveToFile) {
		outFile.close();
		Console::printf("Saved %u assets in %s pool to file.", count, typeName);
	}
	else {
		Console::printf("Total of %u assets in %s pool", count, typeName);
	}
}

void CustomCommands::previewMaterial() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count != 2) {
		Console::printf("Usage: prevmat <material>");
		return;
	}

	const char** args = cmdArgs->argv[nest];
	std::string matName = std::string(args[1]);
	if (matName.size() < 2) {
		DevDraw::previewMaterial = nullptr;
		return;
	}

	DevDraw::previewMaterial = Functions::_Material_RegisterHandle(args[1]);
	Console::devPrint("material " + matName + " located at address 0x" + GameUtil::getAddressAsString(DevDraw::previewMaterial));
}

void printLapUsage(bool isSave) {
	if (isSave) {
		Console::print("saveassetpool <poolnumber>: saves a list of all the assets in the specified pool");
	}
	else {
		Console::print("listassetpool <poolnumber>: lists all the assets in the specified pool");
	}
	uintptr_t g_assetNamesAddr = (uintptr_t)0xF88A60_b;
	const int MAX_ASSET_TYPES = 0x53;

	const char** assetNames = reinterpret_cast<const char**>(g_assetNamesAddr);
	for (int i = 0; i < MAX_ASSET_TYPES; ++i) {
		const char* name = assetNames[i];
		if (!name) {
			break;
		}

		Console::printf("%i %s", i, name);
	}
}

void CustomCommands::listAssetPool() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count != 2) {
		printLapUsage(false);
		return;
	}

	const char** args = cmdArgs->argv[nest];
	unsigned int type = static_cast<unsigned int>(std::strtoul(args[1], nullptr, 10));

	DB_ListAssetPool(type, false);
}

void CustomCommands::saveAssetPool() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count != 2) {
		printLapUsage(true);
		return;
	}

	const char** args = cmdArgs->argv[nest];
	unsigned int type = static_cast<unsigned int>(std::strtoul(args[1], nullptr, 10));

	DB_ListAssetPool(type, true);
}


void CustomCommands::listAllCmds() {
	cmd_function_s* cmd = *(cmd_function_s**)0xAA752C8_b;
	while (cmd) {
		if (IsBadReadPtr(cmd, sizeof(cmd_function_s))) {
			break;
		}


		if (cmd->name && !IsBadStringPtrA(cmd->name, 64)) {
			Console::print(std::string(cmd->name));
		}
		cmd = cmd->next;
	}
}

//cg_hudblood
void CustomCommands::toggleHudBlood(bool b) {
	constexpr std::array<unsigned char, 5> DISABLE_HUDBLOOD_PATCH_BYTES = { 0x90, 0x90, 0x90, 0x90, 0x90 }; //patch
	constexpr std::array<unsigned char, 5> ENABLE_HUDBLOOD_PATCH_BYTES = { 0xE8, 0xD1, 0x48, 0xFE, 0xFF }; //original
	HANDLE pHandle = GetCurrentProcess();
	if (b) {
		WriteProcessMemory(pHandle, (LPVOID)(0x4C35A_b), ENABLE_HUDBLOOD_PATCH_BYTES.data(), ENABLE_HUDBLOOD_PATCH_BYTES.size(), nullptr);
	}
	else {
		WriteProcessMemory(pHandle, (LPVOID)(0x4C35A_b), DISABLE_HUDBLOOD_PATCH_BYTES.data(), DISABLE_HUDBLOOD_PATCH_BYTES.size(), nullptr);
	}
}

void CustomCommands::toggleFullbright(bool enable) {
	constexpr std::byte ENABLE{ 0x08 };
	constexpr std::byte DISABLE{ 0x0F };
	const std::byte value = enable ? ENABLE : DISABLE;
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(0xFE073F4_b), &value, sizeof(value), nullptr);
}

void CustomCommands::toggleWireframe(bool enable) {
	constexpr std::byte ENABLE{ 0x20 };
	constexpr std::byte DISABLE{ 0x0F };
	const std::byte value = enable ? ENABLE : DISABLE;
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(0xFE073F4_b), &value, sizeof(value), nullptr);
}


//r_fog
void CustomCommands::toggleFog(bool b) {
	constexpr std::array<unsigned char, 5> DISABLE_FOG_PATCH_BYTES = { 0x90, 0x90, 0x90, 0x90, 0x90 }; //patch
	constexpr std::array<unsigned char, 5> ENABLE_FOG_PATCH_BYTES = { 0xE8, 0xBF, 0x14, 0x41, 0x00 }; //original
	HANDLE pHandle = GetCurrentProcess();
	if (b) {
		WriteProcessMemory(pHandle, (LPVOID)(0x35A2C_b), ENABLE_FOG_PATCH_BYTES.data(), ENABLE_FOG_PATCH_BYTES.size(), nullptr);
	}
	else {
		WriteProcessMemory(pHandle, (LPVOID)(0x35A2C_b), DISABLE_FOG_PATCH_BYTES.data(), DISABLE_FOG_PATCH_BYTES.size(), nullptr);
	}
}

bool doPortalRendering = true;
void CustomCommands::togglePortals() {
	doPortalRendering = !doPortalRendering;
	//todo: port from bo2
}

void CustomCommands::translateString() {

}

void CustomCommands::cmdTest() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	Console::printf("CmdArgs (nesting = %d) has %d arguemnts:", nest, count);

	const char** args = cmdArgs->argv[nest];

	for (int i = 0; i < count; ++i) {
		if (!IsBadStringPtrA(args[i], 64)) {
			Console::printf("Arg[%d]: %s", i, args[i]);
		}
	}
}

void CustomCommands::tempToggleFullbright() {
	std::byte current{};
	const auto address = reinterpret_cast<void*>(0xFE073F4_b);

	if (ReadProcessMemory(GetCurrentProcess(), address, &current, sizeof(current), nullptr)) {
		toggleFullbright(current != std::byte{ 0x08 });
	}
}

void CustomCommands::tempToggleWireframe() {
	std::byte current{};
	const auto address = reinterpret_cast<void*>(0xFE073F4_b);

	if (ReadProcessMemory(GetCurrentProcess(), address, &current, sizeof(current), nullptr)) {
		toggleWireframe(current != std::byte{ 0x20 });
	}
}

typedef ItemLockStatus(*LiveStorage_IsItemUnlockedFromTable)(/*dont care*/);
LiveStorage_IsItemUnlockedFromTable _LiveStorage_IsItemUnlockedFromTable = nullptr;

typedef ItemLockStatus(*LiveStorage_GetItemLockStatus)(/*dont care*/);
LiveStorage_GetItemLockStatus _LiveStorage_GetItemLockStatus = nullptr;

typedef bool(*GetIsItemUnlockedStr)(bool __cdecl GetIsItemUnlockedStr(LocalClientNum_t num, char const* str));
GetIsItemUnlockedStr _GetIsItemUnlockedStr = nullptr;

ItemLockStatus returnUnlocked() {
	return ItemLockStatus_Unlocked;
}
bool hook_GetIsItemUnlockedStr() {
	return true;
}

void CustomCommands::unlockAll() {
	bool current = ConfigManager::readConfigValue("s2mp-mod.cfg", "unlockall", false);

	if (!current) {
		if (ConfigManager::writeConfigValue("s2mp-mod.cfg", "unlockall", true)) {
			Console::infoPrint("Unlock All saved to config");
		}
	}
	Hook::nopMem((void*)0xCE822_b, 2); //LiveStorage_GetItemLockStateFromStatus (just in case, force "Unlocked")

	MH_CreateHook(reinterpret_cast<void*>(0xCFB10_b), &returnUnlocked, reinterpret_cast<void**>(&_LiveStorage_IsItemUnlockedFromTable));
	MH_EnableHook(reinterpret_cast<void*>(0xCFB10_b));

	MH_CreateHook(reinterpret_cast<void*>(0xCE850_b), &returnUnlocked, reinterpret_cast<void**>(&_LiveStorage_GetItemLockStatus));
	MH_EnableHook(reinterpret_cast<void*>(0xCE850_b));

	MH_CreateHook(reinterpret_cast<void*>(0x73E9F0_b), &hook_GetIsItemUnlockedStr, reinterpret_cast<void**>(&_GetIsItemUnlockedStr));
	MH_EnableHook(reinterpret_cast<void*>(0x73E9F0_b));

	constexpr std::array<unsigned char, 5> UNLOCK_CHALLENGES_PATCH = { 0xB8, 0xFF, 0x00, 0x00, 0x00 }; //GetChallengeHelper
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)(0xCE676_b), UNLOCK_CHALLENGES_PATCH.data(), UNLOCK_CHALLENGES_PATCH.size(), nullptr);

	//custom set vars
	GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "unlockAllConsumables 1");
	GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "unlockAllPassivePerks 1");
}

//when it works, causes too many lui errors in main.lua
//TODO: fix
void CustomCommands::changeMap() {
	bool isMapPreloaded = false;
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count < 2) {
		Console::print("Usage: map <map name> <optional sv_migrate>");
		return;
	}

	if (count <= 3) {
		int* sv_migrate = (int*)0xBB4EE68_b;
		*sv_migrate = 0;
	}
	else {
		int* sv_migrate = (int*)0xBB4EE68_b;
		*sv_migrate = atol(cmdArgs->argv[nest][3]); //TODO: make this safe
	}
	
	Functions::_SV_StartMap(LOCAL_CLIENT_0, cmdArgs->argv[nest][2], isMapPreloaded);
}

void CustomCommands::fastRestart() {
	int* sv_map_restart = (int*)(0xBB4EE60_b);
	*sv_map_restart = 1;
}

void CustomCommands::mapRestart() {
	int* sv_loadScripts = (int*)(0xBB4EE64_b);
	*sv_loadScripts = 1;
	int* sv_map_restart = (int*)(0xBB4EE60_b);
	*sv_map_restart = 1;
}

void CustomCommands::quit() {
	Console::print("quitting...");
	Functions::_Com_Quit_f();
}

bool CustomCommands::ufoActive = false;
void CustomCommands::toggleUfo() {
	if (!GameUtil::areWeHost()) {
		Console::print("Must be host to use this command");
		return;
	}
	if (Noclip::getNoclipState()) { //turn off noclip if on
		Noclip::toggle();
	}
	constexpr std::array<unsigned char, 6> DISABLE_UFO_PATCH_BYTES = { 0x0F, 0x87, 0xDB, 0x04, 0x00, 0x00 }; //original
	constexpr std::array<unsigned char, 6> ENABLE_UFO_PATCH_BYTES = { 0xE9, 0xA0, 0x02, 0x00, 0x00, 0x90 }; //mod
	HANDLE pHandle = GetCurrentProcess();
	if (CustomCommands::ufoActive) {
		Console::print("UFO: OFF");
		Functions::_SV_SendServerCommand(0i64, 0, "%c \"UFO: ^1OFF\"", 101i64);
		WriteProcessMemory(pHandle, (LPVOID)(0x39C0A2_b), DISABLE_UFO_PATCH_BYTES.data(), DISABLE_UFO_PATCH_BYTES.size(), nullptr);
	}
	else {
		Console::print("UFO: ON");
		Functions::_SV_SendServerCommand(0i64, 0, "%c \"UFO: ^2ON\"", 101i64);
		WriteProcessMemory(pHandle, (LPVOID)(0x39C0A2_b), ENABLE_UFO_PATCH_BYTES.data(), ENABLE_UFO_PATCH_BYTES.size(), nullptr);
	}
	CustomCommands::ufoActive = !CustomCommands::ufoActive;
}