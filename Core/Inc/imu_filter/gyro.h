#ifndef IMU_GYRO_H
#define IMU_GYRO_H

#include "stm32f3_discovery_gyroscope.h"

#include "imu_data.h"

HAL_StatusTypeDef init_gyro();
void read_gyro_data(IMUData* data);
void calculate_rpy(IMUStamped* imu);
void clear_RPY(RPY* data);
#endif //IMU_GYRO_H
