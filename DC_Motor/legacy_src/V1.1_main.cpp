// sketch name = DC_Motor
// Outline:直流モーターを制御する

#include <Arduino.h>

#define EN1 5  //Arduino D5 → L293D pin1(EN1)
#define M1A 4  //Arduino D4 → L293D pin2(in1)
#define M2A 3  //Arduino D3 → L293D pin7(in2)

void Motor(int e1,int m1,int m2,int dly)
{
  digitalWrite(EN1, e1);
  digitalWrite(M1A, m1);
  digitalWrite(M2A, m2);
  delay(dly);
}

void Motor2(int e1, int m1, int m2, int dly)
{
  analogWrite(EN1, e1); // モータの回転数を制御 speed control
  digitalWrite(M1A, m1);
  digitalWrite(M2A, m2);
  delay(dly_2);
}

void setup()
{
  //---set pin direction
  pinMode(EN1, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M2A, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int i;
  //---back and forth example
  Serial.println("正転0.5秒,逆転0.5秒,5回繰り返し,2秒停止");
  for (i = 0; i < 5; i++)
  {
    Motor(HIGH, HIGH, LOW, 500); // 正転one way
    Motor(HIGH, LOW, HIGH, 500); // 逆転reverse
  }
  Motor(LOW, LOW, LOW, 2000); // 停止disable

  Serial.println("正転,緩停止,逆転,急停止");
  //---fast/slow stop example
  Motor(HIGH, HIGH, LOW, 3000); // 正転one way
  Motor(LOW, HIGH, LOW, 1000);  // 緩停止slow stop
  Motor(HIGH, LOW, HIGH, 3000);   // 逆転reverse
  Motor(HIGH, LOW, LOW, 2000);   // 急停止fast stop

  Serial.println("最高速,徐々に減速,徐々に増速,最高速");
  //---PWM example, full speed then slow
  Motor2(255, HIGH, LOW, 2000); // EN1 ON , 正転one way
  Motor2(128, HIGH, LOW, 2000); // EN1 ON , 正転one way
  Motor2(64, HIGH, LOW, 2000); // EN1 ON , 正転one way
  Motor2(32, HIGH, LOW, 2000);  // EN1 ON , 正転one way
  Motor2(64, HIGH, LOW, 2000);   // EN1 ON , 正転one way
  Motor2(128, HIGH, LOW, 2000);  // EN1 ON , 正転one way
  Motor2(255, HIGH, LOW, 2000);  // EN1 ON , 正転one way

  Serial.println("緩停止");
  Motor(LOW, HIGH, LOW, 1000); // 緩停止slow stop
}

/*
参考文献1
  Elegoo Super Starter Kit for UNO V1.0.19.09.17-日本語
  「Lesson 21 直流モータ (P191)」
  CODEは、 「Lesson 21 DC Motors」を参考にした
    www.elegoo.com
    2016.12.12
    Exercise the Motor using
    the L293D chip
*/
/*
参考文献2
  福田和宏(著)
    これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter5-5 P133
    ... 本文で使用しているモーター制御用ICがDRV8835だが、
        手持ちがELEGOOのキットのため、解説とソースコードを参照するにとどめた。

*/

/*
参考文献
  魁高専 -SAKIGAKE Colleges of Technology-
  【モータ制御④】モータドライバIC L293D【Arduino】
  https://sakigake-robo.com/Motor-4/
*/
