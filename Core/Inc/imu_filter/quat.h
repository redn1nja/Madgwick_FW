#ifndef QUAT_H
#define QUAT_H
#include "imu_data.h"

typedef struct {
    double w;
    double x;
    double y;
    double z;
} Quaternion;

void quaternion_to_euler(const Quaternion* q, RPY* euler);
void quat_diff(Quaternion* q, const Quaternion* l, const Quaternion* r);
void quat_sum(Quaternion* q, const Quaternion* l, const Quaternion* r);
void quat_prod(Quaternion* q, const Quaternion* l, const Quaternion* r);
void quat_conj(Quaternion* q);
void quat_scalar_mult (Quaternion* q, double s);
float quat_norm(const Quaternion* q);
void quat_normalize(Quaternion* q);
#endif //QUAT_H
