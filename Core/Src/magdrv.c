#include "magdrv.h"

#include "i2c.h"

HAL_StatusTypeDef init_mag(void) {
    my_MAGNETO_Init_t init;
    init.freq_reg = LSM303_MAG_FREQ_75HZ;
    init.gain_reg = LSM303_MAG_GAIN_4_7;
    init.mode_reg = LSM303_MAG_MODE_CONTINUOUS;
    uint8_t pdata[4] = {0x00, init.freq_reg, init.gain_reg, init.mode_reg};
    return HAL_I2C_Master_Transmit(&hi2c1, LSM303_MAG_I2C_ADDR, pdata, 4, 1000);
}

HAL_StatusTypeDef read_mag(float* pData) {
    uint8_t buffer[6] = {0};
    int16_t raw_data[3];
    uint8_t reg = LSM303_MAG_OUT_X_H;
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, LSM303_MAG_I2C_ADDR, &reg, 1, 1000);
    if (status != HAL_OK) {
        return status;
    }
    status = HAL_I2C_Master_Receive(&hi2c1, LSM303_MAG_I2C_ADDR, buffer, 6, 1000);
    if (status != HAL_OK) {
        return status;
    }

    for (int i = 0; i < 3; i++) {
        raw_data[i] = (int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1];

    }

    for(int i = 0; i<3; i++) {
        pData[i] = (float)(raw_data[i] >> 4) / LSM303_MAG_GAIN_LSB_GAUSS;
    }

    return HAL_OK;

}

void update_mag(IMUData* data) {
    float buffer[3] = {0};
    HAL_StatusTypeDef status = read_mag(buffer);
    if (status != HAL_OK) {
        return;
    }
    data->magX = buffer[0];
    data->magY = buffer[1];
    data->magZ = buffer[2];
}
