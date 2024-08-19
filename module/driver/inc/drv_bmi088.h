#ifndef BSP_BMI088_H
#define BSP_BMI088_H

#include "main.h"

extern SPI_HandleTypeDef hspi1;

#define BMI088_TEMP_FACTOR 0.125f
#define BMI088_TEMP_OFFSET 23.0f

#define BMI088_GYRO_DATA_READY_BIT 0
#define BMI088_ACCEL_DATA_READY_BIT 1
#define BMI088_ACCEL_TEMP_DATA_READY_BIT 2

#define BMI088_ACCEL_IIC_ADDRESSE (0x18 << 1)
#define BMI088_GYRO_IIC_ADDRESSE (0x68 << 1)

#define BMI088_ACCEL_RANGE_3G
//#define BMI088_ACCEL_RANGE_6G
//#define BMI088_ACCEL_RANGE_12G
//#define BMI088_ACCEL_RANGE_24G

#define BMI088_GYRO_RANGE_2000
//#define BMI088_GYRO_RANGE_1000
//#define BMI088_GYRO_RANGE_500
//#define BMI088_GYRO_RANGE_250
//#define BMI088_GYRO_RANGE_125

#define BMI088_ACCEL_3G_SEN 0.00091552734375f//3*10/32768 和g没关系，算法里面会归一化;如果想要得到实际的数据则3*9.8015/32768
#define BMI088_ACCEL_6G_SEN 0.0018310546875f
//#define BMI088_ACCEL_12G_SEN 0.0035894165039f 
//#define BMI088_ACCEL_24G_SEN 0.0071788330078f

#define BMI088_GYRO_2000_SEN 0.00106526443603169529841533860381f//(2000/32768)*(pi/180)
#define BMI088_GYRO_1000_SEN 0.00053263221801584764920766930190693f
#define BMI088_GYRO_500_SEN 0.00026631610900792382460383465095346f
#define BMI088_GYRO_250_SEN 0.00013315805450396191230191732547673f
#define BMI088_GYRO_125_SEN 0.000066579027251980956150958662738366f

typedef struct
{
    uint8_t status;
    int16_t accel[3];
    int16_t temp;
    int16_t gyro[3];
}bmi088_raw_data_t;

typedef struct
{
    uint8_t status;
    float accel[3];
    float temp;
    float gyro[3];
}bmi088_real_data_t;

//加速度计和陀螺仪片选信号线控制
#define BMI088_ACCEL_NS_L()		  	HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_RESET) 
#define BMI088_ACCEL_NS_H()		  	HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_SET) 
#define BMI088_GYRO_NS_L()		  	HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_RESET)
#define BMI088_GYRO_NS_H()		  	HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_SET) 


uint8_t SPI_WR_Byte(uint8_t t_data);
void BMI088_Init(void);
uint8_t BMI088_Accel_Init(void);
uint8_t BMI088_Gyro_Init(void);

void BMI088_Read(float gyro[3], float accel[3], float *temperate);
void BMI088_Accel_Read(uint8_t *rx_buf, float accel[3]);
void BMI088_Temperature_Read(uint8_t *rx_buf, float *temperate);
void BMI088_Gyro_Read(uint8_t *rx_buf, float gyro[3]);

#endif
