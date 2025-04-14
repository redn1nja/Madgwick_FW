#ifdef __cplusplus
extern "C" {
#endif


#ifndef IMU_TIME_UTILS_H
#define IMU_TIME_UTILS_H
#include "stdint.h"

#ifndef LOCAL_BUILD
#include "tim.h"
#include "stm32f3xx_hal_tim.h"
#endif

#pragma pack(push, 1)
typedef struct {
    uint32_t sec;
    uint16_t msec;
} time_calc;
#pragma pack(pop)

void start_time();
uint32_t  calc_dt();

#endif

    //IMU_TIME_UTILS_H
#ifdef __cplusplus
    }
#endif