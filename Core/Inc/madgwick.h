#ifndef MADGWICK_H
#define MADGWICK_H

#include <math.h>
#include <imu_data.h>

#define M_PI_MINE 3.14159265358979
#define gyroMeasError M_PI_MINE * (5.0f / 180.0f) // gyroscope measurement error in rad/s (shown as 5 deg/s)
#define gyroMeasDrift M_PI_MINE * (0.2f / 180.0f) // gyroscope measurement error in rad/s/s (shown as 0.2f deg/s/s)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError // compute beta
#define zeta sqrt(3.0f / 4.0f) * gyroMeasDrift


void madgwick_filter_update(IMUStamped* pdata);

#endif //MADGWICK_H
