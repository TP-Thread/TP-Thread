#ifndef ALGO_ATTITUDE_CTRL_H
#define ALGO_ATTITUDE_CTRL_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/
#define ATTITUDE_UPDATE_RATE 	200  //更新频率100hz
#define ATTITUDE_UPDATE_DT 		(1.0f / ATTITUDE_UPDATE_RATE)

/*角度环积分限幅*/
#define PID_ANGLE_ROLL_INTEGRATION_LIMIT 3000.0
#define PID_ANGLE_PITCH_INTEGRATION_LIMIT 3000.0
#define PID_ANGLE_YAW_INTEGRATION_LIMIT 3000.0

/*角速度环积分限幅*/
#define PID_RATE_ROLL_INTEGRATION_LIMIT 10000.0
#define PID_RATE_PITCH_INTEGRATION_LIMIT 10000.0
#define PID_RATE_YAW_INTEGRATION_LIMIT 10000.0

/* Exported types ------------------------------------------------------------*/
extern float angle_m[3]; // 测量姿态角 deg
extern float angle_d[3]; // 期望姿态角 deg

extern float rate_m[3]; // 测量姿态角速度 deg/s
extern float rate_d[3]; // 期望姿态角速度 deg/s

/* Exported functions prototypes ---------------------------------------------*/
void AC_PPID_Init(void);
void Attitude_Ctrl(void);

#endif
