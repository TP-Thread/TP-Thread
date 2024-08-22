/**
 ******************************************************************************
 * @file    algo_pid.c
 * @author  TP-Thread
 * @brief   pid_t.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "algo_pid.h"

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	PID参数初始化
 * @param   pid: pid_t结构数据指针
 * @param   PID_Param: 0: kp, 1: ki, 2:kd
 * @param   imax: pid最大积分输出
 * @param	outmax: pid最大输出
 */
void PID_Init(pid_t *pid, const float pid_param[3])
{
	pid->error = 0;
	pid->perror = 0;
	pid->integ = 0;
	pid->deriv = 0;
	
    pid->kp = pid_param[0];
    pid->ki = pid_param[1];
    pid->kd = pid_param[2];

    pid->out = pid->pout = pid->iout = pid->dout = 0.0f;

//    pid->ilimit = imax;
//    pid->outlimit = outmax;
}

/**
 * @brief  PID更新输出
 * @param  pid: pid_t结构数据指针
 * @retval pid输出
 */
float PID_Update(pid_t *pid)
{
	pid->perror = pid->error;
	pid->error = pid->desired - pid->measured;
	
	pid->integ += pid->error;
	pid->deriv = pid->error - pid->perror;

    pid->pout = pid->kp * pid->error;
    pid->iout += pid->ki * pid->error;
    pid->dout = pid->kd * pid->deriv;

    pid->out = pid->pout + pid->iout + pid->dout;

    return pid->out;
}

/**
 * @brief  PID输出重置
 * @param  pid: pid_t结构数据指针
 */
void PID_Reset(pid_t *pid)
{
	pid->error = 0;
	pid->perror = 0;
	pid->integ = 0;
	pid->deriv = 0;
}
