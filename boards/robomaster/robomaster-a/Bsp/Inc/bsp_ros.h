#ifndef BSP_ROS_H
#define BSP_ROS_H

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

#define ROS_FLAG 0xDD	//数据帧帧头

#define ROS_MAX_LEN     	12
#define ROS_BUF_LEN     	6	//接收一帧数据的长度


//小车目标运动速度，单位：m/s rad/s
typedef struct
{
	float data_s[6];
	float Move_X;
	float Move_Y;
	float Move_W;
}Vector_Struct;


void ROS_Config(void);

void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart);

#endif
