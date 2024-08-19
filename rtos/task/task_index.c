/**
 ******************************************************************************
 * @file    task_index.c
 * @author  TP-Thread
 * @brief   Function implementing the Index thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Function implementing the Index thread.
 * @param  argument: Not used
 * @retval None
 */
void Index_Entry(void *argument)
{
	while (1)
	{
		LED_G_Toggle();
		osDelay(1000);
	}
}
