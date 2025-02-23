#ifndef MADGWICK_H
#define MADGWICK_H

#include <math.h>
#include <imu_data.h>

#include "quat.h"

#define M_PI_MINE 3.14159265358979
#define gyroMeasError M_PI_MINE * (15.0f / 180.0f)
#define gyroMeasDrift M_PI_MINE * (0.03f / 180.0f)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError
#define zeta sqrt(3.0f / 4.0f) * gyroMeasDrift

void madgwick_filter_update(IMUStamped* pdata);

#endif //MADGWICK_H
