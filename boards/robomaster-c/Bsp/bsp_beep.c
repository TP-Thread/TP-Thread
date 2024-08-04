#include "bsp_beep.h"

//void BEEP_On(uint16_t psc, uint16_t pwm)
//{
//    __HAL_TIM_PRESCALER(&htim4, psc);
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);

//}

void BEEP_Volume(uint16_t pwm)
{
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);
}
