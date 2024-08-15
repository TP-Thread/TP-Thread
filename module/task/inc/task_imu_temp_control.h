#ifndef IMU_TEMP_TASK_H
#define IMU_TEMP_TASK_H

#include "main.h"
#include "cmsis_os.h"
#include "bsp_imu_pid.h"


void imu_temp_control_task(void const * argument);

#endif
