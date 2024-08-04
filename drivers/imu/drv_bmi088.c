/**
  ******************************************************************************
  * @作  者  两点一线
  * @版  本  V1.0
  * @日  期  2023-4-28
  * @内  容  BMI088是一款六轴惯性测量单元 (IMU)，三轴陀螺仪和三轴加速度计
             用于配置BMI088陀螺仪 加速度计的各项参数并读取数据
  ******************************************************************************
  */

#include "drv_bmi088.h"
#include "drv_bmi088_reg.h"

float BMI088_ACCEL_SEN = BMI088_ACCEL_3G_SEN;
float BMI088_GYRO_SEN = BMI088_GYRO_2000_SEN;

/**
 * @brief	通过SPI向BMI088的寄存器写入一个字节,同时接收BMI088发送的数据（可以不用）
 * @param  t_data      写入值
 * @retval res     	返回值
 */
uint8_t SPI_WR_Byte(uint8_t t_data)
{
    uint8_t res;
    HAL_SPI_TransmitReceive(&hspi1, &t_data, &res, 1, 1000);
    // HAL_Delay_us(5);//数据手册中两次写之间间隔最短5us
    return res;
}

/**
  * @brief	向BMI088的加速度计寄存器写入一个字节
  * @param  reg      要写入的寄存器地址（SPI设置的高位先发，而加速度计的所有寄存器地址最高位都是0）
                     所以写操作不用对寄存器处理
  * @param  t_data   要写入的数据
  */
// void BMI088_Accel_WriteReg(uint8_t reg, uint8_t t_data)
//{
//	BMI088_ACCEL_NS_L();
//	SPI_WR_Byte(reg);
//	SPI_WR_Byte(t_data);
//	BMI088_ACCEL_NS_H();
// }
#define BMI088_Accel_WriteReg(reg, t_data) \
    {                                      \
        BMI088_ACCEL_NS_L();               \
        SPI_WR_Byte(reg);                  \
        SPI_WR_Byte(t_data);               \
        BMI088_ACCEL_NS_H();               \
    }

/**
 * @brief	从BMI088的加速度计寄存器读取一个字节
 * @param  reg      写入值（根据数据手册，读操作需要将最高位置1）
 * @retval res      返回值
 */
// void BMI088_Accel_ReadReg(uint8_t reg, uint8_t r_data)
//{
//	BMI088_ACCEL_NS_L();
//	SPI_WR_Byte((reg) | 0x80);//发送第一个字节，为向寄存器读命令
//	SPI_WR_Byte(0xff);//随便发送一个数据，同时接收一个无意义的数据
//	r_data = SPI_WR_Byte(0xff);//随便发送一个数据，接收寄存器中的真正数据
//	BMI088_ACCEL_NS_H();
// }
#define BMI088_Accel_ReadReg(reg, r_data) \
    {                                     \
        BMI088_ACCEL_NS_L();              \
        SPI_WR_Byte((reg) | 0x80);        \
        SPI_WR_Byte(0xff);                \
        r_data = SPI_WR_Byte(0xff);       \
        BMI088_ACCEL_NS_H();              \
    }

/**
 * @brief	从BMI088的加速度计寄存器读取多个字节
 * @param  reg      写入值（根据数据手册，读操作需要将最高位置1）
 * @param  buf      接收数据指针
 * @param  len      接收数据长度
 */
void BMI088_Accel_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len)
{
    BMI088_ACCEL_NS_L();
    SPI_WR_Byte((reg) | 0x80);
    SPI_WR_Byte(0xff); // 随便发送一个数据，同时接收一个无意义的数据
    while (len != 0)
    {
        *buf = SPI_WR_Byte(0xff);
        buf++;
        len--;
    }
    BMI088_ACCEL_NS_H();
}

/**
  * @brief	向BMI088的陀螺仪寄存器写入一个字节
  * @param  reg      要写入的寄存器地址（SPI设置的高位先发，而加速度计的所有寄存器地址最高位都是0）
                     所以写操作不用对寄存器处理
  * @param  t_data   要写入的数据
  */
