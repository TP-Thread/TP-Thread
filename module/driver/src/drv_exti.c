/**
  ******************************************************************************
  * @file    drv_key.c
  * @author  TP-Thread
  * @brief   中断回调.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_exti.h"

/* Private functions ---------------------------------------------------------*/

//extern TaskHandle_t INS_task_local_handler;


///**
//  * @brief  中断回调函数
//  */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin == KEY_Pin)
//	{
//		// LED_G 取反
//		LED_G_Toggle(); 
//	}
//    else if(GPIO_Pin == DRDY_IST8310_Pin)
//    {
//    	IST8310_Read(IST8310_Data.mag);
//    }
//}
