
#include "reg52.h"
#include "intrins.h"
/********以下为参数与环境变量区********/
unsigned int path;					//红外对管反馈的环境变量
unsigned int pow;					//电机驱动力度的调节
unsigned int i=0;					//轨道丢失参数(当轨道丢失到一定的时间后启动倒车程序)
sbit  Car_Servo=P2^0;               // 舵机pwm控制

unsigned int Servo0PwmDuty=1500;	//PWM脉冲宽度   1.5ms脉冲宽度  为舵机正中位置

/***********************************************************
* 名    称：InitTimer0()
* 功    能：舵机时钟0初始化
* 入口参数：无
* 出口参数：无
* 说    明：12M晶振，12分频，所以计数器每递增一个数就是1微秒，完全满足舵机控制的精度要求
			因为定时器是TH0，TL0都要全部计数到0xFF后在计1个数就会产生中断，所以要想产生
			x毫秒的中断，那么TH0，TL0就应该赋值（0xFFFF-x）	从这个值开始计数产生定时中断
/**********************************************************/
void InitTimer0(void)		//20ms
{
    TMOD &= 0xF0;		//设置定时器模式
    TMOD |= 0x01;		//设置定时器模式
    TL0 = 0xE0;			//设置定时初值
    TH0 = 0xB1;			//设置定时初值
    TF0 = 0;			//清除TF0标志
    TR0 = 1;			//定时器0开始计时
    ET0 = 1;			//开定时器0中断
    EA = 1;             //开总中断
}
void Car_Servo_Init()	//舵机初始化
{
    InitTimer0();
}

/***********************************************************
* 名    称：Timer0Value(uint16 pwm)
* 功    能：给定时器0计数器赋值产生定时中断
* 入口参数：pwm		控制舵机的PWM脉冲宽度值（范围：500~2500）
* 出口参数：无
* 说    明：12M晶振，12分频，所以计数器每递增一个数就是1微秒，完全满足舵机控制的精度要求
			因为定时器是TH0，TL0都要全部计数到0xFF后在计1个数就会产生中断，所以要想产生
			pwm毫秒的中断，那么TH0，TL0就应该赋值（0xFFFF-pwm）	从这个值开始计数产生定时中断
/**********************************************************/
void Timer0Value(unsigned int pwm)
{
    unsigned int value;
    value=0xffff-pwm;
    TR0 = 0;
    TL0=value;			//16位数据给8位数据赋值默认将16位数据的低八位直接赋给八位数据
    TH0=value>>8;		//将16位数据右移8位，也就是将高8位移到低八位，再赋值给8位数据
    TR0 = 1;
}

/***********************************************************
* 名    称： Timer0_isr() interrupt 1 using 1
* 功    能： 时钟0中断处理
* 入口参数： 无
* 出口参数： 无
* 说    明：
/**********************************************************/
void Timer0_isr(void) interrupt 1 using 1
{
    static unsigned char i = 1;	//静态变量：每次调用函数时保持上一次所赋的值，
    //跟全局变量类似，不同是它只能用于此函数内部
    switch(i)
    {
    case 1:
        Car_Servo = 1;	//PWM控制脚高电平
        //给定时器0赋值，计数Pwm0Duty个脉冲后产生中断，下次中断会进入下一个case语句
        Timer0Value(Servo0PwmDuty);
        break;
    case 2:
        Car_Servo = 0;	//PWM控制脚低电平
        //高脉冲结束后剩下的时间(20000-Pwm0Duty)全是低电平了，Pwm0Duty + (20000-Pwm0Duty) = 20000个脉冲正好为一个周期20毫秒
        Timer0Value(20000-Servo0PwmDuty);
        i = 0;
        break;
    }
    i++;
}

sbit  Car_Motor_A1=P3^2; 	 // 电机PWM控制端
sbit  Car_Motor_EN1=P3^3;	 //电机使能控制端
sbit  Car_Motor_B1=P3^4;	 // 电机控制端

unsigned int Motor0PwmDuty=2750;		  //初始占空比为3000:7000
unsigned int Motor0PwmDuty_daoche=2750;
/***********************************************************
* 名    称：Timer1Value(unsigned int pwm)
* 功    能：给定时器1计数器赋值产生定时中断
* 入口参数：pwm		控制电机的PWM脉冲宽度值（范围：0~10000）
* 出口参数：无
* 说    明：12M晶振，12分频，所以计数器每递增一个数就是1微秒，完全满足舵机控制的精度要求
			因为定时器是TH0，TL0都要全部计数到0xFF后在计1个数就会产生中断，所以要想产生
			pwm毫秒的中断，那么TH0，TL0就应该赋值（0xFFFF-pwm）	从这个值开始计数产生定时中断
/**********************************************************/
void Timer1Value(unsigned int pwm)
{
    unsigned int value;
    value=0xffff-pwm;
    TR1 = 0;
    TL1=value;			//16位数据给8位数据赋值默认将16位数据的低八位直接赋给八位数据
    TH1=value>>8;		//将16位数据右移8位，也就是将高8位移到低八位，再赋值给8位数据
    TR1 = 1;
}

/***********************************************************
* 名    称：Timer1Init
* 功    能：电机时钟1初始化
* 入口参数：无
* 出口参数：无
* 说    明：10ms一周期
/**********************************************************/
void Timer1Init(void)		//10毫秒@12.000MHz
{
    TMOD &= 0x0F;		//设置定时器模式
    TMOD |= 0x10;		//设置定时器模式
    TL1 = 0xF0;			//设置定时初值
    TH1 = 0xD8;			//设置定时初值
    TF1 = 0;			//清除TF1标志
    TR1 = 1;			//定时器1开始计时
    ET1 = 1;			//开定时器1中断
    EA = 1;             //开总中断
}

