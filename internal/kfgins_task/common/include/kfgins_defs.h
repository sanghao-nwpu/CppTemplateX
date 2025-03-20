#ifndef KFGINS_TASK_DEFS_H
#define KFGINS_TASK_DEFS_H

#include <Eigen/Core>

namespace kfgins
{
    constexpr int IMU_STAT_ARRAY_SIZE = 100;

    enum class Status
    {
        STATUS_OK = 0,
        STATUS_ERROR = 1,
        STATUS_TIMEOUT = 2,
    };
    
    // 定义车辆的运动状态
    enum class MotionStatus {
        UNKNOWN = 0,
        MOVING = 1,
        STOPPED = 2
    };

    // 定义车辆的方向状态
    enum class DirectionStatus {
        UNKNOWN = 0,
        STRAIGHT = 1,
        TURNING = 2
    };

    // 定义车辆的速度状态
    enum class SpeedStatus {
        UNKNOWN = 0,
        CONSTANT_SPEED = 1,
        ACCELERATING = 2,
        DECELERATING = 3
    };

    // 定义车辆状态的结构体
    struct VehicleStatus {
        MotionStatus motion_status;       // 运动状态：运动或静止
        DirectionStatus direction_status; // 方向状态：直行或转弯
        SpeedStatus speed_status;         // 速度状态：加速、减速或匀速
    };


    enum class GnssSolType
    {
        NONE = 0,
        STANDARD = 1,
        RTK_FIXED = 4,
        RTK_FLOAT = 5,
    };

    struct Imu
    {
        double timestamp;
        Eigen::Vector3d acc;
        Eigen::Vector3d gyro;
        bool flag;
    };
    
    struct Gnss
    {
        double timestamp;
        Eigen::Vector3d blh;    // latitude, longitude, height
        Eigen::Vector3d pos_dev;    // position deviation in local frame(NED)
        Eigen::Vector3d vel;    // velocity in global frame(NED)，根据vel_forward/track/vel_upward计算得到
        Eigen::Vector3d vel_dev;// velocity deviation in local frame(NED)
        double vel_forward;     // velocity in forward direction
        double vel_upward;      // velocity in upward direction
        double vel_track;       // velocity track direction (deg) 北偏东
        double hdop;
        GnssSolType sol_type;
    };

    struct GnssPos
    {
        double timestamp;
        Eigen::Vector3d blh;    // latitude, longitude, height
        Eigen::Vector3d pos_dev;    // position deviation in local frame(ENU)
        double hdop;
        GnssSolType sol_type;
    };

    struct GnssVel
    {
        double timestamp;
        Eigen::Vector3d vel;    // velocity in global frame(NED)，根据vel_forward/track/vel_upward计算得到
        Eigen::Vector3d vel_dev;// velocity deviation in local frame(NED)
        double vel_forward;     // velocity in forward direction
        double vel_upward;      // velocity in upward direction
        double vel_track;       // velocity track direction (deg) 北偏东
        GnssSolType sol_type;
    };

    struct CalibAccData
    {
        double timestamp;
        Eigen::Vector3d acc_meas;   /** 原始测量值 */
        Eigen::Vector3d acc_veh;    /** 车体实际加速度 前右下 */
    };

    struct CalibGyroData
    {
        double timestamp;
        Eigen::Vector3d gyro_meas;  /** 原始数据去偏置 deg/s */
        Eigen::Vector3d gyro_veh;   /** 车体实际角速度 前右下 deg/s*/
    };
    
}



#endif // COMMON_H