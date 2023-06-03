#include "follow.h"

/*全局变量声明*/
extern TypeADC_temp ADC;//传感器顺序为 R M L
extern TypeADC_temp ADCData;
extern TypeADC_temp ADCRelay;
extern Kalman KalRT,KalRR,KalMM,KalLL;//卡尔曼滤波结构体
extern POWER_PP_Typedef POWER_PP;

extern float L2R_Difference;//偏移距离
extern uint8_t Mode_mark;
extern float PID_POWER;
extern float Adjust;
/*Global variable declaration end*/

/**
 * @brief 主要巡线任务
 * @param none
*/
void main_follw_task(void)
{ 
    ADCData.ADC_R =UserKalFil(&KalRR,(float) ADC.ADC_R,Kal_Scale_factor)  -ADCRelay.ADC_R;//获取右ADC
    ADCData.ADC_L =UserKalFil(&KalLL,(float) ADC.ADC_L ,Kal_Scale_factor) -ADCRelay.ADC_L;//获取左ADC
    
    L2R_Difference=(ADCData.ADC_L-ADCData.ADC_R);//求差获得相对坐标
    L2R_Difference=Coordinate_Conversion(L2R_Difference);//坐标转换
    Adjust = Cross_negative_feedback(131.4,107,L2R_Difference,0);//偏移角度计算返回超调量
    
    PID_POWER = speed_pid(0,Adjust);

    POWER_PP.POWERA = 40+PID_POWER;
    POWER_PP.POWERB = 40-PID_POWER;
    GO_Power_Set(POWER_PP.POWERA, POWER_PP.POWERB);          
    
    /*
    OLED_ShowSignedNum( 2,1,L2R_Difference,4);  //显示偏移量
    OLED_ShowSignedNum( 2,6, POWER_PP.POWERA,3);//显示电机A速度值
    OLED_ShowSignedNum( 2,10, POWER_PP.POWERB,3);//显示电机B速度量
    */                 	 
}
