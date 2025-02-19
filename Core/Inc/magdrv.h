#ifndef MAGRDV_H
#define MAGRDV_H

#include "lsm303dlhc/lsm303dlhc.h"
#include "lsm303agr/lsm303agr.h"
#include "imu_data.h"

#define LSM303_MAG_I2C_ADDR 0x3C

#define LSM303_MAG_FREQ_75HZ 0x18
#define LSM303_MAG_GAIN_4_7 0xA0
#define LSM303_MAG_MODE_CONTINUOUS 0x00

#define LSM303_MAG_OUT_X_H (0x03)
#define LSM303_MAG_GAIN_LSB_GAUSS 400

typedef struct {
    uint8_t freq_reg;
    uint8_t gain_reg;
    uint8_t mode_reg;
}my_MAGNETO_Init_t;

HAL_StatusTypeDef init_mag(void);
HAL_StatusTypeDef read_mag(float* pData);
void update_mag(IMUData* data);



#endif //MAGRDV_H
