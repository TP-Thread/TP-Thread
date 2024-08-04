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

	float expect;	// ����ֵ
	float actual;	// ʵ��ֵ

	float error[2]; //����� 0���� 1��һ��
	float dbuf;  	//΢����
	
	float Pout;
	float Iout;
	float Dout;
	float out;

	float max_iout; //���������	
	float max_out;  //������
}PID;


void PID_Init(PID *pid, const float PID_Param[3], float max_out, float max_iout);
float PID_Calculate(PID* pid, float fdb, float set);
void PID_Clear(PID *pid);

#endif
