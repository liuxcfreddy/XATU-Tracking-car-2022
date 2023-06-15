#include <Arduino.h>

#include <BluetoothSerial.h>
#include "Adafruit_VL53L0X.h"
BluetoothSerial SerialBT;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int  blink_LED = 2;
void setup()
{

  // BLEDevice::init("MyESP32"); // 初始化BLE设备
  Serial.begin(115200);               // 开启串口
  SerialBT.begin("电信科协裁判系统"); // 开启蓝牙串口
  Serial.println("蓝牙开启需要1分钟");
  SerialBT.println("蓝牙开启需要1分钟");
  pinMode(blink_LED,OUTPUT);
  for(int i = 0;i<5;i++)
  {
  digitalWrite(blink_LED,HIGH);
  delay(100);
  digitalWrite(blink_LED,LOW);
  delay(100);
  }
  // wait until serial port opens for native USB devices
  // while (!SerialBT)
  // {
  //   delay(1);
  // }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin())
  {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  //start continuous ranging
  lox.startRangeContinuous();
  
}
int mark = 0;
uint8_t Tof_distance;
char text = ' ';
void loop()
{

  if (lox.isRangeComplete())
  {
    Tof_distance = lox.readRange();
    if (Serial.available() > 0)
    {
      text = (char)(Serial.read());
      if (text == 'O')
      {
        Serial.print("Distance in mm: ");
        Serial.println(Tof_distance);
        
      }
    }
  }
  if (mark == 0)
  {
    if (Tof_distance <= 150)
    {
      SerialBT.print("pass");
      mark = 1;
      digitalWrite(blink_LED,HIGH);
    }
  }
  else
  {
    if (Tof_distance >= 200)
    {
      mark = 0;
      digitalWrite(blink_LED,LOW);
    }
  }
}