// void BMI088_Gyro_WriteReg(uint8_t reg, uint8_t t_data)
//{
//	BMI088_GYRO_NS_L();
//	SPI_WR_Byte(reg);
//	SPI_WR_Byte(t_data);
//	BMI088_GYRO_NS_H();
// }
#define BMI088_Gyro_WriteReg(reg, t_data) \
    {                                     \
        BMI088_GYRO_NS_L();               \
        SPI_WR_Byte(reg);                 \
        SPI_WR_Byte(t_data);              \
        BMI088_GYRO_NS_H();               \
    }

/**
 * @brief	从BMI088的陀螺仪寄存器读取一个字节
 * @param  reg      写入值（根据数据手册，读操作需要将最高位置1）
 * @retval res      返回值
 */
// uint8_t BMI088_Gyro_ReadReg(uint8_t reg, uint8_t r_data)
//{
//	BMI088_GYRO_NS_L();
//	SPI_WR_Byte((reg) | 0x80);//发送第一个字节，为向寄存器读命令
//	r_data = SPI_WR_Byte(0xff);//随便发送一个数据，接收寄存器中的真正数据
//	BMI088_GYRO_NS_H();
//	return	r_data;
// }
#define BMI088_Gyro_ReadReg(reg, r_data) \
    {                                    \
        BMI088_GYRO_NS_L();              \
        SPI_WR_Byte((reg) | 0x80);       \
        r_data = SPI_WR_Byte(0xff);      \
        BMI088_GYRO_NS_H();              \
    }

/**
 * @brief	从BMI088的陀螺仪寄存器读取多个字节
 * @param  reg      写入值（根据数据手册，读操作需要将最高位置1）
 * @param  buf      接收数据指针
 * @param	len      接收数据长度
 */
void BMI088_Gyro_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len)
{
    BMI088_GYRO_NS_L();
    SPI_WR_Byte(reg | 0x80);
    while (len != 0)
    {
        *buf = SPI_WR_Byte(0xff);
        buf++;
        len--;
    }
    BMI088_GYRO_NS_H();
}

/**
 * @brief	BMI088初始化
 */
void BMI088_Init(void)
{
    BMI088_Accel_Init();
    BMI088_Gyro_Init();
}

/**
 * @brief	BMI088加速度计初始化
 */
uint8_t BMI088_Accel_Init(void)
{
    uint8_t res = 0;

    // 执行一个假的SPI读取操作，在初始化阶段将加速度计改为SPI模式
    BMI088_Accel_ReadReg(BMI088_ACC_CHIP_ID, res);
    HAL_Delay(1);
    // 检查设备ID是否正确
    BMI088_Accel_ReadReg(BMI088_ACC_CHIP_ID, res);
    HAL_Delay(1);
    // 加速度计软件复位
    BMI088_Accel_WriteReg(BMI088_ACC_SOFTRESET, BMI088_ACC_SOFTRESET_VALUE);
    HAL_Delay(80);

    // 执行一个假的SPI读取操作，在初始化阶段将加速度计改为SPI模式
    BMI088_Accel_ReadReg(BMI088_ACC_CHIP_ID, res);
    HAL_Delay(1);
    // 检查设备ID是否正确
    BMI088_Accel_ReadReg(BMI088_ACC_CHIP_ID, res);
    if (res != BMI088_ACC_CHIP_ID_VALUE)
    {
        printf("BMI088_ACC_CHIP_ID_VALUE:%d \n", res);
        return 1;
    }

    // 配置加速度计寄存器
    BMI088_Accel_WriteReg(BMI088_ACC_PWR_CTRL, BMI088_ACC_ENABLE_ACC_ON); // 开启加速度计加速度计进入正常模式
    HAL_Delay_us(450);
    BMI088_Accel_WriteReg(BMI088_ACC_PWR_CONF, BMI088_ACC_PWR_ACTIVE_MODE);                                                     // 主动模式
    BMI088_Accel_WriteReg(BMI088_ACC_CONF, BMI088_ACC_800_HZ | BMI088_ACC_NORMAL | BMI088_ACC_CONF_MUST_Set);                   // 过滤器正常，输出频率800Hz
    BMI088_Accel_WriteReg(BMI088_ACC_RANGE, BMI088_ACC_RANGE_3G);                                                               // 加速度计量程3g
    BMI088_Accel_WriteReg(BMI088_INT1_IO_CONF, BMI088_ACC_INT1_IO_ENABLE | BMI088_ACC_INT1_GPIO_PP | BMI088_ACC_INT1_GPIO_LOW); // 使能1号作为中断并配置，输入引脚,将数据就绪中断映射到输出引脚INT1
    BMI088_Accel_WriteReg(BMI088_INT1_INT2_MAP_DATA, BMI088_ACC_INT1_DRDY_INTERRUPT);

    return 0;
}

