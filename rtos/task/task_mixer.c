/**
 ******************************************************************************
 * @file    task_mixer.c
 * @author  TP-Thread
 * @brief   Function implementing the Mixer thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private function prototypes -----------------------------------------------*/
void Mixer_Set(void);

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Function implementing the Mixer thread.
 * @param  argument: Not used
 * @retval None
 */
void Mixer_Entry(void *argument)
{
    SBUS_Init();
	TIM_Init();

    while (1)
    {
		XPWM_Set(XTIM_CHANNEL_1, 2500);
		XPWM_Set(XTIM_CHANNEL_2, 2000);
		XPWM_Set(XTIM_CHANNEL_3, 1000);
		XPWM_Set(XTIM_CHANNEL_4, 1000);
        osDelay(10);
    }
}

void Mixer_Set(void)
{

}

