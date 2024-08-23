#ifndef ALGO_ATTITUDE_CTRL_H
#define ALGO_ATTITUDE_CTRL_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
extern float angle_m[3]; // 测量姿态角 deg
extern float angle_d[3]; // 期望姿态角 deg

extern float rate_m[3]; // 测量姿态角速度 deg/s
extern float rate_d[3]; // 期望姿态角速度 deg/s

/* Exported functions prototypes ---------------------------------------------*/
void AC_PPID_Init(void);
void Attitude_Ctrl(void);

#endif
