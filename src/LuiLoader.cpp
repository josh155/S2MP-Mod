#include "pch.h"
#include "LuiLoader.hpp"
#include "Console.hpp"
#include "DevDef.h"
#include "FuncPointers.h"
#include "Hook.hpp"
#include <filesystem>
#include <fstream>
#include <memory>
#include <unordered_map>

namespace {
	struct CustomLuaAsset {
		std::string assetName;
		std::vector<std::uint8_t> sourceBuffer;
		LuaFile luaFile{};
	};

	using HksLoadHook = int(*)(void* state, void* compilerOptions, void* reader, void* readerData, const char* chunkName);
	using LuiCodInitHook = void(*)(bool frontend, bool immediate);
	using LuiCodShutdownHook = void(*)();
	using LoadLuaFileAssetHook = void(__fastcall*)(LuaFile** luaFile);

	HksLoadHook s_originalHksLoad = nullptr;
	LuiCodInitHook s_originalLuiCodInit = nullptr;
	LuiCodShutdownHook s_originalLuiCodShutdown = nullptr;
	LoadLuaFileAssetHook s_originalLoadLuaFileAsset = nullptr;

	std::unordered_map<std::string, std::unique_ptr<CustomLuaAsset>> g_customLuaAssets;

	std::filesystem::path getModRootPath() {
		const char* cwd = Functions::_Sys_Cwd ? Functions::_Sys_Cwd() : nullptr;
		const std::filesystem::path basePath = (cwd && *cwd) ? std::filesystem::path(cwd) : std::filesystem::current_path();
		return basePath / "S2MP-Mod";
	}

	std::string normalizeLuaAssetName(const char* name) {
		if (!name || !*name) {
			return {};
		}

		std::filesystem::path assetPath(name);
		assetPath = assetPath.lexically_normal();

		if (assetPath.empty() || assetPath.is_absolute() || assetPath.has_root_name() || assetPath.has_root_directory()) {
			return {};
		}

		for (const auto& part : assetPath) {
			if (part == "..") {
				return {};
			}
		}

		if (!assetPath.has_extension()) {
			assetPath += ".lua";
		}

		return assetPath.generic_string();
	}

