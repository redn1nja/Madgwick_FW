#ifndef IMU_UART_UTILS_H
#define IMU_UART_UTILS_H

#include "gyro.h"
#include "usart.h"
#include "imu_data.h"
#include "time_utils.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void send_IMU(IMUData* imu, UART_HandleTypeDef * uart);
void send_IMUStamped(IMUStamped* imu, UART_HandleTypeDef * uart);
void send_RPY(RPY* rpy, UART_HandleTypeDef * uart);
void printerr(const char* data, UART_HandleTypeDef* huart);


#endif //IMU_UART_UTILS_H
