#include "gyro.h"
#include "uart_utils.h"

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