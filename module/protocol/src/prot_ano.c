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
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp)+1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp)+2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp)+3))

/* Private variables ---------------------------------------------------------*/
uint8_t BUFF[100];
uint16_t flen;

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief	上传数据
 */
void sent_data1(uint16_t A,float B,int32_t C)
//发送一个二字节uint16类型，四字节float类型，四字节int32类型
{	
	uint8_t _cnt = 0;
	BUFF[_cnt++]=0xAB;//帧头
	BUFF[_cnt++]=0xFF;//源地址
	BUFF[_cnt++]=0xFF;//目标地址
	BUFF[_cnt++]=0xF1;//功能码（ID）
	BUFF[_cnt++]=10;//数据长度（2字节）
	BUFF[_cnt++]=0;//数据长度
	BUFF[_cnt++]=BYTE0(A);//数据内容A（2字节）
	BUFF[_cnt++]=BYTE1(A);

	BUFF[_cnt++]=BYTE0(B);//数据内容B（4字节）
	BUFF[_cnt++]=BYTE1(B);
	BUFF[_cnt++]=BYTE2(B);
	BUFF[_cnt++]=BYTE3(B);

	BUFF[_cnt++]=BYTE0(C);//数据内容C（4字节）
	BUFF[_cnt++]=BYTE1(C);
	BUFF[_cnt++]=BYTE2(C);
	BUFF[_cnt++]=BYTE3(C);

	uint8_t sumcheck = 0;
	uint8_t addcheck = 0;
	uint16_t flen = BUFF[4] + BUFF[5] * 255;
	for(uint16_t i=0; i < (flen+6); i++)//校验计算
	{
		sumcheck += BUFF[i]; 
		addcheck += sumcheck; 
	}

	BUFF[_cnt++] = sumcheck;//和校验
	BUFF[_cnt++] = addcheck;//附加校验
	// HAL_UART_Transmit(&huart3,BUFF,_cnt,0xffff);//串口发送
	CDC_Transmit_FS(BUFF, _cnt);
}
