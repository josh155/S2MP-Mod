#pragma once
#include <string>
#include <vector>
#include "structs.h"
#include "FuncPointers.h"
#include "Console.hpp"


struct AssetPoolStats {
	unsigned int count = 0;
	unsigned int totalSize = 0;
};


class GameUtil {
public:
	static std::string sanitizeFileName(const std::string& name);
	static bool areWeHost();
	static bool isReadablePtr(const void* ptr, size_t bytes);
	static const char* safeCString(const char* s, size_t maxLen = 4096);
	static bool bytesMatch(const uint8_t* addr, const std::initializer_list<uint8_t>& pattern);
	static void setCustomSplashScreen();
	static void blockGameInput(bool b);
	static std::string colorToString(const unsigned __int8 color[4]);
	static std::string dvarValueToString(const dvar_t* dvar, bool showQuotesAroundStrings, bool truncateFloats);
	static std::string toLower(const std::string& str);
	static std::string toUpper(const std::string& input);
	static bool isOnlyWhitespace(const std::string& str);
	static std::string getStringFromClipboard();
	//static void Cbuf_AddText(LocalClientNum_t localClientNum, std::string text);
	static void Cbuf_AddText(LocalClientNum_t localClientNum, const std::string& command);
	static float safeStringToFloat(const std::string& str);
	static int safeStringToInt(const std::string& str);
	static std::string getAddressAsString(void* address);
	static char asciiToLower(char in);
	static bool stringToBool(const std::string& str);
	static void addCommand(char const* name, void (*func)());

	static void overrideCommand(char const* name, void(*func)());

	static std::string sanitizeFormatWidths(const char* fmt);

	static CmdArgs* getCmdArgs();

	static bool getPlayerPosition(float* outPos);

	static std::list<cmd_function_s> cmdHeap;

	template <typename Callback>
	static AssetPoolStats assetPoolTraverseHelper(XAssetType targetType, Callback&& callback) {
		AssetPoolStats stats{};

		auto db_hashTable = (uint32_t*)0x27D0110_b;
		auto g_assetEntryPool = (uint8_t*)0x50F50E0_b;

		constexpr uint32_t HASH_SIZE = 0x48800;
		constexpr uint32_t MAX_ENTRIES = 0x200000;
		constexpr uint32_t ENTRY_SIZE = 32;
		constexpr uint32_t NEXT_INDEX_OFFSET = 20;

		if (targetType > ASSET_TYPE_DLOGROUTES) {
			Console::printf("Invalid asset type %u", targetType);
			return stats;
		}

		for (uint32_t hash = 0; hash < HASH_SIZE; ++hash) {
			uint32_t index = db_hashTable[hash];

			while (index) {
				if (index >= MAX_ENTRIES) {
					break;
				}

				uint8_t* entry = g_assetEntryPool + (index * ENTRY_SIZE);

				XAssetType assetType = *(XAssetType*)(entry + 0);
				uint32_t nextIndex = *(uint32_t*)(entry + NEXT_INDEX_OFFSET);

				if (assetType == targetType) {
					const char* assetName = Functions::_DB_GetXAssetName(entry);

					if (assetName) {
						XAsset* asset = reinterpret_cast<XAsset*>(entry);

						if (!callback(asset, assetName)) {
							return stats;
						}
					}

					++stats.count;
					stats.totalSize += Functions::_DB_GetXAssetTypeSize(assetType);
				}

				if (nextIndex >= MAX_ENTRIES) {
					break;
				}

				index = nextIndex;
			}
		}

		return stats;
	}
};

