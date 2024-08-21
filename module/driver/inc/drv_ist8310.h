#ifndef DRV_IST8310_H
#define DRV_IST8310_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint8_t status;
	float mag[3];
} ist8310_t;

extern ist8310_t ist8310_data;	//x,y,z轴磁场数组

/* Exported functions prototypes ---------------------------------------------*/
uint8_t IST8310_Init(void);
void IST8310_Read(float * mag);

uint8_t IST8310_ReadReg(uint8_t reg);
void IST8310_WriteReg(uint8_t reg, uint8_t data);
void IST8310_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len);
void IST8310_WriteRegs(uint8_t reg, uint8_t *data, uint8_t len);

#endif
