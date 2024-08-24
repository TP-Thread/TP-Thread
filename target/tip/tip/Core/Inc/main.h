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
#include "drv_key.h"
#include "drv_exti.h"
#include "drv_uart.h"
#include "drv_tim.h" 
#include "drv_ist8310.h"
#include "drv_bmi088.h"

#include "prot_ano.h"
#include "prot_sbus.h"

#include "algo_pid.h"
#include "algo_remote_ctrl.h"
#include "algo_attitude_ctrl.h"
// #include "algo_position_ctrl.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;

extern CAN_HandleTypeDef hcan1;
// extern CAN_HandleTypeDef hcan2;

extern I2C_HandleTypeDef hi2c3;

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim10;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart6;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define TIP

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RSTN_MAG_Pin GPIO_PIN_6
#define RSTN_MAG_GPIO_Port GPIOG
#define LED_R_Pin GPIO_PIN_12
#define LED_R_GPIO_Port GPIOH
#define DRDY_MAG_Pin GPIO_PIN_3
#define DRDY_MAG_GPIO_Port GPIOG
#define DRDY_MAG_EXTI_IRQn EXTI3_IRQn
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOH
#define LED_B_Pin GPIO_PIN_10
#define LED_B_GPIO_Port GPIOH
#define KEY_Pin GPIO_PIN_0
#define KEY_GPIO_Port GPIOA
#define CS1_ACCEL_Pin GPIO_PIN_4
#define CS1_ACCEL_GPIO_Port GPIOA
#define INT1_ACCEL_Pin GPIO_PIN_4
#define INT1_ACCEL_GPIO_Port GPIOC
#define INT1_GYRO_Pin GPIO_PIN_5
#define INT1_GYRO_GPIO_Port GPIOC
#define INT1_GYRO_EXTI_IRQn EXTI9_5_IRQn
#define CS1_GYRO_Pin GPIO_PIN_0
#define CS1_GYRO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LED_R_On()              HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)    
#define LED_R_Off()  	        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)     
#define LED_R_Toggle()          HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)

#define LED_G_On()		        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET)    
#define LED_G_Off()  	        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET)     
#define LED_G_Toggle()          HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin)	

#define LED_B_On()		        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)    
#define LED_B_Off()  	        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET)     
#define LED_B_Toggle()          HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

//#define BEEP_On()		        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)    
//#define BEEP_Off()  	        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)     
//#define BEEP_Toggle()           HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
