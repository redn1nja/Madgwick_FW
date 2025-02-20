#include "gyro.h"
#include "uart_utils.h"
#include "time_utils.h"


extern time_calc time;
#define DIVISOR ((float)0.001)
#define DEGREE_TO_RADIAN 0.017453292519943295769236907684886

HAL_StatusTypeDef init_gyro(){
    if (BSP_GYRO_Init() !=HAL_OK){
        printerr("Failed to init gyroscope", &huart2);
        return HAL_ERROR;
    }
    return HAL_OK;
}

void read_gyro_data(IMUData* data){
    float buffer[3] = {0};
    BSP_GYRO_GetXYZ(buffer);
    data->gyroX = buffer[0] / 16.0 * DIVISOR * DEGREE_TO_RADIAN;
    data->gyroY = buffer[1] / 16.0 * DIVISOR * DEGREE_TO_RADIAN;
    data->gyroZ = buffer[2] / 16.0 * DIVISOR  * DEGREE_TO_RADIAN;
}

inline float normalize_angle(float angle){
    while (angle > 180){
        angle -= 360;
    }
    while (angle < -180){
        angle += 360;
    }
    return angle;
}

void calculate_rpy(IMUStamped* imu) {
    uint32_t dtint = (imu->time.sec - time.sec) * 1000 + (imu->time.msec - time.msec);
    float dt = (float)dtint * DIVISOR;
    imu->rpy.roll = normalize_angle(imu->rpy.roll + imu->imu.gyroX * dt);
    imu->rpy.pitch = normalize_angle(imu->rpy.pitch +  imu->imu.gyroY * dt);
    imu->rpy.yaw = normalize_angle(imu->rpy.yaw + imu->imu.gyroZ * dt);

}

void clear_RPY(RPY* data){
    data->roll = 0;
    data->pitch = 0;
    data->yaw = 0;
}

