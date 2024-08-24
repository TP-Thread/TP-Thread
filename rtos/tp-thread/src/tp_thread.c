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
extern void Index_Entry(void *argument);
extern void Rc_Entry(void *argument);
extern void Imu_Entry(void *argument);

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
	/* creation of Rc */
	RcHandle = osThreadNew(Rc_Entry, NULL, &Rc_attributes);
	/* creation of Imu */
	ImuHandle = osThreadNew(Imu_Entry, NULL, &Imu_attributes);
	
	/* Create the event(s) */
	/* creation of Imu_Event */
	Imu_EventHandle = osEventFlagsNew(&Imu_Event_attributes);
	
}
