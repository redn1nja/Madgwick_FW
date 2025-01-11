#ifndef IMU_MAG_H
#define IMU_MAG_H

#include "magneto.h"
#include "main.h"
#include "imu_data.h"

HAL_StatusTypeDef init_mag();
void read_mag_data(IMUData* data);

#endif //IMU_MAG_H
