#ifndef IMU_ACCEL_H
#define IMU_ACCEL_H

#include "imu_data.h"
#include "accelero.h"
#include "main.h"

HAL_StatusTypeDef init_accel();
void read_accel_data(IMUData* data);



#endif //IMU_ACCEL_H
