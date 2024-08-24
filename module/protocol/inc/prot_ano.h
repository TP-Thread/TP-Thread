#ifndef PROT_ANO_H
#define PROT_ANO_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
//typedef struct
//{
//    uint8_t head;			// 帧头	
//    uint8_t sdevid;			// 源地址
//    uint8_t ddevid;			// 目标地址
//    uint8_t frameid;		// 功能码
//    uint16_t datalen;		// 数据长度
//    uint8_t data[DATA_LEN];	// 数据内容
//    uint8_t sumcheck;		// 和校验
//    uint8_t addcheck;		// 附加校验
//} ano_frame_t;

/* Exported functions prototypes ---------------------------------------------*/
void Sent_ATTitude_Data(float *angle_data_m, float *angle_data_d, float *rate_data_m, float *rate_data_d);

#endif
