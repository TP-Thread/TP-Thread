/**			                                                    
  ******************************************************************************
  * @作  者  两点一线
  * @版  本  V1.0
  * @日  期  2023-1-18
  * @内  容  128*64点阵的OLED显示屏驱动文件，仅适用于SD1306驱动IIC通信方式显示屏
  ******************************************************************************
	* Function List:
	* 1. void I2C_Configuration(void)-- 配置CPU的硬件I2C
	* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- 向寄存器地址写一个byte的数据
	* 3. void WriteCmd(unsigned char I2C_Command) -- 写命令
	* 4. void WriteDat(unsigned char I2C_Data) -- 写数据
	* 5. void OLED_Init(void) -- OLED屏初始化
	* 6. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
	* 7. void OLED_Fill(unsigned char fill_Data) -- 全屏填充
	* 8. void OLED_CLS(void) -- 清屏
	* 9. void OLED_ON(void) -- 唤醒
	* 10. void OLED_OFF(void) -- 睡眠
	* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- 显示字符串(字体大小有6*8和8*16两种)
	* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- 显示中文(中文需要先取模，然后放到codetab.h中)
	* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMP图片
	*
  ******************************************************************************
  */ 
#include "bsp_oled.h"
#include "bsp_codetab.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t cmd_data[2];


 /**
  * @brief  WriteCmd，控制指令，向OLED写入命令
  * @param  cmd：命令代码
  * @retval 无
  */
void WriteCmd(uint8_t cmd)//写命令
{
    cmd_data[0] = 0x00;
    cmd_data[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDRESS, cmd_data, 2, 10);
}


 /**
  * @brief  WriteDat，数据指令，向OLED写入数据
  * @param  I2C_Data：数据
  * @retval 无
  */
void WriteData(uint8_t data)//写数据
{
    cmd_data[0] = 0x40;
    cmd_data[1] = data;
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDRESS, cmd_data, 2, 10);
}


 /**
  * @brief  OLED_Init，初始化OLED
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	WriteCmd(0xAE); //关闭显示
	
	WriteCmd(0xA6); //设置颜色显示方式正常	

	WriteCmd(0x81); //设置屏幕对比度
	WriteCmd(0xff); //亮度调节 0x00~0xff
	
	WriteCmd(0x20);	//设置内存地址模式为页地址模式	
	WriteCmd(0x10);	//00,水平地址模式; 01,垂直地址模式; 10,页地址模式(RESET); 11,无效
	
	WriteCmd(0xB0);	//设置起点页地址为第一页,0-7
	
	WriteCmd(0x00); //页地址模式下设置起始列地址低位，00H~0FH
	WriteCmd(0x10); //页地址模式下设置起始列地址高位，10H~1FH
	
	WriteCmd(0x40); //设置GDDRAM起始行地址，40H~7FH 分别设置显示起始行为 0~63
	
	WriteCmd(0xC8);	//设置 SSD1306 的行扫描方式为顺序扫描	
	WriteCmd(0xA1); //设置输出列扫描顺序正常

	WriteCmd(0xA8); //设置复用率
	WriteCmd(0x3F); // 0FH~3FH 设置复用率为 1~64
	
	WriteCmd(0xA4); //A4H 设置显示模式为正常模式，此时屏幕输出GDDRAM中的显示数据
	
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	
	WriteCmd(0xD5); //设置分频因子与震荡频率
	WriteCmd(0xf0); //
	
	WriteCmd(0xD9); //设置预充电周期
	WriteCmd(0x22); //
	
	WriteCmd(0xDA); //设置COM引脚硬件配置
	WriteCmd(0x12);
	
	WriteCmd(0xDB); //设置Vcomh电压
	WriteCmd(0x20); //0x20,0.77xVcc
	
	WriteCmd(0x8D); //设置电荷泵
	WriteCmd(0x14); //使能
	
	WriteCmd(0xAf); //开启显示
}


 /**
  * @brief  OLED_On，将OLED从休眠中唤醒
  * @param  无
  * @retval 无
  */
void OLED_On(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}


 /**
  * @brief  OLED_OFF，让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
  * @param  无
  * @retval 无
  */
void OLED_Off(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}


/**
  * @brief          设置光标起点(x,y)
  * @param[in]      x:x轴, 从 0 到 127
  * @param[in]      y:y轴, 从 0 到 7
  * @retval         none
  */
void OLED_SetPos(uint8_t x, uint8_t y) 
{ 
	WriteCmd(0xb0+y);				//设置起始页地址 y
	WriteCmd(x&0x0f);				//设置列起始地址的低4位
	WriteCmd(((x&0xf0)>>4)|0x10);	//设置列起始地址的高4位
}


