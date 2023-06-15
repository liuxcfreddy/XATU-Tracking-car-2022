/*
 * Moto.c
 *
 *  Created on: Apr 24, 2023
 *      Author: liuxc
 */
#include "main.h"
#include "tim.h"
#include "Moto.h"



//开启PWM输出
void PWM_OUT_Init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}
//修改PWM占空比
void PWM_SETDUTY(PWM_DutyData *Duty)
{
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Duty->MotoA1);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Duty->MotoA2);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, Duty->MotoB1);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, Duty->MotoB2);
}


/// @brief 前进动力分配
/// @param MR 范围0~100
/// @param ML 范围0~100
void GO_Power_Set(float MR,float ML)
{
	PWM_DutyData Duty;
	if((MR<=100&&MR>=0)&&(ML<=100&&ML>=0))
	{
		Duty.MotoA1=0;
		Duty.MotoA2=(MR*2);

		Duty.MotoB1=0;
		Duty.MotoB2=(ML*2);
		PWM_SETDUTY(&Duty);
	}
}
//后退动力分配
void BACK_Power_Set(float MR,float ML)
{
	PWM_DutyData Duty;
	if((MR<=100&&MR>=0)&&(ML<=100&&ML>=0))
	{
		Duty.MotoA1=(MR*2);
		Duty.MotoA2=0;

		Duty.MotoB1=(ML*2);
		Duty.MotoB2=0;
		PWM_SETDUTY(&Duty);
	}
}

