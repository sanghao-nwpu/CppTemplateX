/*
 * File: rotation.h
 * Created Date: Wednesday March 19th 2025
 * Author: sanghao-nwpu
 * -----
 * Last Modified:
 * Modified By:
 * -----
 * Copyright (c) 2025 None
 */


#ifndef ROTATION_H
#define ROTATION_H

#include <Eigen/Core>
#include <Eigen/Dense>

class Rotation {
public:
    Rotation();

    void fromAxisAngle(Eigen::Vector3d &axis, double angle);

    Eigen::Matrix3d asRotationMatrix();

private:
    Eigen::Quaterniond quat_;
};




#endif // ROTATION_H