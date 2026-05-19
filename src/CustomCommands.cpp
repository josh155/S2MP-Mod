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
#include "LuiLoader.hpp"
#include "ScriptLoader.hpp"
#include "StringTableLoader.hpp"
#include "ConfigManager.h"
#include "xsk/gsc/engine/s2.hpp"
#include <algorithm>
#include <cerrno>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#define ASSET_ENTRY_SIZE 32
uintptr_t CustomCommands::base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;
uintptr_t CustomCommands::rawBase = (uintptr_t)GetModuleHandle(NULL);

namespace xsk::gsc::s2 {
	extern std::array<std::pair<u16, char const*>, func_count> const func_list;
	extern std::array<std::pair<u16, char const*>, meth_count> const meth_list;
}

namespace {
	constexpr std::uint16_t GSC_HIGH_BUILTIN_BASE_ID = 0x8000;
	constexpr std::size_t GSC_LOW_BUILTIN_COUNT = 0x1E30 / sizeof(std::uintptr_t);
	constexpr std::size_t GSC_HIGH_BUILTIN_COUNT = 0x36B0 / sizeof(std::uintptr_t);

	struct GscBuiltinDumpStats {
		std::size_t printed = 0;
		std::size_t resolved = 0;
		std::size_t nullAddress = 0;
		std::size_t outOfRange = 0;
	};

	std::string toLowerCopy(std::string value) {
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
			return static_cast<char>(std::tolower(ch));
		});
		return value;
	}

	std::string trimHexPrefix(std::string value) {
		if (value.size() > 2 && value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) {
			value.erase(0, 2);
		}
		return value;
	}

	bool matchesGscDumpFilter(std::uint16_t id, const char* name, const std::string& filterLower) {
		if (filterLower.empty()) {
			return true;
		}

		const std::string nameLower = toLowerCopy(name ? name : "");
		if (nameLower.find(filterLower) != std::string::npos) {
			return true;
		}

		std::ostringstream hexId;
		hexId << std::hex << std::nouppercase << id;
		return hexId.str().find(trimHexPrefix(filterLower)) != std::string::npos;
	}

	bool getGameModuleRange(std::uintptr_t& moduleStart, std::uintptr_t& moduleEnd) {
		moduleStart = CustomCommands::rawBase;
		if (!moduleStart) {
			return false;
		}

		const auto* dosHeader = reinterpret_cast<const IMAGE_DOS_HEADER*>(moduleStart);
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			return false;
		}

		const auto* ntHeaders = reinterpret_cast<const IMAGE_NT_HEADERS*>(moduleStart + dosHeader->e_lfanew);
		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
			return false;
		}

		moduleEnd = moduleStart + ntHeaders->OptionalHeader.SizeOfImage;
		return moduleEnd > moduleStart;
	}

	const char* getBuiltinTableName(std::uint16_t id) {
		return id >= GSC_HIGH_BUILTIN_BASE_ID ? "high" : "low";
	}

	std::uintptr_t getLowBuiltinTable() {
		return 0xAC9AE40_b; // qword_7FF6D722BE40
	}

	std::uintptr_t getHighBuiltinTable() {
		return 0xAC9CC70_b; // qword_7FF6D722DC70
	}

	bool resolveGscBuiltinAddress(std::uint16_t id, std::uintptr_t& address) {
		address = 0;

		if (id >= GSC_HIGH_BUILTIN_BASE_ID) {
			const std::size_t index = id - GSC_HIGH_BUILTIN_BASE_ID;
			if (index >= GSC_HIGH_BUILTIN_COUNT) {
				return false;
			}

			address = reinterpret_cast<const std::uintptr_t*>(getHighBuiltinTable())[index];
			return true;
		}

		if (id == 0) {
			return false;
		}

		const std::size_t index = id - 1;
		if (index >= GSC_LOW_BUILTIN_COUNT) {
			return false;
		}

		address = reinterpret_cast<const std::uintptr_t*>(getLowBuiltinTable())[index];
		return true;
	}

	std::string formatGscBuiltinAddress(std::uintptr_t address) {
		if (!address) {
			return "0x0";
		}

		std::ostringstream ss;
		ss << "0x" << std::uppercase << std::hex << std::setw(16) << std::setfill('0') << address;

		std::uintptr_t moduleStart = 0;
		std::uintptr_t moduleEnd = 0;
		if (getGameModuleRange(moduleStart, moduleEnd) && address >= CustomCommands::base && address < moduleEnd) {
			ss << " (0x" << std::uppercase << std::hex << (address - CustomCommands::base) << "_b)";
		}

		return ss.str();
	}

	void printGscBuiltinEntry(const char* kind, std::uint16_t id, const char* name, const std::string& filterLower, GscBuiltinDumpStats& stats) {
		if (!matchesGscDumpFilter(id, name, filterLower)) {
			return;
		}

		std::uintptr_t address = 0;
		const bool inRange = resolveGscBuiltinAddress(id, address);

		std::ostringstream line;
		line << kind << " 0x" << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << id;
		line << " " << (name ? name : "<null>");
		line << " [" << getBuiltinTableName(id) << "]";

		if (inRange) {
			line << " -> " << formatGscBuiltinAddress(address);
			if (address) {
				++stats.resolved;
			}
			else {
				++stats.nullAddress;
			}
		}
		else {
			line << " -> <no dispatch slot>";
			++stats.outOfRange;
		}

		++stats.printed;
		Console::print(line.str());
	}

	bool tryParseFloatArgument(const char* text, float& outValue) {
		if (!text || text[0] == '\0') {
			return false;
		}

		errno = 0;
		char* end = nullptr;
		const float value = std::strtof(text, &end);
		if (end == text || *end != '\0' || errno == ERANGE || !std::isfinite(value)) {
			return false;
		}

		outValue = value;
		return true;
	}
}


