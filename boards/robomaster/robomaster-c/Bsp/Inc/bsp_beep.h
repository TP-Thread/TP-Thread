#ifndef BSP_BEEP_H
#define BSP_BEEP_H

#include "main.h"

extern TIM_HandleTypeDef htim4;

//#define MAX_PSC             1000

//#define MAX_BEEP_PWM      20000
//#define MIN_BEEP_PWM      10000

//uint16_t psc = 0;
//uint16_t pwm = MIN_BEEP_PWM;


//void BEEP_On(uint16_t psc, uint16_t pwm);
void BEEP_Volume(uint16_t pwm);

#endif
