/**			                                                                              
  ******************************************************************************
  * @作  者  没PF的老亚瑟
  * @版  本  V1.0
  * @日  期  2022-12-29
  * @内  容  定时器10ms定时
  *
  ******************************************************************************
  * @说  明
  *
  * 1.TIM6定时器终于产生定时信号，通过标志位判断的函数传递
  * 2.TIM定时器输入捕获
  ******************************************************************************
  */

#include "bsp_tim.h" 

/**
  * @brief			微秒级延时
  * @param      	Delay_us      延时微秒数（Delay_us < 1000）
  * @retval         无
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


//中断循环状态控制标志位
//uint8_t flag_tim6 = 0;

/**
  * @简  述  TIM6 更新中断回调函数
  * @参  数  无
  * @返回值  无
  */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM6){
//		//中断处理内容
//		flag_tim6 = 1;  //置位10ms标志位
//	}
//}

/**
  * @brief  检测是否产生中断
  * @param  None
  * @retval None
  */
//uint8_t TIM6_CheckIrqStatus(void)
//{
//	//确认中断,进入控制周期
//	if(flag_tim6 != 0) 
//	{
//		flag_tim6 = 0;
//		return 1;
//	}

//	return 0;
//}
/******************* (C) 版权 TP-Tech **************************************/
