#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

enum class FileType {
    TEXT,
    BINARY
};

enum class FileMode {
    READ,
    WRITE
};

class FileIO {
protected:
    int columns_;          // 数据的列数
    FileType file_type_;   // 文件类型
    FileMode file_mode_;   // 文件打开模式
    std::fstream filefp_;    // 文件流（支持输入和输出）
    char delimiter_;        // 字段分隔符

public:
    // 构造函数
    explicit FileIO(int cols = 1, 
                    FileType type = FileType::TEXT, 
                    FileMode mode = FileMode::READ, 
                    char delimiter = ' ');

    // 析构函数
    virtual ~FileIO();

    // 检查文件是否存在
    bool fileExists(const std::string& file_path) const;

    // 检查文件夹是否存在
    bool dirExists(const std::string& dir_path) const;

    // 创建文件夹（递归创建）
    bool createDir(const std::string& dir_path) const;

    // 删除文件
    bool deleteFile(const std::string& file_path) const;

    // 删除文件夹（递归删除）
    bool deleteDir(const std::string& dir_path) const;

    // 打开文件
    bool openFile(const std::string& file_path);

    // 关闭文件
    void closeFile();

    // 读取下一行数据
    virtual std::vector<double> next();

    // 跳过指定行
    void skipLines(int num_lines);

    // 写入数据（格式化）
    virtual bool writeData(const std::vector<double>& data, const std::vector<int>& precisions = {});

    // 设置列数
    void setColumns(int cols);

    // 获取列数
    int getColumns() const;

    // 设置文件类型
    void setFileType(FileType type);

    // 获取文件类型
    FileType getFileType() const;

    // 设置文件打开模式
    void setFileMode(FileMode mode);

    // 获取文件打开模式
    FileMode getFileMode() const;

    void setDelimiter(char delimiter);

    char getDelimiter() const;
};

#endif // FILEIO_H