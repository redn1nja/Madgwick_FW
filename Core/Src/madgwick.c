#include <madgwick.h>
#include <math.h>

static IMUStamped last_data;
static Quaternion q_data = {1, 0, 0, 0};

void madgwick_filter_update(IMUStamped* pdata) {
    float dt = (pdata->time.sec - last_data.time.sec)*1000 + ((int16_t)pdata->time.msec - (int16_t)last_data.time.msec);
    dt /= 1000;
    const Quaternion q = q_data;
    Quaternion nabla = {0};
    Quaternion qDot = {0};
    Quaternion qAcc = {0, pdata->imu.accX, pdata->imu.accY, pdata->imu.accZ};
    quat_normalize(&qAcc);
    Quaternion qGyro = {0, pdata->imu.gyroX, pdata->imu.gyroY, pdata->imu.gyroZ};
    {
        Quaternion qGyroCpy = qGyro;
        quat_scalar_mult(&qGyro, 0.5);
        quat_prod(&qGyro, &q, &qGyroCpy);
    }
    float Fg[3] ={0};
    float Jg[3][4] = {0};

    {
        Fg[0] = 2*(q.x*q.z - q.w*q.y) - qAcc.x;
        Fg[1] = 2*(q.w*q.x + q.y*q.z) - qAcc.y;
        Fg[2] = 2*(0.5 - q.x*q.x - q.y*q.y) - qAcc.z;
    }

    {
        Jg[0][0] = -2*q.y;
        Jg[0][1] = 2*q.z;
        Jg[0][2] = -2*q.w;
        Jg[0][3] = 2*q.x;

        Jg[1][0] = 2*q.x;
        Jg[1][1] = 2*q.w;
        Jg[1][2] = 2*q.z;
        Jg[1][3] = 2*q.y;

        Jg[2][0] = 0;
        Jg[2][1] = -4*q.x;
        Jg[2][2] = -4*q.y;
        Jg[2][3] = 0;
    }

    {
        nabla.w = Jg[0][0]*Fg[0] + Jg[1][0]*Fg[1] + Jg[2][0]*Fg[2];
        nabla.x = Jg[0][1]*Fg[0] + Jg[1][1]*Fg[1] + Jg[2][1]*Fg[2];
        nabla.y = Jg[0][2]*Fg[0] + Jg[1][2]*Fg[1] + Jg[2][2]*Fg[2];
        nabla.z = Jg[0][3]*Fg[0] + Jg[1][3]*Fg[1] + Jg[2][3]*Fg[2];
        quat_normalize(&nabla);
    }

    quat_scalar_mult(&nabla, beta);
    quat_diff(&qDot, &qGyro, &nabla);
    quat_scalar_mult(&qDot, dt);
    quat_sum(&q_data, &q, &qDot);
    quat_normalize(&q_data);
    quaternion_to_euler(&q_data, &pdata->rpy);
    last_data = *pdata;
}



