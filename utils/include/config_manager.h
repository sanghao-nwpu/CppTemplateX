#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>
#include <string>
#include <map>

class ConfigManager {
public:
    explicit ConfigManager(const std::string& config_file_path);
    void loadConfig();
    void saveConfig();
    void setParam(const std::string& key, const YAML::Node& value);
    YAML::Node getParam(const std::string& key) const;

private:
    std::string config_file_path_;
    YAML::Node config_;
};

#endif // CONFIG_MANAGER_H
