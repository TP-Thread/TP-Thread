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
	#define duart	huart6
	#define suart	huart1
	#define hdma_susart_rx	hdma_usart1_rx
#elif defined(ROBOMASTER_C)
    #define duart	huart1
	#define suart	huart3
	#define hdma_susart_rx	hdma_usart3_rx
#endif

#endif /* TP_THREAD_H */
