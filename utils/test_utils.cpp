#include "config_manager.h"
#include "logger.h"
#include "fileio.h"
#include "tictoc.h"
#include <glog/logging.h>
#include <iostream>
#include <thread>  // 用于模拟耗时操作

int test_tictoc()
{
    TicToc timer;

    // 开始计时
    timer.tic();

    // 模拟耗时操作（睡眠 1 秒）
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 结束计时并打印耗时
    timer.toc("Task 1");
    
    std::cout << "Returned elapsed time: " << timer.elapsed() << " ms" << std::endl;

    // 再次开始计时
    timer.tic();

    // 模拟耗时操作（睡眠 500 毫秒）
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 结束计时并打印耗时
    timer.toc("Task 2");
    std::cout << "Returned elapsed time: " << timer.elapsed() << " ms" << std::endl;

    return 0;
}

int test_fileio(const std::string& read_file_path, const std::string& write_file_path)
{
    FileIO file_io;

    // 设置文件打开模式为读取
    file_io.setFileMode(FileMode::READ);

    // 设置文件列数
    file_io.setColumns(3);

    // 设置文件分割符
    file_io.setDelimiter(',');

    // 打开文件
    if (!file_io.openFile(read_file_path)) {
        return 1;
    }

    // 逐行读取数据
    std::vector<double> row;
    while (!(row = file_io.next()).empty()) {
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    // 关闭文件
    file_io.closeFile();

    std::cout << "File read complete." << std::endl;

    // 设置文件打开模式为写入
    file_io.setFileMode(FileMode::WRITE);

    // 打开文件
    if (!file_io.openFile(write_file_path)) {
        return 1;
    }

    // 写入数据
    std::vector<double> data = {1.23, 4.56, 7.89};
    // std::vector<int> precisions = {2, 3, 4};
    file_io.writeData(data);

    // 关闭文件
    file_io.closeFile();
    return 0;
}

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
    std::string data_dir = "../examples/";
    test_logger("init_test", log_dir);
    test_config_manager(data_dir);
    test_fileio(data_dir + "data.txt", data_dir + "output.txt");
    test_tictoc();
    return 0;
}
