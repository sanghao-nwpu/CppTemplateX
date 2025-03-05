#include "config_manager.h"
#include "logger.h"
#include <iostream>

// void test_logger(std::string log_dir) 
// {
//     std::string log_path = log_dir + "/test_logger.log";
//     // 初始化日志系统
//     Logger::Initialize(log_path);

//     // 记录一些日志信息
//     LOG(INFO) << "This is an info message";
//     LOG(WARNING) << "This is a warning message";
//     LOG(ERROR) << "This is an error message";
//     // 注意：LOG(FATAL) 会导致程序崩溃，因为它被设计用来记录致命错误

//     // 关闭日志系统
//     Logger::Shutdown();
// }

void test_logger(std::string log_dir) 
{
    std::string log_path = log_dir + "/test_logger.log";    
    // 初始化日志系统
    TestLogging(false);
}


void test_config_manager(const std::string& config_path) {
    ConfigManager config(config_path);

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
    test_config_manager(argv[1]);
    test_logger(argv[1]);
    return 0;
}