/**
 * @brief	BMI088陀螺仪初始化
 */
uint8_t BMI088_Gyro_Init(void)
{
    uint8_t res = 0;

    // 上电后延时30ms
    HAL_Delay(30);

    // 检查设备ID是否正确
    BMI088_Gyro_ReadReg(BMI088_GYRO_CHIP_ID, res);
    if (res != BMI088_GYRO_CHIP_ID_VALUE)
    {
        printf("BMI088_GYRO_CHIP_ID_VALUE:%d \n", res);
        return 1;
    }

    // 配置陀螺仪寄存器
    BMI088_Gyro_WriteReg(BMI088_GYRO_RANGE, BMI088_GYRO_2000);                                             // 陀螺仪量程2000。/s
    BMI088_Gyro_WriteReg(BMI088_GYRO_BANDWIDTH, BMI088_GYRO_1000_116_HZ | BMI088_GYRO_BANDWIDTH_MUST_Set); // 输出频率1000
    BMI088_Gyro_WriteReg(BMI088_GYRO_INT_CTRL, BMI088_DRDY_ON);
    BMI088_Gyro_WriteReg(BMI088_GYRO_INT3_INT4_IO_CONF, BMI088_GYRO_INT3_GPIO_PP | BMI088_GYRO_INT3_GPIO_LOW);
    BMI088_Gyro_WriteReg(BMI088_GYRO_INT3_INT4_IO_MAP, BMI088_GYRO_DRDY_IO_INT3);

    return 0;
}

/**
 * @brief	BMI088读取数据
 */
void BMI088_Read(float gyro[3], float accel[3], float *temperate)
{
    uint8_t buf[6] = {0, 0, 0, 0, 0, 0};
    int16_t bmi088_raw_temp; // 无符号整型，自带正负

    BMI088_Accel_ReadRegs(BMI088_ACCEL_XOUT_L, buf, 6);

    bmi088_raw_temp = (int16_t)((buf[1]) << 8) | buf[0];
    accel[0] = bmi088_raw_temp * BMI088_ACCEL_SEN; // 单位：0.1g
    bmi088_raw_temp = (int16_t)((buf[3]) << 8) | buf[2];
    accel[1] = bmi088_raw_temp * BMI088_ACCEL_SEN;
    bmi088_raw_temp = (int16_t)((buf[5]) << 8) | buf[4];
    accel[2] = bmi088_raw_temp * BMI088_ACCEL_SEN;

    BMI088_Accel_ReadRegs(BMI088_TEMP_M, buf, 2);
    bmi088_raw_temp = (int16_t)((buf[0] << 3) | (buf[1] >> 5));
    if (bmi088_raw_temp > 1023)
    {
        bmi088_raw_temp -= 2048;
    }
    *temperate = bmi088_raw_temp * BMI088_TEMP_FACTOR + BMI088_TEMP_OFFSET;

    BMI088_Gyro_ReadRegs(BMI088_GYRO_X_L, buf, 6);

    bmi088_raw_temp = (int16_t)((buf[1]) << 8) | buf[0];
    gyro[0] = bmi088_raw_temp * BMI088_GYRO_SEN; // 单位：度/s
    bmi088_raw_temp = (int16_t)((buf[3]) << 8) | buf[2];
    gyro[1] = bmi088_raw_temp * BMI088_GYRO_SEN;
    bmi088_raw_temp = (int16_t)((buf[5]) << 8) | buf[4];
    gyro[2] = bmi088_raw_temp * BMI088_GYRO_SEN;
}