void CustomCommands::god(){
	if (!GameUtil::areWeHost()){
		Console::print("Must be host to use this command");
		return;
	}

	gentity_s* player = GameUtil::G_getLocalPlayer();
	if (!player){
		Console::print("Local player not found");
		return;
	}

	constexpr int FL_GODMODE = 1 << 0;

	player->flags ^= FL_GODMODE;

	const bool enabled = (player->flags & FL_GODMODE) != 0;
	const char* state = enabled ? "^2ON" : "^1OFF";

	Console::printf("God: %s", state);
	Functions::_SV_SendServerCommand(0, 0, "%c \"GOD: %s\"", 101, state);
}

void CustomCommands::notarget() {
	if (!GameUtil::areWeHost()) {
		Console::print("Must be host to use this command");
		return;
	}

	gentity_s* player = GameUtil::G_getLocalPlayer();
	if (!player) {
		Console::print("Local player not found");
		return;
	}

	constexpr int FL_NOTARGET = 4 << 0;

	player->flags ^= FL_NOTARGET;

	const bool enabled = (player->flags & FL_NOTARGET) != 0;
	const char* state = enabled ? "^2ON" : "^1OFF";

	Console::printf("Notarget: %s", state);
	Functions::_SV_SendServerCommand(0, 0, "%c \"Notarget: %s\"", 101, state);
}

void CustomCommands::demigod() {
	if (!GameUtil::areWeHost()) {
		Console::print("Must be host to use this command");
		return;
	}

	gentity_s* player = GameUtil::G_getLocalPlayer();
	if (!player) {
		Console::print("Local player not found");
		return;
	}

	constexpr int FL_DEMIGOD = 2 << 0;

	player->flags ^= FL_DEMIGOD;

	const bool enabled = (player->flags & FL_DEMIGOD) != 0;
	const char* state = enabled ? "^2ON" : "^1OFF";

	Console::printf("Demigod: %s", state);
	Functions::_SV_SendServerCommand(0, 0, "%c \"Demigod: %s\"", 101, state);
}

void CustomCommands::setViewPos() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count != 4) {
		Console::printf("Usage: setviewpos <x> <y> <z>");
		return;
	}

	if (!GameUtil::areWeHost()) {
		Console::print("Must be host to use this command");
		return;
	}

	gentity_s* player = GameUtil::G_getLocalPlayer();
	if (!player) {
		Console::print("Local player not found");
		return;
	}

	const char** args = cmdArgs->argv[nest];
	if (!args) {
		Console::printf("Usage: setviewpos <x> <y> <z>");
		return;
	}

	std::array<float, 3> origin{};
	for (std::size_t i = 0; i < origin.size(); ++i) {
		if (!tryParseFloatArgument(args[i + 1], origin[i])) {
			Console::printf("Invalid coordinate '%s'. Usage: setviewpos <x> <y> <z>", args[i + 1] ? args[i + 1] : "<null>");
			return;
		}
	}

	Functions::_G_SetOrigin(player, origin.data());
	Console::printf("Set origin to %.2f %.2f %.2f", origin[0], origin[1], origin[2]);
}

