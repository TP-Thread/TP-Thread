/**
 ******************************************************************************
 * @file    algo_pid.c
 * @author  TP-Thread
 * @brief   pid_t.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "algo_pid.h"

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	pid struct data init
 * @param  pid: pid_t结构数据指针
 * @param  PID_Param: 0: k_p, 1: k_i, 2:k_d
 * @param  max_out: pid最大输出
 * @param	max_i_out: pid最大积分输出
 */
void PID_Init(pid_t *pid, const float pid_param[3], float max_out, float max_i_out)
{
    pid->k_p = pid_param[0];
    pid->k_i = pid_param[1];
    pid->k_d = pid_param[2];

    pid->error[0] = pid->error[1] = 0.0f;
    pid->dbuf = 0.0f;

    pid->out = pid->p_out = pid->i_out = pid->d_out = 0.0f;

    pid->max_out = max_out;
    pid->max_i_out = max_i_out;
}

/**
 * @brief	pid计算
 * @param  pid: pid_t结构数据指针
 * @param  set: 设定值
 * @param  fdb: 反馈值
 * @retval pid输出
 */
float PID_Calculate(pid_t *pid, float fdb, float set)
{
    pid->error[1] = pid->error[0];
    pid->actual = fdb;
    pid->expect = set;
    pid->error[0] = set - fdb;

    pid->p_out = pid->k_p * pid->error[0];

    pid->i_out += pid->k_i * pid->error[0];
    Limit_Out(pid->i_out, pid->max_i_out);

    pid->dbuf = (pid->error[0] - pid->error[1]);
    pid->d_out = pid->k_d * pid->dbuf;

    pid->out = pid->p_out + pid->i_out + pid->d_out;
    Limit_Out(pid->out, pid->max_out);

    return pid->out;
}

/**
 * @brief	pid 输出清除
 * @param  pid: pid_t结构数据指针
 */
void PID_Clear(pid_t *pid)
{
    pid->actual = pid->expect = 0.0f;

    pid->error[0] = pid->error[1] = 0.0f;
    pid->dbuf = 0.0f;

    pid->out = pid->p_out = pid->i_out = pid->d_out = 0.0f;
}
