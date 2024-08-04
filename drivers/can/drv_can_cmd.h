#ifndef BSP_CAN_CMD_H
#define BSP_CAN_CMD_H

#include "main.h"

// 通信发送指令
extern uint8_t a_Motor_read_pid[8]; // 读取PID参数
extern uint8_t a_Write_pid_RAM[8];
extern uint8_t a_Write_pid_ROM[8];
extern uint8_t a_Read_Accel[8];             // 读取加速度
extern uint8_t a_Write_Accel[8];            // 写入加速度
extern uint8_t a_Motor_now_place_data[8];   // 当前编码器多圈位置数据
extern uint8_t a_Motor_code_place_data[8];  // 编码器多圈位置数据
extern uint8_t a_Read_code_zero_place[8];   // 编码器多圈零偏
extern uint8_t a_Write_code_zero_ROM[8];    // 写入编码器电机零点多圈到ROM
extern uint8_t a_Write_NOWcode_zero_ROM[8]; // 写入编码器当前多圈位置到ROM作为电机零点命令
extern uint8_t a_Motor_motorAngle_many[8];  // 读取绝对位置多圈角度
extern uint8_t a_Motor_state1[8];           // 读取电机状态1
extern uint8_t a_Motor_state2[8];           // 读取电机状态2
extern uint8_t a_Motor_state3[8];           // 读取电机状态3
extern uint8_t a_Motor_clock[8];            // 电机关闭
extern uint8_t a_Motor_stop[8];             // 电机停止
extern uint8_t a_Motor_torque[8];           // 转矩闭环控制
extern uint8_t a_speed[8];                  // 电机转速100
extern uint8_t a_Motor_torque_control[8];   // 位置跟踪控制命令
extern uint8_t a_Motor_torque_place[8];     // 绝对位置闭环控制命令
extern uint8_t a_speed_control_place[8];    // 带速度限制的位置跟踪控制命令
extern uint8_t a_Motor_add[8];              // 增量位置闭环控制命令
extern uint8_t a_Motor_mode[8];             // 系统模式
extern uint8_t a_Motor_power[8];            // 读取运行功率
extern uint8_t a_Motor_reset[8];            // 系统复位指令
extern uint8_t a_OPEN_RlyCtrlRslt[8];       // 开抱闸
extern uint8_t a_CLOSE_RlyCtrlRslt[8];      // 关抱闸
extern uint8_t a_Motor_time[8];             // 系统运行时间ms
extern uint8_t a_Motor_edition[8];          // 读取程序版本
extern uint8_t a_Motor_comm_time[8];        // 通讯中断保护时间
extern uint8_t a_Motor_baudrate[8];         // 波特率通讯设置
extern uint8_t a_Motor_model[8];            // 电机型号读取指令
extern uint8_t a_Motor_function[8];         // 功能控制指令
extern uint8_t a_Motor_CANID[8];            // CANID设置指令、
extern uint8_t a_Motor_RS485ID[8];          // RS485ID设置指令

void CAN_SendData(uint16_t T_ID, uint8_t *T_data);
void CAN_ReadData(uint8_t *T_Data);

/*************************** 电机控制命令 ******************************/
void Motor_torque(uint16_t F_ID, int16_t iqControl);
void Motor_speed(uint16_t F_ID, int32_t speedSet);
void Motor_state2(uint16_t F_ID, uint8_t *R_Data);
void Motor_stop(uint16_t F_ID);
void Motor_reset(uint16_t F_ID);

void Motor_CANID(uint8_t wReadWriteFlag, uint8_t CANID);
void Motor_read_pid(uint16_t F_ID);
void Motor_close(uint16_t F_ID);

// 该命令读取当前电机的温度、电压和错误状态标志
// 1.电机温度temperature（int8_t类型，单位1℃/LSB）。
// 2,抱闸控制指令：表示抱闸控制指令状态，1代表抱闸释放指令，0代表抱闸锁死指令。
// 3,电压voltage（uint16_t类型，单位0.1V/LSB）。
// 4,错误标志errorState（为uint16_t类型，各个位代表不同的电机状态）
// 错误类型 1，电机堵转。2，系统低压。3，系统过压。4，相电流过流。5，功率超限。6，标定参数写入错误。7，超速。8，电机温度过温。编码器校准错误。
void Motor_state1(uint16_t F_ID);
// 该命令读取当前电机的温度和相电流数据
// 1.电机温度temperature（int8_t类型，1℃/LSB）
// 2.A相电流数据，数据类型为int16_t类型，对应实际相电流为0.01ALSB。
// 3.B相电流数据，数据类型为int16_t类型，对应实际相电流为0.01ALSB。
// 4.C相电流数据，数据类型为int16_t类型，对应实际相电流为0.01ALSB。
void Motor_state3(unsigned short F_ID);
// 控制值angleControl为int32_t类型，对应实际位置为0.01degree/LSB，即36000代表360°
void Motor_torque_control(unsigned short F_ID, unsigned int angleControl);
// 控制值maxSpeed限制了电机输出轴转动的最大速度，为uint16_t类型，对应实际转速1dps/LSB。
// 控制值angleControl为int32_t类型，对应实际位置为0.01degree/LSB。
void Motor_torque_place(unsigned short F_ID, unsigned short maxSpeed, unsigned int angleControl);
// 控制值maxSpeed限制了电机输出轴转动的最大速度，为uint16_t类型，对应实际转速1dps/LSB。
// 控制值angleControl为int32_t类型，对应实际位置为0.01degree/LSB，即36000代表360°
void speed_control_place(unsigned short F_ID, unsigned short maxSpeed, unsigned int angleControl);
// 主机发送该命令以控制电机的增量位置（多圈角度），以当前位置为起点运行输入的位置增量。 控制值angleControl为int32_t类型，对应实际位置为0.01degree/LSB，即36000代表360°
void Motor_add(unsigned short F_ID, unsigned short maxSpeed, unsigned int angleControl);
// 该命令读取当前电机运行模式。1,电流。2，速度。3，位置。
void Motor_mode(unsigned short F_ID);
// 该命令读取当前电机功率。运行功率参数motorpower,为uint16_t类型,单位为瓦，单位0.1w/LSB。
void Motor_power(unsigned short F_ID);
// 该命令用于开启系统抱闸。系统会松开抱闸，电机会处于可运动状态不受抱闸制动器限制。
void OPEN_RlyCtrlRslt(unsigned short F_ID);
// 该命令用于关闭系统抱闸。抱闸会锁住电机，此时电机无法再运行。系统断电后抱闸制动器也是处于这个状态。
void CLOSE_RlyCtrlRslt(unsigned short F_ID);
// 该指令可以设置CAN和RS485总线的通讯波特率。设置后参数会保存在ROM中.
void Motor_baudrate(unsigned short F_ID, uint8_t baudrate);
// 该指令用于读取电机型号，读取出的数据为ACSII码，可以通过查ACSII码表来转换成对应的实际符号。
void Motor_model(unsigned short F_ID);
// 该指令用于一些特定功能的使用，是一条复合功能指令，可以包含多条功能控制指令。
void Motor_function(unsigned short F_ID, uint8_t index, unsigned int Value);

#endif
