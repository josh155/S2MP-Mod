//////////////////////////////////////
//            Errors
//	Mapping out the stripped format 
// strings to the actual error formats
// 
// Very useful for zombies community
//////////////////////////////////////
#include "pch.h"
#include "Errors.hpp"
#include "Console.hpp"
#include "DevDef.h"
#include "Hook.hpp"

//TODO: run script errors thru the same error map
static std::unordered_map<int, std::string> errorMap = {
    {3, "BG_GetAnimationForIndexCI: animIndex out of bounds"},
    {4, "%s: (%s, line %i)"},
    {92, "Couldn't load player animation script %s"},
    {151, "Could not find animation tree '%s'"},
    {198, "Couldn't load file or file is invalid '%s'"},
    {202, "Couldn't load file or file is invalid '%s'"},
    {219, "Mantle anim [%s] has Z translation %f, should be %f\n"},
    {224, "Unable to find the lookup table 'mp/attachmenttable.csv' in the fastfile"},
    {320, "Shared ammo cap mismatch for \"%s\" shared ammo cap: \"%s\" set it to %i, but \"%s\" already set it to %i."},
    {338, "No more room to allocate anymore rumble graphs"},
    {339, "No more room to allocate anymore rumble graphs"},
    {342, "Rumble info file [%s] cannot have broadcast set to true and range set to 0"},
    {363, "CG_RegisterWeapon: No idle anim specified for [%s]"},
    {365, "CG_RegisterWeapon: No idle anim specified for [%s]"},
    {373, "no viewmodel set for player %d for '%s' in '%s' hand. Set viewmodel hands in script or weapon settings"},
    {375, "Weapon index mismatch for '%s'"},
    {399, "CG_ProcessSnapshots: Server time went backwards"},
    {407, "Cannot set data 0x%08x to %i: we don't have stats yet"},
    {447, "Too many active clients.  You may be missing a \"nosplitscreen\" in a menu."},
    {476, "Fastfile for zone '%s' is out of date (version %d, expecting %d)"},
    {477, "Fastfile for zone '%s' is newer than client executable (version %d, expecting %d)"},
    {500, "rawfile '%s' exceeded max size. (%d > %d)"},
    {558, "No world model loaded for entity %i with model %s"},
    {560, "weapDef: No world model loaded for entity %i with model %s"},
    {594, "radius not specified for trigger_radius at (%g %g %g)"},
    {595, "height not specified for trigger_radius at (%g %g %g)"},
    {599, "radius not specified for trigger_radius at (%g %g %g)"},
    {613, "Too many AI_SIGHT_LINE entities. (limited to %i)"},
    {614, "Could not find parent %s"},
    {639, "Field: %s"},
    {644, "G_SpawnTurret: max number of turrets (%d) exceeded"},
    {645, "Bad weaponinfo \"%s\" specified for turret.  It likely needs to be precached in script."},
    {652, "Error parsing hitloc damage table %s"},
    {656, "Save game saved with different script files"},
    {659, "SV_LoadHistoryState: objectivenum out of range (%i, MAX = %i)"},
    {660, "SV_LoadHistoryState: entitynum out of range (%i, MAX = %i)"},
    {661, "SV_LoadHistoryState: clientnum out of range"},
    {662, "SV_LoadHistoryState: agentnum out of range"},
    {663, "SV_LoadHistoryState: entnum out of range: %i"},
    {664, "SV_LoadHistoryState: DObj expected for entnum %i"},
    {665, "Could not find script '%s'"},
    {667, "Could not find label in script '%s'"},
    {668, "SP_worldspawn: The first entity isn't 'worldspawn'"},
    {674, "G_Spawn: no free entities"},
    {719, "R_RegisterFont: Too many TTF fonts registered (%d)."},
    {759, "Could not find compute shader '%s'"},
    {760, "Could not find material '%s'"},
    {837, "Failed to allocate from element pool"},
    {840, "LUI: Out of memory"},
    {845, "LUI ERROR: Failed to allocate from %s pool. Restarting the Lua VM"},
    {847, "PMem_Free: pointer %p is not from the PMem stack"},
    {848, "PMem_Free: bad allocation header for %p"},
    {849, "PMem_Free: tried to free %p out of order"},
    {879, "CM_LoadMap: NULL name"},
    {999, "Trying to set persistent player data while connected to a server (%s, clcState = %i)!"},
    {1000, "Error getting persistent data: see console"},
    {1003, "Error getting persistent data: result type was a %i, expected string; see console"},
    {1043, "unknown anim tree '%s'"},
    {1046, "unknown function"},
    {1049, "ScriptCompile: MAX_PRECACHE_ENTRIES exceeded when adding far_function_count"},
    {1050, "Could not find script '%s'"},
    {1062, "Filename '%s' exceeds maximum length of %d"},
    {1124, "SV_SetConfigstring: bad index %i"},
    {1189, "Error: unable to find '%s' secondary alias"},
    {1259, "FS_AllocSearchPathSlot: out of free file handles"},
    {1260, "FS_BuildOSPath: os path length exceeded"},
    {1262, "FS_Rename: failed to allocate copy buffer"},
    {1263, "FS_Rename: failed to read source file"},
    {1264, "FS_Rename: failed to write destination file"},
    {1274, "ERROR: Invalid server value '%s' for '%s'"},
    {1275, "Invalid game folder"},
    {1276, "Couldn't load %s. Make sure Call of Duty: WWII is run from the correct folder."},
    {1278, "Unable to compare against column number %i - there are only %i columns"},
    {1289, "SAVE_STRING_MAX_SIZE exceeded in save game"},
    {1290, "SAVE_STRING_MAX_SIZE exceeded in save game"},
    {1317, "Exceeded max number of steering graphs.  Max is %d"},
    {1592, "SetDvar: unset dvar '%s' cannot be set as a client dvar. need to be added to the config file. This won't work in a future build"},
    {1593, "server dvar '%s' cannot be set as a client dvar"},
    {1594, "non-writable dvar '%s' cannot be set as a client dvar"},
    {1595, "unknown network id for dvar '%s'"},
    {1599, "%s is an invalid dvar name"},
    {1624, "USAGE: <player> Scr_VisionSetStage( <stage>, <duration> )"},
    {1632, "USAGE: <player> SetClutForPlayer( <clut name>, <duration> )"},
    {1633, "USAGE: <player> SetClutOverrideEnableForPlayer( <clut name>, <duration> )"},
    {1636, "SetBlurForPlayer - Omnvars not found - blur_target or blur_duration_ms"},
    {1715, "out of hudelems"},
    {1727, "Usage: waypoint SetHideTrigger( trigger_ent )"},
    {1802, "only valid on players; called on entity %u at %.0f %.0f %.0f classname %s targetname %s"},
    {1823, "assert fail"},
    {1824, "assert fail: %s"},
    {1825, "assert fail: %s"},
    {1828, "Scr_SetOmnVar - '%s' is a unsigned type, and can not be set to negative values"},
    {1829, "Scr_SetOmnVar - '%s' setting to %d would exceed this Omnvar's specified range [%d,%lld]"},
    {1830, "Scr_SetOmnVar - '%s' is a LUI NetConstString, and cannot be set to '%s'. Did you add this string to ncsLuiStrings.txt?"},
    {1832, "SetOmnvar - '%s' not found"},
    {1833, "GetOmnvar - '%s' not found"},
    {1834, "%s' is not a game-scope Omnvar"},
    {1835, "SetOmnvar - Type for paramater 1 not recognized"},
    {1836, "Dvar %s has an invalid dvar name"},
    {1837, "Dvar %s has an invalid dvar name"},
    {1838, "Dvar %s has an invalid dvar name"},
    {1839, "GScr_SetDvarIfUninitialized( dvarName, initialValue ) requires two parameters"},
    {1841, "GetDvar( <dvar>, <default> ) takes either one or two parameters"},
    {1842, "GetDvarInt( <dvar>, <default> ) takes either one or two parameters"},
    {1843, "GetDvarFloat( <dvar>, <default> ) takes either one or two parameters"},
    {1844, "GetDvarVector( <dvar>, <default> ) takes either one or two parameters"},
    {1845, "GetDvarVector: Dvar %s '%s' isn't parsable as a vector"},
    {2306, "lower-right X and Y coordinates must be both south and east of upper-left X and Y coordinates in terms of the northyaw"},
    {2031, "GScr_Spawn: unable to spawn entity"},
    {2033, "precacheTurret must be called before any wait statements in the level script"},
    {2139, "RandomInt takes 1 parameter"},
    {2140, "RandomInt parm must be positive integer."},
    {2141, "RandomFloat takes 1 parameter"},
    {2142, "RandomIntRange's second parameter must be greater than the first."},
    {2143, "Scr_RandomFloatRange's second parameter must be greater than the first."},
    {2144, "GScr_tan: divide by 0"},
    {2145, "GScr_asin: %g out of range"},
    {2146, "GScr_acos: %g out of range"},
    {2155, "wrong number of arguments to vectornormalize!"},
    {2156, "wrong number of arguments to vectortoangle!"},
    {2157, "wrong number of arguments to vectortoyaw!"},
    {2158, "wrong number of arguments to vectorlerp"},
    {2159, "wrong number of arguments to anglelerp"},
    {2160, "wrong number of arguments to axistoangles"},
    {2168, "Scr_ToLower: string too long (1024 max)"},
    {2170, "StrICmp() only works for strings and names of localized strings"},
    {2178, "precacheModel must be called before any wait statements in the gametype or level script"},
    {2225, "Source Damage vector is invalid : %d %d %d"},
    {2353, "GetLocalPlayerProfileData() must be called on a client entity"},
    {2354, "GetLocalPlayerProfileData() requires the name of the setting"},
    {2355, "annot get bitfield from profile without an index"},
    {2357, "Invalid profile data %s for GetLocalPlayerProfileData()"},
    {2413, "SetSlowMotion requires at least 1 parameter."},
    {2414, "GetPlayerData: entity must be a player entity"},
    {2446, "Incorrect badplace_cylinder() call."},
    {2447, "Error creating BadPlace, see log for details"},
    {2449, "Incorrect usage for badplace_arc()"},
    {2450, "left angle < 0 in badplace_arc"},
    {2451, "right angle < 0 in badplace_arc"},
    {2452, "Error creating BadPlace, see log for details"},
    {2453, "Incorrect badplace_brush() call."},
    {2454, "Error creating BadPlace, see log for details"},
    {2484, "LUIOpenMenu: Need menu name."},
    {2485, "LUIOpenMenu: Menu name (string) is not precached."},
    {2518, "Owner must be a player or agent."},
    {2568, "Cannot call Vehicle_GetSpawnerArray() with parameters"},
    {2997, "StopDynamicAmbience needs 1 parameter - you had %i parameters"},
    {3106, "USAGE: spawn( \"trigger_radius\", <origin>, <spawnflags>, <radius>, <height> )"},
    {3172, "getnode used with more than one node"},
    {3260, "G_SpawnTurret: weapon '%s' isn't a turret. This usually indicates that the weapon failed to load."},
    {3261, "turret '%s' not precached"},
    {3270, "invalid SetSpawnWeapon: %s"},
    {3271, "Scavenger Item \"%s\" does not exist or has not been pre-cached."},
    {3272, "Scavenger Item \"%s\" does not have the 'scavenger' inventory type."},
    {3288, "Player provided is not a client or an agent."},
    {3290, "Invalid slot number %i, must be between 0 and %i."},
    {3328, "USAGE: getMapCustom( customFieldName )"},
    {3390, "exitlevel already called"},
    {3388, "map_restart already called"},
    {3403, "Not enough parameters for Kick()"},
    {3406, "Scr_SetSunLight: Incorrect number of parameters"},
    {3407, "Scr_ResetSunLight: Incorrect number of parameters"},
    {3408, "Illegal teammode string '%s'. Must be ffa, or axis_allies."},
    {3418, "GScr_SendMatchData: No match data def defined"},
    {3483, "Expected 1 argument to setMapCenter()"},
    {3585, "SetGenericField is attempting to truncate a negative number into an F_USHORT (which is unsigned)"},
    {3586, "SetGenericField is attempting to truncate a negative number into an F_BYTE (which is unsigned)"},
    {3705, "type %s is not an int"},
    {3706, "parameter %u does not exist"},
    {3711, "parameter %u does not exist"},
    {3726, "parameter %u does not exist"},
    {3754, "entity %u is not a scripted agent"},
    {3773, "unknown physics mode."},
    {3882, "Trying to call a vehicle command on a spawner.\nEntity '%s' at (%.0f %.0f %.0f)"},
    {3883, "Trying to call a vehicle command on a non-script_vehicle entity.\nEntity '%s' at (%.0f %.0f %.0f)"},
    {3884, "Trying to call a vehicle spawner command on a vehicle.\nEntity '%s' at (%.0f %.0f %.0f)"},
    {3885, "Trying to call a vehicle spawner command on a non-script_vehicle entity.\nEntity '%s' at (%.0f %.0f %.0f)"},
    {3976, "Could not find menu ID for '%s'"},
    {3978, "Could not find menu ID for '%s'"},
    {3979, "Could not find menu ID for '%s'"},
    {3984, "Duration must be positive"},
    {3987, "Duration must be positive"},
    {3989, "Time must be positive"},
    {3990, "Blur value must be greater than 0"},
    {4005, "not a hud element"},
    {4091, "Unknown weapon name \"%s\": weapon may need to be added to the fast file. Or add attachments to the base weapon description. BG_GetNumWeapons() = %u\n"},
    {4092, "Asked for weapon \"%s\", but got weapon \"%s\" - check for missing or misspelled attachments, and make sure they are sorted alphabetically "},
    {4093, "unknown weapon '%s' in getWeaponModel"},
    {4094, "unknown weapon '%s' in GetWeaponBaseName"},
    {4095, "unknown weapon '%s' in GetWeaponAttachments"},
    {4102, "unknown weapon '%s' in GetWeaponCamoName"},
    {4110, "non-primitive animation has no concept of length"},
    {4122, "Scale must be greater than 0"},
    {4124, "duration must be greater than 0"},
    {4125, "Radius must be greater than 0"},
    {4159, "GScr_CastInt: cannot cast %s to int"},
    {4160, "GScr_CastFloat: cannot cast %s to float"},
    {4161, "GScr_VectorFromLineToPoint: The two points on the line must be different from each other"},
    {4162, "GScr_PointOnSegmentNearestToPoint: Line segment must not have zero length"},
    {4166, "Scr_PrecacheModel: Model name string is empty"},
    {4196, "GScr_GetMoveDelta: end time must be between 0 and 1"},
    {4197, "GScr_GetMoveDelta: start time must be between 0 and 1"},
    {4198, "GScr_GetAngleDelta: end time must be between 0 and 1"},
    {4199, "GScr_GetAngleDelta: start time must be between 0 and 1"},
    {4200, "GScr_GetAngleDelta3D: end time must be between 0 and 1"},
    {4201, "GScr_GetAngleDelta3D: start time must be between 0 and 1"},
    {4203, "%s (effect = %s)"},
    {4297, "\"%s\" grenade weapon is not precached"},
    {4304, "Owner entity is not a character"},
    {4445, "Scr_GetNode: key is not internally a string"},
    {4446, "Scr_GetNodeArray: key '%s' does not internally belong to nodes"},
    {4447, "Scr_GetNodeArray: key is not internally a string"},
    {4458, "not a pathnode"},
    {4460, "createthreatbiasgroup [name]"},
    {4468, "isEnemyTeam [team1] [team2]"},
    {4515, "entity %u is not a player"},
    {4516, "not an entity"},
    {4517, "entity %u is not a player or agent"},
    {4518, "not an entity"},
    {4519, "entity %u is not a player or agent"},
    {4521, "not an entity"},
    {4554, "entity is not a player or agent"},
    {4556, "entity is not a player or agent"},
    {4564, "Invalid client specified (%i) out of %i clients"},
    {4563, "Localized string should start with %s"},
    {4569, "getAssignedTeam [player]"},
    {4570, "getAssignedTeam Error: param 1 is not an entity."},
    {4584, "Illegal team string '%s'. Must be allies, axis, or none."},
    {4585, "Illegal team string '%s'. Must be allies, axis, or none."},
    {4657, "not an entity"},
    {4674, "exceeded maximum number of parent script variables"},
    {4685, "entity %u is not an agent"},
    {4686, "not an entity"},
    {4704, "not an entity"},
    {4705, "not an entity"},
    {4706, "VehicleScript_Spawn: Owner entity is not a player"},
    {4751, "Parameter must be a valid client"},

    //if anyone finds more just add them here
};

