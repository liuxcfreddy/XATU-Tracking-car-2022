#include "stm32f10x.h"
#include "motor.h"
#include "delay.h"

 



 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {	

 motor_gpio();
 xunji_gpio();
 pwm();             
	 delay_init();
	 {
  while(1)
	{

//检测到黑线为0    检测不到黑线为1
      if(LEFT_ONE==0&&LEFT_TWO==0&&RIGHT_ONE==0&&RIGHT_TWO==0&&GO==0)
			{
					 run();
			}
			    else if(LEFT_ONE==1&&LEFT_TWO==1&&RIGHT_ONE==1&&RIGHT_TWO==1&&GO==0)
			{
					 run();
			}
					else if(LEFT_ONE==1&&LEFT_TWO==0&&RIGHT_ONE==1&&RIGHT_TWO==1&&GO==1)
			{
			
			  left();
			}
						else if(LEFT_ONE==1&&LEFT_TWO==1&&RIGHT_ONE==1&&RIGHT_TWO==0&&GO==1)
			{
			
			  right();
			}					

			      else if(LEFT_ONE==0&&LEFT_TWO==1&&RIGHT_ONE==1&&RIGHT_TWO==1&&GO==1)
			{
			
			  left();
			}
						else if(LEFT_ONE==1&&LEFT_TWO==1&&RIGHT_ONE==0&&RIGHT_TWO==1&&GO==1)
			{
			
			  right();
			}			      
			      				

			else if(LEFT_ONE==1&&LEFT_TWO==1&&RIGHT_ONE==1&&RIGHT_TWO==1&&GO==1)
			{
			  run();
        delay_ms(20);
        turn();
        delay_ms(5);				
			}

				
				
				
			
			
	}
}
 }
