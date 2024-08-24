/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tp_thread.h"
#include "SEGGER_SYSVIEW.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Led */
osThreadId_t LedHandle;
const osThreadAttr_t Led_attributes = {
  .name = "Led",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Index */
osThreadId_t IndexHandle;
const osThreadAttr_t Index_attributes = {
  .name = "Index",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Rc */
osThreadId_t RcHandle;
const osThreadAttr_t Rc_attributes = {
  .name = "Rc",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Imu */
osThreadId_t ImuHandle;
const osThreadAttr_t Imu_attributes = {
  .name = "Imu",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for Imu_Event */
osEventFlagsId_t Imu_EventHandle;
const osEventFlagsAttr_t Imu_Event_attributes = {
  .name = "Imu_Event"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Led_Entry(void *argument);
extern void Index_Entry(void *argument);
extern void Rc_Entry(void *argument);
extern void Imu_Entry(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  SEGGER_SYSVIEW_Conf();

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Led */
  LedHandle = osThreadNew(Led_Entry, NULL, &Led_attributes);

  /* creation of Index */
  IndexHandle = osThreadNew(Index_Entry, NULL, &Index_attributes);

  /* creation of Rc */
  RcHandle = osThreadNew(Rc_Entry, NULL, &Rc_attributes);

  /* creation of Imu */
  ImuHandle = osThreadNew(Imu_Entry, NULL, &Imu_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of Imu_Event */
  Imu_EventHandle = osEventFlagsNew(&Imu_Event_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Led_Entry */
/**
  * @brief  Function implementing the Led thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Led_Entry */
void Led_Entry(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN Led_Entry */
  /* Infinite loop */
  for(;;)
  {
	LED_R_Toggle();
    osDelay(500);
  }
  /* USER CODE END Led_Entry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

