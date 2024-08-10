/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// #include "bsp_key.h"
// #include "bsp_uart.h"
#include "bsp_sbus.h"
// #include "bsp_vin.h"

// #include "drv_can.h"
// #include "drv_can_cmd.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
// extern ADC_HandleTypeDef hadc1;
// extern ADC_HandleTypeDef hadc3;

// extern CAN_HandleTypeDef hcan1;
// extern CAN_HandleTypeDef hcan2;

// extern UART_HandleTypeDef huart1;
// extern UART_HandleTypeDef huart3;
// extern UART_HandleTypeDef huart6;
// extern DMA_HandleTypeDef hdma_usart3_rx;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
// #define DRV_CAN1
// #define DRV_CAN2

#define THREAD_INDEX
// #define THREAD_MIXER
// #define THREAD_VIN

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_R_Pin GPIO_PIN_4
#define LED_R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LED_R_On() HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)
#define LED_R_Off() HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)
#define LED_R_Toggle() HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
