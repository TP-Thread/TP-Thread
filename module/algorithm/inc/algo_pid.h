#ifndef ALGO_PID_H
#define ALGO_PID_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported types ------------------------------------------------------------*/
#define Limit_Out(input, max)  \
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
	float k_p;
	float k_i;
	float k_d;

	float expect; // 期望值
	float actual; // 实际值

	float error[2]; // 误差项 0最新 1上一次
	float dbuf;		// 微分项

	float p_out;
	float i_out;
	float d_out;
	float out;

	float max_i_out; // 最大积分输出
	float max_out;	// 最大输出
} pid_t;

/* Exported functions prototypes ---------------------------------------------*/
void PID_Init(pid_t *pid, const float pid_param[3], float max_out, float max_iout);
float PID_Calculate(pid_t *pid, float fdb, float set);
void PID_Clear(pid_t *pid);

#endif
