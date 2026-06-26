#pragma once
#include "structs.h"

class Functions {
public:
	static void init();

	typedef void (*Cmd_Exec_f)();
	static Cmd_Exec_f _Cmd_Exec_f;

	typedef void (*UnitQuatToAxis)(const float quat[4], float axis[3][3]);
	static UnitQuatToAxis _UnitQuatToAxis;


	typedef dvar_t* (*Dvar_RegisterFloat)(const char* name, float defaultValue, float minValue, float maxValue, unsigned int flags);
	static Dvar_RegisterFloat _Dvar_RegisterFloat;

	typedef dvar_t* (*Dvar_RegisterInt)(const char* name, int defaultValue, int minValue, int maxValue, unsigned int flags);
	static Dvar_RegisterInt _Dvar_RegisterInt;

	typedef void (*Key_SetBinding)(int localClientNum, int keynum, int bindingIndex);
	static Key_SetBinding _Key_SetBinding;

	typedef int (*Key_GetBindingForCommand)(const char* command);
	static Key_GetBindingForCommand _Key_GetBindingForCommand;

	typedef int (*Key_StringToKeynum)(const char* string);
	static Key_StringToKeynum _Key_StringToKeynum;

	typedef uint32_t(*Image_GetLevelSize)(int format, int width, int height, int depth);
	static Image_GetLevelSize _Image_GetLevelSize;

	typedef void (*Image_Setup)(GfxImage* image, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipCount, uint32_t imageFlags, DXGI_FORMAT imageFormat, const char* name, const void* initData);
	static Image_Setup _Image_Setup;

	typedef void (*G_DObjUpdate)(gentity_s* entity, int link);
	static G_DObjUpdate _G_DObjUpdate;

	typedef void (*G_SetModel)(gentity_s* entity, const char* modelName);
	static G_SetModel _G_SetModel;

	typedef gentity_s* (*G_Spawn)();
	static G_Spawn _G_Spawn;

	typedef void (*G_SpawnItem)(void* gent, Weapon* weapon);
	static G_SpawnItem _G_SpawnItem;

	typedef Weapon* (*G_GetWeaponForName)(Weapon* outWeapon, const char* weaponName);
	static G_GetWeaponForName _G_GetWeaponForName;

	typedef void* (*BG_GetWorldModel)(Weapon* weapon, bool isAlternate, int variation);
	static BG_GetWorldModel _BG_GetWorldModel;

	typedef void (*G_SetOrigin)(void* gentity, const float* origin);
	static G_SetOrigin _G_SetOrigin;

	typedef void (*Touch_Item)(void* entity, void* player, int idk0, int idk1);
	static Touch_Item _Touch_Item;
	
	typedef int (*Add_Ammo)(void* ps, Weapon* weapon, bool isAlternate, int amount, bool allowOverflow);
	static Add_Ammo _Add_Ammo;

	typedef void* (*G_GetEntityPlayerState)(void* entity);
	static G_GetEntityPlayerState _G_GetEntityPlayerState;

	typedef int (*G_TakePlayerWeapon)(void* playerstate, Weapon* weapon);
	static G_TakePlayerWeapon _G_TakePlayerWeapon;

	typedef void(*Cmd_RemoveCommand)(const char* name);
	static Cmd_RemoveCommand _Cmd_RemoveCommand;

	typedef XAssetHeader(*DB_FindXAssetHeader)(XAssetType type, const char* name, int allow_create_default);
	static DB_FindXAssetHeader _DB_FindXAssetHeader;

	typedef unsigned int(__cdecl* Scr_LoadScript)(const char* scriptName);
	static Scr_LoadScript _Scr_LoadScript;

	typedef int(__cdecl* Scr_GetFunctionHandle)(const char* scriptName, unsigned int functionName);
	static Scr_GetFunctionHandle _Scr_GetFunctionHandle;

