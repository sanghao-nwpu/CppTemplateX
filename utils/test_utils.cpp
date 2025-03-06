#include "config_manager.h"
#include "logger.h"
#include <glog/logging.h>
#include <iostream>

void test_logger(const std::string &logger_name, const std::string &log_dir) 
{
    Logger logger;

    logger.Initialize(logger_name, log_dir);

    LOG(INFO) << "This is an INFO message.";
    LOG(WARNING) << "This is a WARNING message.";
    LOG(ERROR) << "This is an ERROR message.";

    logger.Shutdown();
}

void test_config_manager(const std::string& config_dir) {
    ConfigManager config(config_dir + "/config.yaml");

    // 加载配置
    config.loadConfig();

    // 获取参数
    YAML::Node param = config.getParam("example_key");
    if (!param.IsNull()) {
        std::cout << "Value of example_key: " << param.as<std::string>() << std::endl;
    } else {
        std::cout << "example_key not found, setting to default value." << std::endl;
        config.setParam("example_key", YAML::Node("default_value"));
    }

    // 保存配置
    config.saveConfig();
}


int main(int argc, char* argv[]) {
    std::string log_dir = "./logs";
    test_logger("init_test", log_dir);
    test_config_manager("../examples/");
    return 0;
}
