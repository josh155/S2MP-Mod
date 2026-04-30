///////////////////////////////////////////////
//              Config Manager
//	Simple config manager for some mod stuff
////////////////////////////////////////////////
#include "pch.h"
#include "ConfigManager.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

static std::string trim(const std::string& str) {
    const auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }

    const auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

std::unordered_map<std::string, std::string>
ConfigManager::loadConfig(const std::string& filename) {
    std::unordered_map<std::string, std::string> config;

    std::ifstream file(filename);
    if (!file.is_open()) {
        return config;
    }

    std::string line;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        const size_t delimiterPos = line.find('=');

        if (delimiterPos == std::string::npos) {
            continue;
        }

        std::string key = trim(line.substr(0, delimiterPos));
        std::string value = trim(line.substr(delimiterPos + 1));

        if (!key.empty()) {
            config[key] = value;
        }
    }

    return config;
}

bool ConfigManager::saveConfig(const std::string& filename, const std::unordered_map<std::string, std::string>& config) {
    std::ofstream file(filename, std::ios::trunc);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& [key, value] : config) {
        file << key << "=" << value << '\n';
    }

    return true;
}

bool ConfigManager::readConfigValue(const std::string& filename,const std::string& key,bool defaultValue) {
    auto config = loadConfig(filename);

    auto it = config.find(key);
    if (it == config.end()) {
        return defaultValue;
    }

    std::string value = it->second;
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    return value == "true" || value == "1" || value == "yes" || value == "on";
}

bool ConfigManager::writeConfigValue(const std::string& filename,const std::string& key,bool value) {
    auto config = loadConfig(filename);

    config[key] = value ? "true" : "false";

    return saveConfig(filename, config);
}

bool ConfigManager::configExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}