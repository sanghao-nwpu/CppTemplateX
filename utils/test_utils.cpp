#include "config_manager.h"
#include "logger.h"
#include <glog/logging.h>
#include <iostream>

void test_logger_cpp(std::string log_dir) 
{
    std::string log_path = log_dir + "/test_logger_cpp.log";
    // 初始化日志系统
    Logger::Initialize(log_path);

    // 记录一些日志信息
    LOG(INFO) << "This is an info message";
    LOG(WARNING) << "This is a warning message";
    LOG(ERROR) << "This is an error message";
    // 注意：LOG(FATAL) 会导致程序崩溃，因为它被设计用来记录致命错误

    // 关闭日志系统
    Logger::Shutdown();
}

void test_logger_glog_example(std::string log_dir) 
{
    std::string log_path = log_dir + "/test_logger.log";    
    // 初始化日志系统
    TestLogging(false);
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
    
    // 初始化 glog
    google::InitGoogleLogging(argv[0]);

    // 设置日志输出目录
    std::string log_dir = "../examples";
    google::SetLogDestination(google::INFO, (log_dir + "/my_log_").c_str());  // INFO 日志
    std::cout << "Log directory: " << log_dir << std::endl;
    google::SetLogDestination(google::WARNING, (log_dir + "/my_log_").c_str());  // WARNING 日志
    std::cout << "Log directory: " << log_dir << std::endl;
    google::SetLogDestination(google::ERROR, (log_dir + "/my_log_").c_str());  // ERROR 日志
    std::cout << "Log directory: " << log_dir << std::endl;
    google::SetLogDestination(google::FATAL, (log_dir + "/my_log_").c_str());  // FATAL 日志
    std::cout << "Log directory: " << log_dir << std::endl;
    // 设置日志文件的最大大小（单位：MB）
    FLAGS_max_log_size = 10;  // 每个日志文件最大 10MB

    // 设置日志是否输出到控制台
    FLAGS_logtostderr = false;  // 不输出到控制台
    FLAGS_alsologtostderr = false;  // 不额外输出到控制台

    // 创建日志目录（如果不存在）
    system(("mkdir -p " + log_dir).c_str());

    // 记录日志
    LOG(INFO) << "This is an INFO message.";
    std::cout << "This is a cout message." << std::endl;
    LOG(WARNING) << "This is a WARNING message.";
    std::cout << "This is a cout message." << std::endl;
    LOG(ERROR) << "This is an ERROR message.";
    std::cout << "This is a cout message." << std::endl;

    // 关闭 glog
    google::ShutdownGoogleLogging();    
    // test_config_manager(argv[1]);
    // // test_logger_glog_example(argv[1]);
    // test_logger_cpp(argv[1]);
    return 0;
}
