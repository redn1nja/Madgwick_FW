#include <madgwick.h>

static IMUStamped last_data;

void madgwick_filter_update(IMUStamped* pdata) {
    float dt = (pdata->time.sec - last_data.time.sec)*1000 + ((int16_t)pdata->time.msec - (int16_t)last_data.time.msec);


}