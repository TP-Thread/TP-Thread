/**
  ******************************************************************************
  * @file    tp_define.h
  * @author  TP-Thread
  * @brief   Application specific definitions.
  *          These definitions should be adjusted for your particular hardware and application requirements.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TP_DEFINE_H
#define TP_DEFINE_H

#define ROBOMASTER_A

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include "drv_key.h"
#include "drv_uart.h"
//#include "bsp_tim.h" 
//#include "bsp_beep.h"
//#include "bsp_vin.h"
//#include "bsp_sbus.h"
//#include "bsp_oled.h"
//#include "bsp_can.h"
#if defined(TIP)
    printf("Compiling for Windows.\n");
#elif defined(TIP1)
    printf("Compiling for Windows.\n");
#elif defined(ROBOMASTER_A)
//	#include "bsp_ist8310.h"
//	#include "bsp_bmi088.h"
#elif defined(ROBOMASTER_C)
    printf("Compiling for Linux.\n");
#endif

/* Exported types ------------------------------------------------------------*/
#if defined(TIP)
	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc3;
	extern CAN_HandleTypeDef hcan1;
	extern CAN_HandleTypeDef hcan2;
	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart3;
	extern DMA_HandleTypeDef hdma_usart3_rx;
#elif defined(TIP1)
	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc3;
	extern CAN_HandleTypeDef hcan1;
	extern CAN_HandleTypeDef hcan2;
	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart3;
	extern DMA_HandleTypeDef hdma_usart3_rx;
#elif defined(ROBOMASTER_A)
	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc3;
//	extern CAN_HandleTypeDef hcan1;
//	extern CAN_HandleTypeDef hcan2;
	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart6;
	extern DMA_HandleTypeDef hdma_usart1_rx;
#elif defined(ROBOMASTER_C)
	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc3;
	extern CAN_HandleTypeDef hcan1;
	extern CAN_HandleTypeDef hcan2;
	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart3;
	extern DMA_HandleTypeDef hdma_usart3_rx;
#endif

/* Exported macro ------------------------------------------------------------*/
#if defined(TIP)
    #define duart	huart1
#elif defined(TIP1)
    #define duart	huart1
#elif defined(ROBOMASTER_A)
	#define duart	huart6
#elif defined(ROBOMASTER_C)
    #define duart	huart1
#endif

#endif /* TP_DEFINE_H */
