## Eigen3 configuration
message("Eigen3 configuration...")

find_package(Eigen3 REQUIRED)
if (Eigen3_FOUND)
    if (NOT Eigen3_INCLUDE_DIRS)
        set(Eigen3_INCLUDE_DIRS "/usr/include/eigen3")  # 根据实际路径修改
    endif()
    include_directories(${Eigen3_INCLUDE_DIRS})
    message("Eigen3 found in system.")
    message("Eigen3 version: ${Eigen3_VERSION}")
    message("Eigen3 include directory: ${Eigen3_INCLUDE_DIRS}")
else()
    message("Eigen3 not found in system. Using local version.")
    include_directories(${CMAKE_SOURCE_DIR}/thirdparty/eigen3)
endif()