/**
  * @brief          操作GRAM内存(128*8char数组),操作完成后再通过 OLED_refresh_gram 函数整体刷新 OLED 内部的 GRAM
  * @param[in]      pen: 操作类型.
                    PEN_CLEAR: 		将所有像素熄灭
                    PEN_WRITE: 		将所有像素点亮
                    PEN_INVERSION: 	将所有像素状态反转
  * @retval         none
  */
void OLED_operate_gram(pen_typedef pen)
{
    uint8_t i, n;

    for(i = 0; i < 8; i++)
    {
        for(n = 0; n < 128; n++)
        {
            if(pen == PEN_WRITE)
            {
                OLED_GRAM[n][i] = 0xff;
            }
            else if(pen == PEN_CLEAR)
            {
                OLED_GRAM[n][i] = 0x00;
            }
            else
            {
                OLED_GRAM[n][i] = 0xff - OLED_GRAM[n][i];
            }
        }
    }
}


/**
  * @brief          发送数据到OLED的GRAM
  * @param[in]      none
  * @retval         none
  */
void OLED_refresh_gram(void)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        OLED_SetPos(0, i);
        for (n = 0; n < 128; n++)
        {
            WriteData(OLED_GRAM[n][i]);
        }
    }
}

 
/**
  * @brief          操作GRAM中的一个位，相当于操作屏幕的一个点
  * @param[in]      x:x轴,  [0,X_WIDTH-1]  0-127
  * @param[in]      y:y轴,  [0,Y_WIDTH-1]  0-63
  * @param[in]      pen: 操作类型,
                        PEN_CLEAR: 设置 (x,y) 点为 0
                        PEN_WRITE: 设置 (x,y) 点为 1
                        PEN_INVERSION: (x,y) 值反转
  * @retval         none
  */
void OLED_draw_point(int8_t x, int8_t y, pen_typedef pen)
{
    uint8_t page = 0, row = 0;

	/* check the corrdinate */
    if ((x < 0) || (x > (X_WIDTH - 1)) || (y < 0) || (y > (Y_WIDTH - 1)))
    {
        return;
    }
	
    page = y / 8;
    row = y % 8;

    if(pen == PEN_WRITE)
    {
        OLED_GRAM[x][page] |= 1 << row;
    }
    else if(pen == PEN_INVERSION)
    {
        OLED_GRAM[x][page] ^= 1 << row;
    }
    else
    {
        OLED_GRAM[x][page] &= ~(1 << row);
    }
}


/**
  * @brief          显示codetab.h中的汉字,16*16点阵
  * @param[in]      x,y: 起始点坐标(x:0~127, y:0~7)
  * @param[in]      n:汉字在codetab.h中的索引 0-3
  * @retval         none
  */
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t n)
{
	uint32_t  adder = 32*n;
	uint8_t i;
	
	OLED_SetPos(x, y);
	
	for(i = 0; i < 16; i++)
	{
		WriteData(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(i = 0; i < 16; i++)
	{
		WriteData(F16x16[adder]);
		adder += 1;
	}
}


/**
  * @brief          显示codetab.h中的ASCII字符,有6*8和8*16（宽*高）可选择 |——>x
  * @param[in]      x:x轴, 从 0 到 127                                  y v
  * @param[in]      y:y轴, 从 0 到 7
  * @param[in]      chr: 要显示的字符
  * @param[in]      TextSize:    字符大小 1：6*8    2：8*16
  * @retval         none
  */
void OLED_ShowChr(uint8_t x, uint8_t y, uint8_t chr)
{
    uint8_t c = 0,i = 0;
    c = chr - ' ';

	OLED_SetPos(x, y);

	for(i=0;i<6;i++)
		WriteData(F6x8[c][i]);
}


/**
  * @brief          显示字符串,有6*8和8*16（宽*高）可选择 |——>x
  * @param[in]      x:x轴, 从 0 到 127                                  y v
  * @param[in]      y:y轴, 从 0 到 7
  * @param[in]      chr: 字符串起始地址
  * @retval         none
  */
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t *chr)
{
    uint8_t n =0;

    while(chr[n] != '\0')
    {
        OLED_ShowChr(x, y, chr[n]);
		
		x += 6;
        n++;
    }
}


/**
  * @brief          显示RM的LOGO
  * @param[in]      none
  * @retval         none
  */
void OLED_LOGO(void)
{
    uint8_t temp_char = 0;
    uint8_t x = 0, y = 0;
    uint8_t i = 0;
    OLED_operate_gram(PEN_CLEAR);

    for(; y < 64; y += 8)
    {
        for(x = 0; x < 128; x++)
        {
            temp_char = LOGO_BMP[x][y/8];
            for(i = 0; i < 8; i++)
            {
                if(temp_char & 0x80)
                {
                    OLED_draw_point(x, y + i,PEN_WRITE);
                }
                else
                {
                    OLED_draw_point(x,y + i,PEN_CLEAR);
                }
                temp_char <<= 1;
            }
        }
    }
    OLED_refresh_gram();
}

