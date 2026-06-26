/////////////////////////////////////
//       Func Pointers
//	Engine Function Pointers
/////////////////////////////////////
#include "pch.h"
#include "FuncPointers.h"
#include "Console.hpp"
#include "DevDef.h"

Functions::UnitQuatToAxis Functions::_UnitQuatToAxis = nullptr;
Functions::Cmd_Exec_f Functions::_Cmd_Exec_f = nullptr;
Functions::Dvar_RegisterFloat Functions::_Dvar_RegisterFloat = nullptr;
Functions::Dvar_RegisterInt Functions::_Dvar_RegisterInt = nullptr;
Functions::Key_SetBinding Functions::_Key_SetBinding = nullptr;
Functions::Key_GetBindingForCommand Functions::_Key_GetBindingForCommand = nullptr;
Functions::Key_StringToKeynum Functions::_Key_StringToKeynum = nullptr;
Functions::Image_GetLevelSize Functions::_Image_GetLevelSize = nullptr;
Functions::Image_Setup Functions::_Image_Setup = nullptr;
Functions::G_DObjUpdate Functions::_G_DObjUpdate = nullptr;
Functions::G_SetModel Functions::_G_SetModel = nullptr;
Functions::G_Spawn Functions::_G_Spawn = nullptr;
Functions::G_SpawnItem Functions::_G_SpawnItem = nullptr;
Functions::G_GetWeaponForName Functions::_G_GetWeaponForName = nullptr;
Functions::BG_GetWorldModel Functions::_BG_GetWorldModel = nullptr;
Functions::G_SetOrigin Functions::_G_SetOrigin = nullptr;
Functions::Touch_Item Functions::_Touch_Item = nullptr;
Functions::Add_Ammo Functions::_Add_Ammo = nullptr;
Functions::G_GetEntityPlayerState Functions::_G_GetEntityPlayerState = nullptr;
Functions::G_TakePlayerWeapon Functions::_G_TakePlayerWeapon = nullptr;
Functions::SV_StartMap Functions::_SV_StartMap = nullptr;
Functions::GetStringFromResource Functions::_GetStringFromResource = nullptr;
Functions::SV_SendServerCommand Functions::_SV_SendServerCommand = nullptr;
Functions::Com_Error Functions::_Com_Error = nullptr;
Functions::Scr_MakeGameMessage Functions::_Scr_MakeGameMessage = nullptr;
Functions::Sys_EnterCriticalSection Functions::_Sys_EnterCriticalSection = nullptr;
Functions::Sys_LeaveCriticalSection Functions::_Sys_LeaveCriticalSection = nullptr;
Functions::Sys_Cwd Functions::_Sys_Cwd = nullptr;
Functions::Dvar_FindVar Functions::_Dvar_FindVar = nullptr;
Functions::SEH_SafeTranslateString Functions::_SEH_SafeTranslateString = nullptr;
Functions::SEH_StringEd_GetString Functions::_SEH_StringEd_GetString = nullptr;
Functions::Com_Quit_f Functions::_Com_Quit_f = nullptr;
Functions::GetAvailableCommandBufferIndex Functions::_GetAvailableCommandBufferIndex = nullptr;
Functions::SV_MapRestart_f Functions::_SV_MapRestart_f = nullptr;

Functions::R_AddCmdDrawText Functions::_R_AddCmdDrawText = nullptr;
Functions::R_RegisterFont Functions::_R_RegisterFont = nullptr;
Functions::UI_RunMenuScript Functions::_UI_RunMenuScript = nullptr;
Functions::SV_Loaded Functions::_SV_Loaded = nullptr;
Functions::R_AddCmdDrawStretchPic Functions::_R_AddCmdDrawStretchPic = nullptr;
Functions::R_AddCmdDrawTextWithCursor Functions::_R_AddCmdDrawTextWithCursor = nullptr;
Functions::LUI_OpenMenu Functions::_LUI_OpenMenu = nullptr;
Functions::LiveStorage_UploadStats Functions::_LiveStorage_UploadStats = nullptr;
Functions::Cmd_AddCommandInternal Functions::_Cmd_AddCommandInternal = nullptr;

