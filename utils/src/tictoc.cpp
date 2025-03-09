#include "tictoc.h"

// 开始计时
void TicToc::tic() {
    start_time = std::chrono::high_resolution_clock::now();
}

// 结束计时并打印耗时（单位：毫秒）
void TicToc::toc(const std::string& message) {
    end_time = std::chrono::high_resolution_clock::now();
    double duration = elapsed();
    if (!message.empty()) {
        std::cout << message << " ";
    }
    std::cout << "Elapsed time: " << duration << " ms" << std::endl;
}

// 获取耗时（单位：毫秒）
double TicToc::elapsed() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
}