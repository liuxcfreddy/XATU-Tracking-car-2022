#ifndef _scan_red_h_
#define _scan_red_h_


#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"




typedef struct{
uint16_t ADC_R;
uint16_t ADC_M;
uint16_t ADC_L;
} TypeADC_temp;


float Coordinate_Conversion(int16_t input);
float Cross_negative_feedback(float wheelbase,float Dist_sensor2axis, float Difference,int mode);

#endif
