/*驱动模块代码移植自唐杰学长，感谢2022届，唐杰学长的先前工作*/

#include "intrins.h"
#include "stc89c5xrc.h"
/********以下为参数与环境变量区********/
unsigned int path;                 //红外对管反馈的环境变量
unsigned int power;                // P1口读取常量
unsigned char pow;                 //电机驱动力度的调节
unsigned char pos;                 //舵机转向等级调节
unsigned char posx;                //转向加力参数，请于void ctry（）函数内修改返回值
unsigned int i = 0;                //轨道丢失参数(当轨道丢失到一定的时间后启动倒车程序)
unsigned int ik=4000;               //触发倒车的延迟时间（单位：2微秒-2us）
unsigned int ikt=2;
unsigned int Servo0PwmDuty = 1500; // PWM脉冲宽度   1.5ms脉冲宽度  为舵机正中位置
unsigned int Motor0PwmDuty = 2750; //初始占空比为3000:7000

int Zhuan_Jiao[3] = {21, 31, 45}; //最大转向角设置（左右对称，所以只需要一组，依次从小变大）
int Zhong_Xin_Xiu_Zheng = -7;     //单位 度° 偏右就向左修正，减去一个角度。

sbit AB = P2 ^ 3;            // 舵机转向的标记端口
sbit Car_Motor_A1 = P3 ^ 2;  // 电机控制端
sbit Car_Motor_EN1 = P3 ^ 3; //电机使能控制端（也是PWM输出路径）
sbit Car_Motor_B1 = P3 ^ 4;  // 电机控制端
sbit LEDA = P2 ^ 1;          //刹车灯的IO接口
sbit LEDB = P2 ^ 2;          //刹车灯的IO接口
sbit Car_Servo = P2 ^ 0;     // 舵机pwm控制

/***********************************************************
* 名    称：InitTimer0()
* 功    能：舵机时钟0初始化
* 入口参数：无
* 出口参数：无
* 说    明：12M晶振，12分频，所以计数器每递增一个数就是1微秒，完全满足舵机控制的精度要求
            因为定时器是TH0，TL0都要全部计数到0xFF后在计1个数就会产生中断，所以要想产生
            x毫秒的中断，那么TH0，TL0就应该赋值（0xFFFF-x）	从这个值开始计数产生定时中断
/**********************************************************/
void InitTimer0(void) // 20ms
{
    TMOD &= 0xF0; //设置定时器模式
    TMOD |= 0x01; //设置定时器模式
    TL0 = 0xE0;   //设置定时初值
    TH0 = 0xB1;   //设置定时初值
    TF0 = 0;      //清除TF0标志
    TR0 = 1;      //定时器0开始计时
    ET0 = 1;      //开定时器0中断
    EA = 1;       //开总中断
}
void Car_Servo_Init() //舵机初始化
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
    value = 0xffff - pwm;
    TR0 = 0;
    TL0 = value;      // 16位数据给8位数据赋值默认将16位数据的低八位直接赋给八位数据
    TH0 = value >> 8; //将16位数据右移8位，也就是将高8位移到低八位，再赋值给8位数据
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
    static unsigned char i = 1; //静态变量：每次调用函数时保持上一次所赋的值，
    //跟全局变量类似，不同是它只能用于此函数内部
    switch (i)
    {
    case 1:
        Car_Servo = 1; // PWM控制脚高电平
        //给定时器0赋值，计数Pwm0Duty个脉冲后产生中断，下次中断会进入下一个case语句
        Timer0Value(Servo0PwmDuty);
        break;
    case 2:
        Car_Servo = 0; // PWM控制脚低电平
        //高脉冲结束后剩下的时间(20000-Pwm0Duty)全是低电平了，Pwm0Duty + (20000-Pwm0Duty) = 20000个脉冲正好为一个周期20毫秒
        Timer0Value(20000 - Servo0PwmDuty);
        i = 0;
        break;
    }
    i++;
}
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
    value = 0xffff - pwm;
    TR1 = 0;
    TL1 = value;      // 16位数据给8位数据赋值默认将16位数据的低八位直接赋给八位数据
    TH1 = value >> 8; //将16位数据右移8位，也就是将高8位移到低八位，再赋值给8位数据
    TR1 = 1;
}

/***********************************************************
* 名    称：Timer1Init
* 功    能：电机时钟1初始化
* 入口参数：无
* 出口参数：无
* 说    明：10ms一周期
/**********************************************************/
void Timer1Init(void) // 10毫秒@12.000MHz
{
    TMOD &= 0x0F; //设置定时器模式
    TMOD |= 0x10; //设置定时器模式
    TL1 = 0xF0;   //设置定时初值
    TH1 = 0xD8;   //设置定时初值
    TF1 = 0;      //清除TF1标志
    TR1 = 1;      //定时器1开始计时
    ET1 = 1;      //开定时器1中断
    EA = 1;       //开总中断
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
    Car_Motor_EN1 = 1; //电机使能控制端
    Car_Motor_B1 = 0;  // 电机控制端一端为低
    Car_Motor_A1 = 0;  // 电机PWM控制端一端为低
    Timer1Init();      //电机定时器初始化
}
/***********************************************************
* 名    称： Timer1_isr() interrupt 3 using 3
* 功    能： 时钟0中断处理
* 入口参数： 无
* 出口参数： 无
* 说    明： 无
/**********************************************************/
void Timer1_isr(void) interrupt 3 using 3
{
    static unsigned char j = 1; //静态变量：每次调用函数时保持上一次所赋的值，
                                //跟全局变量类似，不同是它只能用于此函数内部
    switch (j)
    {
    case 1:
        Car_Motor_EN1 = 1; // PWM控制脚高电平
        //给定时器0赋值，计数Pwm0Duty个脉冲后产生中断，下次中断会进入下一个case语句

        Timer1Value(Motor0PwmDuty); //高电平持续时间
        break;
    case 2:
        Car_Motor_EN1 = 0; // PWM控制脚低电平
        //高脉冲结束后剩下的时间(20000-Pwm0Duty)全是低电平了，Pwm0Duty + (20000-Pwm0Duty) = 20000个脉冲正好为一个周期20毫秒
        Timer1Value(10000 - Motor0PwmDuty); //低电平持续时间
        j = 0;
        break;
    }
    j++;
}

