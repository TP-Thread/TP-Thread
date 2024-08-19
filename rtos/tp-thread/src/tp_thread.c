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
/* Definitions for Mixer */
osThreadId_t MixerHandle;
const osThreadAttr_t Mixer_attributes = {
  .name = "Mixer",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
extern void Index_Entry(void *argument);
extern void Mixer_Entry(void *argument);

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
    /* creation of Mixer */
    MixerHandle = osThreadNew(Mixer_Entry, NULL, &Mixer_attributes);
}
