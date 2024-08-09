/**			                                                    
  ******************************************************************************
  * @作  者  两点一线
  * @版  本  V1.1
  * @日  期  2024-02-07
  * @内  容  PID 控制算法
  ******************************************************************************
  */

#include "bsp_pid.h"

/**
  * @brief	pid struct data init
  * @param  pid: PID结构数据指针
  * @param  PID_Param: 0: Kp, 1: Ki, 2:Kd
  * @param  max_out: pid最大输出
  * @param	max_iout: pid最大积分输出
  */
void PID_Init(PID* pid, const float PID_Param[3], float max_out, float max_iout)
{
    pid->Kp = PID_Param[0];
    pid->Ki = PID_Param[1];
    pid->Kd = PID_Param[2];

    pid->error[0] = pid->error[1] = 0.0f;
    pid->dbuf = 0.0f;
	
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;

    pid->max_out = max_out;
    pid->max_iout = max_iout;
}

/**
  * @brief	pid计算
  * @param  pid: PID结构数据指针
  * @param  set: 设定值
  * @param  fdb: 反馈值
  * @retval pid输出
  */
float PID_Calculate(PID* pid, float fdb, float set)
{
    pid->error[1] = pid->error[0];
	pid->actual = fdb;
    pid->expect = set;
    pid->error[0] = set - fdb;

    pid->Pout = pid->Kp * pid->error[0];
	
    pid->Iout += pid->Ki * pid->error[0];
    Limit_Out(pid->Iout, pid->max_iout);
	
    pid->dbuf = (pid->error[0] - pid->error[1]);
    pid->Dout = pid->Kd * pid->dbuf;
    
    pid->out = pid->Pout + pid->Iout + pid->Dout;
    Limit_Out(pid->out, pid->max_out);

    return pid->out;
}

/**
  * @brief	pid 输出清除
  * @param  pid: PID结构数据指针
  */
void PID_Clear(PID* pid)
{
	pid->actual = pid->expect = 0.0f;
	
    pid->error[0] = pid->error[1] = 0.0f;
    pid->dbuf = 0.0f;
	
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
}

