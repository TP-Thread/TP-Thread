/**
 ******************************************************************************
 * @file    task_index.c
 * @author  TP-Thread
 * @brief   Function implementing the Index thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private includes ----------------------------------------------------------*/


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
		// LED_G_Toggle();
		sent_data1(100, 0.1, -100);
		// printf("the Yaw value is :%f \n", angle_c[2]);
		// printf("the temp value is: %.2f \n", bmi088_data.temp);
		
		osDelay(10);
	}
}

