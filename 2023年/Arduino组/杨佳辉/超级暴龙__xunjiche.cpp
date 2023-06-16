/*
#include<Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>
#define OLED_DISPLAY 13
Adafruit_SSD1306 display(OLED_DISPLAY)
*/
int p1=8;
int p2=9;
int p3=10;
int p4=11;
int p5=12;
int moto1=5;
int moto2=6;
int moto1_EN=3;
int moto2_EN=4;
int cnt;
void setup(){
  pinMode(p1,INPUT);
  pinMode(p2,INPUT);
  pinMode(p3,INPUT);
  pinMode(p4,INPUT);
  pinMode(p5,INPUT);

  pinMode(moto1,OUTPUT);
  pinMode(moto2,OUTPUT);
  pinMode(moto1_EN,OUTPUT);
  pinMode(moto2_EN,OUTPUT);

  digitalWrite(p1,LOW);
  digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  digitalWrite(p4,LOW);
  digitalWrite(p5,LOW);
 /* display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();*/
}

void loop(){
  switch(fetch()){
    case 15:seek_route(5,45);
            break;
    case 23:seek_route(5,35);
            break;
    case 27:seek_route(30,30);
            break;
    case 29:seek_route(35,5);
            break;
    case 30:seek_route(45,5);
            break;
    case 31:seek_route(15,26);//丟线时寻线，不完全丢线时或调整姿态，或快速回线
            break;
    case 7:
            crash_left(60,60);
            break;
    case 11:
            crash_left(60,60);
            break;
    case 3:crash_left(60,60);
          break;
    case 24:crash_right(60,60);
            break;
    case 28:crash_right(60,60);
            break;
    case 0:seek_route(30,30);
           break;
    default :seek_route(30,30);
            break;
  }
}
void crash_left(int a,int b){//90度急转弯左转
  digitalWrite(moto2_EN,LOW);//右边电机正转
  digitalWrite(moto1_EN,HIGH);//左边电机反转
  int motoa=0;
  int motob=0;
  motoa=-a*2.55;//反转
  motob=b*2.55;
  analogWrite(moto1,motoa);
  analogWrite(moto2,motob);
}
void crash_right(int a,int b){//90度急转弯左转
  digitalWrite(moto2_EN,HIGH);//左边电机正转
  digitalWrite(moto1_EN,LOW);//右边电机反转
  int motoa=0;
  int motob=0;
  motoa=a*2.55;
  motob=-b*2.55;//反转
  analogWrite(moto1,motoa);
  analogWrite(moto2,motob);
}
void seek_route(int a,int b){
  digitalWrite(moto1_EN,LOW);
  digitalWrite(moto2_EN,LOW);
  int motoa=0;
  int motob=0;
  motoa=a*2.55;
  motob=b*2.55;
  analogWrite(moto1,motoa);
  analogWrite(moto2,motob);
}

int fetch{
  uint8_t rev;
  rev=0;
  uint8_t p_1,p_2,p_3,p_4,p_5;
  p_1=digitalRead(p1);
  p_2=digitalRead(p2);
  p_3=digitalRead(p3);
  p_4=digitalRead(p4);
  p_5=digitalRead(p5);
  rev|=p_1;
  rev<<=1;
  rev|=p_2;
  rev<<=1;
  rev|=p_3;
  rev<<=1;
  rev|=p_4;
  rev<<=1;
  rev|=p_5;
  return rev;
}