#ifdef __cplusplus
extern "C" {
#endif

#ifndef MADGWICK_H
#define MADGWICK_H

#include <math.h>
#include <imu_data.h>

#include "quat.h"

#define M_PI_MINE 3.14159265358979
#define gyroMeasError M_PI_MINE * (1.0f / 180.0f)
#define gyroMeasDrift M_PI_MINE * (0.03f / 180.0f)
Quaternion madgwick_filter_update(IMUStamped* pdata);

#endif //MADGWICK_H

#ifdef __cplusplus
#define beta_mad ((std::sqrt(0.75) * gyroMeasError))
#define zeta_mad ((std::sqrt(0.75) * gyroMeasDrift))
    }
#else
#define beta_mad (sqrt(0.75) * gyroMeasError)
#define zeta_mad (sqrt(0.75) * gyroMeasDrift)
#endif
