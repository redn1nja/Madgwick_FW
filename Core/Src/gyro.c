#include "gyro.h"
#include "uart_utils.h"
#include "time_utils.h"

#define DIVISOR ((float)0.001)



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
    data->gyroX = buffer[0] * DIVISOR;
    data->gyroY = buffer[1] * DIVISOR;
    data->gyroZ = buffer[2] * DIVISOR;
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

void calculate_rpy(const IMUData* imu, RPY* data) {
    uint32_t dt_int = calc_dt();
    float dt = (float)dt_int * DIVISOR;
    data->roll = normalize_angle(data->roll + imu->gyroX * dt);
    data->pitch = normalize_angle(data->pitch + imu->gyroY * dt);
    data->yaw = normalize_angle(data->yaw + imu->gyroZ * dt);

}

void clear_RPY(RPY* data){
    data->roll = 0;
    data->pitch = 0;
    data->yaw = 0;
}