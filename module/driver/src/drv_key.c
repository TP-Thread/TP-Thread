/**
  ******************************************************************************
  * @file    drv_key.c
  * @author  TP-Thread
  * @brief   按键检测.
  *          获取键值，有软件消抖，按键抬起后输出键值
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_key.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  KEY 获取按键值
  * @param  None
  * @retval 按键状态
  */
uint8_t Key_Scan(void)
{
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == KEY_DOWN)
    {
        // HAL_Delay(10);	//延时 10ms 软件防抖

        if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == KEY_DOWN)
        {
            /* 等待按键释放 */
            while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == KEY_DOWN)
                ;
            return KEY_DOWN;
        }
    }

    return KEY_UP;
}