void Timer2Init(void) // 1毫秒@12.000MHz
{
    T2MOD = 0;     //初始化模式寄存器
    T2CON = 0;     //初始化控制寄存器
    TL2 = 0x18;    //设置定时初始值
    TH2 = 0xfc;    //设置定时初始值
    RCAP2L = 0x18; //设置定时重载值
    RCAP2H = 0xfc; //设置定时重载值
    TR2 = 1;       //定时器2开始计时
    PT2 = 0;
    ET2 = 1;
    EA = 1;
}
void Car_scan_Init(void)
{
    Timer2Init();
}
/***********************************************************
* 名    称： Timer1_isr() interrupt 5
* 功    能： 时钟2中断处理
* 入口参数： P1
* 出口参数： 无
* 说    明： 利用定时器2，对P1口进行高速扫描，提高舵机转向速度
/**********************************************************/
void Timer2_isr(void) interrupt 5
{
    TF2 = 0;
    path = P0;
    power = P1;
    pow = (~power & 0x0f); //低4位是速度
    pos = (power >> 4);    //高4位是转向
}
/***********************************************************
* 名    称：ctry()
* 功    能：轨道位置的判断
* 入口参数：P0 P2^3
* 出口参数：输出轨道变量path，该参数为环境变量，舵机的中断处理
            会因为path的改变而选择合适的角度
* 说    明：i++就是对轨道偏离的统计
/**********************************************************/

int ctry(unsigned int parameter)
{
    if (AB == 1)
    {
        switch (parameter)
        {
        case 191:
            i = 0;
            posx = 4;
            return 1500 + ((Zhuan_Jiao[2] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng; //右转
        case 223:
            i = 0;
            posx = 3;
            return 1500 + ((Zhuan_Jiao[1] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 239:
            i = 0;
            posx = 1;
            return 1500 + ((Zhuan_Jiao[0] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 247:
            i = 0;
            posx = 0;
            return 1500 + 11 * Zhong_Xin_Xiu_Zheng; // 90°
        case 251:
            i = 0;
            posx = 1;
            return 1500 - ((Zhuan_Jiao[0] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 253:
            i = 0;
            posx = 3;
            return 1500 - ((Zhuan_Jiao[1] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 254:
            i = 0;
            posx = 4;
            return 1500 - ((Zhuan_Jiao[2] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng; //左转
        case 255:
            i++;
            if (i > ik)
            {
                posx = 0;
                return 1500 + 11 * Zhong_Xin_Xiu_Zheng; //检测无轨道就让车头对正帮助倒车
            }
        default:
            return Servo0PwmDuty;
        }
    }
    else
    {
        switch (parameter)
        {
        case 191:
            i = 0;
            return 1500 - ((Zhuan_Jiao[2] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng; //右转
        case 223:
            i = 0;
            return 1500 - ((Zhuan_Jiao[1] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 239:
            i = 0;
            return 1500 - ((Zhuan_Jiao[0] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 247:
            i = 0;
            return 1500 + 11 * Zhong_Xin_Xiu_Zheng; // 90°
        case 251:
            i = 0;
            return 1500 + ((Zhuan_Jiao[0] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 253:
            i = 0;
            return 1500 + ((Zhuan_Jiao[1] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng;
        case 254:
            i = 0;
            return 1500 + ((Zhuan_Jiao[2] * 11) / pos) + 11 * Zhong_Xin_Xiu_Zheng; //左转
        case 255:
            i++;
            if (i > ik)
            {
                return 1500 + 11 * Zhong_Xin_Xiu_Zheng; //检测无轨道就让车头对正帮助倒车
            }
        default:
            return Servo0PwmDuty;
        }
    }
}

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
    if (i > ik) //轨道丢失防抖，开始倒车
    {
        LEDA = 1;
        LEDB = 0;
        Car_Motor_B1 = 0;
        Car_Motor_A1 = 1;
        Motor0PwmDuty = 450 * (pow);
        if (i > ik*ikt) //倒车持续的检测周期
        {
            i = 0; //丢失标记清除
        }
    }
    else //正常前进

    {
        Car_Motor_B1 = 1;
        Car_Motor_A1 = 0;
        LEDA = 0;
        LEDB = 0;
        Motor0PwmDuty = 300 * (pow + posx);
    }
}
void main()
{
    Car_scan_Init();
    Car_Servo_Init();
    Car_Motor_Init();

    while (1)
    {
        daoche();
        Servo0PwmDuty = ctry(path);
    }
}