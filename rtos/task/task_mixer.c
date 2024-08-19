/**
 ******************************************************************************
 * @file    task_mixer.c
 * @author  TP-Thread
 * @brief   Function implementing the Mixer thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Function implementing the Mixer thread.
 * @param  argument: Not used
 * @retval None
 */
void Mixer_Entry(void *argument)
{
    // SBUS初始化
    SBUS_Init();

    while (1)
    {

        printf("CH3:%d\n", SBUS_CH.CH3);
        osDelay(10);
    }
}
