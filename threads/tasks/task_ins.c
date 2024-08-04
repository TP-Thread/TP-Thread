/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.2
 * @日  期  2024-04-08
 * @内  容  利用陀螺仪加速度计bmi088，磁力计ist8310，完成姿态解算，得出欧拉角，
 *          提供通过bmi088的data ready 中断完成外部触发，减少数据等待延迟
 *          通过DMA的SPI传输节约CPU时间.
 ******************************************************************************
 */

#include "task_ins.h"
#include "math.h"

extern osEventFlagsId_t ins_eventHandle;
#define INT_EVENT (0x01 << 0) // 设置事件掩码的位 0
#define FIN_EVENT (0x01 << 1) // 设置事件掩码的位 1

TaskHandle_t imu_task_Handle; // 任务句柄

volatile uint8_t imu_task_start_flag = 0;

bmi088_real_data_t BMI088_Data;
ist8310_real_data_t IST8310_Data;

float Temp_PID[3] = {TEMP_KP, TEMP_KI, TEMP_KD};
static PID imu_temp_pid;

float INS_angle[3] = {0.0f, 0.0f, 0.0f}; // 欧拉角 单位 rad
float Roll, Pitch, Yaw;                  // 欧拉角 单位 rad

/**
 * @brief	imu任务, 初始化 bmi088, ist8310, 计算欧拉角
 * @param	argument: NULL
 */
void ins_task(void *argument)
{
    IST8310_Init(); // 初始化IST8310
    BMI088_Init();  // 初始化BMI088

    // IMU温控PID初始化
    PID_Init(&imu_temp_pid, Temp_PID, TEMP_MAX_OUT, TEMP_MAX_IOUT);
    // 开启温控PWM通道，使定时器对应通道开始 PWM 输出
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);

    // 获取当前任务的任务句柄，
    //    imu_task_Handle = xTaskGetHandle(pcTaskGetName(NULL));
    //    imu_task_start_flag = 1;	// 配合数据更新中断使用

    osEventFlagsSet(ins_eventHandle, FIN_EVENT);

    while (1)
    {
        // 等待通知
        //        while (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != pdPASS)
        //        {
        //        }
        osEventFlagsWait(ins_eventHandle, INT_EVENT | FIN_EVENT, osFlagsWaitAll, portMAX_DELAY);

        // 读取数据
        BMI088_Read(BMI088_Data.gyro, BMI088_Data.accel, &BMI088_Data.temp);
        IST8310_Read(IST8310_Data.mag);

        AHRS_Update(BMI088_Data.gyro, BMI088_Data.accel, IST8310_Data.mag);
        INS_Angle(&Roll, &Pitch, &Yaw);
        // printf("the Yaw value is :%f \n", Yaw);

        IMU_Temp_Control(BMI088_Data.temp);
        // printf("the temp value is :%.2f \n", BMI088_Data.temp);

        osEventFlagsSet(ins_eventHandle, FIN_EVENT);
    }
}

void AHRS_Update(float gyro[3], float accel[3], float mag[3])
{
    MahonyAHRSupdate(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], mag[0], mag[1], mag[2]);
    // MahonyAHRSupdateIMU(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2]);
}

void INS_Angle(float *roll, float *pitch, float *yaw)
{
    *roll = atan2f(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2)) * 57.3f;
    *pitch = asinf(2.0f * (q0 * q2 - q1 * q3)) * 57.3f;
    *yaw = atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3)) * 57.3f;
}

/**
 * @brief   控制bmi088的温度
 * @param	temp	bmi088的温度
 */
void IMU_Temp_Control(float temp)
{
    uint16_t tempPWM;

    PID_Calculate(&imu_temp_pid, temp, 40.0f);

    if (imu_temp_pid.out < 0.0f)
    {
        imu_temp_pid.out = 0.0f;
    }

    tempPWM = (uint16_t)imu_temp_pid.out;
    __HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, tempPWM);
}

/**
 * @brief	IMU数据更新引脚中断
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == INT1_GYRO_Pin) // 加速度计数据更新中断
    {
        osEventFlagsSet(ins_eventHandle, INT_EVENT);
        //        if(imu_task_start_flag)
        //        {
        //            // 唤醒任务
        //            if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        //            {
        //                static BaseType_t xHigherPriorityTaskWoken;
        //                vTaskNotifyGiveFromISR(imu_task_Handle, &xHigherPriorityTaskWoken);	// 发送通知
        //                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        //            }
        //        }
    }
}
