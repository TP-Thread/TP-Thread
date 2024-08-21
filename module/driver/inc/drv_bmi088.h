#ifndef DRV_BMI088_H
#define DRV_BMI088_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t status;
    float accel[3];
    float temp;
    float gyro[3];
} bmi088_t;

extern bmi088_t bmi088_data;

/* Exported functions prototypes ---------------------------------------------*/
void BMI088_Init(void);
void BMI088_Read(float gyro[3], float accel[3], float *temperate);

#endif
