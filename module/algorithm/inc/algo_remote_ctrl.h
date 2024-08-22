#ifndef ALGO_REMOTE_CTRL_H
#define ALGO_REMOTE_CTRL_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
typedef enum
{
    DISARMED,   // 无人机未解锁
    ARMED,      // 无人机已解锁
	CALIBRATE,  // 无人机电调校准模式
    STABILIZE,  // 无人机处于自稳模式
} state_e;

typedef struct
{
	uint16_t thrust;
	uint16_t roll;
	uint16_t pitch;
	uint16_t yaw;
} rctrl_t;

typedef struct
{
	uint16_t pwm1;
	uint16_t pwm2;
	uint16_t pwm3;
	uint16_t pwm4;
} mctrl_t;

extern state_e mav_state;
extern rctrl_t rc_ctrl;
extern mctrl_t motor_ctrl;

/* Exported functions prototypes ---------------------------------------------*/
void Remote_Ctrl(void);

#endif