	typedef unsigned int(__cdecl* Scr_ExecThread)(int handle, unsigned int paramCount);
	static Scr_ExecThread _Scr_ExecThread;

	typedef void(__cdecl* Scr_FreeThread)(unsigned int threadId);
	static Scr_FreeThread _Scr_FreeThread;

	typedef int(__cdecl* Scr_GetNumParam)();
	static Scr_GetNumParam _Scr_GetNumParam;

	typedef const char* (__cdecl* Scr_GetString)(unsigned int paramIndex);
	static Scr_GetString _Scr_GetString;

	typedef void(__cdecl* Scr_Error)(const char* fmt, ...);
	static Scr_Error _Scr_Error;

	typedef void(__cdecl* Scr_ParamError)(int paramIndex, const char* fmt, ...);
	static Scr_ParamError _Scr_ParamError;

	typedef int (__cdecl* hksi_hksL_loadbuffer)(void* s, const void* options, const char* buff, unsigned __int64 sz, const char* name);
	static hksi_hksL_loadbuffer _hksi_hksL_loadbuffer;

	typedef int (__cdecl* DB_GetXAssetTypeSize)(int type);
	static DB_GetXAssetTypeSize _DB_GetXAssetTypeSize;

	typedef const char* (__cdecl* DB_GetXAssetName)(const void* asset);
	static DB_GetXAssetName _DB_GetXAssetName;

	typedef void (__cdecl* StringTable_GetAsset)(const char* name, StringTable** table);
	static StringTable_GetAsset _StringTable_GetAsset;

	typedef void (__cdecl* GamerProfile_ToggleAimAssistSlowdown)(int controller);
	static GamerProfile_ToggleAimAssistSlowdown _GamerProfile_ToggleAimAssistSlowdown;

	typedef void (__cdecl* GamerProfile_ToggleAimAssistLockon)(int controller);
	static GamerProfile_ToggleAimAssistLockon _GamerProfile_ToggleAimAssistLockon;

	typedef void (__cdecl* SV_StartMap)(LocalClientNum_t localClientNum, const char* map, bool mapIsPreloaded);
	static SV_StartMap _SV_StartMap;

	typedef char* (__cdecl* GetStringFromResource)(UINT num);
	static GetStringFromResource _GetStringFromResource;

	typedef void(__cdecl* SV_SendServerCommand)(__int64 client, int type, const char* fmt, ...);
	static SV_SendServerCommand _SV_SendServerCommand;

	typedef void(__cdecl* Com_Error)(errorParm_t code, const char* fmt, ...);
	static Com_Error _Com_Error;

	typedef void(__cdecl* Scr_MakeGameMessage)(const char *msg);
	static Scr_MakeGameMessage _Scr_MakeGameMessage;

	typedef void(__cdecl* Sys_EnterCriticalSection)(int critSect);
	static Sys_EnterCriticalSection _Sys_EnterCriticalSection;

	typedef void(__cdecl* Sys_LeaveCriticalSection)(int critSect);
	static Sys_LeaveCriticalSection _Sys_LeaveCriticalSection;

	typedef const char* (__cdecl* Sys_Cwd)();
	static Sys_Cwd _Sys_Cwd;

	typedef dvar_t* (__cdecl* Dvar_FindVar)(const char* dvarName);
	static Dvar_FindVar _Dvar_FindVar;

	typedef char* (__cdecl* SEH_SafeTranslateString)(const char* pszReference);
	static SEH_SafeTranslateString _SEH_SafeTranslateString;

	typedef char* (__cdecl* SEH_StringEd_GetString)(const char* pszReference);
	static SEH_StringEd_GetString _SEH_StringEd_GetString;

	typedef void (__cdecl* Com_Quit_f)();
	static Com_Quit_f _Com_Quit_f;

	typedef __int64 (__cdecl* GetAvailableCommandBufferIndex)();
	static GetAvailableCommandBufferIndex _GetAvailableCommandBufferIndex;

