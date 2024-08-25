#ifndef ALGO_REMOTE_CTRL_H
#define ALGO_REMOTE_CTRL_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/
#define ch_thrust	sbus_ch.ch3
#define ch_roll		sbus_ch.ch1
#define ch_pitch	sbus_ch.ch2
#define ch_yaw 		sbus_ch.ch4

#define ch_mode		sbus_ch.ch5
#define ch_kill 	sbus_ch.ch6

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    DISARMED,   // 无人机未解锁
    ARMED,      // 无人机已解锁
	CALIBRATE,  // 无人机电调校准模式
} state_e;

extern state_e mav_state;

/* Exported functions prototypes ---------------------------------------------*/
void Remote_Ctrl(void);

#endif
