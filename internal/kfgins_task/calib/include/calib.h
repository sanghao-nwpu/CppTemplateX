/*
 * File: calib.h
 * Created Date: Thursday March 20th 2025
 * Author: sanghao-nwpu
 * -----
 * Last Modified:
 * Modified By:
 * -----
 * Copyright (c) 2025 None
 */


#ifndef CALIB_H
#define CALIB_H

#include <deque>
#include "kfgins_defs.h"

using namespace kfgins;

struct CalibResult
{
    bool gyro_bias_flag;
    bool gyro_bias_dev_flag;
    bool acc_bias_flag;
    bool acc_bias_dev_flag;
    bool gyro_stat_dev_flag;
    bool acc_stat_dev_flag;
    bool gyro_move_dev_flag;
    bool acc_move_dev_flag;
    bool R_veh_imu_flag;
    bool R_veh_imu_dev_flag;
    bool imu_arm_flag;
    bool imu_arm_dev_flag;
    bool gnss_arm_flag;
    bool gnss_arm_dev_flag;
    bool imu_gnss_time_offset_flag;
    double imu_gnss_time_offset;    /** IMU 与 GNSS 时间偏差: imu_time = gnss_time + time_offset */
    Eigen::Vector3d gyro_bias;      /** 陀螺仪偏置 */
    Eigen::Vector3d gyro_bias_dev;  /** 陀螺仪偏置标定精度 */
    Eigen::Vector3d acc_bias;       /** 加速度计偏置 */
    Eigen::Vector3d acc_bias_dev;   /** 加速度计偏置标定精度 */
    Eigen::Vector3d gyro_stat_dev;  /** 陀螺仪静态噪声 */
    Eigen::Vector3d acc_stat_dev;   /** 加速度计静态噪声 */
    Eigen::Vector3d gyro_move_dev;  /** 陀螺仪运动噪声 */
    Eigen::Vector3d acc_move_dev;   /** 加速度计运动噪声 */
    Eigen::Matrix3d R_veh_imu;      /** 旋转外参，车体定义 前右下, R^veh_imu * imu = veh */
    Eigen::Vector3d R_veh_imu_dev;  /** 旋转外参标定精度 roll pitch yaw (deg) */
    Eigen::Vector3d imu_arm;        /** IMU 杆臂，在车体坐标系前右下的位置 */
    Eigen::Vector3d imu_arm_dev;    /** IMU 杆臂标定精度 */
    Eigen::Vector3d gnss_arm;       /** GNSS 杆臂，在车体坐标系前右下的位置 */
    Eigen::Vector3d gnss_arm_dev;   /** GNSS 杆臂标定精度 */
};

class Calib
{
private:
    /* data */
    std::deque<Imu> imu_stat_array_;         // 注意是连续的数据，用来计算陀螺偏置和静态IMU噪声
    std::deque<Imu> imu_const_vel_array_;    // 注意是连续的数据，用来计算 IMU 动态噪声，
    std::deque<Imu> imu_variable_vel_array_; // 可以不连续，用来收集数据标定外参
    std::deque<Imu> imu_turn_array_;         // 可以不连续，用来收集数据标定外参
    
    std::deque<Gnss> gnss_array_;

    std::deque<CalibAccData> calib_acc_array_;
    std::deque<CalibGyroData> calib_gyro_array_;

    int calib_variable_vel_count_;   /** 变速运动数据收集量 */
    int calib_turn_count_;           /** 转向运动数据收集量 */

    VehicleStatus vehicle_status_;
    CalibResult calib_result_;

    Status updateVehicleStatus();
    /**
     * @brief 计算车体的实际加速度和角速度
     * 
     * @param acc 
     * @param gyro 
     * @return Status 
     */
    Status calculateVehicleAccGryo(Eigen::Vector3d& acc, Eigen::Vector3d& gyro);

public:
    Calib(/* args */);
    Status AddImu(const Imu& imu);
    Status AddGnss(const Gnss& gnss);

    Status TryCalib();
    Status GetCalibResult(CalibResult &calib_result);
    ~Calib();
};

Calib::Calib(/* args */)
{
}

Calib::~Calib()
{
}


#endif //CALIB_H