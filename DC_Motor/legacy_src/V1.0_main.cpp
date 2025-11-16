// sketch name = DC_Motor
// Outline:直流モーターを制御する

#include <Arduino.h>

#define ENABLE 5
#define DIRA 3
#define DIRB 4

void setup()
{
  //---set pin direction
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int i;
  //---back and forth example
  Serial.println("One way, then reverse");
  digitalWrite(ENABLE, HIGH); // enable on
  for (i = 0; i < 5; i++)
  {
    digitalWrite(DIRA, HIGH); // one way
    digitalWrite(DIRB, LOW);
    delay(500);
    digitalWrite(DIRA, LOW); // reverse
    digitalWrite(DIRB, HIGH);
    delay(500);
  }
  digitalWrite(ENABLE, LOW); // disable
  delay(2000);

  Serial.println("fast Slow example");
  //---fast/slow stop example
  digitalWrite(ENABLE, HIGH); // enable on
  digitalWrite(DIRA, HIGH);   // one way
  digitalWrite(DIRB, LOW);
  delay(3000);
  digitalWrite(ENABLE, LOW); // slow stop
  delay(1000);
  digitalWrite(ENABLE, HIGH); // enable on
  digitalWrite(DIRA, LOW);    // one way
  digitalWrite(DIRB, HIGH);
  delay(3000);
  digitalWrite(DIRA, LOW); // fast stop
  delay(2000);

  Serial.println("PWM full then slow");
  //---PWM example, full speed then slow
  analogWrite(ENABLE, 255); // enable on
  digitalWrite(DIRA, HIGH); // one way
  digitalWrite(DIRB, LOW);
  delay(2000);
  analogWrite(ENABLE, 180); // half speed
  delay(2000);
  analogWrite(ENABLE, 128); // half speed
  delay(2000);
  analogWrite(ENABLE, 50); // half speed
  delay(2000);
  analogWrite(ENABLE, 128); // half speed
  delay(2000);
  analogWrite(ENABLE, 180); // half speed
  delay(2000);
  analogWrite(ENABLE, 255); // half speed
  delay(2000);
  digitalWrite(ENABLE, LOW); // all done
  delay(10000);
}

/*
参考文献1
  Elegoo Super Starter Kit for UNO V1.0.19.09.17-日本語
  「Lesson 21 直流モータ (P191)」
  CODEは、 「Lesson 21 DC Motors」を参考にした
    www.elegoo.com
    2016.12.12
    Exercise the motor using
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