Functions::LUI_CoD_GetMaxMemory Functions::_LUI_CoD_GetMaxMemory = nullptr;
Functions::LUI_CoD_GetFreeMemoryBytes Functions::_LUI_CoD_GetFreeMemoryBytes = nullptr;
Functions::Load_LuaFileAsset Functions::_Load_LuaFileAsset = nullptr;
Functions::Hks_Load Functions::_Hks_Load = nullptr;
Functions::LUI_CoD_Init Functions::_LUI_CoD_Init = nullptr;
Functions::LUI_CoD_Shutdown Functions::_LUI_CoD_Shutdown = nullptr;
Functions::hks_HashTable_contiguousArraySize Functions::_hks_HashTable_contiguousArraySize = nullptr;
Functions::Material_RegisterHandle Functions::_Material_RegisterHandle = nullptr;
Functions::Dvar_RegisterBool Functions::_Dvar_RegisterBool = nullptr;
Functions::DB_GetXAssetTypeSize Functions::_DB_GetXAssetTypeSize = nullptr;
Functions::DB_GetXAssetName Functions::_DB_GetXAssetName = nullptr;
Functions::hksi_hksL_loadbuffer Functions::_hksi_hksL_loadbuffer = nullptr;
Functions::Cmd_RemoveCommand Functions::_Cmd_RemoveCommand = nullptr;
Functions::DB_FindXAssetHeader Functions::_DB_FindXAssetHeader = nullptr;
Functions::Scr_LoadScript Functions::_Scr_LoadScript = nullptr;
Functions::Scr_GetFunctionHandle Functions::_Scr_GetFunctionHandle = nullptr;
Functions::Scr_ExecThread Functions::_Scr_ExecThread = nullptr;
Functions::Scr_FreeThread Functions::_Scr_FreeThread = nullptr;
Functions::Scr_GetNumParam Functions::_Scr_GetNumParam = nullptr;
Functions::Scr_GetString Functions::_Scr_GetString = nullptr;
Functions::Scr_Error Functions::_Scr_Error = nullptr;
Functions::Scr_ParamError Functions::_Scr_ParamError = nullptr;
Functions::Sys_Milliseconds Functions::_Sys_Milliseconds = nullptr;
Functions::Com_TimeScaleMsec Functions::_Com_TimeScaleMsec = nullptr;
Functions::Dvar_GetString Functions::_Dvar_GetString = nullptr;

