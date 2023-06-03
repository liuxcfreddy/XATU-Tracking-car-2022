/*
 * pfunc.h
 *
 *  Created on: Feb 15, 2023
 *      Author: liuxc
 *      Doc:printf()函数重定向
 */

#ifndef INC_PFUNC_H_
#define INC_PFUNC_H_


#include "main.h"
#include "usart.h"
#include <stdio.h>

#ifdef __GNUC__									//串口重定向
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
#endif /* INC_PFUNC_H_ */
