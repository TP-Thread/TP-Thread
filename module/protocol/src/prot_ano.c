/**
  ******************************************************************************
  * @file    prot_ano.c
  * @author  TP-Thread
  * @brief   匿名上位机通信.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "prot_ano.h"

/* Private includes ----------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* Private macro -------------------------------------------------------------*/
#define BYTE0(data) (*(char *)(&data))
#define BYTE1(data) (*((char *)(&data)+1))
#define BYTE2(data) (*((char *)(&data)+2))
#define BYTE3(data) (*((char *)(&data)+3))

/* Private variables ---------------------------------------------------------*/
uint8_t ano_buf[100];
uint16_t flen;

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief	上传姿态数据
 */
void Sent_ATTitude_Data(float *angle_data_m, float *angle_data_d, float *rate_data_m, float *rate_data_d)
{	
	uint8_t cnt = 0;

	ano_buf[cnt++] = 0xAB;	// 帧头
	ano_buf[cnt++] = 0xFF;	// 源地址
	ano_buf[cnt++] = 0xFF;	// 目标地址
	ano_buf[cnt++] = 0xF1;	// 功能码
	ano_buf[cnt++] = 48;	// 数据长度低字节
	ano_buf[cnt++] = 0;		// 数据长度高字节

	// angle_m_r
	ano_buf[cnt++] = BYTE0(angle_data_m[0]);
	ano_buf[cnt++] = BYTE1(angle_data_m[0]);
	ano_buf[cnt++] = BYTE2(angle_data_m[0]);
	ano_buf[cnt++] = BYTE3(angle_data_m[0]);
	// angle_m_p
	ano_buf[cnt++] = BYTE0(angle_data_m[1]);
	ano_buf[cnt++] = BYTE1(angle_data_m[1]);
	ano_buf[cnt++] = BYTE2(angle_data_m[1]);
	ano_buf[cnt++] = BYTE3(angle_data_m[1]);
	// angle_m_y
	ano_buf[cnt++] = BYTE0(angle_data_m[2]);
	ano_buf[cnt++] = BYTE1(angle_data_m[2]);
	ano_buf[cnt++] = BYTE2(angle_data_m[2]);
	ano_buf[cnt++] = BYTE3(angle_data_m[2]);

	// angle_d_r
	ano_buf[cnt++] = BYTE0(angle_data_d[0]);
	ano_buf[cnt++] = BYTE1(angle_data_d[0]);
	ano_buf[cnt++] = BYTE2(angle_data_d[0]);
	ano_buf[cnt++] = BYTE3(angle_data_d[0]);
	// angle_d_p
	ano_buf[cnt++] = BYTE0(angle_data_d[1]);
	ano_buf[cnt++] = BYTE1(angle_data_d[1]);
	ano_buf[cnt++] = BYTE2(angle_data_d[1]);
	ano_buf[cnt++] = BYTE3(angle_data_d[1]);
	// angle_d_y
	ano_buf[cnt++] = BYTE0(angle_data_d[2]);
	ano_buf[cnt++] = BYTE1(angle_data_d[2]);
	ano_buf[cnt++] = BYTE2(angle_data_d[2]);
	ano_buf[cnt++] = BYTE3(angle_data_d[2]);

	// rate_m_r
	ano_buf[cnt++] = BYTE0(rate_data_m[0]);
	ano_buf[cnt++] = BYTE1(rate_data_m[0]);
	ano_buf[cnt++] = BYTE2(rate_data_m[0]);
	ano_buf[cnt++] = BYTE3(rate_data_m[0]);
	// rate_m_p
	ano_buf[cnt++] = BYTE0(rate_data_m[1]);
	ano_buf[cnt++] = BYTE1(rate_data_m[1]);
	ano_buf[cnt++] = BYTE2(rate_data_m[1]);
	ano_buf[cnt++] = BYTE3(rate_data_m[1]);
	// rate_m_y
	ano_buf[cnt++] = BYTE0(rate_data_m[2]);
	ano_buf[cnt++] = BYTE1(rate_data_m[2]);
	ano_buf[cnt++] = BYTE2(rate_data_m[2]);
	ano_buf[cnt++] = BYTE3(rate_data_m[2]);

	// rate_d_r
	ano_buf[cnt++] = BYTE0(rate_data_d[0]);
	ano_buf[cnt++] = BYTE1(rate_data_d[0]);
	ano_buf[cnt++] = BYTE2(rate_data_d[0]);
	ano_buf[cnt++] = BYTE3(rate_data_d[0]);
	// rate_d_p
	ano_buf[cnt++] = BYTE0(rate_data_d[1]);
	ano_buf[cnt++] = BYTE1(rate_data_d[1]);
	ano_buf[cnt++] = BYTE2(rate_data_d[1]);
	ano_buf[cnt++] = BYTE3(rate_data_d[1]);
	// rate_d_y
	ano_buf[cnt++] = BYTE0(rate_data_d[2]);
	ano_buf[cnt++] = BYTE1(rate_data_d[2]);
	ano_buf[cnt++] = BYTE2(rate_data_d[2]);
	ano_buf[cnt++] = BYTE3(rate_data_d[2]);
	
	uint8_t sumcheck = 0;
	uint8_t addcheck = 0;
	uint16_t flen = ano_buf[4] + ano_buf[5] * 255;
	for (uint16_t i=0; i < (flen+6); i++)	//校验计算
	{
		sumcheck += ano_buf[i]; 
		addcheck += sumcheck; 
	}

	ano_buf[cnt++] = sumcheck;	// 和校验
	ano_buf[cnt++] = addcheck;	// 附加校验
	
	// HAL_UART_Transmit(&duart, ano_buf, cnt, 0xffff); //串口发送
	CDC_Transmit_FS(ano_buf, cnt);
}

