#ifndef __OLED_H
#define __OLED_H

#include "main.h"

#define Hardware_IIC_No hi2c1 /*选择自己使用的IIC号码*/

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);//显示字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);//字符串
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//数字
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);//负数
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//16进制数
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//二进制数
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t CHN);
void OLED_ShowPicture(uint8_t Pic);//满屏幕显示照片
uint32_t OLED_Pow(uint32_t X, uint32_t Y);

#endif
