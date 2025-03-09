#include "fileio.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// 构造函数
FileIO::FileIO(int cols, FileType type, FileMode mode, char delimiter)
    : columns_(cols), file_type_(type), file_mode_(mode), delimiter_(delimiter) {}

// 析构函数
FileIO::~FileIO() {
    closeFile();
}

// 检查文件是否存在
bool FileIO::fileExists(const std::string& file_path) const {
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0);
}

// 检查文件夹是否存在
bool FileIO::dirExists(const std::string& dir_path) const {
    struct stat buffer;
    return (stat(dir_path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

// 创建文件夹（递归创建）
bool FileIO::createDir(const std::string& dir_path) const {
    if (dirExists(dir_path)) {
        return true;  // 文件夹已存在
    }

    size_t pos = 0;
    std::string path = dir_path;
    while ((pos = path.find_first_of('/', pos + 1)) != std::string::npos) {
        std::string subdir = path.substr(0, pos);
        if (!dirExists(subdir) && mkdir(subdir.c_str(), 0777) != 0) {
            std::cerr << "Error: Failed to create directory: " << subdir << std::endl;
            return false;
        }
    }

    if (mkdir(path.c_str(), 0777) != 0) {
        std::cerr << "Error: Failed to create directory: " << path << std::endl;
        return false;
    }

    return true;
}

// 删除文件
bool FileIO::deleteFile(const std::string& file_path) const {
    if (std::remove(file_path.c_str()) != 0) {
        std::cerr << "Error: Failed to delete file: " << file_path << std::endl;
        return false;
    }
    return true;
}

// 删除文件夹（递归删除）
bool FileIO::deleteDir(const std::string& dir_path) const {
    if (!dirExists(dir_path)) {
        return true;  // 文件夹不存在
    }

    DIR* dir = opendir(dir_path.c_str());
    if (!dir) {
        std::cerr << "Error: Failed to open directory: " << dir_path << std::endl;
        return false;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") {
            continue;
        }

        std::string full_path = dir_path + "/" + name;
        if (entry->d_type == DT_DIR) {
            deleteDir(full_path);  // 递归删除子文件夹
        } else {
            deleteFile(full_path);  // 删除文件
        }
    }

    closedir(dir);

    if (rmdir(dir_path.c_str()) != 0) {
        std::cerr << "Error: Failed to delete directory: " << dir_path << std::endl;
        return false;
    }

    return true;
}

// 打开文件
bool FileIO::openFile(const std::string& file_path) {
    if (filefp_.is_open()) {
        closeFile();  // 关闭已打开的文件
    }

    std::ios_base::openmode mode = std::ios_base::in;  // 默认输入模式
    if (file_mode_ == FileMode::WRITE) {
        mode = std::ios_base::out;  // 输出模式
    }

    if (file_type_ == FileType::BINARY) {
        mode |= std::ios_base::binary;  // 二进制模式
    }

    filefp_.open(file_path, mode);

    if (!filefp_.is_open()) {
        std::cerr << "Error: Failed to open file: " << file_path << std::endl;
        return false;
    }

    return true;
}

// 关闭文件
void FileIO::closeFile() {
    if (filefp_.is_open()) {
        filefp_.close();
    }
}

// 读取下一行数据
std::vector<double> FileIO::next() {
    std::vector<double> row(columns_);
    std::string line;
    std::string token;

    while (std::getline(filefp_, line)) {
        if (line.empty() || line[0] == '#') {
            continue;  // 跳过空行或注释行
        }

        std::istringstream iss(line);
        for (int i = 0; i < columns_; ++i) {
            if (!std::getline(iss, token, delimiter_)) {
                std::cerr << "Error: Data format should be: " << columns_ << " columns separated by " << delimiter_ << std::endl;
                break;  // 如果列数不足，跳出循环
            }
            row[i] = std::stod(token);
        }

        return row;
    }

    return {};  // 文件读取完毕
}

// 跳过指定行
void FileIO::skipLines(int num_lines) {
    std::string line;
    for (int i = 0; i < num_lines; ++i) {
        if (!std::getline(filefp_, line)) {
            break;
        }
    }
}

// 写入数据（格式化）
bool FileIO::writeData(const std::vector<double>& data, 
                       const std::vector<int>& precisions) {
    if (!filefp_.is_open() || file_mode_ != FileMode::WRITE) {
        std::cerr << "Error: File is not open for writing." << std::endl;
        return false;
    }

    if (file_type_ == FileType::BINARY)
    {
        std::cerr << "Error: Binary file writing is not supported." << std::endl;
        return false;
    }
    else
    {
        for (size_t i = 0; i < data.size(); ++i) {   
            filefp_ << std::fixed << std::setprecision(precisions.empty() ? 6 : precisions[i]) << data[i];
            if (i < data.size() - 1) {
                filefp_ << delimiter_;  // 添加分隔符
            }
        }
        filefp_ << "\n";
    }

    return true;
}

// 设置列数
void FileIO::setColumns(int cols) {
    columns_ = cols;
}

// 获取列数
int FileIO::getColumns() const {
    return columns_;
}

// 设置文件类型
void FileIO::setFileType(FileType type) {
    file_type_ = type;
}

// 获取文件类型
FileType FileIO::getFileType() const {
    return file_type_;
}

// 设置文件打开模式
void FileIO::setFileMode(FileMode mode) {
    file_mode_ = mode;
}

// 获取文件打开模式
FileMode FileIO::getFileMode() const {
    return file_mode_;
}

// 设置字段分隔符
void FileIO::setDelimiter(char delimiter) {
    delimiter_ = delimiter;
}

// 获取字段分隔符
char FileIO::getDelimiter() const {
    return delimiter_;
}