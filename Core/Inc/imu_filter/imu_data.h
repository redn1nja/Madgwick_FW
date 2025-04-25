#ifdef __cplusplus
extern "C" {
#endif

#ifndef IMU_IMU_DATA_H
#define IMU_IMU_DATA_H

#include "time_utils.h"

#pragma pack(push,1)
typedef struct {
    double gyroX;
    double gyroY;
    double gyroZ;
    double accX;
    double accY;
    double accZ;
    double magX;
    double magY;
    double magZ;
} IMUData;

typedef struct {
    double roll;
    double pitch;
    double yaw;
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