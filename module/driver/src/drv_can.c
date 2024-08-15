/**
 ******************************************************************************
 * @file    drv_can.c
 * @author  TP-Thread
 * @brief   CAN驱动（正常工作模式）
 * @version 0.1
 * @date    2024-04-10
 *
 * Copyright (c) 2022 TP-Thread
 ******************************************************************************
 */

#include "drv_can.h"

static CAN_TxHeaderTypeDef Tx_Header;
static CAN_RxHeaderTypeDef Rx_Header;
static uint32_t CAN_TX_MAILBOX;
static uint8_t Rx_Data[8];

static int16_t speed_L, speed_R;

/**
 * @brief	CAN滤波器配置
 * @param	argument: 空
 * @retval	None
 */
void CAN_Filter_Init(void)
{
    CAN_FilterTypeDef sFilterConfig;

    sFilterConfig.FilterIdHigh = 0x0000;                  // CAN_FxR1 寄存器的高 16 位
    sFilterConfig.FilterIdLow = 0x0000;                   // CAN_FxR1 寄存器的低 16 位
    sFilterConfig.FilterMaskIdHigh = 0x0000;              // CAN_FxR2 寄存器的高 16 位
    sFilterConfig.FilterMaskIdLow = 0x0000;               // CAN_FxR2 寄存器的低 16 位
    sFilterConfig.FilterFIFOAssignment = CAN_FilterFIFO0; // 设置经过筛选后数据存储到哪个接收 FIFO
    sFilterConfig.FilterBank = 0;                         // 筛选器编号，范围 0-（SlaveStartFilterBank-1）
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;     // 筛选器模式
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;    // 设置筛选器的尺度
    sFilterConfig.FilterActivation = ENABLE;              // 是否使能本筛选器

#ifdef DRV_CAN1
    HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
    // __HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);    // 使能FIFO0数据中断接收
    HAL_CAN_Start(&hcan1);
#endif

#ifdef DRV_CAN2
    sFilterConfig.FilterBank = 14;							//筛选器编号，范围 SlaveStartFilterBank-27
    sFilterConfig.SlaveStartFilterBank = 14;				//选择从设备的扇区滤波器开始的编号，can1(0-13)和can2(14-27)分别得到一半的filter
    HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig);
    //	__HAL_CAN_ENABLE_IT(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);   // 使能FIFO0数据中断接收
    HAL_CAN_Start(&hcan2);
#endif
}

/**
 * @brief  发送标准ID的数据帧
 * @param  hcan     CAN的句柄
 * @param  T_Id     标准帧ID
 * @param  T_Data   发送数据指针
 */
void CAN_SendStdData(CAN_HandleTypeDef *hcan, uint16_t T_Id, uint8_t *T_Data)
{
    Tx_Header.StdId = T_Id;
    Tx_Header.IDE = CAN_ID_STD;
    Tx_Header.RTR = CAN_RTR_DATA;
    Tx_Header.DLC = 8;
    Tx_Header.TransmitGlobalTime = DISABLE;

    /* Wait transmission complete */
    while (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0)
    {
    }

    /* Request transmission */
    if (HAL_CAN_AddTxMessage(hcan, &Tx_Header, T_Data, &CAN_TX_MAILBOX) != HAL_OK)
    {
        /* Transmission request Error */
        Error_Handler();
    }
}

/**
 * @brief  接收标准数据帧的数据
 * @param  hcan     CAN的句柄
 * @param  R_Data	接收到的消息指针
 */
uint16_t CAN_ReadStdData(CAN_HandleTypeDef *hcan, uint8_t *R_Data)
{
    // 检测接收邮箱已经接收到数据
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &Rx_Header, Rx_Data) == HAL_OK)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            R_Data[i] = Rx_Data[i];
        }
        return Rx_Header.StdId;
    }
    return 0;
}

/**
 * @brief  CAN接收反馈信息并处理
 * @param
 */
void CAN_Process(uint8_t *R_Data)
{
    // 判断ID是哪组的电机
    switch (CAN_ReadStdData(&hcan1, R_Data))
    {
    case (0x241): // 1号电机
    {
        speed_L = (int16_t)((R_Data[5]) << 8) | R_Data[4];
        printf("speed_L:%d\n", speed_L);
    }
    break;

    case (0x242): // 2号电机
    {
        speed_R = (int16_t)((R_Data[5]) << 8) | R_Data[4];
        printf("speed_R:%d\n", speed_R);
    }
    break;
    }
}

/**
 * @brief  接收数据处理
 * @param  hcan: CAN句柄指针
 * @retval 无
 */
void can_msg_info(CAN_RxHeaderTypeDef *rx_header, uint8_t *pData)
{
    printf("IDE     : %s\r\n",
           rx_header->IDE == CAN_ID_STD ? "CAN_ID_STD" : "CAN_ID_EXT");
    printf("RTR     : %s\r\n",
           rx_header->RTR == CAN_RTR_DATA ? "CAN_RTR_DATA" : "CAN_RTR_REMOTE");
    printf("DLC     : %d\r\n", rx_header->DLC);
    printf("StdId   : 0x%X\r\n", rx_header->StdId);

    for (uint8_t i = 0; i < 8; i++)
    {
        printf("Data    : %d\r\n", pData[i]);
    }
}

/**
 * @brief  CAN FIFO0的中断回调函数，在里面完成数据的接收
 * @param  hcan: CAN句柄指针
 * @retval 无
 */
// void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
//{
//	CAN_RxHeaderTypeDef		RxHeader;  //接收句柄
//
//	if(hcan->Instance == hcan1.Instance)
//	{
//		if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, Rx_Data)== HAL_OK)	// 获得接收到的数据头和数据
//		{
//			can_msg_info(&RxHeader, Rx_Data);
//			__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);	// 再次使能FIFO0接收中断
//		}
//	}
//	else if(hcan->Instance == hcan2.Instance)
//	{
//		if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, Rx_Data)== HAL_OK)	// 获得接收到的数据头和数据
//		{
//			can_msg_info(&RxHeader, Rx_Data);
//			__HAL_CAN_ENABLE_IT(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);	// 再次使能FIFO0接收中断
//		}
//	}
// }
