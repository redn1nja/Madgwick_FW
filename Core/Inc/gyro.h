#ifndef IMU_GYRO_H
#define IMU_GYRO_H

#include "stm32f3_discovery_gyroscope.h"
#include "imu_data.h"

HAL_StatusTypeDef init_gyro();
void read_gyro_data(IMUData* data);

#endif //IMU_GYRO_H
