#include "pch.h"
#include "ScriptLoader.hpp"
#include "Console.hpp"
#include "FuncPointers.h"
#include "Hook.hpp"
#include "DevDef.h"
#include "xsk/gsc/engine/s2.hpp"
#include "xsk/utils/zlib.hpp"

typedef void(*Load_ScriptFileAsset)(ScriptFile** scriptFile);
Load_ScriptFileAsset _Load_ScriptFileAsset = nullptr;

namespace {
	std::mutex& scriptContextMutex() {
		static std::mutex mutex;
		return mutex;
	}

	xsk::gsc::s2::context& getS2Context() {
		static xsk::gsc::s2::context ctx(xsk::gsc::instance::server);
		static bool init = []() {
			DEV_PRINTF("ScriptLoader: initializing fallback S2 xsk context");
			ctx.init(xsk::gsc::build::prod, [](xsk::gsc::context const*, std::string const&) -> std::pair<xsk::gsc::buffer, std::vector<xsk::u8>> {
				return {};
			});

			return true;
		}();

		return ctx;
	}


	std::vector<xsk::u8> makeByteVec(const char* data, int len) {
		if (!data || len <= 0) {
			return {};
		}

		auto begin = reinterpret_cast<xsk::u8 const*>(data);
		return std::vector<xsk::u8>(begin, begin + len);
	}

	std::vector<xsk::u8> makeByteVec(xsk::gsc::buffer const& data) {
		if (!data.data || data.size == 0) {
			return {};
		}

		return std::vector<xsk::u8>(data.data, data.data + data.size);
	}

	std::vector<xsk::u8> getScriptStack(ScriptFile* script) {
		if (!script || !script->buffer) {
			DEV_PRINTF("ScriptLoader: script stack unavailable");
			return {};
		}

		if (script->compressedLen > 0) {
			DEV_PRINTF("ScriptLoader: decompressing stack for '%s' compressed=%i len=%i", script->name ? script->name : "<null>", script->compressedLen, script->len);
			return xsk::utils::zlib::decompress(makeByteVec(script->buffer, script->compressedLen), script->len);
		}

		DEV_PRINTF("ScriptLoader: using uncompressed stack for '%s' len=%i", script->name ? script->name : "<null>", script->len);
		return makeByteVec(script->buffer, script->len);
	}

	std::vector<xsk::u8> decompileScript(ScriptFile* script) {
		DEV_PRINTF("ScriptLoader: decompiling '%s'", script && script->name ? script->name : "<null>");
		auto bytecode = makeByteVec(script->bytecode, script->bytecodeLen);
		auto stack = getScriptStack(script);

		std::lock_guard<std::mutex> lock(scriptContextMutex());

		auto& ctx = getS2Context();
		auto outasm = ctx.disassembler().disassemble(bytecode, stack);
		auto outast = ctx.decompiler().decompile(*outasm);
		auto source = ctx.source().dump(*outast);
		DEV_PRINTF("ScriptLoader: decompiled '%s' (%llu bytes)", script && script->name ? script->name : "<null>", static_cast<unsigned long long>(source.size()));
		return source;
	}



}

void ScriptLoader::dumpScript(ScriptFile* script) {
	DEV_PRINTF("ScriptLoader: dumpScript '%s'", script && script->name ? script->name : "<null>");
	if (!script || !script->name) {
		return;
	}

	std::string filePath = "S2MP-Mod/dump/scripts/" + std::string(script->name) + ".gsc";
	//get directory path from filePath
	std::filesystem::path dirPath = std::filesystem::path(filePath).parent_path();
	if (!std::filesystem::exists(dirPath)) {
		std::filesystem::create_directories(dirPath);
	}

	auto data = std::vector<xsk::u8>{};
	try {
		data = decompileScript(script);
	}
	catch (const std::exception& e) {
		DEV_PRINTF("ScriptLoader: dump decompile failed '%s': %s", script && script->name ? script->name : "<null>", e.what());
		Console::printf("Failed to decompile script '%s': %s", script->name, e.what());
		return;
	}

	std::ofstream outFile(filePath, std::ios::out | std::ios::binary);
	if (!outFile) {
		DEV_PRINTF("ScriptLoader: dump output open failed '%s'", filePath.c_str());
		Console::printf("File path error for: %s", filePath.c_str());
		return;
	}
	outFile.write(reinterpret_cast<const char*>(data.data()), data.size());
	outFile.close();
	DEV_PRINTF("ScriptLoader: dumped source to '%s' (%llu bytes)", filePath.c_str(), static_cast<unsigned long long>(data.size()));
	//Console::printf("Script Dumped to: %s", filePath.c_str());
}


void ScriptLoader::loadCustomScripts() {

}




void ScriptLoader::init() {

}
