#ifndef LOGGER_H
#define LOGGER_H

#include <glog/logging.h>

class Logger {
public:
    static void Initialize(const std::string& log_dir);
    static void Shutdown();
};

void TestLogging(bool check_counts);

#endif // LOGGER_H
