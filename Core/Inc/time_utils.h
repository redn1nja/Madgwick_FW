#ifndef IMU_TIME_UTILS_H
#define IMU_TIME_UTILS_H
#include "stdint.h"
#include "tim.h"
#include "stm32f3xx_hal_tim.h"

typedef struct {
    uint32_t sec;
    uint32_t msec;
} time_calc;

void start_time();
uint32_t  calc_dt();
#endif //IMU_TIME_UTILS_H
