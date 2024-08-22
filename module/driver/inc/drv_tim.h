#ifndef DRV_TIM_H
#define DRV_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported functions prototypes ---------------------------------------------*/
void TIM_Init(void);
void BEEP_Volume(uint16_t compare);
void XPWM_Set(uint32_t channe, uint16_t compare);

void HAL_Delay_us(uint16_t Delay_us);
// uint8_t TIM6_CheckIrqStatus(void);

#endif
