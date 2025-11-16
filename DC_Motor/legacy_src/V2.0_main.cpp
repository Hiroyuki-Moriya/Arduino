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
// V2.0 増減速をするにはanalogWriteでPWMポートを使う必要が
//      あることが判明。(多分ELEGOO社の説明不足)
//      EN1,M1A,M2AのArduino側ポートを変更し、回路変更するとともに、
//      #defineのM1A,M2AをL293Dデータシートに合わせてIN1_1A,IN2_2Aにする。
//      Motor2()を一部analogWriteに再変更。

#include <Arduino.h>

#define EN1 7     //Arduino PD7 → L293D pin1
#define IN1_1A 6  //Arduino PD6 → L293D pin2
#define IN2_2A 5  //Arduino PD5 → L293D pin7

void Motor1(int e1,int m1,int m2,int dly)
{
  digitalWrite(EN1, e1);
  digitalWrite(IN1_1A, m1);
  digitalWrite(IN2_2A, m2);
  delay(dly);
}

void Motor2(int e1_2, int m1_2, int m2_2, int dly_2)
{
  // モータの回転数を制御 speed control
  digitalWrite(EN1, e1_2);
  analogWrite(IN1_1A, m1_2); // 正転=speed(0-255)、逆転=LOW
  analogWrite(IN2_2A, m2_2); // 逆転=LOW、逆転=speed(0-255)
  delay(dly_2);
}

void setup()
{
  //---set pin direction
  pinMode(EN1, OUTPUT);
  pinMode(IN1_1A, OUTPUT);
  pinMode(IN2_2A, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println("正転5秒");
  Motor1(HIGH, HIGH, LOW, 5000); // 正転Turn left

  Serial.println("緩停止5秒");
  Motor1(LOW, LOW, LOW, 5000); // 緩停止Free-running motor stop

  Serial.println("逆転5秒");
  Motor1(HIGH, LOW, HIGH, 5000); // 逆転Turn right

  Serial.println("急停止5秒");
  Motor1(HIGH, LOW, LOW, 5000); // 急停止Fast motor stop

  Serial.println("正転半速5秒");
  Motor2(HIGH, LOW, 200, 5000); // 逆転半速 Turn right & Half Speed

  Serial.println("急停止5秒");
  Motor1(HIGH, HIGH, HIGH, 5000); // 急停止Fast motor stop

  Serial.println("正転しながら徐々に増速");
  int motorSpeed = 150; // 0-150まではモーターがほとんど動かない
  while ( motorSpeed < 255)
  {
    Motor2(HIGH, LOW, motorSpeed, 1000); // 逆転Turn right
    motorSpeed = motorSpeed + 10;
    Serial.print(".");
   }
   Serial.println("*");

  Serial.println("緩停止1秒");
  Motor2(LOW, LOW, LOW, 1000); // 緩停止slow stop

}

/* 参考文献
 テキサスインスツルメンツ社
 L293D アクティブクワッド ハーフH ドライバ
 L293x Quadruple Half-H Drivers データシート (Rev. D)
 https://www.ti.com/product/ja-jp/L293D#tech-docs

 Table 3. Bidrectional DC Motor Control
  | EN | 1A | 2A | FUNCTION(1)
  -----|----| ---|------------
  | H  | L  | H  | Turn right
  | H  | H  | L  | Turn left
  | H  | L  | L  | Fast motor stop
  | H  | H  | H  | Fast motor stop
  | L  | X  | X  | Free-running motor stop
  (1) L = low, H = high, X = don’t care
*/

/* 参考文献
  Elegoo Super Starter Kit for UNO V1.0.19.09.17-日本語
  「Lesson 21 直流モータ (P191)」
  CODEは、 「Lesson 21 DC Motors」を参考にした
    www.elegoo.com
    2016.12.12
    Exercise the Motor using
    the L293D chip
*/

/* 参考文献
  福田和宏(著)
    これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter5-5 P133
    ... 本文で使用しているモーター制御用ICがDRV8835だが、
        手持ちがELEGOOのキットのため、解説とソースコードを参照するにとどめた。

*/

/* 参考文献
  魁高専 -SAKIGAKE Colleges of Technology-
  【モータ制御④】モータドライバIC L293D【Arduino】
  https://sakigake-robo.com/Motor-4/
*/

/* 参考文献
Arduino と L293D で DC モーターを制御する方法 - Arduino - 基礎からの IoT 入門
https://iot.keicode.com/arduino/arduino-l293d-dc-motor.php
*/

/* 参考文献
  Arduinoで遊ぼう(25,DCモータ)  ※ELEGOO社のキットを使用している
  https://mecha-norimaki.com/arduino_start_25/
*/
