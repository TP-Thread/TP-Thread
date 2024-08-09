/**
  ******************************************************************************
  * @file           : tp_thread.c
  * @brief          : thread entry function
  ******************************************************************************
  */
  
#include "tp_thread.h"

/* Private define ------------------------------------------------------------*/
UCHAR Trace_BUF[5120];	// Can't set it too big

TX_THREAD Index_TCB;
CHAR Index_STK[512];

TX_THREAD Mixer_TCB;
CHAR Mixer_STK[512];

TX_THREAD Vin_TCB;
CHAR Vin_STK[1024];

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  Define TP_Thread_Init.
  * @retval None
  */
VOID TP_Thread_Init(VOID)
{
	tx_trace_enable(Trace_BUF, 5120, 30);

	tx_thread_create(&Index_TCB, "Index", Index_Entry, 0, Index_STK, 512, 1, 1,
					 TX_NO_TIME_SLICE, TX_AUTO_START);
	
	tx_thread_create(&Mixer_TCB, "Mixer", Mixer_Entry, 0, Mixer_STK, 512, 1, 1,
					 TX_NO_TIME_SLICE, TX_AUTO_START);

	tx_thread_create(&Vin_TCB, "Voltage", Vin_Entry, 0, Vin_STK, 1024, 4, 4,
					 TX_NO_TIME_SLICE, TX_AUTO_START);
}
