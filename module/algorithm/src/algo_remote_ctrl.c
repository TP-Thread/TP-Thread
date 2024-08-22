/**
 ******************************************************************************
 * @file    algo_remote_ctrl.c
 * @author  TP-Thread
 * @brief   遥控.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "algo_remote_ctrl.h"

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
state_e mav_state = DISARMED;
rctrl_t rc_ctrl;
mctrl_t motor_ctrl;

/* Private functions ---------------------------------------------------------*/
void Remote_Ctrl(void)
{
	switch (mav_state) 
	{
        case DISARMED:
            if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 > 1500))
			{
				osDelay(1000);
				if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 > 1500))
				{
					mav_state = ARMED;
					BEEP_Volume(20000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
			else if ((sbus_ch.ch3 > 1500) && (sbus_ch.ch4 > 1500))
			{
				osDelay(1000);
				if ((sbus_ch.ch3 > 1500) && (sbus_ch.ch4 > 1500))
				{
					mav_state = CALIBRATE;
					BEEP_Volume(10000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
            break;
        case ARMED:
            if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 < 500))
			{
				osDelay(1000);
				if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 < 500))
				{
					mav_state = DISARMED;
					BEEP_Volume(20000);
					osDelay(2000);
					BEEP_Volume(0);
				}
			}
			else
			{
				// 控制期望角度
				angle_d[0] = (sbus_ch.ch1 - 1000) * 0.05;
				angle_d[1] = (sbus_ch.ch2 - 1000) * 0.05;
				// angle_d[2] = 0;

				Attitude_Ctrl();
			}
            break;
		case CALIBRATE:
            if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 > 1500))
			{
				osDelay(1000);
				if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 > 1500))
				{
					mav_state = ARMED;
					BEEP_Volume(20000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
			else if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 < 500))
			{
				osDelay(1000);
				if ((sbus_ch.ch3 < 500) && (sbus_ch.ch4 < 500))
				{
					mav_state = DISARMED;
					BEEP_Volume(20000);
					osDelay(2000);
					BEEP_Volume(0);
				}
			}
			else
			{
				// 油门校准
				rc_ctrl.thrust = (sbus_ch.ch3 - 300) * 5.0f / 7.0f + 1000; // 电调极值：1000~2000
				rc_ctrl.thrust = CONSTRAIN(rc_ctrl.thrust, 1000, 2000);
				XPWM_Set(XTIM_CHANNEL_1, rc_ctrl.thrust);
				XPWM_Set(XTIM_CHANNEL_2, rc_ctrl.thrust);
				XPWM_Set(XTIM_CHANNEL_3, rc_ctrl.thrust);
				XPWM_Set(XTIM_CHANNEL_4, rc_ctrl.thrust);
			}
            break;
        case STABILIZE:
            printf("Flight Mode: STABILIZE\n");
            break;
        default:
            printf("Flight Mode: UNKNOWN\n");
            break;
    }
}
