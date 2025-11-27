// sketch name = Servo_Motor
// Outline:サーボモーターを制御する
// >> ライブラリ導入 Servo
// V1.0 Servoライブラリのソースをベースに
//      参考文献1のロジックを改修して作成
//
#include <Arduino.h>

#include <Servo.h>
Servo myservo;

int SERVO_SOCKET = 9;

void setup()
{
  myservo.attach(SERVO_SOCKET);
  Serial.begin(9600); // for debug
}

void loop()
{
  for (int angle = 0; angle < 181; angle+=15){
    myservo.write(angle);
    delay(1000);
    Serial.println(angle); // for debug
  }
}

/* 参考文献1
  福田和宏(著)
    これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter5-6 P142
*/

/* 参考文献2
  Spiceman
  Arduino-Servo(サーボモーター)ライブラリの使い方
  https://spiceman.jp/arduino-servo-library/
*/