#ifndef ALGO_MAHONY_AHRS_H
#define ALGO_MAHONY_AHRS_H

/* Includes ------------------------------------------------------------------*/
#include "math.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

/* Exported functions prototypes ---------------------------------------------*/
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

float invSqrt(float x);

#endif
