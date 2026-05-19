#include "pch.h"
#include "Binds.hpp"
#include "GameUtil.hpp"
#include "Console.hpp"
#include "DvarInterface.hpp"
#include <array>
#include <cstdint>
#include <cstring>

namespace {
	constexpr char CUSTOM_BIND_FILE_MAGIC[4] = { 'S', '2', 'C', 'B' };
	constexpr std::uint32_t CUSTOM_BIND_FILE_VERSION = 1;
	constexpr std::size_t MAX_CUSTOM_BIND_COUNT = 256;
	constexpr std::uint32_t MAX_CUSTOM_COMMAND_LENGTH = 4096;

	struct CustomBindFileHeader {
		char magic[4];
		std::uint32_t version;
		std::uint32_t bindCount;
	};

	struct CustomBindFileRecordHeader {
		std::uint32_t keyNum;
		std::uint32_t commandLength;
	};

	std::array<std::string, MAX_CUSTOM_BIND_COUNT> g_customBinds;

	int normalizeKeyNum(int keyNum) {
		if (keyNum < 0) {
			return -1;
		}

		if (keyNum <= 0xFF) {
			return std::tolower(static_cast<unsigned char>(keyNum));
		}

		return keyNum;
	}

	bool isValidCustomBindKey(int keyNum) {
		return keyNum >= 0 && keyNum < static_cast<int>(g_customBinds.size());
	}

	void clearCustomBinds() {
		for (std::string& bindCommand : g_customBinds) {
			bindCommand.clear();
		}
	}

	std::uint32_t getCustomBindCount() {
		std::uint32_t bindCount = 0;
		for (const std::string& bindCommand : g_customBinds) {
			if (!bindCommand.empty()) {
				++bindCount;
			}
		}

		return bindCount;
	}

	std::filesystem::path getCustomBindFilePath() {
		const char* cwd = Functions::_Sys_Cwd ? Functions::_Sys_Cwd() : nullptr;
		const std::filesystem::path basePath = (cwd && *cwd) ? std::filesystem::path(cwd) : std::filesystem::current_path();
		return basePath / "players2" / "s2mp_custom_binds.dat";
	}

	bool saveCustomBindsToFile() {
		const std::filesystem::path bindFilePath = getCustomBindFilePath();

		std::error_code createDirsError;
		std::filesystem::create_directories(bindFilePath.parent_path(), createDirsError);
		if (createDirsError) {
			Console::printf("Failed to create custom bind folder: %s", bindFilePath.parent_path().string().c_str());
			return false;
		}

		std::ofstream bindFile(bindFilePath, std::ios::binary | std::ios::trunc);
		if (!bindFile.is_open()) {
			Console::printf("Failed to open custom bind file for write: %s", bindFilePath.string().c_str());
			return false;
		}

		CustomBindFileHeader fileHeader{};
		std::memcpy(fileHeader.magic, CUSTOM_BIND_FILE_MAGIC, sizeof(fileHeader.magic));
		fileHeader.version = CUSTOM_BIND_FILE_VERSION;
		fileHeader.bindCount = getCustomBindCount();

		bindFile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));

		for (std::uint32_t keyNum = 0; keyNum < g_customBinds.size(); ++keyNum) {
			const std::string& bindCommand = g_customBinds[keyNum];
			if (bindCommand.empty()) {
				continue;
			}

			CustomBindFileRecordHeader recordHeader{};
			recordHeader.keyNum = keyNum;
			recordHeader.commandLength = static_cast<std::uint32_t>(bindCommand.size());

			bindFile.write(reinterpret_cast<const char*>(&recordHeader), sizeof(recordHeader));
			bindFile.write(bindCommand.data(), static_cast<std::streamsize>(bindCommand.size()));
		}

		if (!bindFile.good()) {
			Console::printf("Failed to finish writing custom bind file: %s", bindFilePath.string().c_str());
			return false;
		}

		return true;
	}

	bool loadCustomBindsFromFile() {
		clearCustomBinds();

		const std::filesystem::path bindFilePath = getCustomBindFilePath();
		std::ifstream bindFile(bindFilePath, std::ios::binary);
		if (!bindFile.is_open()) {
			return false;
		}

		CustomBindFileHeader fileHeader{};
		bindFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
		if (!bindFile) {
			Console::printf("Custom bind file is truncated: %s", bindFilePath.string().c_str());
			return false;
		}

		if (std::memcmp(fileHeader.magic, CUSTOM_BIND_FILE_MAGIC, sizeof(fileHeader.magic)) != 0) {
			Console::printf("Custom bind file has an invalid header: %s", bindFilePath.string().c_str());
			return false;
		}

		if (fileHeader.version != CUSTOM_BIND_FILE_VERSION) {
			Console::printf("Custom bind file version mismatch (%u): %s", fileHeader.version, bindFilePath.string().c_str());
			return false;
		}

		for (std::uint32_t bindIndex = 0; bindIndex < fileHeader.bindCount; ++bindIndex) {
			CustomBindFileRecordHeader recordHeader{};
			bindFile.read(reinterpret_cast<char*>(&recordHeader), sizeof(recordHeader));
			if (!bindFile) {
				clearCustomBinds();
				Console::printf("Custom bind file record header is truncated: %s", bindFilePath.string().c_str());
				return false;
			}

			if (recordHeader.commandLength == 0 || recordHeader.commandLength > MAX_CUSTOM_COMMAND_LENGTH) {
				clearCustomBinds();
				Console::printf("Custom bind file has an invalid command length: %s", bindFilePath.string().c_str());
				return false;
			}

			std::string bindCommand(recordHeader.commandLength, '\0');
			bindFile.read(bindCommand.data(), static_cast<std::streamsize>(bindCommand.size()));
			if (!bindFile) {
				clearCustomBinds();
				Console::printf("Custom bind file command data is truncated: %s", bindFilePath.string().c_str());
				return false;
			}

			if (!isValidCustomBindKey(static_cast<int>(recordHeader.keyNum))) {
				continue;
			}

			g_customBinds[recordHeader.keyNum] = std::move(bindCommand);
			Functions::_Key_SetBinding(LOCAL_CLIENT_0, static_cast<int>(recordHeader.keyNum), 0);
		}

		return true;
	}
}

