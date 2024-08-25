/**
  ******************************************************************************
  * @file    prot_sbus.c
  * @author  TP-Thread
  * @brief   遥控器SBUS信号处理.
  *          遥控器通过SBUS的协议传输，利用DMA传输方式节约CPU资源，利用串口空闲
  *          中断来拉起处理函数。  
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "prot_sbus.h"

/* Private macro -------------------------------------------------------------*/
#define SBUS_BUF_SIZE 	50	// 接收数据缓存数组给了50个字节长度，防止DMA传输越界

// 定义subs信号的最小值 最大值 中值 死区 以及希望转换成PWM值的范围（1000-2000）
#define SBUS_RANGE_MIN 		300.0f
#define SBUS_RANGE_MAX 		1700.0f
#define SBUS_TARGET_MIN 	1000.0f
#define SBUS_TARGET_MAX 	2000.0f
#define DEAD_RANGE_MIN 		960 // 死区
#define DEAD_RANGE_MAX 		1040
#define SBUS_RANGE_MIDDLE 	1000.0f
#define SBUS_SCALE_FACTOR 	0.71428
#define SBUS_CONNECT_FLAG 	0x00 // flag位标志字节在AT9S遥控器连通时为 0x00

/* Private variables ---------------------------------------------------------*/
uint8_t sbus_buf[25]; 
uint8_t sbus_state;	  // 遥控器与接收器连接状态 0=未连接，1=正常连接

sbus_t sbus_ch; // 遥控器通道数据
uint16_t command[16]; // 遥控器通道数据转换成PWM值

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief	使能IDLE串口空闲中断和DMA接收
 */
void SBUS_Init(void)
{
	// 启动UART IDLE中断，设置HAL_UART_RECEPTION_TOIDLE
	HAL_UARTEx_ReceiveToIdle_DMA(&suart, sbus_buf, SBUS_BUF_SIZE);
	HAL_Delay(1);
	// 启动UART DMA接收，进入中断
	HAL_UARTEx_ReceiveToIdle_DMA(&suart, sbus_buf, SBUS_BUF_SIZE);
}

/**
 * @brief	获取遥控器数据指针
 * @retval	遥控器数据指针
 */
sbus_t *t_SBUS_CH_Get(void)
{
	return &sbus_ch;
}

/**
 * @brief	将sbus信号转化为通道值（300-1700），在串口中断函数里面会调用这个函数，用于更新SBUS信号值
 * @param
 * @retval
 */
uint8_t SBUS_Process(uint8_t *buf)
{
	for (uint8_t i = 0; i < 25; i++)
		sbus_ch.signal[i] = buf[i];

	if (buf[23] == SBUS_CONNECT_FLAG)
	{
		sbus_ch.ch1 = ((int16_t)buf[1] >> 0 | ((int16_t)buf[2] << 8)) & 0x07FF;
		sbus_ch.ch2 = ((int16_t)buf[2] >> 3 | ((int16_t)buf[3] << 5)) & 0x07FF;
		sbus_ch.ch3 = ((int16_t)buf[3] >> 6 | ((int16_t)buf[4] << 2) | (int16_t)buf[5] << 10) & 0x07FF;
		sbus_ch.ch4 = ((int16_t)buf[5] >> 1 | ((int16_t)buf[6] << 7)) & 0x07FF;
		sbus_ch.ch5 = ((int16_t)buf[6] >> 4 | ((int16_t)buf[7] << 4)) & 0x07FF;
		sbus_ch.ch6 = ((int16_t)buf[7] >> 7 | ((int16_t)buf[8] << 1) | (int16_t)buf[9] << 9) & 0x07FF;
		sbus_ch.ch7 = ((int16_t)buf[9] >> 2 | ((int16_t)buf[10] << 6)) & 0x07FF;
		sbus_ch.ch8 = ((int16_t)buf[10] >> 5 | ((int16_t)buf[11] << 3)) & 0x07FF;
		sbus_ch.ch9 = ((int16_t)buf[12] << 0 | ((int16_t)buf[13] << 8)) & 0x07FF;
		sbus_ch.ch10 = ((int16_t)buf[13] >> 3 | ((int16_t)buf[14] << 5)) & 0x07FF;
		sbus_ch.ch11 = ((int16_t)buf[14] >> 6 | ((int16_t)buf[15] << 2) | (int16_t)buf[16] << 10) & 0x07FF;
		sbus_ch.ch12 = ((int16_t)buf[16] >> 1 | ((int16_t)buf[17] << 7)) & 0x07FF;
		sbus_ch.ch13 = ((int16_t)buf[17] >> 4 | ((int16_t)buf[18] << 4)) & 0x07FF;
		sbus_ch.ch14 = ((int16_t)buf[18] >> 7 | ((int16_t)buf[19] << 1) | (int16_t)buf[20] << 9) & 0x07FF;
		sbus_ch.ch15 = ((int16_t)buf[20] >> 2 | ((int16_t)buf[21] << 6)) & 0x07FF;
		sbus_ch.ch16 = ((int16_t)buf[21] >> 5 | ((int16_t)buf[22] << 3)) & 0x07FF;

		return 1;
	}
	else
		return 0;
}

/**
 * @brief	串口空闲中断回调函数
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == suart.Instance)
	{
		HAL_UART_DMAStop(&suart);			// 关闭DMA防止在处理数据时候接收数据，产生干扰

		// 处理接收到的数据
		SBUS_Process(sbus_buf);

		// 重新启动 UART DMA 接收，准备接收下一段数据
        HAL_UARTEx_ReceiveToIdle_DMA(&suart, sbus_buf, SBUS_BUF_SIZE);
	}
}

// 将sbus信号通道值转化为PWM的数值  [1000,2000]
// uint16_t sbus2pwm(uint16_t sbus_value)
//{
//     float pwm;
//	  //                1000                                   300              1000/1400
//     pwm = (float)SBUS_TARGET_MIN + (float)(sbus_value - SBUS_RANGE_MIN) * SBUS_SCALE_FACTOR;
//
//     if (pwm > 2000) pwm = 2000;
//     if (pwm < 1000) pwm = 1000;
//     return (uint16_t)pwm;
// }

// 将sbus信号通道值转化为特定区间的数值  [p_min,p_max]
// float sbus_to_Range(uint16_t sbus_value, float p_min, float p_max)
//{
//     float p;
//     p = p_min + (float)(sbus_value - SBUS_RANGE_MIN) * (p_max-p_min)/(float)(SBUS_RANGE_MAX - SBUS_RANGE_MIN);
//     if (p > p_max) p = p_max;
//     if (p < p_min) p = p_min;
//     return p;
// }
