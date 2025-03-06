#include "logger.h"
#include <glog/logging.h>
#include <string>

void Logger::Initialize(const std::string &logger_name, const std::string& log_dir) {
    // 创建日志目录（如果不存在）
    system(("mkdir -p " + log_dir).c_str());
        
    // 设置日志目录
    FLAGS_log_dir = log_dir;

    // 初始化 glog
    google::InitGoogleLogging(logger_name.data());
    // 设置日志级别
    FLAGS_minloglevel = 0;  // 输出所有日志

    // 设置日志文件的最大大小（单位：MB）
    FLAGS_max_log_size = 10;  // 每个日志文件最大 10MB

    // 设置日志是否输出到控制台
    FLAGS_logtostderr = false;  // 不输出到控制台
    FLAGS_alsologtostderr = false;  // 不额外输出到控制台

}
  

void Logger::Shutdown() {
    // 关闭glog
    google::ShutdownGoogleLogging();
}
