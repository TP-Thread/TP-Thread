#ifndef BSP_TIM_H
#define BSP_TIM_H

#include "main.h"

extern TIM_HandleTypeDef htim6;


void HAL_Delay_us(uint16_t Delay_us);
uint8_t TIM6_CheckIrqStatus(void);

#endif
