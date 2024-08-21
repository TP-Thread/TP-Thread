/**
  ******************************************************************************
  * @file    tp_thread.h
  * @author  TP-Thread
  * @brief   Application specific definitions.
  *          These definitions should be adjusted for your particular hardware and application requirements.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TP_THREAD_H
#define TP_THREAD_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
extern float angle_c[3]; // 当前欧拉角姿态rpy °

#if defined(TIP)
	extern osEventFlagsId_t Imu_EventHandle;
#elif defined(TIP1)
	extern osEventFlagsId_t Imu_EventHandle;
#elif defined(ROBOMASTER_A)
	extern osEventFlagsId_t Imu_EventHandle;
#elif defined(ROBOMASTER_C)
	
#endif

/* Exported macro ------------------------------------------------------------*/
#if defined(TIP)
    #define duart	huart1
	#define suart	huart3
	#define hdma_susart_rx	hdma_usart3_rx
#elif defined(TIP1)
    #define duart	huart1
	#define suart	huart3
	#define hdma_susart_rx	hdma_usart3_rx
#elif defined(ROBOMASTER_A)
	#define suart	huart1
	#define hdma_susart_rx	hdma_usart1_rx
	
	#define duart	huart6
#elif defined(ROBOMASTER_C)
	#define xtim	htim1
	#define XTIM_CHANNEL_1	TIM_CHANNEL_1
	#define XTIM_CHANNEL_2	TIM_CHANNEL_2
	#define XTIM_CHANNEL_3	TIM_CHANNEL_3
	#define XTIM_CHANNEL_4	TIM_CHANNEL_4
	
	#define ttim	htim10
	#define TTIM_CHANNEL	TIM_CHANNEL_1
	
    #define duart	huart1
	#define hdma_susart_rx	hdma_usart3_rx
	
	#define suart	huart3
	

#endif

#endif /* TP_THREAD_H */
