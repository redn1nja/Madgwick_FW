#include "accel.h"
#include "uart_utils.h"
#include "stm32f3_discovery_accelerometer.h"

HAL_StatusTypeDef init_accel(){
    if (BSP_ACCELERO_Init() != HAL_OK){
        printerr("failed to initialize accelerometer", &huart2);
        return HAL_ERROR;
    }
    return HAL_OK;
}

#define GFORCE_MILI ((float)0.00980665)
#define GFORCE ((float)9.80665)

void read_accel_data(IMUData* data){
    int16_t buffer[3] = {0};
    BSP_ACCELERO_GetXYZ(buffer);
    data->accX = (float)(buffer[0] >> 4) * GFORCE_MILI;
    data->accY = (float)(buffer[1] >> 4) * GFORCE_MILI;
    data->accZ = (float)(buffer[2] >> 4) * GFORCE_MILI;
}