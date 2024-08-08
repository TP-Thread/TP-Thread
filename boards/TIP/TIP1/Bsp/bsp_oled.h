#ifndef BSP_OLED_H
#define	BSP_OLED_H

#include "main.h"

#define OLED_I2C_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78 

//the resolution of oled   128*64
#define MAX_COLUMN      128
#define MAX_ROW         64

#define X_WIDTH         MAX_COLUMN
#define Y_WIDTH         MAX_ROW

static uint8_t OLED_GRAM[128][8];

typedef enum
{
    PEN_CLEAR = 0x00,
    PEN_WRITE = 0x01,
    PEN_INVERSION= 0x02,
}pen_typedef;






void WriteCmd(uint8_t I2C_Command);
void WriteData(uint8_t I2C_Data);

void OLED_Init(void);
void OLED_operate_gram(pen_typedef pen);
void OLED_SetPos(uint8_t x, uint8_t y);
void OLED_refresh_gram(void);
void OLED_draw_point(int8_t x, int8_t y, pen_typedef pen);
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t n);
void OLED_ShowChr(uint8_t row, uint8_t col, uint8_t chr);
void OLED_ShowStr(uint8_t row, uint8_t col, uint8_t *chr);
void OLED_LOGO(void);

#endif
