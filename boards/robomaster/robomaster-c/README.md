# STM32F407 Robomaster 开发板C型 BSP 说明

## 开发板介绍

Robomaster 开发板C型 是大疆创新科技有限公司推出的一款基于 ARM Cortex-M4 内核的开发板。开发板主控芯片为 STM32F407IGH6TR，最高主频为 168Mhz，拥有丰富的扩展接口和通信接口。板载IMU传感器，可配合RoboMaster出品的M3508、 M2006直流无刷减速电机、UWB模块以及妙算等产品使用，亦可配合DJI飞控SDK使用。

该开发板常用 **板载资源** 如下：

- MCU：STM32F407IGH6TR, 主频 168MHz, 1024KB FLASH, 192KB RAM(含64KB CCM RAM)
- 常用外设
  - 三色 LED：LED_R(PH12), LED_G(PH11), LED_B(PH11), 
  - 按键：KEY(PA0)
  - 电压检测：ADC_BAT(PF10)
- 常用接口：UART 接口、CAN 总线接口、PWM 接口
- 调试接口：SWD


开发板的用户手册：[RoboMaster 开发板 C 型用户手册.pdf](https://rm-static.djicdn.com/tem/35228/RoboMaster%20%20%E5%BC%80%E5%8F%91%E6%9D%BF%20C%20%E5%9E%8B%E7%94%A8%E6%88%B7%E6%89%8B%E5%86%8C.pdf)

开发板更多详细信息请参考 RoboMaster官网：[RoboMaster开发板 C 型](https://www.robomaster.com/zh-CN/products/components/general/development-board-type-c/info) 

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设** | **支持情况** | **备注**                             |
| :----------- | :----------: | :----------------------------------- |
| BMI088       |   暂不支持   | 六轴惯性测量单元（有软件包）            |
| IST8310      |   暂不支持   | 三轴磁力计                           |
| **片上外设** | **支持情况** | **备注**                             |
| GPIO         |     支持     | PA0, PA1... PH1 ---> PIN: 0, 1...144 |
| UART         |     支持     | UART1(FinSH),  UART3(DBUS),  UART6          |
| CAN          |     支持    | CAN1, CAN2                           |
| PWM          |   支持   | TIM1(CH1/2/3/4), TIM4(CH3), TIM8(CH1/2/3)  |
| SPI          |   支持   | SPI2 |
| IIC          |   支持   | 模拟IIC(SDA-->PF0, SCL-->PF1) |

## 使用说明

#### 硬件连接

将准备好的 ST-Link/JLink/DapLink 与开发板连接，开发板上的调试接口为 MX1.25 4Pin。C板上没有电源指示灯，供电可以选用：调试接口的 3.3V 输入，micro USB 接口供电，XT30 电源输入。 

#### 编译下载

工程默认配置使用 JLink 下载程序，点击下载按钮即可下载程序到开发板。

## 注意事项

- 部分外设需通过 XT30 或 USB 接口供电才能正常使用，包括 CAN、舵机5V供电、IMU恒温电路等
- 

## 联系人信息

维护人:

- [Vic](https://github.com/TP-Thread) ，邮箱：<TP-Thread@outlook.com>

