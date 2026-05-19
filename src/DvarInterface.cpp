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
#include "Exec.hpp"
#include "FuncPointers.h"
#include <algorithm>
#include <iomanip>
#include "DevDef.h"

std::unordered_map<std::string, std::string> DvarInterface::userToEngineMap;
std::unordered_map<std::string, std::string> DvarInterface::engineToUserMap;
std::unordered_map<std::string, std::string> DvarInterface::descriptionMap; //so descriptions are no longer stored within the dvar_t structure :/

namespace {
    std::string normalizeCommandToken(const std::string& token) {
        std::string normalized = token;
        if (!normalized.empty() && normalized[0] == '/') {
            normalized.erase(0, 1);
        }

        std::transform(normalized.begin(), normalized.end(), normalized.begin(), GameUtil::asciiToLower);
        return normalized;
    }

    bool isTranslatableDvarPrefix(const std::string& commandName) {
        return commandName == "toggle"
            || commandName == "togglep"
            || commandName == "set"
            || commandName == "seta"
            || commandName == "reset";
    }

    bool hasProtectedSetter(dvarType_t type) {
        return type == DVAR_TYPE_FLOAT_SECURE;
    }

    bool tryParseFloat(const std::string& text, float& outValue) {
        char* end = nullptr;
        outValue = std::strtof(text.c_str(), &end);
        return end != text.c_str() && *end == '\0';
    }

    std::string floatToConfigString(float value) {
        std::ostringstream stream;
        stream << std::setprecision(9) << value;
        return stream.str();
    }

    std::string quoteCommandTokenIfNeeded(const std::string& token) {
        if (token.empty()) {
            return "\"\"";
        }

        if (token.find_first_of(" \t\r\n\"") == std::string::npos) {
            return token;
        }

        std::string escapedToken;
        escapedToken.reserve(token.size());

        for (const char ch : token) {
            if (ch == '"') {
                escapedToken += "\\\"";
            }
            else {
                escapedToken.push_back(ch);
            }
        }

        return "\"" + escapedToken + "\"";
    }

    std::string buildCommandString(const std::vector<std::string>& tokens) {
        std::string rebuiltCommand;

        for (std::size_t i = 0; i < tokens.size(); ++i) {
            if (i != 0) {
                rebuiltCommand += ' ';
            }

            rebuiltCommand += quoteCommandTokenIfNeeded(tokens[i]);
        }

        return rebuiltCommand;
    }

    bool setProtectedDvarValue(dvar_t* dvar, const std::string& engineString, const std::string& value) {
        if (!dvar || !hasProtectedSetter(dvar->type)) {
            return false;
        }

        std::vector<std::string> directSetCmd;
        directSetCmd.push_back(engineString);
        directSetCmd.push_back(value);

        std::string dvarName = engineString;
        return DvarInterface::setDvar(dvarName, directSetCmd);
    }

    bool setProtectedDvarToggle(dvar_t* dvar, const std::string& engineString, const std::vector<std::string>& parsedCmd) {
        if (parsedCmd.size() < 3) {
            return false;
        }

        if (dvar->type != DVAR_TYPE_FLOAT_SECURE) {
            return false;
        }

        float currentValue = 0.0f;
        if (!tryParseFloat(GameUtil::dvarValueToString(dvar, false, false), currentValue)) {
            return false;
        }

        std::size_t nextValueIndex = 2;
        for (std::size_t i = 2; i < parsedCmd.size(); ++i) {
            float toggleValue = 0.0f;
            if (!tryParseFloat(parsedCmd[i], toggleValue)) {
                return false;
            }

            if (std::fabs(currentValue - toggleValue) <= 0.0001f) {
                nextValueIndex = i + 1;
                if (nextValueIndex >= parsedCmd.size()) {
                    nextValueIndex = 2;
                }
                break;
            }
        }

        return setProtectedDvarValue(dvar, engineString, parsedCmd[nextValueIndex]);
    }
}

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

    //will use direct writes for protected dvars to ensure full control
    switch (var->type)
    {
    case DVAR_TYPE_FLOAT_SECURE:
    {
        if (cmd.size() < 2) {
            return false;
        }

        char* end = nullptr;
        const float value = std::strtof(cmd[1].c_str(), &end);

        if (end == cmd[1].c_str() || *end != '\0') {
            return false;
        }

        GameUtil::setDvarSecureFloat(var, value);
        if (GameUtil::toLower(engineString) == "cg_fov") {
            Exec::updateAutoexecDvar("cg_fov", cmd[1]);
        }
        return true;
    }

    case DVAR_TYPE_BOOL_SECURE:
    {
        if (cmd.size() < 2) {
            return false;
        }
        
        const std::string valueLower = [&]() {
            std::string s = cmd[1];
            std::transform(s.begin(), s.end(), s.begin(), GameUtil::asciiToLower);
            return s;
        }();
        
        bool value;
        
        if (valueLower == "1" || valueLower == "true" || valueLower == "on" || valueLower == "yes") {
            value = true;
        }
        else if (valueLower == "0" || valueLower == "false" || valueLower == "off" || valueLower == "no") {
            value = false;
        }
        else {
            return false;
        }
        
        GameUtil::setDvarSecureBool(var, value);
        return true;
    }

    case DVAR_TYPE_INT_SECURE:
    {
        //if (cmd.size() < 2) {
        //    return false;
        //}
        //
        //char* end = nullptr;
        //const long value = std::strtol(cmd[1].c_str(), &end, 10);
        //
        //if (end == cmd[1].c_str() || *end != '\0') {
        //    return false;
        //}
        //
        //GameUtil::setDvarSecureInt(var, static_cast<int>(value));
        //return true;
    }

    default:
        break;
    }

    // Normal dvar path.
    std::vector<std::string> rebuiltCmd;
    rebuiltCmd.reserve(cmd.size() + 1);
    rebuiltCmd.push_back("set");
    rebuiltCmd.push_back(engineString);

    for (std::size_t i = 1; i < cmd.size(); ++i) {
        rebuiltCmd.push_back(cmd[i]);
    }

    std::string dvarCmd = buildCommandString(rebuiltCmd);

    int flags = var->flags;
    var->flags = 0;
    GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, dvarCmd.c_str());
    var->flags = flags;

    return true;
}

