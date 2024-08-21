/**
 ******************************************************************************
 * @file    task_imu.c
 * @author  TP-Thread
 * @brief   Function implementing the Imu thread.
 *		    利用陀螺仪加速度计bmi088，磁力计ist8310，完成姿态解算，得出欧拉角，
 *          提供通过bmi088的data ready 中断完成外部触发，减少数据等待延迟
 *          通过DMA的SPI传输节约CPU时间.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tp_thread.h"

/* Private includes ----------------------------------------------------------*/
#include "algo_mahony_ahrs.h"
#include "math.h"

/* Private macro -------------------------------------------------------------*/
#define INT_EVENT (0x01 << 0) // 设置事件掩码的位 0
#define FIN_EVENT (0x01 << 1) // 设置事件掩码的位 1

#define TEMP_KP 1600.0f // 温度控制PID的kp
#define TEMP_KI 0.2f    // 温度控制PID的ki
#define TEMP_KD 0.0f    // 温度控制PID的kd

#define TEMP_MAX_OUT 4500.0f  // 温度控制PID的max_out
#define TEMP_MAX_IOUT 4400.0f // 温度控制PID的max_iout

/* Private variables ---------------------------------------------------------*/
extern osEventFlagsId_t Imu_EventHandle;

float angle_c[3] = {0.0f, 0.0f, 0.0f}; // 当前欧拉角姿态rpy °

pid_t temp_pid;
float temp_pid_param[3] = {TEMP_KP, TEMP_KI, TEMP_KD};

/* Private function prototypes -----------------------------------------------*/
void Imu_Temp_Control(float temp);
void AHRS_Update(float gyro[3], float accel[3], float mag[3]);
void Imu_Angle(float *angle);

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	imu任务, 初始化 bmi088, ist8310, 计算欧拉角
 * @param	argument: NULL
 */
void Imu_Entry(void *argument)
{
	BMI088_Init();  // 初始化BMI088
    IST8310_Init(); // 初始化IST8310

    // IMU温控PID初始化
    PID_Init(&temp_pid, temp_pid_param, TEMP_MAX_OUT, TEMP_MAX_IOUT);
    // 开启温控PWM通道，使定时器对应通道开始 PWM 输出
    HAL_TIM_PWM_Start(&ttim, TTIM_CHANNEL);

    osEventFlagsSet(Imu_EventHandle, FIN_EVENT);

    while (1)
    {
        osEventFlagsWait(Imu_EventHandle, INT_EVENT | FIN_EVENT, osFlagsWaitAll, portMAX_DELAY);
		
        // 读取数据
        BMI088_Read(bmi088_data.gyro, bmi088_data.accel, &bmi088_data.temp);
        IST8310_Read(ist8310_data.mag);

        AHRS_Update(bmi088_data.gyro, bmi088_data.accel, ist8310_data.mag);
        Imu_Angle(angle_c);
        // printf("the Yaw value is :%f \n", Yaw);

        Imu_Temp_Control(bmi088_data.temp);
        //printf("the temp value is: %.2f \n", bmi088_data.temp);

        osEventFlagsSet(Imu_EventHandle, FIN_EVENT);
    }
}

void AHRS_Update(float gyro[3], float accel[3], float mag[3])
{
    MahonyAHRSupdate(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], mag[0], mag[1], mag[2]);
    // MahonyAHRSupdateIMU(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2]);
}

void Imu_Angle(float *angle)
{
    angle[0] = atan2f(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2)) * 57.3f;
    angle[1] = asinf(2.0f * (q0 * q2 - q1 * q3)) * 57.3f;
    angle[2] = atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3)) * 57.3f;
}

/**
 * @brief   控制bmi088的温度
 * @param	temp	bmi088的温度
 */
void Imu_Temp_Control(float temp)
{
    uint16_t tempPWM;

    PID_Calculate(&temp_pid, temp, 40.0f);

    if (temp_pid.out < 0.0f)
    {
        temp_pid.out = 0.0f;
    }

    tempPWM = (uint16_t)temp_pid.out;
    __HAL_TIM_SetCompare(&ttim, TTIM_CHANNEL, tempPWM);
}

/**
 * @brief	IMU数据更新中断回调函数
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == INT1_GYRO_Pin) // 加速度计数据更新中断
    {
        osEventFlagsSet(Imu_EventHandle, INT_EVENT);
    }
}
