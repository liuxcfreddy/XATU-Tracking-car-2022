#ifndef __motor_H
#define __motor_H 			   
#include "sys.h"  

#define      IN1         PAout(6)
#define      IN2         PAout(5)
#define      IN3         PAout(4)
#define      IN4         PAout(3)


#define      LEFT_ONE      PBin(4)  
#define      LEFT_TWO      PBin(6) 
#define      RIGHT_ONE      PBin(7) 
#define      RIGHT_TWO      PBin(8) 
#define      GO      PBin(5)  
 
void run(void);
void left(void);
void right(void);
void back(void);
void qleft(void);
void qight(void);
void stop(void);
void turn(void);
void motor_gpio(void);
void xunji_gpio(void);
void pwm(void);
#endif


