/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.0
 * @日  期  2024-02-20
 * @内  容  指示索引
 ******************************************************************************
 */

#include "task_index.h"

/**
 * @brief	vin 任务,测量电压
 * @param	argument: NULL
 */
VOID Index_Entry(ULONG thread_input)
{
    while (1)
    {
        LED_R_Toggle();
        printf("Index\n");
        tx_thread_sleep(1000);
    }
}
