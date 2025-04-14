#ifdef __cplusplus
extern "C" {
#endif

#ifndef IMU_IMU_DATA_H
#define IMU_IMU_DATA_H

#include "time_utils.h"

#pragma pack(push,1)
typedef struct {
    float gyroX;
    float gyroY;
    float gyroZ;
    float accX;
    float accY;
    float accZ;
    float magX;
    float magY;
    float magZ;
} IMUData;

typedef struct {
    float roll;
    float pitch;
    float yaw;
}RPY;

typedef struct {
    time_calc time;
    IMUData imu;
    RPY rpy;
    uint8_t sync;
} IMUStamped;
#pragma pack(pop)

void stamp_IMUData(IMUStamped* imu);


#endif //IMU_IMU_DATA_H


#ifdef __cplusplus
    }
#endif