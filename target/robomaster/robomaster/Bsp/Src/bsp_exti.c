#include "bsp_exti.h"

//extern TaskHandle_t INS_task_local_handler;


///**
//  * @brief  KEY中断回调函数
//  */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin == KEY_Pin)
//	{
//		// LED_G 取反
//		LED_G_Toggle(); 
//	}
//    else if(GPIO_Pin == INT1_ACCEL_Pin)
//    {
//        //唤醒任务
//        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
//        {
//            static BaseType_t xHigherPriorityTaskWoken;
//            vTaskNotifyGiveFromISR(INS_task_local_handler, &xHigherPriorityTaskWoken);
//            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//        }
//    }
//}
