/*
 * Moto.h
 *
 *  Created on: Apr 24, 2023
 *      Author: liuxc
 */

#ifndef INC_MOTO_H_
#define INC_MOTO_H_

typedef struct
{
	float MotoA1;
	float MotoA2;
	float MotoB1;
	float MotoB2;

}PWM_DutyData;

typedef struct {
	float POWERA;
	float POWERB;
}POWER_PP_Typedef;

void PWM_OUT_Init(void);
void PWM_SETDUTY(PWM_DutyData *Duty);
void GO_Power_Set(float MR,float ML);
void BACK_Power_Set(float MR,float ML);

#endif /* INC_MOTO_H_ */
