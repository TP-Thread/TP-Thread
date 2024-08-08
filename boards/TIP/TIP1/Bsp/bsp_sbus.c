/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.2
 * @日  期  2024-02-20
 * @内  容  遥控器处理，遥控器是通过SBUS的协议传输，利用DMA传输方式节约CPU
 *          资源，利用串口空闲中断来拉起处理函数，同时提供一些掉线重启DMA，串口
 *          的方式保证热插拔的稳定性。
 ******************************************************************************
 */

#include "bsp_sbus.h"

uint8_t sbus_buf[SBUS_FRAME_SIZE]; // 接收数据缓存数组，为25个字节，给了50个字节长度，防止DMA传输越界

SBUS_Struct SBUS_CH; // 遥控器通道数据

uint8_t sbus_state;	  // 遥控器与接收器连接状态 0=未连接，1=正常连接
uint16_t command[16]; // 遥控器通道数据转换成PWM值

/**
 * @brief	使能IDLE串口空闲中断和DMA接收
 */
void SBUS_Init(void)
{
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

	HAL_UART_Receive_DMA(&huart3, sbus_buf, SBUS_MAX_LEN);
}

/**
 * @brief	获取遥控器数据指针
 * @retval	遥控器数据指针
 */
SBUS_Struct *t_SBUS_CH_Get(void)
{
	return &SBUS_CH;
}

/**
 * @brief	将sbus信号转化为通道值（300-1700），在串口中断函数里面会调用这个函数，用于更新SBUS信号值
 * @param
 * @retval
 */
uint8_t SBUS_Process(uint8_t *buf)
{
	for (uint8_t i = 0; i < 25; i++)
		SBUS_CH.signal[i] = buf[i];

	if (buf[23] == SBUS_CONNECT_FLAG)
	{
		SBUS_CH.CH1 = ((int16_t)buf[1] >> 0 | ((int16_t)buf[2] << 8)) & 0x07FF;
		SBUS_CH.CH2 = ((int16_t)buf[2] >> 3 | ((int16_t)buf[3] << 5)) & 0x07FF;
		SBUS_CH.CH3 = ((int16_t)buf[3] >> 6 | ((int16_t)buf[4] << 2) | (int16_t)buf[5] << 10) & 0x07FF;
		SBUS_CH.CH4 = ((int16_t)buf[5] >> 1 | ((int16_t)buf[6] << 7)) & 0x07FF;
		SBUS_CH.CH5 = ((int16_t)buf[6] >> 4 | ((int16_t)buf[7] << 4)) & 0x07FF;
		SBUS_CH.CH6 = ((int16_t)buf[7] >> 7 | ((int16_t)buf[8] << 1) | (int16_t)buf[9] << 9) & 0x07FF;
		SBUS_CH.CH7 = ((int16_t)buf[9] >> 2 | ((int16_t)buf[10] << 6)) & 0x07FF;
		SBUS_CH.CH8 = ((int16_t)buf[10] >> 5 | ((int16_t)buf[11] << 3)) & 0x07FF;
		SBUS_CH.CH9 = ((int16_t)buf[12] << 0 | ((int16_t)buf[13] << 8)) & 0x07FF;
		SBUS_CH.CH10 = ((int16_t)buf[13] >> 3 | ((int16_t)buf[14] << 5)) & 0x07FF;
		SBUS_CH.CH11 = ((int16_t)buf[14] >> 6 | ((int16_t)buf[15] << 2) | (int16_t)buf[16] << 10) & 0x07FF;
		SBUS_CH.CH12 = ((int16_t)buf[16] >> 1 | ((int16_t)buf[17] << 7)) & 0x07FF;
		SBUS_CH.CH13 = ((int16_t)buf[17] >> 4 | ((int16_t)buf[18] << 4)) & 0x07FF;
		SBUS_CH.CH14 = ((int16_t)buf[18] >> 7 | ((int16_t)buf[19] << 1) | (int16_t)buf[20] << 9) & 0x07FF;
		SBUS_CH.CH15 = ((int16_t)buf[20] >> 2 | ((int16_t)buf[21] << 6)) & 0x07FF;
		SBUS_CH.CH16 = ((int16_t)buf[21] >> 5 | ((int16_t)buf[22] << 3)) & 0x07FF;

		return 1;
	}
	else
		return 0;
}

/**
 * @brief	自定义的串口中断空闲回调函数（HAL库并没有实现）
 */
void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart)
{
	if ((__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE)) != RESET) // idle标志被置位
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart3); // 清除标志位
		HAL_UART_DMAStop(&huart3);			// 关闭DMA防止在处理数据时候接收数据，产生干扰

		// 实际接收的字节= 预先定义的接收总字节 - __HAL_DMA_GET_COUNTER()
		if ((SBUS_MAX_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx)) == SBUS_FRAME_SIZE)
		{
			sbus_state = SBUS_Process(sbus_buf);
		}
		// 重新设置预先定义的接收总字节
		__HAL_DMA_SET_COUNTER(&hdma_usart3_rx, SBUS_MAX_LEN);

		// 打开DMA接收
		HAL_UART_Receive_DMA(&huart3, sbus_buf, SBUS_MAX_LEN);
	}
}

// 将sbus信号通道值转化为PWM的数值  [1000,2000]
// uint16_t sbus_to_pwm(uint16_t sbus_value)
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
