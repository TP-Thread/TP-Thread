#ifndef DRV_IST8310_H
#define DRV_IST8310_H

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Exported macro ------------------------------------------------------------*/
#define IST8310_IIC_ADDRESS		0x0E  	//the I2C address of IST8310

#define IST8310_WHO_AM_I 		0x00    //ist8310 "who am I " 
#define IST8310_WHO_AM_I_VALUE 	0x10 	//device ID

/* Exported types ------------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c3;
extern float mag[3];	//x,y,z轴磁场数组

typedef struct
{
  uint8_t status;
  float mag[3];
}ist8310_real_data_t;

/* Exported functions prototypes ---------------------------------------------*/
uint8_t IST8310_Init(void);
void IST8310_Read(float * mag);

uint8_t IST8310_ReadReg(uint8_t reg);
void IST8310_WriteReg(uint8_t reg, uint8_t data);
void IST8310_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len);
void IST8310_WriteRegs(uint8_t reg, uint8_t *data, uint8_t len);

#endif
