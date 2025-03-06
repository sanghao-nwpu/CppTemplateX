cmake_minimum_required(VERSION 3.10)
project(ConfigManager)

# 查找yaml-cpp库
find_package(yaml-cpp REQUIRED)

# 包含yaml-cpp头文件
include_directories(${yaml-cpp_INCLUDE_DIRS})
message(STATUS "yaml-cpp_INCLUDE_DIRS: ${yaml-cpp_INCLUDE_DIRS}")

# 在你的项目根目录下的CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(CppTemplateX)

# 设置yaml-cpp库
set(YAML_CPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/yaml-cpp/include)
set(YAML_CPP_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/yaml-cpp/lib/libyaml-cpp.a)
include_directories(${YAML_CPP_INCLUDE_DIR})
message(STATUS "YAML_CPP_INCLUDE_DIR: ${YAML_CPP_INCLUDE_DIR}")

# 设置glog库
set(GLOG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/glog/lib/glog/include)
set(GLOG_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/glog/lib/libglog.a)
include_directories(${GLOG_INCLUDE_DIRS})

# if (GLOG_FOUND)
#     message(STATUS "glog found")
# else()
#     message(FATAL_ERROR "glog not found")
# endif()


# 包含项目头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "include_directories: ${CMAKE_CURRENT_SOURCE_DIR}/include")

# 添加可执行文件
file(GLOB_RECURSE SOURCES include/*.h src/*.cpp)
add_executable(test_utils test_utils.cpp ${SOURCES})

# 链接yaml-cpp库
target_link_libraries(test_utils ${YAML_CPP_LIBRARY})
message(STATUS "target linkYAML_CPP_LIBRARY: ${YAML_CPP_LIBRARY}")

# # 链接gflags库
# target_link_libraries(test_utils ${GFLAGS_LIBRARY})
# message(STATUS "target linkGFLAGS_LIBRARY: ${GFLAGS_LIBRARY}")

# 链接glog库
target_link_libraries(test_utils ${GLOG_LIBRARY})
message(STATUS "target linkGLOG_LIBRARY: ${GLOG_LIBRARY}")
