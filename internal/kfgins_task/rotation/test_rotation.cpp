/*
 * File: test_rotation.cpp
 * Created Date: Wednesday March 19th 2025
 * Author: sanghao-nwpu
 * -----
 * Last Modified:
 * Modified By:
 * -----
 * Copyright (c) 2025 None
 */


#include <iostream>
#include "rotation.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Rotation rotation;

    Eigen::Vector3d axis(0, 0, 1);
    Eigen::Matrix3d R = Eigen::Matrix3d::Zero();
    double angle = 30 * M_PI / 180.0;
    rotation.fromAxisAngle(axis, angle);
    R = rotation.asRotationMatrix();

    std::cout << "Rotation matrix: " << std::endl << R << std::endl;

    return 0;
}