void CustomCommands::getCmdFuncAddr() {
	cmd_function_s* cmd = *(cmd_function_s**)0xAA752C8_b;

	while (cmd) {
		if (IsBadReadPtr(cmd, sizeof(cmd_function_s))) {
			break;
		}

		if (cmd->name && !IsBadStringPtrA(cmd->name, 64)) {
			std::ostringstream ss;

			ss << cmd->name << " -> ";
			ss << "0x" << std::hex << std::uppercase << reinterpret_cast<uintptr_t>(cmd->function);

			Console::print(ss.str());
		}

		cmd = cmd->next;
	}
}

void CustomCommands::dumpGscFunctions() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();

	bool dumpFunctions = true;
	bool dumpMethods = true;
	std::string filter;

	if (cmdArgs) {
		const int nest = cmdArgs->nesting;
		const int count = cmdArgs->argc[nest];
		const char** args = cmdArgs->argv[nest];

		if (count >= 2 && args[1]) {
			const std::string mode = toLowerCopy(args[1]);
			if (mode == "help" || mode == "?") {
				Console::print("Usage: dumpgscfuncs [functions|methods] [name_or_id_filter]");
				Console::print("Examples: dumpgscfuncs, dumpgscfuncs methods enableplayeruse, dumpgscfuncs 800c");
				return;
			}

			if (mode == "func" || mode == "funcs" || mode == "function" || mode == "functions") {
				dumpMethods = false;
				if (count >= 3 && args[2]) {
					filter = args[2];
				}
			}
			else if (mode == "meth" || mode == "meths" || mode == "method" || mode == "methods") {
				dumpFunctions = false;
				if (count >= 3 && args[2]) {
					filter = args[2];
				}
			}
			else {
				filter = args[1];
			}
		}
	}

	if (IsBadReadPtr(reinterpret_cast<const void*>(getLowBuiltinTable()), GSC_LOW_BUILTIN_COUNT * sizeof(std::uintptr_t)) ||
		IsBadReadPtr(reinterpret_cast<const void*>(getHighBuiltinTable()), GSC_HIGH_BUILTIN_COUNT * sizeof(std::uintptr_t))) {
		Console::print("GSC builtin dispatch tables are not readable.");
		return;
	}

	const std::string filterLower = toLowerCopy(filter);
	GscBuiltinDumpStats stats{};

	Console::printf(
		"GSC builtin tables: low=%s entries=%zu, high=%s entries=%zu",
		formatGscBuiltinAddress(getLowBuiltinTable()).c_str(),
		GSC_LOW_BUILTIN_COUNT,
		formatGscBuiltinAddress(getHighBuiltinTable()).c_str(),
		GSC_HIGH_BUILTIN_COUNT);

	if (!filter.empty()) {
		Console::printf("GSC builtin dump filter: %s", filter.c_str());
	}

	if (dumpFunctions) {
		for (const auto& entry : xsk::gsc::s2::func_list) {
			printGscBuiltinEntry("func", entry.first, entry.second, filterLower, stats);
		}
	}

	if (dumpMethods) {
		for (const auto& entry : xsk::gsc::s2::meth_list) {
			printGscBuiltinEntry("meth", entry.first, entry.second, filterLower, stats);
		}
	}

	if (stats.printed == 0) {
		Console::print("No GSC builtins matched the requested filter.");
		return;
	}

	std::ostringstream summary;
	summary << "GSC builtin dump complete: printed=" << stats.printed;
	summary << " resolved=" << stats.resolved;
	summary << " null=" << stats.nullAddress;
	summary << " out_of_range=" << stats.outOfRange;
	Console::print(summary.str());

	if (stats.resolved == 0 && stats.nullAddress > 0) {
		Console::print("No builtin addresses were resolved. The dispatch tables may not be initialized yet; load into a lobby or game and run the command again.");
	}
}

void CustomCommands::dumpAllScriptFiles() {
	AssetPoolStats stats = GameUtil::assetPoolTraverseHelper(ASSET_TYPE_SCRIPTFILE,
		[](XAsset* asset, const char* name) -> bool {
			ScriptLoader::dumpScript(asset->header.script);
			return true; //keep traversing
		});

	Console::printf("Dumped %u GSC files", stats.count);
}

void CustomCommands::dumpAllLuaFiles() {
	AssetPoolStats stats = GameUtil::assetPoolTraverseHelper(ASSET_TYPE_LUA_FILE,
		[](XAsset* asset, const char* name) -> bool {
			LuiLoader::dumpLuaFile(asset->header.luafile);
			return true;
		});

	Console::printf("Dumped %u lua files", stats.count);
}

