#include <Arduino.h>

int P1 = 2;//这里意味着你应该把传感器的P1接口接到你板子上的2口余下同理
int P2 = 3;
int P3 = 4;
int P4 = 5;
int P5 = 6;

int moto1 = 9;//这里意味着是你应该把1号电机的一端接9
int moto2 = 10;//这里意味着是你应该把2号电机的一端接10

int moto1_EN = 7;//这里意味着是你应该把1号电机的另一端接7
int moto2_EN = 8;//这里意味着是你应该把2号电机的另一端接8
void setup()
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(P4, INPUT_PULLUP);
  pinMode(P5, INPUT_PULLUP);

  digitalWrite(P1,LOW);
  digitalWrite(P2,LOW);
  digitalWrite(P3,LOW);
  digitalWrite(P4,LOW);
  digitalWrite(P5,LOW);
  //上面这一节是初始化传感的端口的，意思就是说：
  //这几个端口你们听好了，你们的作用是用来获取外接传感器的信号，别的事情你们别管啦！
  pinMode(moto1, OUTPUT);
  pinMode(moto2, OUTPUT);
  pinMode(moto1_EN, OUTPUT);
  pinMode(moto2_EN, OUTPUT);
  //这上面这几个也是同理，初始化端口，用来输出信号
  Serial.begin(9600);
}


/* @brief 用于调整电机输出比例
 * @param motoA 参数范围设置为0~100;
 * @param motoB 参数范围设置为0~100;
 */
void dirve(int motoA, int motoB)
{
  digitalWrite(moto1_EN, LOW);
  digitalWrite(moto2_EN, LOW);
  motoA = motoA * 2.55;
  motoB = motoB * 2.55;
  analogWrite(moto1, motoA);
  analogWrite(moto2, motoB);
}
/// @brief 用于倒车的驱动程序
/// @param motoA 
/// @param motoB 
void back_drive(int motoA, int motoB)
{
    digitalWrite(moto1_EN, HIGH);
  digitalWrite(moto2_EN, HIGH);
  motoA = (100-motoA) * 2.55;
  motoB = (100-motoB )* 2.55;
  analogWrite(moto1, motoA);
  analogWrite(moto2, motoB);
}
/// @brief 用于获取传感器的真值
/// @return 5位二进制数，代表着你的路径
/// 你会获取到这几个值 
/// 11111(路径丢失) 
/// 11110(黑线在右) 
/// 11101(黑线偏右) 
/// 11011(黑线在中) 
/// 10111(黑线偏左) 
/// 01111(黑线在左) 
/// 但是具体下来可能会与你的硬件连接不匹配，所以需要你自己调整
uint8_t user_scan()
{
  uint8_t rev=0;
  rev |= digitalRead(P1);
  rev = rev<<1;
  rev |= digitalRead(P2);
 rev = rev<<1;
  rev |= digitalRead(P3);
 rev = rev<<1;
  rev |= digitalRead(P4);
rev = rev<<1;
  rev |= digitalRead(P5);
  return rev;
}
void loop()
{
  uint8_t def =0;
  def = user_scan();
  Serial.println(def);
  switch (def)
  {
  case 30:dirve(80,20);
    /* code */
    break;
  case 29:dirve(60,40);
    /* code */
    break;
  case 27:dirve(50 ,50);
    /* code */
    break;
  case 23:dirve(40 ,60);
    /* code */
    break;
  case 15:dirve(20 ,80);
    /* code */
    break;
  }
}