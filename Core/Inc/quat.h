#ifndef QUAT_H
#define QUAT_H
#include "imu_data.h"

typedef struct {
    float w;
    float x;
    float y;
    float z;
} Quaternion;

void quaternion_to_euler(const Quaternion* q, RPY* euler);
void quat_diff(Quaternion* q, const Quaternion* l, const Quaternion* r);
void quat_sum(Quaternion* q, const Quaternion* l, const Quaternion* r);
void quat_prod(Quaternion* q, const Quaternion* l, const Quaternion* r);
void quat_conj(Quaternion* q);
void quat_scalar_mult (Quaternion* q, float s);
float quat_norm(const Quaternion* q);
void quat_normalize(Quaternion* q);
void quaternion_to_euler(const Quaternion* q, RPY* euler);
#endif //QUAT_H