void CustomCommands::dumpAllCSVFiles() {
	AssetPoolStats stats = GameUtil::assetPoolTraverseHelper(ASSET_TYPE_STRINGTABLE,
		[](XAsset* asset, const char* name) -> bool {
			StringTableLoader::dump(asset->header.table);
			return true;
		});

	Console::printf("Dumped %u stringtables", stats.count);
}

void DB_ListAssetPool(XAssetType targetType, bool saveToFile) {
	auto g_assetNames = (const char**)0xF88A60_b;

	if (targetType > ASSET_TYPE_DLOGROUTES) {
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

	AssetPoolStats stats = GameUtil::assetPoolTraverseHelper(targetType,
		[&](XAsset* asset, const char* assetName) -> bool {
			if (saveToFile) {
				outFile << assetName << '\n';
			}
			else {
				Console::printf("%s", assetName);
			}
			return true;
		});

	if (saveToFile) {
		outFile.close();
		Console::printf("Saved %u assets in %s pool to file.", stats.count, typeName);
	}
	else {
		Console::printf("Total of %u assets in %s pool", stats.count, typeName);
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

	DB_ListAssetPool((XAssetType)type, false);
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

	DB_ListAssetPool((XAssetType)type, true);
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

	Hook::create("LiveStorage_IsItemUnlockedFromTable", 0xCFB10_b, &returnUnlocked, &_LiveStorage_IsItemUnlockedFromTable);

	Hook::create("LiveStorage_GetItemLockStatus", 0xCE850_b, &returnUnlocked, &_LiveStorage_GetItemLockStatus);

	Hook::create("GetIsItemUnlockedStr", 0x73E9F0_b, &hook_GetIsItemUnlockedStr, &_GetIsItemUnlockedStr);

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

	int* sv_migrate = (int*)0xBB4EE68_b;
	*sv_migrate = count >= 3 ? GameUtil::safeStringToInt(cmdArgs->argv[nest][2]) : 0;
	
	Functions::_SV_StartMap(LOCAL_CLIENT_0, cmdArgs->argv[nest][1], isMapPreloaded);
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

void CustomCommands::dropWeapon() {

}

void CustomCommands::give() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count != 2) {
		Console::print("Usage: give <item>");
		return;
	}

	if (!GameUtil::areWeHost()) { //yeah not ideal but good enough for testing and preventing crash
		Console::print("Must be host to use give command"); 
		return;
	}

	gentity_s* spawned = Functions::_G_Spawn();
	if (!spawned) {
		DEV_PRINTF("G_Spawn() failed in function: %s", __FUNCTION__);
		return;
	}

	float pos[3];

	if (!GameUtil::getPlayerPosition(pos)) {
		DEV_PRINTF("getPlayerPosition failed in function: %s", __FUNCTION__);
		return;
	}
	pos[2] += 10;
	Functions::_G_SetOrigin(spawned, pos);

	DEV_PRINTF("Giving weapon %s", cmdArgs->argv[nest][1]);

	Weapon weapon{}; //not used since we use result
	Weapon* result = Functions::_G_GetWeaponForName(&weapon, cmdArgs->argv[nest][1]);

	if (!result) {
		DEV_PRINTF("G_GetWeaponForName() failed in function: %s", __FUNCTION__);
		return;
	}

	//going to take the weapon first
	void* player0 = reinterpret_cast<void*>(0x9ED3430_b);
	Functions::_G_TakePlayerWeapon(Functions::_G_GetEntityPlayerState(player0), result);

	Functions::_G_SpawnItem(spawned, result);
	spawned->autoPickupFlag = 1;
	Functions::_Touch_Item(spawned, player0, 0, 0);
	spawned->autoPickupFlag = 0;

	//TODO: add alt+ check
	Functions::_Add_Ammo(Functions::_G_GetEntityPlayerState(player0), result, false, 998, 1);
}

void CustomCommands::modelviewer() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	if (count != 2) {
		Console::print("Usage: modelviewer <modelname>");
		return;
	}
	if (!GameUtil::areWeHost()) { //yeah not ideal but good enough for testing and preventing crash
		Console::print("Must be host to use give command");
		return;
	}
	gentity_s* spawned = Functions::_G_Spawn();
	if (!spawned) {
		DEV_PRINTF("G_Spawn() failed in function: %s", __FUNCTION__);
		return;
	}
	float pos[3];
	GameUtil::getPlayerPosition(pos);
	pos[2] += 20;
	Functions::_G_SetOrigin(spawned, pos);
	Functions::_G_SetModel(spawned, cmdArgs->argv[nest][1]);
	Functions::_G_DObjUpdate(spawned, 1);
	DEV_PRINTF("spawned gentity address: %p", (void*)spawned);
}

void CustomCommands::none() {

}
