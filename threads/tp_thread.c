/**
  ******************************************************************************
  * @file           : tp_thread.c
  * @brief          : thread entry function
  ******************************************************************************
  */
  
#include "tp_thread.h"

/* Private define ------------------------------------------------------------*/
static UCHAR Trace_BUF[1024]; // 0X1000

TX_THREAD Chassis_TCB;
CHAR Chassis_STK[512];

TX_THREAD Vin_TCB;
CHAR Vin_STK[512];

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  Define TP_Thread_Init.
  * @retval None
  */
VOID TP_Thread_Init(VOID)
{
	tx_trace_enable(Trace_BUF, 1024, 30);

	tx_thread_create(&Chassis_TCB, "Chassis", chassis_entry, 0, Chassis_STK, 512, 1, 1,
					 TX_NO_TIME_SLICE, TX_AUTO_START);

	tx_thread_create(&Vin_TCB, "Voltage", vin_entry, 0, Vin_STK, 512, 4, 4,
					 TX_NO_TIME_SLICE, TX_AUTO_START);
}
