// sketch name = DC_Motor
// Outline:直流モーターを制御する
// V1.0 ELEGOO社オリジナルソース
// V1.1 Motor(),Motor2()でソースを見やすく整備
// V1.2 Motor()をMotor1()にリネーム
//      Motor1()とMotor2()で変数名が重複しないように整備
// V1.3 Motor2()をすべてanalogWriteに変更
//      増速と減速ロジックを変更
//      Debug用表示追加
// V1.4 0.5秒ごとに正転/逆転するロジックを削除
//      Motor2()をanalogWriteとdigitaiWriteに変更
//      増速と減速ロジックを変更

#include <Arduino.h>

#define EN1 5  //Arduino D5 → L293D pin1(EN1)
#define M1A 4  //Arduino D4 → L293D pin2(in1)
#define M2A 3  //Arduino D3 → L293D pin7(in2)

void Motor1(int e1,int m1,int m2,int dly)
{
  digitalWrite(EN1, e1);
  digitalWrite(M1A, m1);
  digitalWrite(M2A, m2);
  delay(dly);
}

void Motor2(int e1_2, int m1_2, int m2_2, int dly_2)
{
  digitalWrite(EN1, e1_2); // モータの回転数を制御 speed control
  analogWrite(M1A, m1_2);
  digitalWrite(M2A, m2_2);
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
  Serial.println("正転5秒");
  Motor1(HIGH, HIGH, LOW, 5000); // 正転one way

  Serial.println("緩停止5秒");
  Motor1(LOW, HIGH, LOW, 5000);  // 緩停止slow stop

  Serial.println("逆転5秒");
  Motor1(HIGH, LOW, HIGH, 5000);   // 逆転reverse

  Serial.println("急停止5秒");
  Motor1(HIGH, LOW, LOW, 5000);   // 急停止fast stop

  Serial.println("0.1秒毎に徐々に減速");
  for (int k = 255; k > 0; k--)
  {
    Motor2(HIGH, LOW, k, 100); // EN1 ON , 正転one way
  }

  Serial.println("0.1秒毎に徐々に増速");
  for (int j = 0; j < 256; j++)
  {
    //---PWM example, full speed then slow
    Motor2(HIGH, LOW, j, 100); // EN1 ON , 正転one way
  }

  Serial.println("緩停止1秒");
  Motor2(LOW, LOW, LOW, 1000); // 緩停止slow stop

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

/*
Arduino と L293D で DC モーターを制御する方法 - Arduino - 基礎からの IoT 入門
https://iot.keicode.com/arduino/arduino-l293d-dc-motor.php
*/

/*
  Arduinoで遊ぼう(25,DCモータ)  ※ELEGOO社のキットを使用している
  https://mecha-norimaki.com/arduino_start_25/
*/
