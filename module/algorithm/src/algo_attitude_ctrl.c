/**
 ******************************************************************************
 * @file    algo_attitude_ctrl.c
 * @author  TP-Thread
 * @brief   姿态控制.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "algo_attitude_ctrl.h"

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
float angle_m[3]; // 测量姿态角 deg
float angle_d[3]; // 期望姿态角 deg（rp:-35~35°）

float rate_m[3]; // 测量姿态角速度 deg/s
float rate_d[3]; // 期望姿态角速度 deg/s（rp:-180~180deg/s）

pid_t att_r_pid;
pid_t att_p_pid;
pid_t att_y_pid;

pid_t rate_r_pid;
pid_t rate_p_pid;
pid_t rate_y_pid;

// 角度PID参数
float att_r_pid_param[3] = {5, 0, 0};
float att_p_pid_param[3] = {5, 0, 0};
float att_y_pid_param[3] = {5, 0, 0};
// 角速度PID参数
float rate_r_pid_param[3] = {0.5, 0, 0.1};
float rate_p_pid_param[3] = {0.5, 0, 0.1};
float rate_y_pid_param[3] = {0.1, 0, 0.1};

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	姿态环P-PID参数初始化
 */
void AC_PPID_Init(void)
{
	PID_Init(&att_r_pid, att_r_pid_param);
	PID_Init(&att_p_pid, att_p_pid_param);
	PID_Init(&att_y_pid, att_y_pid_param);
	
	PID_Init(&rate_r_pid, rate_r_pid_param);
	PID_Init(&rate_p_pid, rate_p_pid_param);
	PID_Init(&rate_y_pid, rate_y_pid_param);
}

/**
 * @brief	姿态环P-PID控制
 */
void Attitude_Ctrl(void)
{
	// 外环角度测量值
	att_r_pid.measured = angle_m[0];
	att_p_pid.measured = angle_m[1];
	att_y_pid.measured = angle_m[2];
	// 内环角速度测量值
	rate_r_pid.measured = rate_m[0];
	rate_p_pid.measured = rate_m[1];
	rate_y_pid.measured = rate_m[2];

	// 外环控制角度期望值
	att_r_pid.desired = angle_d[0];
	att_p_pid.desired = angle_d[1];
	// att_y_pid.desired = angle_d[2];
	// 内环控制角速度期望值
	rate_r_pid.desired = PID_Update(&att_r_pid);
	rate_p_pid.desired = PID_Update(&att_p_pid);
	// rate_y_pid.desired = PID_Update(&att_y_pid);
	rate_y_pid.desired = (sbus_ch.ch3 - 1000) * 0.1;
	
	// 电机PWM控制分量
	rc_ctrl.thrust = (sbus_ch.ch3 - 300) * 0.5 + 1000; // 油门分量：1000~1700
	rc_ctrl.roll = PID_Update(&rate_r_pid);
	rc_ctrl.pitch = PID_Update(&rate_p_pid);
	rc_ctrl.yaw = PID_Update(&rate_y_pid);
	
	motor_ctrl.pwm1 = rc_ctrl.thrust - rc_ctrl.roll + rc_ctrl.pitch + rc_ctrl.yaw;
	motor_ctrl.pwm2 = rc_ctrl.thrust + rc_ctrl.roll - rc_ctrl.pitch + rc_ctrl.yaw;
	motor_ctrl.pwm3 = rc_ctrl.thrust + rc_ctrl.roll + rc_ctrl.pitch - rc_ctrl.yaw;
	motor_ctrl.pwm4 = rc_ctrl.thrust - rc_ctrl.roll - rc_ctrl.pitch - rc_ctrl.yaw;

    // 限制PWM信号在合理范围内
    motor_ctrl.pwm1 = CONSTRAIN(motor_ctrl.pwm1, 1000, 2000);
	motor_ctrl.pwm2 = CONSTRAIN(motor_ctrl.pwm2, 1000, 2000);
	motor_ctrl.pwm3 = CONSTRAIN(motor_ctrl.pwm3, 1000, 2000);
	motor_ctrl.pwm4 = CONSTRAIN(motor_ctrl.pwm4, 1000, 2000);

	// 输出PWM信号到电机
	if (motor_ctrl.pwm1 > motor_ctrl.pwm4)
	{
		XPWM_Set(XTIM_CHANNEL_1, motor_ctrl.pwm1);
		XPWM_Set(XTIM_CHANNEL_2, motor_ctrl.pwm2);
		XPWM_Set(XTIM_CHANNEL_3, motor_ctrl.pwm3);
		XPWM_Set(XTIM_CHANNEL_4, motor_ctrl.pwm4);
	}
	else
	{
		XPWM_Set(XTIM_CHANNEL_4, motor_ctrl.pwm4);
		XPWM_Set(XTIM_CHANNEL_3, motor_ctrl.pwm3);
		XPWM_Set(XTIM_CHANNEL_2, motor_ctrl.pwm2);
		XPWM_Set(XTIM_CHANNEL_1, motor_ctrl.pwm1);
	}
}