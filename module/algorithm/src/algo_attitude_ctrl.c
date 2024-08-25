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

float rate_m[3]; // 测量姿态角速度 dps
float rate_d[3]; // 期望姿态角速度 dps（rp:-180~180dps）

uint16_t motor_pwm[4];	// 四个电机的PWM控制量

// 角度PID
static pid_t att_r_pid;
static pid_t att_p_pid;
static pid_t att_y_pid;
// 角速度PID
static pid_t rate_r_pid;
static pid_t rate_p_pid;
static pid_t rate_y_pid;

// 角度PID参数：kp ki kd ilimit outlimit
float att_r_pid_param[5] = {5, 0, 0, 200, 200};
float att_p_pid_param[5] = {5, 0, 0, 200, 200};
float att_y_pid_param[5] = {5, 0, 0, 200, 200};
// 角速度PID参数：kp ki kd ilimit outlimit
float rate_r_pid_param[5] = {0.5, 0, 0.00, 200, 200};
float rate_p_pid_param[5] = {0.5, 0, 0.00, 200, 200};
float rate_y_pid_param[5] = {0.1, 0, 0.00, 100, 100};

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	姿态环P-PID参数初始化
 */
void AC_PPID_Init(void)
{
	// 角度PID参数初始化
	PID_Init(&att_r_pid, att_r_pid_param);
	PID_Init(&att_p_pid, att_p_pid_param);
	PID_Init(&att_y_pid, att_y_pid_param);
	// 角速度PID参数初始化
	PID_Init(&rate_r_pid, rate_r_pid_param);
	PID_Init(&rate_p_pid, rate_p_pid_param);
	PID_Init(&rate_y_pid, rate_y_pid_param);
}

/**
 * @brief	姿态环P-PID控制，输出控制器分量
 */
void Attitude_Ctrl(rctrl_t *act_control)
{
	// 角度测量值
	att_r_pid.measured = angle_m[0];
	att_p_pid.measured = angle_m[1];
	att_y_pid.measured = angle_m[2];
	// 角速度测量值
	rate_r_pid.measured = rate_m[0];
	rate_p_pid.measured = rate_m[1];
	rate_y_pid.measured = rate_m[2];

	// 角度期望值
	att_r_pid.desired = angle_d[0];
	att_p_pid.desired = angle_d[1];
	// att_y_pid.desired = angle_d[2];
	// 角速度期望值
	rate_r_pid.desired = rate_d[0] = PID_Calculate(&att_r_pid);
	rate_p_pid.desired = rate_d[1] = PID_Calculate(&att_p_pid);
	// rate_y_pid.desired = rate_d[2] = PID_Calculate(&att_y_pid);
	rate_y_pid.desired = rate_d[2];

	// 电机PWM控制分量
	act_control->roll = PID_Calculate(&rate_r_pid);
	act_control->pitch = PID_Calculate(&rate_p_pid);
	act_control->yaw = PID_Calculate(&rate_y_pid);
	
	Mixer_Ctrl(act_control);
}

/**
 * @brief	混控输出
 */
void Mixer_Ctrl(rctrl_t *act_control)
{
	motor_pwm[0] = act_control->thrust - act_control->roll + act_control->pitch + act_control->yaw;
	motor_pwm[1] = act_control->thrust + act_control->roll - act_control->pitch + act_control->yaw;
	motor_pwm[2] = act_control->thrust + act_control->roll + act_control->pitch - act_control->yaw;
	motor_pwm[3] = act_control->thrust - act_control->roll - act_control->pitch - act_control->yaw;

    // 限制PWM信号在合理范围内
	motor_pwm[0] = PWM_LIMIT(motor_pwm[0], 1000, 2000);
	motor_pwm[1] = PWM_LIMIT(motor_pwm[1], 1000, 2000);
	motor_pwm[2] = PWM_LIMIT(motor_pwm[2], 1000, 2000);
	motor_pwm[3] = PWM_LIMIT(motor_pwm[3], 1000, 2000);
	
	// 输出PWM信号到电机
	if (motor_pwm[0] > motor_pwm[3])
	{
		XPWM_Set(XTIM_CHANNEL_1, motor_pwm[0]);
		XPWM_Set(XTIM_CHANNEL_2, motor_pwm[1]);
		XPWM_Set(XTIM_CHANNEL_3, motor_pwm[2]);
		XPWM_Set(XTIM_CHANNEL_4, motor_pwm[3]);
	}
	else
	{
		XPWM_Set(XTIM_CHANNEL_4, motor_pwm[3]);
		XPWM_Set(XTIM_CHANNEL_3, motor_pwm[2]);
		XPWM_Set(XTIM_CHANNEL_2, motor_pwm[1]);
		XPWM_Set(XTIM_CHANNEL_1, motor_pwm[0]);
	}
}
