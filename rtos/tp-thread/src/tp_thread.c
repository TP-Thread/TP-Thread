/**
  ******************************************************************************
  * @file    tp_thread.c
  * @author  TP-Thread
  * @brief   TP-Thread initialization.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private includes ----------------------------------------------------------*/
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
	/* SystemView Init */
	SEGGER_SYSVIEW_Conf();

	/* Create the thread(s) */
	/* creation of Index */
	IndexHandle = osThreadNew(Index_Entry, NULL, &Index_attributes);
}
