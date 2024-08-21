/**
  ******************************************************************************
  * @file    drv_ist8310.c
  * @author  TP-Thread
  * @brief   IST8310三轴数字磁力计初始化和读取磁场数据.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_ist8310.h"

/* Private macro -------------------------------------------------------------*/
#define IST8310_IIC_ADDRESS		0x0E  	//the I2C address of IST8310

#define IST8310_WHO_AM_I 		0x00    //ist8310 "who am I " 
#define IST8310_WHO_AM_I_VALUE 	0x10 	//device ID

/* Private variables ---------------------------------------------------------*/
ist8310_t ist8310_data;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief	初始化IST8310磁力计
  * @retval error value
  */
uint8_t IST8310_Init(void)
{
	uint8_t res = 0;

	//重启IST8310
	HAL_GPIO_WritePin(RSTN_MAG_GPIO_Port, RSTN_MAG_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(RSTN_MAG_GPIO_Port, RSTN_MAG_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	res = IST8310_ReadReg(IST8310_WHO_AM_I);
	
	if(res != IST8310_WHO_AM_I_VALUE)
	{
		return 1;//错误
	}

	//配置 IST8310 四个寄存器
	IST8310_WriteReg(0x0A, 0x0B);//配置成连续测量模式，200Hz 输出频率
	IST8310_WriteReg(0x0B, 0x08);//中断寄存器，配置成开启中断，中断时为低电平
	IST8310_WriteReg(0x41, 0x09);//采样次数寄存器，配置成 x,y,z 均是 2 次采样
	
	return 0;
}

/**
  * @brief	通过读取磁场数据
  * @param  磁场数组
  */
void IST8310_Read(float * mag)
{
	uint8_t buf[6];
	int16_t temp_ist8310_data = 0;
	//读取三轴磁场数据，单位为 uT
	IST8310_ReadRegs(0x03, buf, 6);

	//将两个八位数据合并成一个 16位整型数据，再乘以 0.3 灵敏度变成单位是 ut 的磁场强度数据
	temp_ist8310_data = (int16_t)((buf[1] << 8) | buf[0]);
	mag[0] = 0.3f * temp_ist8310_data;
	temp_ist8310_data = (int16_t)((buf[3] << 8) | buf[2]);
	mag[1] = 0.3f * temp_ist8310_data;
	temp_ist8310_data = (int16_t)((buf[5] << 8) | buf[4]);
	mag[2] = 0.3f * temp_ist8310_data;
}

/**
  * @brief	读取IST8310的一个字节
  * @param	寄存器地址
  * @retval 寄存器值
  */
uint8_t IST8310_ReadReg(uint8_t reg)
{
    uint8_t res = 0;
    HAL_I2C_Mem_Read(&hi2c3, IST8310_IIC_ADDRESS <<1, reg, I2C_MEMADD_SIZE_8BIT, &res, 1, 10);
    return res;
}

/**
  * @brief	写入一个字节到IST8310的寄存器中
  * @param	寄存器地址
  * @param	写入值
  */
void IST8310_WriteReg(uint8_t reg, uint8_t data)
{
    HAL_I2C_Mem_Write(&hi2c3, IST8310_IIC_ADDRESS <<1, reg,I2C_MEMADD_SIZE_8BIT,&data,1,10);
}

/**
  * @brief	读取IST8310的多个字节
  * @param	寄存器开始地址
  * @param	存取缓冲区
  * @param	读取字节总数
  */
void IST8310_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len)
{
    HAL_I2C_Mem_Read(&hi2c3, IST8310_IIC_ADDRESS <<1, reg,I2C_MEMADD_SIZE_8BIT,buf,len,10);
}

/**
  * @brief	写入多个字节到IST8310的寄存器
  * @param	寄存器开始地址
  * @param	存取缓冲区
  * @param	读取字节总数
  */
void IST8310_WriteRegs(uint8_t reg, uint8_t *data, uint8_t len)
{
    HAL_I2C_Mem_Write(&hi2c3, IST8310_IIC_ADDRESS <<1, reg,I2C_MEMADD_SIZE_8BIT,data,len,10);
}
