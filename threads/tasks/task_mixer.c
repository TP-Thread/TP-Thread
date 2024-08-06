/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.2
 * @日  期  2024-03-05
 * @内  容  底盘控制任务
 ******************************************************************************
 */

#include "task_mixer.h"

/**
 * @brief	底盘任务
 * @param	thread_input:0
 */
VOID Mixer_Entry(ULONG thread_input)
{
    // 遥控器初始化
    SBUS_Init();
    // CAN过滤器配置
    CAN_Filter_Init();

    int32_t speedSet_L, speedSet_R;

    while (1)
    {
        // 切换为陆行模式
        if (SBUS_CH.CH6 > 1500)
        {
            if ((SBUS_CH.CH3 > 950) && (SBUS_CH.CH3 < 1050) && (SBUS_CH.CH1 > 950) && (SBUS_CH.CH1 < 1050))
            {
                Motor_stop(0x141);
                Motor_stop(0x142);
            }
            else
            {
                if ((SBUS_CH.CH3 > 700) && (SBUS_CH.CH3 < 1300))
                {
                    if ((SBUS_CH.CH1 > 700) && (SBUS_CH.CH1 < 1300))
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) - (SBUS_CH.CH1 - 1000)) * 28;
                        speedSet_R = ((SBUS_CH.CH3 - 1000) + (SBUS_CH.CH1 - 1000)) * 28;
                    }
                    else
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) * 28 - (SBUS_CH.CH1 - 1000) * 280);
                        speedSet_R = ((SBUS_CH.CH3 - 1000) * 28 + (SBUS_CH.CH1 - 1000) * 280);
                    }
                }
                else
                {
                    if ((SBUS_CH.CH1 > 700) && (SBUS_CH.CH1 < 1300))
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) * 280 - (SBUS_CH.CH1 - 1000) * 28);
                        speedSet_R = ((SBUS_CH.CH3 - 1000) * 280 + (SBUS_CH.CH1 - 1000) * 28);
                    }
                    else
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) - (SBUS_CH.CH1 - 1000)) * 280;
                        speedSet_R = ((SBUS_CH.CH3 - 1000) + (SBUS_CH.CH1 - 1000)) * 280;
                    }
                }
            }

            Motor_speed(0x141, speedSet_L);
            Motor_speed(0x142, speedSet_R);
        }
        else
        {
            Motor_stop(0x141);
            Motor_stop(0x142);
        }

        // printf("CH3:%d\n", SBUS_CH.CH3);
        tx_thread_sleep(10);
    }
}
