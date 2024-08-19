/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  TP-Thread
  * @brief   串口通信.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_uart.h"

/* Private functions ---------------------------------------------------------*/
/**
 * @简  述  重定义putc函数
 * 重定向 c 库函数 printf 到串口，重定向后可使用 printf 函数
 */
size_t __write(int handle, const unsigned char *buffer, size_t size)
{
    /* Sending in normal mode */
    HAL_UART_Transmit(&duart, (uint8_t *)buffer, size, 100000);

    return size;
}

int fputc(int ch, FILE *f)
{
    // 发送一个字节数据到串口
    HAL_UART_Transmit(&duart, (uint8_t *)&ch, 1, 10);

    return (ch);
}

/**
 * @简  述  重定义getc函数
 * 重定向 c 库函数 scanf 到串口，重写向后可使用 scanf、getchar 等函数
 */
int fgetc(FILE *f)
{
    int ch;
    /* 等待串口输入数据 */
    while (__HAL_UART_GET_FLAG(&duart, UART_FLAG_RXNE) == RESET)
        ;

    HAL_UART_Receive(&duart, (uint8_t *)&ch, 1, 10);

    return (ch);
}