//this function is fired on every key input from the hook_CL_KeyEvent in InternalConsole.cpp
//so most keys wont be a bind and will do nothing
void Binds::execBindForKey(int keyNum, int down) {
	if (!down) {
		return;
	}

	const int normalizedKeyNum = normalizeKeyNum(keyNum);
	if (!isValidCustomBindKey(normalizedKeyNum)) {
		return;
	}

	const std::string& cmd = g_customBinds[normalizedKeyNum];
	if (cmd.empty()) {
		return;
	}

	std::string translatedCmd = cmd;
	if (DvarInterface::setProtectedDvarFromPrefixedCommand(translatedCmd)) {
		return;
	}

	if (DvarInterface::translatePrefixedCommand(translatedCmd)) {
		GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, translatedCmd);
		return;
	}

	std::vector<std::string> parsedCmd = Console::parseCmdToVec(cmd);
	if (!parsedCmd.empty()) {
		std::string dvarName = parsedCmd[0];
		if (DvarInterface::setDvar(dvarName, parsedCmd)) {
			return;
		}
	}

	GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, cmd);
}

void Binds::setupCustomBindFromCmd(int keyNum, const char* command) {
	if (!strcmp(command, "toggleconsole")) { //this keeps getting sent in 
		return;
	}
	const int normalizedKeyNum = normalizeKeyNum(keyNum);
	if (!isValidCustomBindKey(normalizedKeyNum)) {
		Console::printf("Cannot bind invalid key %d", keyNum);
		return;
	}

	const std::string bindCommand = command ? command : "";
	if (bindCommand.empty() || GameUtil::isOnlyWhitespace(bindCommand)) {
		Binds::unbindCustomBind(normalizedKeyNum);
		return;
	}

	Functions::_Key_SetBinding(LOCAL_CLIENT_0, normalizedKeyNum, 0);
	g_customBinds[normalizedKeyNum] = bindCommand;

	if (!saveCustomBindsToFile()) {
		Console::print("Failed to save custom keybind");
	}
}

void Binds::unbindCustomBind(int keyNum) {
	const int normalizedKeyNum = normalizeKeyNum(keyNum);
	if (!isValidCustomBindKey(normalizedKeyNum)) {
		return;
	}

	if (g_customBinds[normalizedKeyNum].empty()) {
		return;
	}

	g_customBinds[normalizedKeyNum].clear();
	if (!saveCustomBindsToFile()) {
		Console::print("Failed to save custom keybind removal");
	}
}


void Binds::bindCmd() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	const char** args = cmdArgs->argv[nest];

	if (count >= 2) {
		int keynum = Functions::_Key_StringToKeynum(args[1]);
		if (keynum != -1) {
			int properKeynum = normalizeKeyNum(keynum);
			if (count != 2 && (*(uint8_t*)(0x8B8FF54_b + 5036) & 2) == 0) {
				int bindingForCommand = Functions::_Key_GetBindingForCommand(args[2]);
				if (bindingForCommand) {
					Binds::unbindCustomBind(properKeynum);
					Functions::_Key_SetBinding(LOCAL_CLIENT_0, properKeynum, bindingForCommand);
				}
				else {
					//do custom commands here
					Console::print("Setting up custom keybind");
					Binds::setupCustomBindFromCmd(properKeynum, args[2]);
				}
			}
			else {
				Console::print("Bind not allowed");
			}
		}
		else {
			Console::printf("\"%s\" isn't a valid key", args[1]);
		}
	}
	else {
		Console::printf("bind <key> [command] : attach a command to a key");
	}
}

void Binds::unbindCmd() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	const char** args = cmdArgs->argv[nest];

	if (count == 2) {
		int keynum = Functions::_Key_StringToKeynum(args[1]);
		if (keynum != -1) {
			int properKeynum = normalizeKeyNum(keynum);
			Functions::_Key_SetBinding(LOCAL_CLIENT_0, properKeynum, 0);
			Binds::unbindCustomBind(properKeynum);
		}
		else {
			Console::printf("\"%s\" isn't a valid key", args[1]);
		}
	}
	else {
		Console::print("unbind <key> : remove commands from a key");
	}	
}

void Binds::unbindAllCmd() {
	for (int i = 0; i < 256; ++i) {
		Functions::_Key_SetBinding(LOCAL_CLIENT_0, i, 0);
		g_customBinds[i].clear();
	}

	if (!saveCustomBindsToFile()) {
		Console::print("Failed to save cleared custom binds");
	}
}

void Binds::init() {
	loadCustomBindsFromFile();
}
