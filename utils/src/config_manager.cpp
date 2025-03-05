#include "config_manager.h"
#include <iostream>
#include <fstream>

ConfigManager::ConfigManager(const std::string& config_file_path) : config_file_path_(config_file_path) {}

void ConfigManager::loadConfig() {
    try {
        config_ = YAML::LoadFile(config_file_path_);
    } catch (const YAML::Exception& e) {
        std::cerr << "Error loading YAML file: " << e.what() << std::endl;
    }
}

void ConfigManager::saveConfig() {
    try {
        std::ofstream fout(config_file_path_);
        fout << config_;
    } catch (const YAML::Exception& e) {
        std::cerr << "Error saving YAML file: " << e.what() << std::endl;
    }
}

void ConfigManager::setParam(const std::string& key, const YAML::Node& value) {
    config_[key] = value;
}

YAML::Node ConfigManager::getParam(const std::string& key) const {
    return config_[key];
}