	typedef void (__cdecl* SV_MapRestart_f)();
	static SV_MapRestart_f _SV_MapRestart_f;

	typedef void(__cdecl* R_AddCmdDrawText)(const char* text, int max_chars, font_t* font, int unk0, int unk1, int pixel_h, float pos_x, float pos_y, float scale_x, float scale_y, float rotation, float* color, long long style);
	static R_AddCmdDrawText _R_AddCmdDrawText;

	typedef font_t* (__cdecl* R_RegisterFont)(const char* name, int size);
	static R_RegisterFont _R_RegisterFont;

	typedef void(__cdecl* UI_RunMenuScript)(int client, const char** args);
	static UI_RunMenuScript _UI_RunMenuScript;

	typedef bool(__cdecl* SV_Loaded)();
	static SV_Loaded _SV_Loaded;

	typedef bool(__cdecl* R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, float* color, Material* material);
	static R_AddCmdDrawStretchPic _R_AddCmdDrawStretchPic;

	typedef bool(__cdecl* R_AddCmdDrawTextWithCursor)(const char* text, int max_chars, font_t* font, int unk0, int unk1, int pixel_h, float pos_x, float pos_y, float scale_x, float scale_y, float rotation, const float* color, long long style, int cursorPos, char cursor);
	static R_AddCmdDrawTextWithCursor _R_AddCmdDrawTextWithCursor;

	typedef bool(__cdecl* LUI_OpenMenu)(int client, const char* menu, int a, unsigned int is_exclusive);
	static LUI_OpenMenu _LUI_OpenMenu;

	typedef void(__cdecl* LiveStorage_UploadStats)(int clientNum);
	static LiveStorage_UploadStats _LiveStorage_UploadStats;

	typedef void(__cdecl* Cmd_AddCommandInternal)(char const* name, void (*func)(), cmd_function_s* cmd);
	static Cmd_AddCommandInternal _Cmd_AddCommandInternal;

	typedef int(__cdecl* LUI_CoD_GetMaxMemory)();
	static LUI_CoD_GetMaxMemory _LUI_CoD_GetMaxMemory;

	typedef int(__cdecl* LUI_CoD_GetFreeMemoryBytes)();
	static LUI_CoD_GetFreeMemoryBytes _LUI_CoD_GetFreeMemoryBytes;

	typedef void(__fastcall* Load_LuaFileAsset)(LuaFile** luaFile);
	static Load_LuaFileAsset _Load_LuaFileAsset;

	typedef int(*Hks_Load)(void* state, void* compilerOptions, void* reader, void* readerData, const char* chunkName);
	static Hks_Load _Hks_Load;

	typedef void(*LUI_CoD_Init)(bool frontend, bool immediate);
	static LUI_CoD_Init _LUI_CoD_Init;

	typedef void(*LUI_CoD_Shutdown)();
	static LUI_CoD_Shutdown _LUI_CoD_Shutdown;

	typedef int(__cdecl* hks_HashTable_contiguousArraySize)();
	static hks_HashTable_contiguousArraySize _hks_HashTable_contiguousArraySize;

	typedef Material* (__cdecl* Material_RegisterHandle)(const char* name);
	static Material_RegisterHandle _Material_RegisterHandle;

	typedef void* (__cdecl* Dvar_RegisterBool)(const char* dvarName, bool value, unsigned int flags);
	static Dvar_RegisterBool _Dvar_RegisterBool;

	// ===== Demo system (verified via IDA: RVA - 0x1000) =====
	typedef int (__cdecl* Sys_Milliseconds)();
	static Sys_Milliseconds _Sys_Milliseconds;

	typedef int (__cdecl* Com_TimeScaleMsec)(int msec);
	static Com_TimeScaleMsec _Com_TimeScaleMsec;

	typedef const char* (__cdecl* Dvar_GetString)(const char* dvarName);
	static Dvar_GetString _Dvar_GetString;
};
