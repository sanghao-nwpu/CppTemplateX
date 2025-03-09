#ifndef TICTOC_H
#define TICTOC_H

#include <chrono>
#include <iostream>

class TicToc {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;  // 开始时间点
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;    // 结束时间点

public:
    // 开始计时
    void tic();

    // 结束计时并打印耗时（单位：毫秒）
    void toc(const std::string& message = "");

    // 获取耗时（单位：毫秒）
    double elapsed() const;
};

#endif // TICTOC_H