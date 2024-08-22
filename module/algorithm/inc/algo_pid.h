#ifndef ALGO_PID_H
#define ALGO_PID_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	float desired;	 //< set point
	float measured;	 //< current point

	float error;	 //< error
	float perror; 	 //< previous error
	float integ;	 //< integral
	float deriv;	 //< derivative
	
	float kp;		 //< proportional gain
	float ki;		 //< integral gain
	float kd;		 //< derivative gain
	
	float pout;		 //< proportional output
	float iout;		 //< integral output
	float dout;		 //< derivative output
	float out;
	
	float ilimit;	 //< integral limit
	float outlimit;
} pid_t;

/* Exported functions prototypes ---------------------------------------------*/
void PID_Init(pid_t *pid, const float pid_param[3]);
void PID_Reset(pid_t *pid);
float PID_Update(pid_t *pid);

#endif
