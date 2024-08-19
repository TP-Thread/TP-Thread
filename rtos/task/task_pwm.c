/**			                                                    
  ******************************************************************************
  * @作  者  两点一线
  * @版  本  V1.0
  * @日  期  2023-09-4
  * @内  容  PWM输入捕获实验
  ******************************************************************************
  */
  
#include "task_pwm.h"

//任务句柄
TaskHandle_t pwm_task_Handle;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

uint8_t capture_Cnt = 0;    //状态标志位
uint32_t  capture_H = 0;    //高电平计数
uint32_t  capture_HL = 0;   //周期计数
float pwm_duty;

/**
  * @brief          pwm任务,输入捕获实验
  * @param[in]      argument: NULL
  * @retval         none
  */
void pwm_task(void const * argument)
{  	
	//获取当前任务的任务句柄，
    pwm_task_Handle = xTaskGetHandle(pcTaskGetName(NULL));

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);	//启动PWM输出
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 1000);//最大2500
	
	HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_3);	//启动输入捕获
	
	for(;;)
	{
		//等待通知
        while(ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != pdPASS)
		{
		}
		
		if(capture_Cnt == 0)
		{
			pwm_duty = (float)capture_H/capture_HL;
			printf("占空比：%-.2f\n",pwm_duty);
			osDelay(1000);
			HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_3);	//启动输入捕获
		}
	}
}

//定时器输入捕获中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(TIM8 == htim->Instance)
	{
		switch(capture_Cnt){
			case 0:
				__HAL_TIM_SET_COUNTER(&htim8, 0);
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim8, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt++;
				break;
			case 1:
				capture_H = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_3);
				//capture_H = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_3);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim8, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
				capture_Cnt++; 
				break;			
			case 2:
				capture_HL = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_3);
				//capture_HL = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_3);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim8, TIM_CHANNEL_3); //停止捕获
				capture_Cnt = 0;
				break; 			
		}
		
		//唤醒任务
		if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
			static BaseType_t xHigherPriorityTaskWoken;
			vTaskNotifyGiveFromISR(pwm_task_Handle, &xHigherPriorityTaskWoken);//发送通知
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
}

