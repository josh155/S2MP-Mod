////////////////////////////////////////////
//          DVar Interface
// 
//  Convert DVar strings into enumerated 
//  DVar strings for S2MP
////////////////////////////////////////////
#include "pch.h"
#include "DvarInterface.hpp"
#include "DvarMappings.hpp"
#include "Console.hpp"
#include "GameUtil.hpp"
#include "FuncPointers.h"
#include <algorithm>
#include "DevDef.h"

std::unordered_map<std::string, std::string> DvarInterface::userToEngineMap;
std::unordered_map<std::string, std::string> DvarInterface::engineToUserMap;
std::unordered_map<std::string, std::string> DvarInterface::descriptionMap; //so descriptions are no longer stored within the dvar_t structure :/

/**
 * @brief Sets a Dvar in the engine using the Dvar interface.
 *
 * Converts the provided user-facing dvar name to its engine equivalent,
 * builds a "set" command from the supplied command arguments, and
 * submits it to the engine command buffer.
 *
 * @param dvarname The user-facing name of the dvar to set.
 * @param cmd Command arguments where index 0 is the dvar name and
 *            subsequent elements are the values to assign.
 *
 * @return true if the dvar was found and a set command was issued;
 *         false if the dvar does not exist.
 */
bool DvarInterface::setDvar(std::string& dvarname, std::vector<std::string> cmd) {
    std::string dvarLower = dvarname;
    std::transform(dvarLower.begin(), dvarLower.end(), dvarLower.begin(), GameUtil::asciiToLower);

    std::string engineString = DvarInterface::toEngineString(dvarLower);
    dvar_t* var = Functions::_Dvar_FindVar(engineString.c_str());
    if (!var) {
        return false;
    }
    var->flags = 0;
    std::string dvarCmd = "set " + engineString;
    for (int i = 1; i < cmd.size(); ++i) { //skip 0 cuz thats dvarname
        dvarCmd += " " + cmd[i];
    }

    GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, dvarCmd.c_str());
    return true;
}

/**
 * @brief Gets the number of registered user-to-engine dvar mappings.
 *
 * @return The number of dvar mappings currently stored.
 */
unsigned int DvarInterface::getDvarListSize() {
    return DvarInterface::userToEngineMap.size();
}

/**
 * @brief Adds a user-to-engine dvar name mapping.
 *
 * The user-facing string is normalized to lowercase before being stored.
 *
 * @param userString The user-facing dvar name.
 * @param engineString The engine-facing dvar name.
 */
void DvarInterface::addMapping(const std::string& userString, const std::string& engineString) {
    std::string dvarLower = userString;
    std::transform(dvarLower.begin(), dvarLower.end(), dvarLower.begin(), GameUtil::asciiToLower);
    userToEngineMap[dvarLower] = engineString;
    engineToUserMap[engineString] = userString;
}

/**
 * @brief Adds a user-to-engine dvar name mapping with a description.
 *
 * The user-facing string is normalized to lowercase before being stored.
 * The description is associated with the engine-facing dvar name.
 *
 * @param userString The user-facing dvar name.
 * @param engineString The engine-facing dvar name.
 * @param description A description of the dvar.
 */
void DvarInterface::addMapping(const std::string& userString, const std::string& engineString, const std::string& description) {
    std::string dvarLower = userString;
    std::transform(dvarLower.begin(), dvarLower.end(), dvarLower.begin(), GameUtil::asciiToLower);
    userToEngineMap[dvarLower] = engineString;
    engineToUserMap[engineString] = userString;
    
    //add desc
    descriptionMap[engineString] = description;
}


/**
 * @brief Retrieves the description for a dvar.
 *
 * @param engineStr The engine-facing dvar name.
 *
 * @return The dvar description if found; otherwise "undefined".
 */
std::string DvarInterface::getDvarDescription(const std::string& engineStr) {
    auto it = descriptionMap.find(engineStr);
    if (it != descriptionMap.end()) {
        return it->second;
    }
    return "undefined"; //couldnt find
}

/**
 * @brief Converts a user-facing dvar name to its engine-facing equivalent.
 *
 * The lookup is performed case-insensitively. If no mapping exists,
 * the original string is returned.
 *
 * @param userString The user-facing dvar name.
 *
 * @return The engine-facing dvar name, or the original string if no mapping exists.
 */
std::string DvarInterface::toEngineString(const std::string& userString) {
    std::string dvarLower = userString;
    std::transform(dvarLower.begin(), dvarLower.end(), dvarLower.begin(), GameUtil::asciiToLower);
    auto it = userToEngineMap.find(dvarLower);
    if (it != userToEngineMap.end()) {
       // Console::devPrint(userString + " ----> " + it->second);
        return it->second;
    }
    return userString; //couldnt find
}

/**
 * @brief Converts an engine-facing dvar name to its user-facing equivalent.
 *
 * If no mapping exists, the original engine string is returned.
 *
 * @param engineString The engine-facing dvar name.
 *
 * @return The user-facing dvar name, or the original string if no mapping exists.
 */
std::string DvarInterface::toUserString(const std::string& engineString) {
    auto it = engineToUserMap.find(engineString);
    if (it != engineToUserMap.end()) {
        return it->second;
    }
    return engineString; //couldnt find
}


/**
 * @brief Registers a dvar using the same name for both user and engine mappings.
 *
 * @param name The dvar name.
 */
void DvarInterface::addDvarsWithName(const char* name) {
    addMapping(name, name);
}
void DvarInterface::addDvarsWithNameDesc(const char* name, const char* description) {
    addMapping(name, name, description);
}


/**
 * @brief Registers a boolean dvar and adds it to the dvar mapping system.
 *
 * @param name The name of the dvar.
 * @param val The default value.
 * @param flags Dvar flags.
 * @param description A description of the dvar.
 */
void DvarInterface::registerBool(const char* name, bool val, int flags, const char* description) {
    Functions::_Dvar_RegisterBool(name, val, flags);
    DvarInterface::addMapping(name, name, description); //TODO: make a dedicated function for custom dvars
}

void DvarInterface::addAllMappings() {
    for (const DvarMappingEntry& mapping : DvarMappings::entries) {
        if (mapping.description.empty()) {
            addMapping(std::string(mapping.user), std::string(mapping.engine));
        }
        else {
            addMapping(std::string(mapping.user), std::string(mapping.engine), std::string(mapping.description));
        }
    }
}

void DvarInterface::init() {
    DEV_INIT_PRINT();
    DvarInterface::addAllMappings();
    Console::infoPrint("Mapped " + std::to_string(DvarInterface::userToEngineMap.size()) + " DVars");
}