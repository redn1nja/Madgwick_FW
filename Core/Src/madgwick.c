#ifdef __cplusplus
extern "C" {
#endif


#include <madgwick.h>
#include <math.h>

static IMUStamped last_data;
static Quaternion q_data = {1, 0, 0, 0};

Quaternion madgwick_filter_update(IMUStamped* pdata) {
    double dt = (pdata->time.sec - last_data.time.sec)*1000 + ((int16_t)pdata->time.msec - (int16_t)last_data.time.msec);
    dt /= 1000;
    Quaternion q = q_data;
    Quaternion nabla = {0};
    Quaternion qDot = {0};
    Quaternion qAcc = {0, pdata->imu.accX, pdata->imu.accY, pdata->imu.accZ};
    quat_normalize(&qAcc);
    Quaternion qGyro = {0, pdata->imu.gyroX, pdata->imu.gyroY, pdata->imu.gyroZ};
    {
        Quaternion qGyroCpy = qGyro;
        quat_scalar_mult(&qGyroCpy, 0.5);
        quat_prod(&qGyro, &q, &qGyroCpy);
    }
    double Fg[3] ={0};

    {
        Fg[0] = 2*(q.x*q.z - q.w*q.y) - qAcc.x;
        Fg[1] = 2*(q.w*q.x + q.y*q.z) - qAcc.y;
        Fg[2] = 2*(0.5 - q.x*q.x - q.y*q.y) - qAcc.z;
    }

    {
        nabla.w = -2*q.y * Fg[0] + 2*q.x *Fg[1];
        nabla.x = 2*q.z * Fg[0] + 2*q.w *Fg[1] -4 * q.x * Fg[2];
        nabla.y =  -2*q.w * Fg[0] +  2*q.z *Fg[1]  -4 * q.y * Fg[2];
        nabla.z =  2*q.x * Fg[0] + 2*q.y *Fg[1];
        quat_normalize(&nabla);
    }

    quat_scalar_mult(&nabla, beta_mad);
    quat_diff(&qDot, &qGyro, &nabla);
    quat_scalar_mult(&qDot, dt);
    quat_sum(&q_data, &q, &qDot);
    quat_normalize(&q_data);
    quaternion_to_euler(&q_data, &pdata->rpy);
    last_data = *pdata;
    Quaternion q_cpy = q_data;
    return q_cpy;
}

#ifdef __cplusplus
}
#endif

