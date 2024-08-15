/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.1
 * @日  期  2023-04-25
 * @内  容  CAN电机驱动
 *
 ******************************************************************************
 */

#include "drv_can_cmd.h"

// 通信发送指令
uint8_t a_Motor_torque[8] = {0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 转矩闭环控制
uint8_t a_Motor_speed[8] = {0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // 电机转速,对应实际转速为 0.01dps/LSB。
uint8_t a_Motor_state2[8] = {0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 读取电机转速
uint8_t a_Motor_stop[8] = {0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 电机停止,并使电机保持不动
uint8_t a_Motor_reset[8] = {0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // 系统复位指令

uint8_t a_Motor_CANID[8] = {0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};    // CANID读写指令
uint8_t a_Motor_read_pid[8] = {0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 读取PID参数
uint8_t a_Write_pid_RAM[8] = {0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t a_Write_pid_ROM[8] = {0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t a_Read_Accel[8] = {0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};             // 读取加速度
uint8_t a_Write_Accel[8] = {0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};            // 写入加速度
uint8_t a_Motor_now_place_data[8] = {0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 当前编码器多圈位置数据
uint8_t a_Motor_code_place_data[8] = {0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // 编码器多圈位置数据
uint8_t a_Read_code_zero_place[8] = {0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 编码器多圈零偏
uint8_t a_Write_code_zero_ROM[8] = {0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};    // 写入编码器电机零点多圈到ROM
uint8_t a_Write_NOWcode_zero_ROM[8] = {0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 写入编码器当前多圈位置到ROM作为电机零点命令
uint8_t a_Motor_motorAngle_many[8] = {0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // 读取绝对位置多圈角度
uint8_t a_Motor_state1[8] = {0x9a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};           // 读取电机状态1
uint8_t a_Motor_state3[8] = {0x9d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};           // 读取电机状态3
uint8_t a_Motor_close[8] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};            // 电机关闭,同时清除电机运行状态，不在任何闭环模式下
uint8_t a_Motor_torque_control[8] = {0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 位置跟踪控制命令
uint8_t a_Motor_torque_place[8] = {0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};     // 绝对位置闭环控制命令
uint8_t a_speed_control_place[8] = {0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};    // 带速度限制的位置跟踪控制命令
uint8_t a_Motor_add[8] = {0xa8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};              // 增量位置闭环控制命令
uint8_t a_Motor_mode[8] = {0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};             // 系统模式
uint8_t a_Motor_power[8] = {0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};            // 读取运行功率
uint8_t a_OPEN_RlyCtrlRslt[8] = {0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};       // 开抱闸
uint8_t a_CLOSE_RlyCtrlRslt[8] = {0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};      // 关抱闸
uint8_t a_Motor_time[8] = {0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};             // 系统运行时间ms
uint8_t a_Motor_edition[8] = {0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};          // 读取程序版本
uint8_t a_Motor_comm_time[8] = {0xb3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};        // 通讯中断保护时间
uint8_t a_Motor_baudrate[8] = {0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};         // 波特率通讯设置
uint8_t a_Motor_model[8] = {0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};            // 电机型号读取指令
uint8_t a_Motor_function[8] = {0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};         // 功能控制指令

/**
 * @brief  CAN发送函数
 * @param  T_ID	数据帧ID
 * @param  pData   数组指针
 */
void CAN_SendData(uint16_t T_Id, uint8_t *T_Data)
{
    CAN_SendStdData(&hcan1, T_Id, T_Data);
}

/**
 * @brief  接收标准数据帧的数据
 * @param  R_Data	接收到的消息指针
 */
void CAN_ReadData(uint8_t *R_Data)
{
    CAN_ReadStdData(&hcan1, R_Data);
}

/*************************** 电机控制命令 ******************************/
/**
 * @brief  电机转矩闭环控制 最大5N.M对应5.8A
 * @param  iqControl最大值580，单位为0.01A/LSB。
 */
void Motor_torque(uint16_t F_ID, int16_t iqControl)
{
    a_Motor_torque[4] = iqControl;
    a_Motor_torque[5] = iqControl >> 8;

    CAN_SendData(F_ID, a_Motor_torque);
}

/**
 * @brief  电机转速闭环控制
 * @param  speedSet最大值200000，对应电机输出轴实际转速时需要*0.01dps/LSB
 */
void Motor_speed(uint16_t F_ID, int32_t speedSet)
{
    a_Motor_speed[4] = speedSet;
    a_Motor_speed[5] = speedSet >> 8;
    a_Motor_speed[6] = speedSet >> 16;
    a_Motor_speed[7] = speedSet >> 24;

    CAN_SendData(F_ID, a_Motor_speed);
}

/**
 * @brief  读取当前电机的温度、转速、编码器位置
 * 1.电机温度temperature（int8_t类型，1℃/LSB）
 * 2.电机的转矩电流值iq（int16_t类型，0.01A/LSB）
 * 3.电机输出轴转速speed（int16_t类型，1dps/LSB）
 * 4.电机输出轴角度（int16_t类型，1degree/LSB,最大范围±32767degree）
 */
void Motor_state2(uint16_t F_ID, uint8_t *R_Data)
{
    CAN_SendData(F_ID, a_Motor_state2);
    CAN_Process(R_Data);
}

/**
 * @brief  停止电机，并使电机保持不动
 */
void Motor_stop(uint16_t F_ID)
{
    CAN_SendData(F_ID, a_Motor_stop);
}

/**
 * @brief	电机复位，当电机堵转时电流过大就会进入保护状态，复位重新运行
 */
void Motor_reset(uint16_t F_ID)
{
    CAN_SendData(F_ID, a_Motor_reset);
}

/**
 * @brief  设置和读取CANID,修改时需要注意是否连接了多个设备，那样可能会同时将多个设备的 ID 修改为相同的
 * @param  wReadWriteFlag	读写标志位 0或1
 * @param	CANID			大小范围：1-32，单电机控制指令发送ID：0x140 + ID(1~32)，电机反馈指令ID：0x240 + ID(1~32)
 */
void Motor_CANID(uint8_t wReadWriteFlag, uint8_t CANID)
{
    a_Motor_CANID[2] = wReadWriteFlag;
    a_Motor_CANID[7] = CANID;

    CAN_SendData(0x300, a_Motor_CANID);
}

// 读出电流、速度、位置环KP和KI的参数 uint8_t最大范围256个单位进行等分
void Motor_read_pid(uint16_t F_ID)
{
    CAN_SendData(F_ID, a_Motor_read_pid);
}

// 关闭电机输出，同时清除电机运行状态，不在任何闭环模式下。
void Motor_close(uint16_t F_ID)
{
    CAN_SendData(F_ID, a_Motor_close);
}

void Motor_state1(uint16_t F_ID)
{
    CAN_SendData(F_ID, a_Motor_state1);
}

void Motor_state3(unsigned short F_ID)
{
    CAN_SendData(F_ID, a_Motor_state3);
}

void Motor_torque_control(unsigned short F_ID, unsigned int angleControl)
{
    a_Motor_torque_control[4] = angleControl;
    a_Motor_torque_control[5] = angleControl >> 8;
    a_Motor_torque_control[6] = angleControl >> 16;
    a_Motor_torque_control[7] = angleControl >> 24;

    CAN_SendData(F_ID, a_Motor_torque_control);
}

void Motor_torque_place(unsigned short F_ID, unsigned short maxSpeed, unsigned int angleControl)
{
    a_Motor_torque_place[2] = maxSpeed;
    a_Motor_torque_place[3] = maxSpeed >> 8;

    a_Motor_torque_place[4] = angleControl;
    a_Motor_torque_place[5] = angleControl >> 8;
    a_Motor_torque_place[6] = angleControl >> 16;
    a_Motor_torque_place[7] = angleControl >> 24;

    CAN_SendData(F_ID, a_Motor_torque_place);
}

void speed_control_place(unsigned short F_ID, unsigned short maxSpeed, unsigned int angleControl)
{
    a_speed_control_place[2] = maxSpeed;
    a_speed_control_place[3] = maxSpeed >> 8;

    a_speed_control_place[4] = angleControl;
    a_speed_control_place[5] = angleControl >> 8;
    a_speed_control_place[6] = angleControl >> 16;
    a_speed_control_place[7] = angleControl >> 24;

    CAN_SendData(F_ID, a_speed_control_place);
}

void Motor_add(unsigned short F_ID, unsigned short maxSpeed, unsigned int angleControl)
{
    a_Motor_add[2] = maxSpeed;
    a_Motor_add[3] = maxSpeed >> 8;

    a_Motor_add[4] = angleControl;
    a_Motor_add[5] = angleControl >> 8;
    a_Motor_add[6] = angleControl >> 16;
    a_Motor_add[7] = angleControl >> 24;

    CAN_SendData(F_ID, a_Motor_add);
}

void Motor_mode(unsigned short F_ID)
{
    CAN_SendData(F_ID, a_Motor_mode);
}

void Motor_power(unsigned short F_ID)
{
    CAN_SendData(F_ID, a_Motor_power);
}

void OPEN_RlyCtrlRslt(unsigned short F_ID)
{
    CAN_SendData(F_ID, a_OPEN_RlyCtrlRslt);
}

void CLOSE_RlyCtrlRslt(unsigned short F_ID)
{
    CAN_SendData(F_ID, a_CLOSE_RlyCtrlRslt);
}

void Motor_baudrate(unsigned short F_ID, uint8_t baudrate)
{
    a_Motor_baudrate[7] = baudrate;

    CAN_SendData(F_ID, a_Motor_baudrate);
}

void Motor_function(unsigned short F_ID, uint8_t index, unsigned int Value)
{
    a_Motor_function[1] = index;

    a_Motor_function[4] = Value;
    a_Motor_function[5] = Value >> 8;
    a_Motor_function[6] = Value >> 16;
    a_Motor_function[7] = Value >> 24;

    CAN_SendData(F_ID, a_Motor_function);
}