typedef void(*Com_Error)(errorParm_t code, const char* fmt, ...);
Com_Error _Com_Error = nullptr;


void hook_Com_Error(errorParm_t code, const char* fmt, ...) {
    std::string fmtStr(fmt);
    std::istringstream iss(fmtStr);
    std::string firstToken;
    iss >> firstToken;

    int errorId = -1;
    bool isNumber = !firstToken.empty() && std::all_of(firstToken.begin(), firstToken.end(), ::isdigit);

    //this is the main error string replacement thingy
    if (isNumber) {
        errorId = std::stoi(firstToken);
        auto it = errorMap.find(errorId);
        if (it != errorMap.end()) {
            fmtStr = it->second;
        }
    }

    va_list args;
    va_start(args, fmt);

    //needed copy cuz original was getting cleared
    //UPDATE: why did i do this, just pass the formatted string with no va args into com_error like what
    //TODO: do what i said above.
    va_list argsCopy;
    va_copy(argsCopy, args);

    int needed = vsnprintf(nullptr, 0, fmtStr.c_str(), args);
    va_end(args);

    if (needed < 0) {
        _Com_Error(code, fmtStr.c_str());
        va_end(argsCopy);
        return;
    }

    std::vector<char> buf(needed + 1);
    vsnprintf(buf.data(), buf.size(), fmtStr.c_str(), argsCopy);
    va_end(argsCopy);

    //taken from t6 so idk if this is SHG accurate
    Console::print("********************");
    Console::printf("ERROR: %s", buf.data());
    Console::print("********************");


    _Com_Error(code, "%s", buf.data());
}


void Errors::init() {
    DEV_INIT_PRINT();
    Hook::create("Com_Error", 0x8F750_b, &hook_Com_Error, &_Com_Error);
}
