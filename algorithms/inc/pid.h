#ifndef BSP_PID_H
#define BSP_PID_H

#include "main.h"

#define Limit_Out(input, max)   \
	{                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

typedef struct
{
	float Kp;
	float Ki;
	float Kd;

	float expect;	// 期望值
	float actual;	// 实际值

	float error[2]; //误差项 0最新 1上一次
	float dbuf;  	//微分项
	
	float Pout;
	float Iout;
	float Dout;
	float out;

	float max_iout; //最大积分输出	
	float max_out;  //最大输出
}PID;


void PID_Init(PID *pid, const float PID_Param[3], float max_out, float max_iout);
float PID_Calculate(PID* pid, float fdb, float set);
void PID_Clear(PID *pid);

#endif