/**
* @brief	上传电机PWM数据
 */
void Sent_Motor_Data(uint16_t *motor_data_pwm)
{	
	uint8_t cnt = 0;

	ano_buf[cnt++] = 0xAB;	// 帧头
	ano_buf[cnt++] = 0xFF;	// 源地址
	ano_buf[cnt++] = 0xFF;	// 目标地址
	ano_buf[cnt++] = 0xF2;	// 功能码
	ano_buf[cnt++] = 8;		// 数据长度低字节
	ano_buf[cnt++] = 0;		// 数据长度高字节

	// motor_pwm1
	ano_buf[cnt++] = BYTE0(motor_data_pwm[0]);
	ano_buf[cnt++] = BYTE1(motor_data_pwm[0]);
	// motor_pwm2
	ano_buf[cnt++] = BYTE0(motor_data_pwm[1]);
	ano_buf[cnt++] = BYTE1(motor_data_pwm[1]);
	// motor_pwm3
	ano_buf[cnt++] = BYTE0(motor_data_pwm[2]);
	ano_buf[cnt++] = BYTE1(motor_data_pwm[2]);
	// motor_pwm4
	ano_buf[cnt++] = BYTE0(motor_data_pwm[3]);
	ano_buf[cnt++] = BYTE1(motor_data_pwm[3]);

	uint8_t sumcheck = 0;
	uint8_t addcheck = 0;
	uint16_t flen = ano_buf[4] + ano_buf[5] * 255;
	for (uint16_t i=0; i < (flen+6); i++)	//校验计算
	{
		sumcheck += ano_buf[i]; 
		addcheck += sumcheck; 
	}

	ano_buf[cnt++] = sumcheck;	// 和校验
	ano_buf[cnt++] = addcheck;	// 附加校验
	
	// HAL_UART_Transmit(&duart, ano_buf, cnt, 0xffff); //串口发送
	CDC_Transmit_FS(ano_buf, cnt);
}