	std::filesystem::path getCustomLuaPath(const std::string& assetName) {
		return (getModRootPath() / std::filesystem::path(assetName)).lexically_normal();
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

	void clearCustomLuaAssets() {
		g_customLuaAssets.clear();
	}

	CustomLuaAsset* findCustomLuaAsset(const std::string& assetName) {
		const auto existing = g_customLuaAssets.find(assetName);
		return existing != g_customLuaAssets.end() ? existing->second.get() : nullptr;
	}

	CustomLuaAsset* findCustomLuaAssetByChunkName(const char* chunkName) {
		if (!chunkName || !*chunkName) {
			return nullptr;
		}

		const char* normalizedChunkName = chunkName;
		if (*normalizedChunkName == '@' || *normalizedChunkName == '=') {
			++normalizedChunkName;
		}

		const std::string assetName = normalizeLuaAssetName(normalizedChunkName);
		if (assetName.empty()) {
			return nullptr;
		}

		return findCustomLuaAsset(assetName);
	}

	bool isDumpEnabled() {
		dvar_t* dumpDvar = Functions::_Dvar_FindVar ? Functions::_Dvar_FindVar("g_dumpLui") : nullptr;
		return dumpDvar && dumpDvar->current.enabled;
	}

	HksGlobal* getHksGlobal(void* state) {
		if (!state) {
			return nullptr;
		}

		lua_State* luaState = reinterpret_cast<lua_State*>(state);
		return luaState->global;
	}

	CustomLuaAsset* findOrCreateCustomLuaAsset(const std::string& assetName) {
		const auto existing = g_customLuaAssets.find(assetName);
		if (existing != g_customLuaAssets.end()) {
			return existing->second.get();
		}

		const std::filesystem::path filePath = getCustomLuaPath(assetName);
		if (!std::filesystem::exists(filePath)) {
			return nullptr;
		}

		auto customAsset = std::make_unique<CustomLuaAsset>();
		customAsset->assetName = assetName;

		if (!readBinaryFile(filePath, customAsset->sourceBuffer)) {
			Console::printf("Failed to read custom Lua file: %s", filePath.string().c_str());
			return nullptr;
		}

		const int luaLength = static_cast<int>(customAsset->sourceBuffer.size());

		customAsset->sourceBuffer.push_back(0);

		customAsset->luaFile.name = customAsset->assetName.c_str();
		customAsset->luaFile.len = luaLength;
		customAsset->luaFile.strippingType = 0;
		customAsset->luaFile.buffer = customAsset->sourceBuffer.data();

		CustomLuaAsset* assetPtr = customAsset.get();
		g_customLuaAssets.emplace(assetName, std::move(customAsset));

		Console::printf("Loaded custom Lua file: %s", filePath.string().c_str());
		return assetPtr;
	}

	void __fastcall loadLuaFileAssetHook(LuaFile** luaFile) {
		if (luaFile && *luaFile && isDumpEnabled()) {
			LuiLoader::dumpLuaFile(*luaFile);
		}

		if (s_originalLoadLuaFileAsset) {
			s_originalLoadLuaFileAsset(luaFile);
		}
	}

	int hksLoadHook(void* state, void* compilerOptions, void* reader, void* readerData, const char* chunkName) {
		HksGlobal* global = getHksGlobal(state);
		const HksBytecodeSharingMode originalGlobalMode = global ? global->m_bytecodeSharingMode : HKS_BYTECODE_SHARING_OFF;
		const HksBytecodeSharingMode originalCompilerMode = global ? global->m_compilerSettings.m_bytecodeSharingMode : HKS_BYTECODE_SHARING_OFF;
		CustomLuaAsset* customAsset = findCustomLuaAssetByChunkName(chunkName);

		if (global) {
			// Keep both runtime and compiler settings aligned while custom Lua source is loaded.
			global->m_bytecodeSharingMode = HKS_BYTECODE_SHARING_ON;
			global->m_compilerSettings.m_bytecodeSharingMode = HKS_BYTECODE_SHARING_ON;
		}

		int result = 0;
		if (customAsset && Functions::_hksi_hksL_loadbuffer) {
			result = Functions::_hksi_hksL_loadbuffer(
				state,
				compilerOptions,
				reinterpret_cast<const char*>(customAsset->sourceBuffer.data()),
				static_cast<unsigned __int64>(customAsset->luaFile.len),
				chunkName
			);
		}
		else {
			result = s_originalHksLoad
				? s_originalHksLoad(state, compilerOptions, reader, readerData, chunkName)
				: 0;
		}

		if (result != 0) {
			Console::printf(
				"hks_load failed for chunk '%s' with code %d",
				chunkName ? chunkName : "<null>",
				result
			);
		}

		if (global) {
			global->m_bytecodeSharingMode = originalGlobalMode;
			global->m_compilerSettings.m_bytecodeSharingMode = originalCompilerMode;
		}

		return result;
	}

	void luiCodInitHook(bool frontend, bool immediate) {
		clearCustomLuaAssets();

		if (s_originalLuiCodInit) {
			s_originalLuiCodInit(frontend, immediate);
		}
	}

	void luiCodShutdownHook() {
		if (s_originalLuiCodShutdown) {
			s_originalLuiCodShutdown();
		}

		clearCustomLuaAssets();
	}
}

void LuiLoader::dumpLuaFile(const LuaFile* luaFile) {
	if (!luaFile || !luaFile->name || !luaFile->buffer || luaFile->len <= 0) {
		Console::printf("Invalid LuaFile passed to %s", __FUNCTION__);
		return;
	}

	const std::string normalizedName = normalizeLuaAssetName(luaFile->name);
	if (normalizedName.empty()) {
		Console::printf("Refused to dump LuaFile with invalid path: %s", luaFile->name);
		return;
	}

	const std::filesystem::path filePath = getModRootPath() / "dump" / normalizedName;
	std::filesystem::create_directories(filePath.parent_path());

	try {
		std::ofstream out(filePath, std::ios::binary);
		if (!out.is_open()) {
			DEV_PRINTF("Failed to open file for writing: %s", filePath.string().c_str());
			return;
		}

		out.write(reinterpret_cast<const char*>(luaFile->buffer), luaFile->len);
		out.close();

		DEV_PRINTF("Dumped LuaFile to: %s", filePath.string().c_str());
	}
	catch (const std::exception& e) {
		DEV_PRINTF("Exception during LuaFile dump: %s", e.what());
	}
}

bool LuiLoader::FindXAssetHeader(XAssetType type, const char* name, int allow_create_default, XAssetHeader& header) {
	(void)allow_create_default;

	if (type != ASSET_TYPE_LUA_FILE) {
		return false;
	}

	return LUI_CoD_GetRawFile(header, name);
}

bool LuiLoader::LUI_CoD_GetRawFile(XAssetHeader& header, const char* name) {
	const std::string normalizedName = normalizeLuaAssetName(name);
	if (normalizedName.empty()) {
		return false;
	}

	CustomLuaAsset* customAsset = findOrCreateCustomLuaAsset(normalizedName);
	if (!customAsset) {
		return false;
	}

	header.luafile = &customAsset->luaFile;
	return true;
}

void LuiLoader::init() {
	clearCustomLuaAssets();
	Hook::create("Load_LuaFileAsset", reinterpret_cast<std::uintptr_t>(Functions::_Load_LuaFileAsset), &loadLuaFileAssetHook, &s_originalLoadLuaFileAsset);
	Hook::create("hks_load", reinterpret_cast<std::uintptr_t>(Functions::_Hks_Load), &hksLoadHook, &s_originalHksLoad);
	Hook::create("LUI_CoD_Init", reinterpret_cast<std::uintptr_t>(Functions::_LUI_CoD_Init), &luiCodInitHook, &s_originalLuiCodInit);
	Hook::create("LUI_CoD_Shutdown", reinterpret_cast<std::uintptr_t>(Functions::_LUI_CoD_Shutdown), &luiCodShutdownHook, &s_originalLuiCodShutdown);
}
