/**
 ******************************************************************************
 * @file    task_rc.c
 * @author  TP-Thread
 * @brief   Function implementing the Rc thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Function implementing the Mixer thread.
 * @param  argument: Not used
 * @retval None
 */
void Rc_Entry(void *argument)
{
    SBUS_Init();
	TIM_Init();

    while (1)
    {	
		Remote_Ctrl();
        osDelay(10);
    }
}
