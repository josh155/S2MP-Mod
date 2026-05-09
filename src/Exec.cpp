#include "pch.h"
#include "Exec.hpp"
#include "GameUtil.hpp"
#include "Console.hpp"
#include "FuncPointers.h"

#include <sstream>
#include <unordered_set>
#include <zlib.h>
#include <DevDef.h>

namespace {
	std::unordered_set<std::string> g_activeExecFiles;

	std::string trimLine(const std::string& line) {
		const std::size_t first = line.find_first_not_of(" \t\r\n");
		if (first == std::string::npos) {
			return "";
		}

		const std::size_t last = line.find_last_not_of(" \t\r\n");
		return line.substr(first, last - first + 1);
	}

	std::filesystem::path getPlayers2Path() {
		const char* cwd = Functions::_Sys_Cwd ? Functions::_Sys_Cwd() : nullptr;
		const std::filesystem::path basePath = (cwd && *cwd) ? std::filesystem::path(cwd) : std::filesystem::current_path();
		return basePath / "players2";
	}

	std::string normalizeCfgFilename(const std::string& rawFilename) {
		const std::string trimmedName = trimLine(rawFilename);
		if (trimmedName.empty()) {
			return "";
		}

		const std::filesystem::path filePath = std::filesystem::path(trimmedName).lexically_normal();
		if (filePath.empty() || filePath.is_absolute() || filePath.has_root_name()) {
			return "";
		}

		for (const auto& part : filePath) {
			if (part == "..") {
				return "";
			}
		}

		std::string normalizedName = filePath.generic_string();
		if (!GameUtil::toLower(normalizedName).ends_with(".cfg")) {
			normalizedName += ".cfg";
		}

		return normalizedName;
	}

	bool readBinaryFile(const std::filesystem::path& filePath, std::vector<std::uint8_t>& outData) {
		std::ifstream file(filePath, std::ios::binary);
		if (!file.is_open()) {
			return false;
		}

		file.seekg(0, std::ios::end);
		const std::streamoff fileSize = file.tellg();
		if (fileSize < 0) {
			return false;
		}

		file.seekg(0, std::ios::beg);
		outData.resize(static_cast<std::size_t>(fileSize));

		if (!outData.empty()) {
			file.read(reinterpret_cast<char*>(outData.data()), static_cast<std::streamsize>(outData.size()));
		}

		return file.good() || file.eof();
	}

	bool readRawFileAsset(const std::string& assetName, std::vector<std::uint8_t>& outData) {
		if (!Functions::_DB_FindXAssetHeader) {
			return false;
		}

		RawFile* rawFile = Functions::_DB_FindXAssetHeader(ASSET_TYPE_RAWFILE, assetName.c_str(), 0).rawfile;
		if (!rawFile || !rawFile->buffer) {
			return false;
		}

		if (rawFile->len > 0 && rawFile->compressedLen > 0) {
			outData.resize(static_cast<std::size_t>(rawFile->len));

			z_stream strm{};
			strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(rawFile->buffer));
			strm.avail_in = static_cast<uInt>(rawFile->compressedLen);
			strm.next_out = outData.data();
			strm.avail_out = static_cast<uInt>(outData.size());

			int ret = inflateInit(&strm);
			if (ret == Z_OK) {
				ret = inflate(&strm, Z_FINISH);
				if (ret == Z_STREAM_END || ret == Z_OK) {
					outData.resize(strm.total_out);
					inflateEnd(&strm);
					return true;
				}
				inflateEnd(&strm);
			}

			outData.clear();
		}

		const int rawSize = rawFile->compressedLen > 0 ? rawFile->compressedLen : rawFile->len;
		if (rawSize <= 0) {
			return false;
		}

