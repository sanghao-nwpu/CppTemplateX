cmake_minimum_required(VERSION 3.10.0)
project(kfgins VERSION 0.1.0 LANGUAGES C CXX)

set(LIBRARY_CMAKE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../../cmake")
message("LIBRARY_CMAKE_DIRECTORY: ${LIBRARY_CMAKE_DIRECTORY}")

set(PROJECT_WORKSPACE_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
message("PROJECT_WORKSPACE_DIR: ${PROJECT_WORKSPACE_DIR}")

# include eigen library
include(${LIBRARY_CMAKE_DIRECTORY}/eigen.cmake)

# include common module
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

# include rotation module
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rotation/include)

# source files
# 添加可执行文件
file(GLOB_RECURSE SOURCES rotation/src/*.cpp)

add_executable(test_rotation rotation/test_rotation.cpp ${SOURCES})