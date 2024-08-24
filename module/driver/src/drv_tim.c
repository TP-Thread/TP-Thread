/**
  ******************************************************************************
  * @file    drv_tim.c
  * @author  TP-Thread
  * @brief   Timer.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_tim.h" 

/* Private variables ---------------------------------------------------------*/
//中断循环状态控制标志位
//uint8_t flag_tim7 = 0;

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	开启定时器PWM输出
 */
void TIM_Init(void)
{
	HAL_TIM_PWM_Start(&btim, BTIM_CHANNEL);

	HAL_TIM_PWM_Start(&xtim, XTIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&xtim, XTIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&xtim, XTIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&xtim, XTIM_CHANNEL_4);
}

/**
 * @brief	蜂鸣器PWM占空比设置,频率：4000Hz
 * @param   compare specifies the Capture Compare register new value: 0~21000.
 */
void BEEP_Volume(uint16_t compare)
{
    __HAL_TIM_SetCompare(&btim, BTIM_CHANNEL, compare);
}

/**
 * @brief	PWM占空比设置,周期：20ms,高电平：1~2ms
 * @param  	pwm: 
 * @param   channel TIM Channels to be configured.
 *          @arg XTIM_CHANNEL_1: TIM Channel 1 selected
 *          @arg XTIM_CHANNEL_2: TIM Channel 2 selected
 *          @arg XTIM_CHANNEL_3: TIM Channel 3 selected
 *          @arg XTIM_CHANNEL_4: TIM Channel 4 selected
 * @param   compare specifies the Capture Compare register new value: 1000~2000.
 */
void XPWM_Set(uint32_t channel, uint16_t compare)
{
    __HAL_TIM_SetCompare(&xtim, channel, compare);
}

/**
  * @brief		微秒级延时
  * @param      Delay_us      延时微秒数（Delay_us < 1000）
  * @retval     无
  */
void HAL_Delay_us(uint16_t Delay_us)
{
	uint32_t tickwait = Delay_us * 168;//延时需要等待的tick数
	uint32_t tickcnt;//用于记录已经延时的tick数
	
	uint32_t reload = SysTick->LOAD;//重装载值168000-1，HAL_SYSTICK_Config()中设置好的    LOAD=168000，1ms=168000tick，1us=168tick
	uint32_t tickstart = SysTick->VAL;

    while (1)
    {
        uint32_t ticknow = SysTick->VAL;
        if(ticknow != tickstart)
        {
            if(ticknow < tickstart)
            {
                tickcnt = tickstart - ticknow;
            }
            else
            {
                tickcnt = reload - ticknow + tickstart;
            }
  
            if(tickcnt >= tickwait)
            {
                break;
            }
        }
    }
}

/**
  * @简  述  TIM7 中断回调函数
  * @参  数  无
  * @返回值  无
  */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM7){
//		//中断处理内容
//		flag_tim7 = 1;  //置位10ms标志位
//	}
//}

/**
  * @brief  检测是否产生中断
  * @param  None
  * @retval None
  */
//uint8_t TIM7_CheckIrqStatus(void)
//{
//	//确认中断,进入控制周期
//	if(flag_tim7 != 0) 
//	{
//		flag_tim7 = 0;
//		return 1;
//	}

//	return 0;
//}
