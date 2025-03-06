#include "logger.h"
#include <glog/logging.h>
#include <string>

void Logger::Initialize(const std::string& log_dir) {
    // 设置日志文件的存储路径
    google::SetLogDestination(google::GLOG_INFO, (log_dir + "/info_").c_str());
    google::SetLogDestination(google::GLOG_WARNING, (log_dir + "/warning_").c_str());
    google::SetLogDestination(google::GLOG_ERROR, (log_dir + "/error_").c_str());
    google::SetLogDestination(google::GLOG_FATAL, (log_dir + "/fatal_").c_str());


    // 初始化glog
    google::InitGoogleLogging("MyApp");
}

void TestLogging(bool check_counts) {
    int base_num_infos   = google::LogMessage::num_messages(google::GLOG_INFO);
    int base_num_warning = google::LogMessage::num_messages(google::GLOG_WARNING);
    int base_num_errors  = google::LogMessage::num_messages(google::GLOG_ERROR);
  
    LOG(INFO) << std::string("foo ") << "bar " << 10 << ' ' << 3.4;
    for ( int i = 0; i < 10; ++i ) {
      int old_errno = errno;
      errno = i;
      PLOG_EVERY_N(ERROR, 2) << "Plog every 2, iteration " << i;
      errno = old_errno;
  
      LOG_EVERY_N(ERROR, 3) << "Log every 3, iteration " << i << std::endl;
      LOG_EVERY_N(ERROR, 4) << "Log every 4, iteration " << i << std::endl;
  
      LOG_IF_EVERY_N(WARNING, true, 5) << "Log if every 5, iteration " << i;
      LOG_IF_EVERY_N(WARNING, false, 3)
          << "Log if every 3, iteration " << i;
      LOG_IF_EVERY_N(INFO, true, 1) << "Log if every 1, iteration " << i;
      LOG_IF_EVERY_N(ERROR, (i < 3), 2)
          << "Log if less than 3 every 2, iteration " << i;
    }
    LOG_IF(WARNING, true) << "log_if this";
    LOG_IF(WARNING, false) << "don't log_if this";
  
    char s[] = "array";
    LOG(INFO) << s;
    const char const_s[] = "const array";
    LOG(INFO) << const_s;
    int j = 1000;
  
    google::LogMessage("foo", google::LogMessage::kNoLogPrefix, google::GLOG_INFO).stream() << "no prefix";

}
  

void Logger::Shutdown() {
    // 关闭glog
    google::ShutdownGoogleLogging();
}