/***********************************************************
* 名    称：Car_Motor_Init()
* 功    能：电机初始化
* 入口参数：无
* 出口参数：无
* 说    明：10ms一周期
/**********************************************************/
void Car_Motor_Init()
{
    Car_Motor_EN1=1;	 //电机使能控制端
    Car_Motor_B1=0;	 // 电机控制端一端为低
    Car_Motor_A1=0;	 // 电机PWM控制端一端为低
    Timer1Init();	//电机定时器初始化
}
/***********************************************************
* 名    称： Timer1_isr() interrupt 3 using 3
* 功    能： 时钟0中断处理
* 入口参数： 无
* 出口参数： 无
* 说    明：i变量是轨道丢失的统计参数，根据i的计数量判断已经丢失轨道多久
			其中程序是指5000个命令周期后执行倒车的计时器内容
/**********************************************************/
void Timer1_isr(void) interrupt 3 using 3
{
    static unsigned char j = 1;	//静态变量：每次调用函数时保持上一次所赋的值，
    //跟全局变量类似，不同是它只能用于此函数内部
    if(i<5000)//左侧参数就是判断丢失的时间，丢失判断防抖
    {
        switch(j)
        {
        case 1:
            Car_Motor_A1 = 1;	//PWM控制脚高电平
            //给定时器0赋值，计数Pwm0Duty个脉冲后产生中断，下次中断会进入下一个case语句

            Timer1Value(Motor0PwmDuty);	//高电平持续时间
            break;
        case 2:
            Car_Motor_A1 = 0;	//PWM控制脚低电平
            //高脉冲结束后剩下的时间(20000-Pwm0Duty)全是低电平了，Pwm0Duty + (20000-Pwm0Duty) = 20000个脉冲正好为一个周期20毫秒
            Timer1Value(10000-Motor0PwmDuty);//低电平持续时间
            j = 0;
            break;
        }
        j++;
    }
    else
    {
        switch(j)
        {
        case 1:
            Car_Motor_B1 = 1;	//PWM控制脚高电平
            //给定时器0赋值，计数Pwm0Duty个脉冲后产生中断，下次中断会进入下一个case语句

            Timer1Value(Motor0PwmDuty_daoche);	//高电平持续时间
            break;
        case 2:
            Car_Motor_B1 = 0;	//PWM控制脚低电平
            //高脉冲结束后剩下的时间(20000-Pwm0Duty)全是低电平了，Pwm0Duty + (20000-Pwm0Duty) = 20000个脉冲正好为一个周期20毫秒
            Timer1Value(10000-Motor0PwmDuty_daoche);
            j = 0;
            break;
        }
        j++;
    }

}
/***********************************************************
* 名    称：ctry()
* 功    能：轨道位置的判断
* 入口参数：P0 P2^3
* 出口参数：输出轨道变量path，该参数为环境变量，舵机的中断处理
			会因为path的改变而选择合适的角度
* 说    明：i++就是对轨道偏离的统计
/**********************************************************/
sbit AB=P2^3; // 舵机转向的标记端口
int ctry(unsigned int parameter)
{
    if(AB==1)
    {
        switch(parameter)
		{
		case 191:
            i=0;
            return 2166;
        case 223:
            i=0;
            return 2000;
        case 239:
            i=0;
            return 1800;
        case 247:
            i=0;
            return 1500;//90°
        case 251:
            i=0;
            return 1200;
        case 253:
            i=0;
            return 1000;
        case 254:
            i=0;
            return 833;//30°
        case 255:
            i++;
            return 1500;//检测无轨道就让车头对正帮助倒车
        default:
            return Servo0PwmDuty;
		}
    }
    else
    {
        switch(parameter)
        {
        case 191:
            i=0;
            return 833;//30°
        case 223:
            i=0;
            return 1000;
        case 239:
            i=0;
            return 1200;
        case 247:
            i=0;
            return 1500;//90°
        case 251:
            i=0;
            return 1800;
        case 253:
            i=0;
            return 2000;
        case 254:
            i=0;
            return 2166;
        case 255:
            i++;
            return 1500;//检测无轨道就让车头对正帮助倒车
        default:
            return Servo0PwmDuty;
        }
    }

}
sbit LEDA=P2^1;//刹车灯的IO接口
sbit LEDB=P2^2;//刹车灯的IO接口
/***********************************************************
* 名    称：daoche()
* 功    能：倒车指示以及对倒车状态的清零
* 入口参数：无
* 出口参数：无
* 说    明：检测到丢失后又执行10000个命令周期的倒车，无论是否
			重新寻找到路径都前进一段，重新巡线反复扫描，保证成功率
/**********************************************************/
void daoche()
{
    if(i>5000)		//轨道丢失防抖
    {   LEDA = 1;
        LEDB = 0;
        if(i>15000)//倒车持续的检测周期
        {
            i=0;//丢失标记清楚
        }
    }

    else
    {   LEDA = 0;
        LEDB = 0;
    }
}
void main()
{
    Car_Servo_Init();
    Car_Motor_Init();

    while(1)
    {
        pow=P1;
        path=P0;
        Servo0PwmDuty=ctry(path);
        Motor0PwmDuty=30*(pow);
        Motor0PwmDuty_daoche=30*(pow);
        daoche();
    }
}