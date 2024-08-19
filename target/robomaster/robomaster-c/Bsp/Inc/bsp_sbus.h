#ifndef BSP_SBUS_H
#define BSP_SBUS_H

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

extern uint16_t command[16];

#define UART_RX_DMA_SIZE 1024
#define SBUS_MAX_LEN 50
#define SBUS_FRAME_SIZE 25 // 接收一帧数据的长度

#define SBUS_CONNECT_FLAG 0x00 // flag位标志字节在AT9S遥控器连通时为 0x00

// 定义subs信号的最小值 最大值 中值 死区 以及希望转换成PWM值的范围（1000-2000）
#define SBUS_RANGE_MIN 300.0f
#define SBUS_RANGE_MAX 1700.0f
#define SBUS_TARGET_MIN 1000.0f
#define SBUS_TARGET_MAX 2000.0f
#define DEAD_RANGE_MIN 960 // 死区
#define DEAD_RANGE_MAX 1040
#define SBUS_RANGE_MIDDLE 1000.0f
#define SBUS_SCALE_FACTOR 0.71428

// 定义四个摇杆与拨动开关的功能
#define ROLL 1
#define PITCH 2
#define THROTTLE 3
#define YAW 4
// #define CONTROL_MODE 6

typedef struct
{
	uint16_t signal[25];
	uint16_t CH1;  // 通道1数值
	uint16_t CH2;  // 通道2数值
	uint16_t CH3;  // 通道3数值
	uint16_t CH4;  // 通道4数值
	uint16_t CH5;  // 通道5数值
	uint16_t CH6;  // 通道6数值
	uint16_t CH7;  // 通道7数值
	uint16_t CH8;  // 通道8数值
	uint16_t CH9;  // 通道9数值
	uint16_t CH10; // 通道10数值
	uint16_t CH11; // 通道11数值
	uint16_t CH12; // 通道12数值
	uint16_t CH13; // 通道13数值
	uint16_t CH14; // 通道14数值
	uint16_t CH15; // 通道15数值
	uint16_t CH16; // 通道16数值
} SBUS_Struct;

extern SBUS_Struct SBUS_CH;

void SBUS_Init(void);
SBUS_Struct *t_SBUS_CH_Get(void);
void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart);
uint16_t sbus_to_pwm(uint16_t sbus_value);

#endif
