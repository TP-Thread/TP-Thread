/**			                                                    
  ******************************************************************************
  * @��  ��  ����һ��
  * @��  ��  V1.0
  * @��  ��  2023-1-18
  * @��  ��  128*64�����OLED��ʾ�������ļ�����������SD1306����IICͨ�ŷ�ʽ��ʾ��
  ******************************************************************************
	* Function List:
	* 1. void I2C_Configuration(void)-- ����CPU��Ӳ��I2C
	* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- ��Ĵ�����ַдһ��byte������
	* 3. void WriteCmd(unsigned char I2C_Command) -- д����
	* 4. void WriteDat(unsigned char I2C_Data) -- д����
	* 5. void OLED_Init(void) -- OLED����ʼ��
	* 6. void OLED_SetPos(unsigned char x, unsigned char y) -- ������ʼ������
	* 7. void OLED_Fill(unsigned char fill_Data) -- ȫ�����
	* 8. void OLED_CLS(void) -- ����
	* 9. void OLED_ON(void) -- ����
	* 10. void OLED_OFF(void) -- ˯��
	* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- ��ʾ�ַ���(�����С��6*8��8*16����)
	* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- ��ʾ����(������Ҫ��ȡģ��Ȼ��ŵ�codetab.h��)
	* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMPͼƬ
	*
  ******************************************************************************
  */ 
#include "bsp_oled.h"
#include "bsp_codetab.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t cmd_data[2];


 /**
  * @brief  WriteCmd������ָ���OLEDд������
  * @param  cmd���������
  * @retval ��
  */
void WriteCmd(uint8_t cmd)//д����
{
    cmd_data[0] = 0x00;
    cmd_data[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDRESS, cmd_data, 2, 10);
}


 /**
  * @brief  WriteDat������ָ���OLEDд������
  * @param  I2C_Data������
  * @retval ��
  */
void WriteData(uint8_t data)//д����
{
    cmd_data[0] = 0x40;
    cmd_data[1] = data;
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDRESS, cmd_data, 2, 10);
}


 /**
  * @brief  OLED_Init����ʼ��OLED
  * @param  ��
  * @retval ��
  */
void OLED_Init(void)
{
	WriteCmd(0xAE); //�ر���ʾ
	
	WriteCmd(0xA6); //������ɫ��ʾ��ʽ����	

	WriteCmd(0x81); //������Ļ�Աȶ�
	WriteCmd(0xff); //���ȵ��� 0x00~0xff
	
	WriteCmd(0x20);	//�����ڴ��ַģʽΪҳ��ַģʽ	
	WriteCmd(0x10);	//00,ˮƽ��ַģʽ; 01,��ֱ��ַģʽ; 10,ҳ��ַģʽ(RESET); 11,��Ч
	
	WriteCmd(0xB0);	//�������ҳ��ַΪ��һҳ,0-7
	
	WriteCmd(0x00); //ҳ��ַģʽ��������ʼ�е�ַ��λ��00H~0FH
	WriteCmd(0x10); //ҳ��ַģʽ��������ʼ�е�ַ��λ��10H~1FH
	
	WriteCmd(0x40); //����GDDRAM��ʼ�е�ַ��40H~7FH �ֱ�������ʾ��ʼ��Ϊ 0~63
	
	WriteCmd(0xC8);	//���� SSD1306 ����ɨ�跽ʽΪ˳��ɨ��	
	WriteCmd(0xA1); //���������ɨ��˳������

	WriteCmd(0xA8); //���ø�����
	WriteCmd(0x3F); // 0FH~3FH ���ø�����Ϊ 1~64
	
	WriteCmd(0xA4); //A4H ������ʾģʽΪ����ģʽ����ʱ��Ļ���GDDRAM�е���ʾ����
	
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	
	WriteCmd(0xD5); //���÷�Ƶ��������Ƶ��
	WriteCmd(0xf0); //
	
	WriteCmd(0xD9); //����Ԥ�������
	WriteCmd(0x22); //
	
	WriteCmd(0xDA); //����COM����Ӳ������
	WriteCmd(0x12);
	
	WriteCmd(0xDB); //����Vcomh��ѹ
	WriteCmd(0x20); //0x20,0.77xVcc
	
	WriteCmd(0x8D); //���õ�ɱ�
	WriteCmd(0x14); //ʹ��
	
	WriteCmd(0xAf); //������ʾ
}


 /**
  * @brief  OLED_On����OLED�������л���
  * @param  ��
  * @retval ��
  */
void OLED_On(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X14);  //������ɱ�
	WriteCmd(0XAF);  //OLED����
}


 /**
  * @brief  OLED_OFF����OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
  * @param  ��
  * @retval ��
  */
void OLED_Off(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X10);  //�رյ�ɱ�
	WriteCmd(0XAE);  //OLED����
}


/**
  * @brief          ���ù�����(x,y)
  * @param[in]      x:x��, �� 0 �� 127
  * @param[in]      y:y��, �� 0 �� 7
  * @retval         none
  */
void OLED_SetPos(uint8_t x, uint8_t y) 
{ 
	WriteCmd(0xb0+y);				//������ʼҳ��ַ y
	WriteCmd(x&0x0f);				//��������ʼ��ַ�ĵ�4λ
	WriteCmd(((x&0xf0)>>4)|0x10);	//��������ʼ��ַ�ĸ�4λ
}


/**
  * @brief          ����GRAM�ڴ�(128*8char����),������ɺ���ͨ�� OLED_refresh_gram ��������ˢ�� OLED �ڲ��� GRAM
  * @param[in]      pen: ��������.
                    PEN_CLEAR: 		����������Ϩ��
                    PEN_WRITE: 		���������ص���
                    PEN_INVERSION: 	����������״̬��ת
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
  * @brief          �������ݵ�OLED��GRAM
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
  * @brief          ����GRAM�е�һ��λ���൱�ڲ�����Ļ��һ����
  * @param[in]      x:x��,  [0,X_WIDTH-1]  0-127
  * @param[in]      y:y��,  [0,Y_WIDTH-1]  0-63
  * @param[in]      pen: ��������,
                        PEN_CLEAR: ���� (x,y) ��Ϊ 0
                        PEN_WRITE: ���� (x,y) ��Ϊ 1
                        PEN_INVERSION: (x,y) ֵ��ת
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
  * @brief          ��ʾcodetab.h�еĺ���,16*16����
  * @param[in]      x,y: ��ʼ������(x:0~127, y:0~7)
  * @param[in]      n:������codetab.h�е����� 0-3
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
  * @brief          ��ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16����*�ߣ���ѡ�� |����>x
  * @param[in]      x:x��, �� 0 �� 127                                  y v
  * @param[in]      y:y��, �� 0 �� 7
  * @param[in]      chr: Ҫ��ʾ���ַ�
  * @param[in]      TextSize:    �ַ���С 1��6*8    2��8*16
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
  * @brief          ��ʾ�ַ���,��6*8��8*16����*�ߣ���ѡ�� |����>x
  * @param[in]      x:x��, �� 0 �� 127                                  y v
  * @param[in]      y:y��, �� 0 �� 7
  * @param[in]      chr: �ַ�����ʼ��ַ
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
  * @brief          ��ʾRM��LOGO
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