		outData.resize(static_cast<std::size_t>(rawSize));
		std::memcpy(outData.data(), rawFile->buffer, outData.size());
		return true;
	}

	bool executeCfgFile(const std::string& rawFilename);

	void executeCfgText(const std::string& cfgText) {
		std::istringstream cfgStream(cfgText);
		std::string line;
		bool isFirstLine = true;

		while (std::getline(cfgStream, line)) {
			if (!line.empty() && line.back() == '\r') {
				line.pop_back();
			}

			if (isFirstLine && line.size() >= 3
				&& static_cast<unsigned char>(line[0]) == 0xEF
				&& static_cast<unsigned char>(line[1]) == 0xBB
				&& static_cast<unsigned char>(line[2]) == 0xBF) {
				line.erase(0, 3);
			}
			isFirstLine = false;

			const std::string trimmedLine = trimLine(line);
			if (trimmedLine.empty() || trimmedLine.rfind("//", 0) == 0) {
				continue;
			}

			std::vector<std::string> parsedLine = Console::parseCmdToVec(trimmedLine);
			if (!parsedLine.empty()) {
				std::string commandName = GameUtil::toLower(parsedLine[0]);
				if (commandName == "exec" && parsedLine.size() == 2) {
					executeCfgFile(parsedLine[1]);
					continue;
				}
			}

			Console::execCmd(trimmedLine);
		}
	}

	bool executeCfgFile(const std::string& rawFilename) {
		const std::string cfgFilename = normalizeCfgFilename(rawFilename);
		if (cfgFilename.empty()) {
			Console::print("exec <filename> : execute a cfg file from players2");
			return false;
		}

		const std::filesystem::path cfgFilePath = (getPlayers2Path() / cfgFilename).lexically_normal();
		const std::string normalizedExecPath = cfgFilePath.generic_string();
		if (g_activeExecFiles.contains(normalizedExecPath)) {
			Console::printf("Prevented recursive exec of cfg file: %s", cfgFilename.c_str());
			return false;
		}

		struct ExecScopeGuard {
			std::unordered_set<std::string>* activeExecFiles = nullptr;
			std::string normalizedPath;

			~ExecScopeGuard() {
				if (activeExecFiles) {
					activeExecFiles->erase(normalizedPath);
				}
			}
		};

		g_activeExecFiles.insert(normalizedExecPath);
		ExecScopeGuard execScopeGuard{ &g_activeExecFiles, normalizedExecPath };

		if (GameUtil::toLower(cfgFilename) == "system_config_mp.cfg") {
			Console::printf("Encrypted cfg not supported yet: %s", cfgFilename.c_str());
			return false;
		}

		std::vector<std::uint8_t> cfgData;
		if (!readBinaryFile(cfgFilePath, cfgData)) {
			if (!readRawFileAsset(cfgFilename, cfgData)) {
				Console::printf("Could not open cfg file: %s", cfgFilename.c_str());
				return false;
			}
		}

		while (!cfgData.empty() && cfgData.back() == '\0') {
			cfgData.pop_back();
		}

		const std::string cfgText(reinterpret_cast<const char*>(cfgData.data()), cfgData.size());
		executeCfgText(cfgText);
		return true;
	}
}

void Exec::init() {
	const std::filesystem::path players2Path = getPlayers2Path();
	const std::filesystem::path autoexecPath = players2Path / "autoexec.cfg";

	std::error_code createDirsError;
	std::filesystem::create_directories(players2Path, createDirsError);
	if (createDirsError) {
		Console::printf("Failed to create players2 folder for autoexec: %s", players2Path.string().c_str());
		return;
	}

	if (std::filesystem::exists(autoexecPath)) {
		return;
	}

	std::ofstream autoexecFile(autoexecPath, std::ios::out | std::ios::trunc);
	if (!autoexecFile.is_open()) {
		Console::printf("Failed to create autoexec.cfg: %s", autoexecPath.string().c_str());
		return;
	}

	autoexecFile << "// put dvars and commands here to execute each time the game starts\n";
}

void Exec::execCmd() {
	CmdArgs* cmdArgs = GameUtil::getCmdArgs();
	if (!cmdArgs) {
		return;
	}

	int nest = cmdArgs->nesting;
	int count = cmdArgs->argc[nest];
	const char** args = cmdArgs->argv[nest];

	if (count != 2) {
		Console::print("exec <filename> : execute a cfg file from players2");
		return;
	}
	executeCfgFile(args[1] ? args[1] : "");
}
