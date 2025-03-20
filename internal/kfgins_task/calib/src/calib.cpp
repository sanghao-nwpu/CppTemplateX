

#include "calib.h"


Status Calib::AddImu(const Imu& imu)
{
    if (MotionStatus::STOPPED == vehicle_status_.motion_status)
    {
        imu_stat_array_.push_back(imu);
        if (IMU_STAT_ARRAY_SIZE < imu_stat_array_.size())
        {
            imu_stat_array_.pop_front();
        }
    }
    else
    {
        imu_stat_array_.clear();
    }
}
Status Calib::AddGnss(const Gnss& gnss)
{
    return Status::STATUS_OK;
}
Status Calib::updateVehicleStatus()
{
    return Status::STATUS_OK;
}
Status Calib::TryCalib()
{
    return Status::STATUS_OK;
}
Status Calib::GetCalibResult(CalibResult &calib_result)
{
    return Status::STATUS_OK;
}