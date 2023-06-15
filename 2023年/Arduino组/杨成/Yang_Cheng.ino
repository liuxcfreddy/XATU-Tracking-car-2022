int sensor[5];
const int moto1A = 9;
const int moto1B = 7;
const int moto2A = 10;
const int moto2B = 8;
const int base = 95;    // 基础速度
float err, last_err, sum_err, delta_err;

// 传感器引脚定义
const int P1 = 6;
const int P2 = 5;
const int P3 = 4;
const int P4 = 3;
const int P5 = 2;

void setup()
{
  Serial.begin(115200);
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(P4, INPUT_PULLUP);
  pinMode(P5, INPUT_PULLUP);

  pinMode(moto1A, OUTPUT);
  pinMode(moto1B, OUTPUT);
  pinMode(moto2A, OUTPUT);
  pinMode(moto2B, OUTPUT);

  err = 0;
  last_err = 0;
  sum_err = 0; // 重置累计误差
}

void flash()
{
  uint8_t sensorValue = 0;

  sensorValue |= digitalRead(P1) << 4;
  sensorValue |= digitalRead(P2) << 3;
  sensorValue |= digitalRead(P3) << 2;
  sensorValue |= digitalRead(P4) << 1;
  sensorValue |= digitalRead(P5);

  switch (sensorValue)
  {
    case 0b11011: // 11011
      err = 0;
      break;
    case 0b01111: // 01111
      err = 2;
      break;
    case 0b10111: // 10111
      err = 1;
      break;
    case 0b11101: // 11101
      err = -1;
      break;
    case 0b11110: // 11110
      err = -2;
      break;
    default:
      // Handle unrecognized sensor value
      break;
  }
}

int cacu_pwm()
{
  int output;
  float kp = 37, ki = 0.0052, kd = 8.8;
  float P, I, D;

  delta_err = err - last_err;  // Calculate the change in error

  // 增加积分限制
  sum_err += err;
  if (sum_err > 90) {
    sum_err = 90;
  }
  else if (sum_err < -90) {
    sum_err = -90;
  }

  P = kp * err;
  I = ki * sum_err;
  D = kd * delta_err;

  output = P + I + D;

  last_err = err;
  return output;
}

void moto_run(int motorSpeed1, int motorSpeed2)
{
  int motor1A = motorSpeed1 > 0 ? motorSpeed1 : 0;
  int motor1B = motorSpeed1 < 0 ? -motorSpeed1 : 0;
  int motor2A = motorSpeed2 > 0 ? motorSpeed2 : 0;
  int motor2B = motorSpeed2 < 0 ? -motorSpeed2 : 0;

  analogWrite(moto1A, motor1A);
  analogWrite(moto1B, motor1B);
  analogWrite(moto2A, motor2A);
  analogWrite(moto2B, motor2B);
}

void loop()
{
  flash();
  moto_run(base - cacu_pwm(), base + cacu_pwm());
}
