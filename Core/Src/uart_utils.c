#include "uart_utils.h"

volatile bool sent = true;
static char buf[256];
extern time_calc time;

void wait_for_sent(){
    while (!sent){}
    sent = false;
}

void send_IMU(IMUData* imu, UART_HandleTypeDef * uart){
    wait_for_sent();
    sprintf(buf, "[%lu.%lu]\n\rgX=%.2f,gY=%.2f,gZ=%.2f\n\raX=%.2f,aY=%.2f,aZ=%.2f\n\rmX=%.2f,mY=%.2f,mZ=%.2f\n\r\n\r",
    // sprintf(buf, "[%lu.%lu]\n\rgX=%.2f,gY=%.2f,gZ=%.2f\n\raX=%.2f,aY=%.2f,aZ=%.2f\n\r\n\r",
            time.sec, time.msec,
            imu->gyroX, imu->gyroY, imu->gyroZ,
            imu->accX, imu->accY, imu->accZ,
            imu->magX, imu->magY, imu->magZ);
    HAL_UART_Transmit_IT(uart, (unsigned char*)buf, strlen(buf));
}

void send_RPY(RPY* rpy, UART_HandleTypeDef * uart) {
    wait_for_sent();
    sprintf(buf, "[%lu.%lu]\n\rRoll=%.2f,Pitch=%.2f,Yaw=%.2f\n\r\n\r",
            time.sec, time.msec,
            rpy->roll, rpy->pitch, rpy->yaw);
    HAL_UART_Transmit_IT(uart, (unsigned char*)buf, strlen(buf));
}

void printerr(const char* data, UART_HandleTypeDef* huart){
    wait_for_sent();
    HAL_UART_Transmit_IT(huart, (unsigned char*)data, strlen(data));
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
    sent = true;
}

void send_IMUStamped(IMUStamped* imu, UART_HandleTypeDef * uart) {
    wait_for_sent();
    HAL_UART_Transmit_IT(uart, (unsigned char*)imu , sizeof(IMUStamped));
}

