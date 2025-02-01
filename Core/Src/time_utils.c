#include "time_utils.h"
#include "imu_data.h"

time_calc time;
#define MIL 1000

void start_time(){
    HAL_TIM_Base_Start_IT(&htim1);
    time.sec = 0;
    time.msec = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
    time.msec += 1;
    if (time.msec > MIL){
        time.sec +=1;
        time.msec ^= time.msec;
    }
}


uint32_t calc_dt(){
    static time_calc stopwatch;
    uint32_t res = (time.sec * MIL + time.msec) - (stopwatch.sec * MIL + stopwatch.msec);
    stopwatch.sec = time.sec;
    stopwatch.msec = time.msec;
    return res;
}

void stamp_IMUData(IMUStamped* imu){
    imu->time.sec = time.sec;
    imu->time.msec = time.msec;
}