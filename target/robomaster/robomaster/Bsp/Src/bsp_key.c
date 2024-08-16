/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  TP-Thread
  * @brief   按键检测.
  *          获取键值，有软件消抖，按键抬起后输出键值
  ******************************************************************************
  */ 

#include "bsp_key.h"

/**
 * @简  述  KEY 获取按键值
 * @返回值  按键值，按键按下为0，抬起为1（抬起后输出键值）
 */
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
