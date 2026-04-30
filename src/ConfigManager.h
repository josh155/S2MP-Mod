#pragma once
#include <string>
#include <unordered_map>

class ConfigManager {
public:
    static bool readConfigValue(const std::string& filename, const std::string& key, bool defaultValue = false);
    static bool writeConfigValue(const std::string& filename, const std::string& key, bool value);
    static bool configExists(const std::string& filename);

private:
    static std::unordered_map<std::string, std::string>loadConfig(const std::string& filename);
    static bool saveConfig(const std::string& filename, const std::unordered_map<std::string, std::string>& config);
};