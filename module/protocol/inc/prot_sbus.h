#ifndef PROT_SBUS_H
#define PROT_SBUS_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint16_t signal[25];
	uint16_t ch1;  // 通道1数值
	uint16_t ch2;  // 通道2数值
	uint16_t ch3;  // 通道3数值
	uint16_t ch4;  // 通道4数值
	uint16_t ch5;  // 通道5数值
	uint16_t ch6;  // 通道6数值
	uint16_t ch7;  // 通道7数值
	uint16_t ch8;  // 通道8数值
	uint16_t ch9;  // 通道9数值
	uint16_t ch10; // 通道10数值
	uint16_t ch11; // 通道11数值
	uint16_t ch12; // 通道12数值
	uint16_t ch13; // 通道13数值
	uint16_t ch14; // 通道14数值
	uint16_t ch15; // 通道15数值
	uint16_t ch16; // 通道16数值
} sbus_t;

extern sbus_t sbus_ch;
extern uint16_t command[16];

/* Exported functions prototypes ---------------------------------------------*/
void SBUS_Init(void);
sbus_t *t_SBUS_CH_Get(void);
uint16_t sbus2pwm(uint16_t sbus_value);

#endif
