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
		LED_G_Toggle();
		Sent_ATTitude_Data(angle_m, angle_d, rate_m, rate_d);
		printf("the Yaw value is \n");
		// printf("the temp value is: %.2f \n", bmi088_data.temp);
		
		osDelay(100);
	}
}
