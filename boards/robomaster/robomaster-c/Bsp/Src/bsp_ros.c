/**			                                                    
  ******************************************************************************
  * @作  者  两点一线
  * @版  本  V1.0
  * @日  期  2023-5-17
  * @内  容  ROS 通信
  *
  ******************************************************************************
  * @说  明
  *
  * 1.上位机通信串口
  * 2.可以使用具有TP-Protocol协议进行数据发送
  * 3.开启UART的串口数据接收功能，使用中断dma方式
  *
  * TP-Protocol协议介绍
  * 帧定义：DD | 01 | UL DL UR DR（U整数部分，D小数部分 U+D*0.01)
  *        帧头 符号位 数据             
  * 帧示例：( DD 01 01 32 01 3C ) 内容：1.5，-1.6
  *
  ******************************************************************************
  */                                                                                                              
#include "bsp_ros.h"


uint8_t ros_buf[ROS_MAX_LEN];	//接收数据缓存数组，为25个字节，给了50个字节长度，防止DMA传输越界

Vector_Struct Vector_S;
uint8_t ros_tate;				//上下位机连接状态 0=未连接，1=正常连接

/**
  * @brief      使能IDLE串口空闲中断和DMA接收  
  */
void ROS_Config(void)
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);

	HAL_UART_Receive_DMA(&huart1, ros_buf, ROS_MAX_LEN);
}


/**
  * @brief      将sbus信号转化为通道值，300-1700
  * @param   
  * @retval  
  */
uint8_t ROS_Process(uint8_t *buf)
{
	for(int8_t i=0; i<6; i++)
		Vector_S.data_s[i] = buf[i];
	
	if(Vector_S.data_s[1]==0x01)
		Vector_S.data_s[4] = -Vector_S.data_s[4];
	else if(Vector_S.data_s[1]==0x10)
		Vector_S.data_s[2] = -Vector_S.data_s[2];
	else if(Vector_S.data_s[1]==0x11)
		{
			Vector_S.data_s[2] = -Vector_S.data_s[2];
			Vector_S.data_s[4] = -Vector_S.data_s[4];
		}
	
	if(Vector_S.data_s[0] == ROS_FLAG)
	{
		
		Vector_S.Move_X = Vector_S.data_s[2] + Vector_S.data_s[3]*0.01f;
		Vector_S.Move_Y = 0;
		Vector_S.Move_W = Vector_S.data_s[4] + Vector_S.data_s[5]*0.01f;

		return 1;
	}
	else 
		return 0;
}


//自定义的串口中断空闲回调函数（HAL库并没有实现）
//void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart)
//{  
//	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE))!= RESET)//idle标志被置位
//	{ 
//		__HAL_UART_CLEAR_IDLEFLAG(&huart1);//清除标志位
//        HAL_UART_DMAStop(&huart1);//关闭DMA防止在处理数据时候接收数据，产生干扰
//		
//		//实际接收的字节= 预先定义的接收总字节 - __HAL_DMA_GET_COUNTER()
//		if((ROS_MAX_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx)) == ROS_BUF_LEN)
//		{
//			ros_tate = ROS_Process(ros_buf);	
//		}
//		//重新设置预先定义的接收总字节
//		__HAL_DMA_SET_COUNTER(&hdma_usart1_rx, ROS_MAX_LEN);
//		
//		//打开DMA接收
//		HAL_UART_Receive_DMA(&huart1, ros_buf, ROS_MAX_LEN);
//	}
//}

