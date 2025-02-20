#include "quat.h"
#include <math.h>

void quat_diff(Quaternion* q, const Quaternion* l, const Quaternion* r) {
    q->w = l->w - r->w;
    q->x = l->x - r->x;
    q->y = l->y - r->y;
    q->z = l->z - r->z;
}

void quat_sum(Quaternion* q, const Quaternion* l, const Quaternion* r) {
    q->w = l->w + r->w;
    q->x = l->x + r->x;
    q->y = l->y + r->y;
    q->z = l->z + r->z;
}

void quat_prod(Quaternion* q, const Quaternion* l, const Quaternion* r) {
    q->w = l->w*r->w - l->x*r->x - l->y*r->y - l->z*r->z;
    q->x = l->w*r->x + l->x*r->w + l->y*r->z - l->z*r->y;
    q->y = l->w*r->y - l->x*r->z + l->y*r->w + l->z*r->x;
    q->z = l->w*r->z + l->x*r->y - l->y*r->x + l->z*r->w;
}

void quat_conj(Quaternion* q) {
    q->x = -q->x;
    q->y = -q->y;
    q->z = -q->z;
}

void quat_scalar_mult (Quaternion* q, float s) {
    q->w *= s;
    q->x *= s;
    q->y *= s;
    q->z *= s;
}

float quat_norm(const Quaternion* q) {
    return sqrt(q->w*q->w + q->x*q->x + q->y*q->y + q->z*q->z);
}

void quat_normalize(Quaternion* q) {
    float norm = quat_norm(q);
    quat_scalar_mult(q, 1/norm);
}

void quaternion_to_euler(const Quaternion* q, RPY* euler) {
    euler->roll = atan2(2*(q->w*q->x + q->y*q->z), 1 - 2*(q->x*q->x + q->y*q->y));
    euler->pitch = asin(2*(q->w*q->y - q->z*q->x));
    euler->yaw = atan2(2*(q->w*q->z + q->x*q->y), 1 - 2*(q->y*q->y + q->z*q->z));
}