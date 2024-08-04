/**			                                                    
  ******************************************************************************
  * @��  ��  ����һ��
  * @��  ��  V1.0
  * @��  ��  2023-05-15
  * @��  ��  IMU��Ư��������
  ******************************************************************************
  */
  
#include "imu_temp_control_task.h"


#define TEMP_PID_KP 1600.0f //kp of temperature control PID 
#define TEMP_PID_KI 0.2f    //ki of temperature control PID 
#define TEMP_PID_KD 0.0f    //kd of temperature control PID 

#define TEMP_PID_MAX_OUT 4500.0f  //max out of temperature control PID 
#define TEMP_PID_MAX_IOUT 4400.0f //max iout of temperature control PID 


//������
TaskHandle_t INS_task_local_handler;


volatile uint8_t imu_start_flag = 0;

float gyro[3], accel[3], temp;

//kp, ki,kd three params
const float imu_temp_PID[3] = {TEMP_PID_KP, TEMP_PID_KI, TEMP_PID_KD};
//pid struct 
pid_type_def imu_temp_pid;


/**
  * @brief          bmi088�¶ȿ���
  * @param[in]      argument: NULL
  * @retval         none
  */
void imu_temp_control_task(void const * argument)
{
    //PID��ʼ��
    IMU_TEMP_PID_Init(&imu_temp_pid, imu_temp_PID, TEMP_PID_MAX_OUT, TEMP_PID_MAX_IOUT);
    //bmi088��ʼ��
    BMI088_Init();
    //�����¿�PWMͨ����ʹ��ʱ����Ӧͨ����ʼ PWM ���
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    //��ȡ��������������cubeMXʹ��'xTaskGetHandle'
    INS_task_local_handler = xTaskGetHandle(pcTaskGetName(NULL));
    imu_start_flag = 1;   
    while(1)
    {
        //��ȡ����
        BMI088_Read(gyro, accel, &temp);
        
        //�ȴ����񱻻���
        while(ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != pdPASS)
        {
        }

        uint16_t tempPWM;
        //PID����
        tempPWM = PID_calc(&imu_temp_pid, temp, 40.0f);
        imu_pwm_set(tempPWM);
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == INT1_ACCEL_Pin)
    {
        if(imu_start_flag)
        {
            //��������
            if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
            {
                static BaseType_t xHigherPriorityTaskWoken;
                vTaskNotifyGiveFromISR(INS_task_local_handler, &xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    }
}

