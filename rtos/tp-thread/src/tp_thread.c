/**
  ******************************************************************************
  * @file    tp_thread.c
  * @author  TP-Thread
  * @brief   TP-Thread initialization.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"
#include "task.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
#include "tp_define.h"
#include "SEGGER_SYSVIEW.h"

/* Private variables ---------------------------------------------------------*/
/* Definitions for Index */
osThreadId_t IndexHandle;
const osThreadAttr_t Index_attributes = {
  .name = "Index",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
extern void Index_Entry(void *argument);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  TP-Thread initialization
  * @param  None
  * @retval None
  */
void TP_Thread_Init(void)
{
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
  /* creation of Index */
  IndexHandle = osThreadNew(Index_Entry, NULL, &Index_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}
