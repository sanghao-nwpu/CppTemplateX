/*
 * File: rotation.cpp
 * Created Date: Wednesday March 19th 2025
 * Author: sanghao-nwpu
 * -----
 * Last Modified:
 * Modified By:
 * -----
 * Copyright (c) 2025 None
 */


#include "rotation.h"
#include <Eigen/Dense>

Rotation::Rotation() {
   quat_.setIdentity();
}



void Rotation::fromAxisAngle(Eigen::Vector3d &axis, double angle)
{
    quat_ = Eigen::Quaterniond(Eigen::AngleAxisd(angle, axis));
    return ;
}


Eigen::Matrix3d Rotation::asRotationMatrix()
{
    return quat_.toRotationMatrix();
}




