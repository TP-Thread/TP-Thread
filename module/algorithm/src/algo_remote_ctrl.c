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
state_e mav_state = DISARMED;	// 无人机当前状态
rctrl_t rc_ctrl;	// 电机控制分量
mctrl_t motor_ctrl;	// 电机PWM控制量

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	Remote control.
 *			正式起飞前需要进行电调校准，通电后左侧遥杆推至右上角进入电调校准模式
 *			保持油门通道最高，电调会发出一系列提示音，然后将PWM信号设置为最小值
 *			电调将发出一组确认音，表示已成功记录油门数值，然后重新连接以保存校准设置。
 * @param  	argument: Not used
 * @retval 	None
 */
void Remote_Ctrl(void)
{
	switch (mav_state) 
	{
        case DISARMED:    // 锁定模式
            if ((ch_thrust < 500) && (ch_yaw > 1500)) // 解锁
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw > 1500))
				{
					mav_state = ARMED;
					BEEP_Volume(20000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
			else if ((ch_thrust > 1500) && (ch_yaw > 1500)) // 校准油门
			{
				osDelay(1000);
				if ((ch_thrust > 1500) && (ch_yaw > 1500))
				{
					mav_state = CALIBRATE;
					BEEP_Volume(10000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
            break;
        case ARMED:    // 解锁模式
            if ((ch_thrust < 500) && (ch_yaw < 500)) // 锁定
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw < 500))
				{
					mav_state = DISARMED;
					BEEP_Volume(20000);
					osDelay(2000);
					BEEP_Volume(0);
				}
			}
			else // 遥控
			{
				// 期望角度 -35~35°
				angle_d[0] = (ch_roll - 1000) * 0.05;
				angle_d[1] = (ch_pitch - 1000) * 0.05;
				// angle_d[2] = 0;

				Attitude_Ctrl();
			}
            break;
		case CALIBRATE:    // 校准模式
            if ((ch_thrust < 500) && (ch_yaw > 1500)) // 解锁
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw > 1500))
				{
					mav_state = ARMED;
					BEEP_Volume(20000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
			else if ((ch_thrust < 500) && (ch_yaw < 500)) // 锁定
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw < 500))
				{
					mav_state = DISARMED;
					BEEP_Volume(20000);
					osDelay(2000);
					BEEP_Volume(0);
				}
			}
			else // 油门校准
			{
				rc_ctrl.thrust = (ch_thrust - 300) * 0.7143f + 1000; // 电调极值：1000~2000
				rc_ctrl.thrust = PWM_LIMIT(rc_ctrl.thrust, 1000, 2000);
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