void Functions::init()
{
	DEV_INIT_PRINT();
	_Sys_Cwd = (Sys_Cwd)(0x771750_b);
	_SV_StartMap = (SV_StartMap)(0x6D7200_b);
	_GetStringFromResource = (GetStringFromResource)(0x7894A0_b);
	_SV_SendServerCommand = (SV_SendServerCommand)(0x6DFBA0_b);
	_Com_Error = (Com_Error)(0x8F750_b);
	_Scr_MakeGameMessage = (Scr_MakeGameMessage)(0x5AE7A0_b);
	_Sys_EnterCriticalSection = (Sys_EnterCriticalSection)(0x7719B0_b);
	_Sys_LeaveCriticalSection = (Sys_LeaveCriticalSection)(0x771A20_b);
	_Dvar_FindVar = (Dvar_FindVar)(0xAE9D0_b);
	_SEH_SafeTranslateString = (SEH_SafeTranslateString)(0x72CE50_b);
	_SEH_StringEd_GetString = (SEH_StringEd_GetString)(0x72CEA0_b);
	_Dvar_RegisterBool = (Dvar_RegisterBool)(0xAF5E0_b);
	_Com_Quit_f = (Com_Quit_f)(0x99130_b);
	_GetAvailableCommandBufferIndex = (GetAvailableCommandBufferIndex)(0x4A05C0_b);
	_SV_MapRestart_f = (SV_MapRestart_f)(0x6D5B50_b);
	_R_AddCmdDrawText = (R_AddCmdDrawText)(0x8B9480_b);
	_R_RegisterFont = (R_RegisterFont)(0x892D90_b);
	_UI_RunMenuScript = (UI_RunMenuScript)(0x745A50_b);
	_SV_Loaded = (SV_Loaded)(0x6DF9D6_b);
	_R_AddCmdDrawStretchPic = (R_AddCmdDrawStretchPic)(0x8B8A00_b);
	_R_AddCmdDrawTextWithCursor = (R_AddCmdDrawTextWithCursor)(0x8B9D10_b);
	_LUI_OpenMenu = (LUI_OpenMenu)(0x743F60_b);
	_LiveStorage_UploadStats = (LiveStorage_UploadStats)(0x65BA90_b);
	_Cmd_AddCommandInternal = (Cmd_AddCommandInternal)(0x6496B0_b);
	_LUI_CoD_GetMaxMemory = (LUI_CoD_GetMaxMemory)(0x180CA0_b);
	_LUI_CoD_GetFreeMemoryBytes = (LUI_CoD_GetFreeMemoryBytes)(0x180C90_b);
	_Load_LuaFileAsset = (Load_LuaFileAsset)(0xD81A0_b);
	_Hks_Load = (Hks_Load)(0x2D6D10_b);
	_LUI_CoD_Init = (LUI_CoD_Init)(0x317A00_b);
	_LUI_CoD_Shutdown = (LUI_CoD_Shutdown)(0x31A6F0_b);
	_hks_HashTable_contiguousArraySize = (hks_HashTable_contiguousArraySize)(0x2CA7D0_b);
	_Material_RegisterHandle = (Material_RegisterHandle)(0x8AB5F0_b);
	_DB_GetXAssetTypeSize = (DB_GetXAssetTypeSize)(0x4A2F20_b);
	_DB_GetXAssetName = (DB_GetXAssetName)(0x4A2EF0_b);
	_hksi_hksL_loadbuffer = (hksi_hksL_loadbuffer)(0x2D9020_b);
	_Cmd_RemoveCommand = (Cmd_RemoveCommand)(0x64A830_b);
	_Scr_LoadScript = (Scr_LoadScript)(0x684B10_b);
	_Scr_GetFunctionHandle = (Scr_GetFunctionHandle)(0x6849A0_b);
	_Scr_ExecThread = (Scr_ExecThread)(0x68F1F0_b);
	_Scr_FreeThread = (Scr_FreeThread)(0x68F2D0_b);
	_Scr_GetNumParam = (Scr_GetNumParam)(0x68F9E0_b);
	_Scr_GetString = (Scr_GetString)(0x68FC00_b);
	_Scr_Error = (Scr_Error)(0x68F0F0_b);
	_Scr_ParamError = (Scr_ParamError)(0x690660_b);
	_G_Spawn = (G_Spawn)(0x5C0FC0_b);
	_G_SpawnItem = (G_SpawnItem)(0x55ACC0_b);
	_G_GetWeaponForName = (G_GetWeaponForName)(0x5C3C00_b);
	_G_SetOrigin = (G_SetOrigin)(0x5C0EB0_b);
	_Touch_Item = (Touch_Item)(0x55B8B0_b);
	_Add_Ammo = (Add_Ammo)(0x5585E0_b);
	_G_GetEntityPlayerState = (G_GetEntityPlayerState)(0x5C0020_b);
	_G_TakePlayerWeapon = (G_TakePlayerWeapon)(0x5C5490_b);
	_BG_GetWorldModel = (BG_GetWorldModel)(0x3BCD30_b);
	_DB_FindXAssetHeader = (DB_FindXAssetHeader)(0xA0080_b);
	_G_SetModel = (G_SetModel)(0x5C0E00_b);
	_G_DObjUpdate = (G_DObjUpdate)(0x5BDAF0_b);
	_Image_Setup = (Image_Setup)(0x8978C0_b);
	_Image_GetLevelSize = (Image_GetLevelSize)(0x897730_b);
	_Key_StringToKeynum = (Key_StringToKeynum)(0x45ED70_b);
	_Key_GetBindingForCommand = (Key_GetBindingForCommand)(0x64A460_b);
	_Key_SetBinding = (Key_SetBinding)(0x45EBC0_b);
	_Dvar_RegisterInt = (Dvar_RegisterInt)(0xAFC70_b);
	_Dvar_RegisterFloat = (Dvar_RegisterFloat)(0xAFA50_b);
	_Cmd_Exec_f = (Cmd_Exec_f)(0x64A2A0_b);
	_UnitQuatToAxis = (UnitQuatToAxis)(0x75CBB0_b);

	// Demo system (verified via IDA MCP against s2x_dump: _b = RVA - 0x1000)
	_Sys_Milliseconds = (Sys_Milliseconds)(0x7B0290_b);   // RVA 0x7B1290, named Sys_Milliseconds
	_Com_TimeScaleMsec = (Com_TimeScaleMsec)(0x9B090_b);  // RVA 0x9C090, uses PlaybackSpeedScale
	_Dvar_GetString = (Dvar_GetString)(0xAED20_b);        // RVA 0xAFD20
}