bool DvarInterface::setProtectedDvarFromPrefixedCommand(const std::string& cmd) {
    std::vector<std::string> parsedCmd = Console::parseCmdToVec(cmd);
    if (parsedCmd.size() < 2) {
        return false;
    }

    const std::string normalizedPrefix = normalizeCommandToken(parsedCmd[0]);
    if (!isTranslatableDvarPrefix(normalizedPrefix)) {
        return false;
    }

    const std::string engineString = DvarInterface::toEngineString(parsedCmd[1]);
    dvar_t* var = Functions::_Dvar_FindVar(engineString.c_str());
    if (!var || !hasProtectedSetter(var->type)) {
        return false;
    }

    if (normalizedPrefix == "set" || normalizedPrefix == "seta") {
        if (parsedCmd.size() < 3) {
            return false;
        }

        return setProtectedDvarValue(var, engineString, parsedCmd[2]);
    }

    if (normalizedPrefix == "toggle" || normalizedPrefix == "togglep") {
        return setProtectedDvarToggle(var, engineString, parsedCmd);
    }

    if (normalizedPrefix == "reset") {
        GameUtil::setDvarSecureFloat(var, var->reset.value);
        if (GameUtil::toLower(engineString) == "cg_fov") {
            Exec::updateAutoexecDvar("cg_fov", floatToConfigString(var->reset.value));
        }
        return true;
    }

    return false;
}

bool DvarInterface::translatePrefixedCommand(std::string& cmd) {
    std::vector<std::string> parsedCmd = Console::parseCmdToVec(cmd);
    if (parsedCmd.size() < 2) {
        return false;
    }

    const std::string normalizedPrefix = normalizeCommandToken(parsedCmd[0]);
    if (!isTranslatableDvarPrefix(normalizedPrefix)) {
        return false;
    }

    const std::string engineString = DvarInterface::toEngineString(parsedCmd[1]);
    if (!Functions::_Dvar_FindVar(engineString.c_str())) {
        return false;
    }

    parsedCmd[0] = normalizedPrefix;
    parsedCmd[1] = engineString;
    cmd = buildCommandString(parsedCmd);
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
 * @return The dvar description if found; otherwise uses a placeholder
 */
std::string DvarInterface::getDvarDescription(const std::string& engineStr) {
    auto it = descriptionMap.find(engineStr);
    if (it != descriptionMap.end()) {
        return it->second;
    }
    return "No Description for this Dvar"; //couldnt find
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


/**
 * @brief Registers a integer dvar and adds it to the dvar mapping system.
 *
 * @param name The name of the dvar.
 * @param val The default value.
 * @param min The minimum value.
 * @param max The maximum value.
 * @param flags Dvar flags.
 * @param description A description of the dvar.
 */
void DvarInterface::registerInt(const char* name, int val, int min, int max, unsigned int flags, const char* description) {
    Functions::_Dvar_RegisterInt(name, val, min, max, flags);
    DvarInterface::addMapping(name, name, description);
}

/**
 * @brief Registers a float dvar and adds it to the dvar mapping system.
 *
 * @param name The name of the dvar.
 * @param val The default value.
 * @param min The minimum value.
 * @param max The maximum value.
 * @param flags Dvar flags.
 * @param description A description of the dvar.
 */
void DvarInterface::registerFloat(const char* name, float val, float min, float max, unsigned int flags, const char* description) {
    Functions::_Dvar_RegisterFloat(name, val, min, max, flags);
    DvarInterface::addMapping(name, name, description);
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
