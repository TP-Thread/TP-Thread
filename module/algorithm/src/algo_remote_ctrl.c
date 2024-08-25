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
	rctrl_t act_ctrl;	// 控制分量
	
	switch (mav_state) 
	{
        case DISARMED:    // 锁定模式
            if ((ch_thrust < 500) && (ch_yaw < 500)) // 解锁
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw < 500))
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
			else // 停止PWM输出
			{
				// printf("DISARMED\n");
				act_ctrl.thrust = 0;
				act_ctrl.roll = 0;
				act_ctrl.pitch = 0;
				act_ctrl.yaw = 0;
				Mixer_Ctrl(&act_ctrl);
			}
            break;
        case ARMED:    // 解锁模式	
            if ((ch_thrust < 500) && (ch_yaw > 1500)) // 锁定
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw > 1500))
				{
					mav_state = DISARMED;
					BEEP_Volume(20000);
					osDelay(2000);
					BEEP_Volume(0);
				}
			}
			else if(ch_kill > 1500) // 停止PWM输出
			{
				// printf("KILL\n");
				act_ctrl.thrust = 0;
				act_ctrl.roll = 0;
				act_ctrl.pitch = 0;
				act_ctrl.yaw = 0;
				Mixer_Ctrl(&act_ctrl);
			}
			else if(ch_mode < 500) // 自稳模式
			{
				//printf("STABILIZE\n");
				act_ctrl.thrust = (ch_thrust - 300) * 0.5 + 1000; // 油门分量：1000~1700
				angle_d[0] = (ch_roll - 1000) * 0.05;
				angle_d[1] = (ch_pitch - 1000) * 0.05;
				rate_d[2] = (ch_yaw - 1000) * 0.1;

				Attitude_Ctrl(&act_ctrl);
			}
			else
			{
				// printf("UNKNOWN\n");
				act_ctrl.thrust = 0;
				act_ctrl.roll = 0;
				act_ctrl.pitch = 0;
				act_ctrl.yaw = 0;
				Mixer_Ctrl(&act_ctrl);
			}
            break;
		case CALIBRATE:    // 校准模式
            if ((ch_thrust < 500) && (ch_yaw < 500)) // 解锁
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw < 500))
				{
					mav_state = ARMED;
					BEEP_Volume(20000);
					osDelay(1000);
					BEEP_Volume(0);
				}
			}
			else if ((ch_thrust < 500) && (ch_yaw > 1500)) // 锁定
			{
				osDelay(1000);
				if ((ch_thrust < 500) && (ch_yaw > 1500))
				{
					mav_state = DISARMED;
					BEEP_Volume(20000);
					osDelay(2000);
					BEEP_Volume(0);
				}
			}
			else // 油门校准
			{
				// printf("CALIBRATE\n");
				act_ctrl.thrust = (ch_thrust - 300) * 0.7143f + 1000;
				act_ctrl.roll = 0;
				act_ctrl.pitch = 0;
				act_ctrl.yaw = 0;
				Mixer_Ctrl(&act_ctrl);
			}
            break;
        default:
            printf("Flight Mode: UNKNOWN\n");
            break;
    }
}
