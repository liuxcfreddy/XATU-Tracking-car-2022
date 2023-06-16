#include "motor.h"  
#include "stm32f10x.h"

void motor_gpio()
{

  GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_3;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     

}

void xunji_gpio()
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_5;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);		

}
void pwm()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	

	
	TIM_TimeBaseStructure.TIM_Period = 899; 
	TIM_TimeBaseStructure.TIM_Prescaler =0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 

	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  
	

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); 

	
	TIM_Cmd(TIM2, ENABLE);
}
void run()
{

		TIM_SetCompare2(TIM2,80);
   	TIM_SetCompare3(TIM2,80);
   IN1 = 1;
	 IN2 = 0;
	
	 IN3 = 1;
	 IN4 = 0;
}
void back()
{
	TIM_SetCompare2(TIM2,20);
	TIM_SetCompare3(TIM2,20);
	
   IN1 = 0;
	 IN2 = 1;
	
	 IN3 = 0;
	 IN4 = 1;
}
void right()
{
	TIM_SetCompare2(TIM2,120);
	TIM_SetCompare3(TIM2,120);
	
   IN1 = 1;
	 IN2 = 0;
	
	 IN3 = 0;
	 IN4 = 0;
}

void left()
{
	TIM_SetCompare2(TIM2,120);
	TIM_SetCompare3(TIM2,120);
	
   IN1 = 0;
	 IN2 = 0;
	
	 IN3 = 1;
	 IN4 = 0;
}

void turn()
{
	TIM_SetCompare2(TIM2,20);
	TIM_SetCompare3(TIM2,20);
	
   IN1 = 0;
	 IN2 = 1;
	
	 IN3 = 1;
	 IN4 = 0;
}
void stop()
{

   IN1 = 0;
	 IN2 = 0;
	
	 IN3 = 0;
	 IN4 = 0;
}



