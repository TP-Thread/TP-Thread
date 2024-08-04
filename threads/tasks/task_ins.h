#ifndef INS_TASK_H
#define INS_TASK_H

#include "main.h"
#include "cmsis_os.h"

#include "MahonyAHRS.h"

extern TIM_HandleTypeDef htim10;

#define TEMP_KP 1600.0f //温度控制PID的kp
#define TEMP_KI 0.2f    //温度控制PID的ki
#define TEMP_KD 0.0f    //温度控制PID的kd

#define TEMP_MAX_OUT   4500.0f //温度控制PID的max_out
#define TEMP_MAX_IOUT  4400.0f //温度控制PID的max_iout


void ins_task(void *argument);

void IMU_Temp_Control(float temp);

void AHRS_Update(float gyro[3], float accel[3], float mag[3]);
void INS_Angle(float *roll, float *pitch, float *yaw);

#endif
