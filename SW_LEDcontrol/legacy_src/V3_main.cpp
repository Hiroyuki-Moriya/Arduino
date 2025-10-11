// sketch name = SW_LEDcontor
// Switch押下でLED点滅しブザー鳴動する

/*
  Version 3.0
    スケッチ調整
      接続端子の番号を #define から constに変更
    関数定義
      setRemainingLed()
*/

/* スイッチを押下したらブザー鳴動する
   タイマー時間がゼロでなければ青LEDを毎秒点滅する
   タイマー時間が1/2超ならば緑LEDを点滅する
   タイマー時間が1/2以下かつ1/4超ならば黄LEDを点滅する
   タイマー時間が1/4以下ならば赤LEDを点滅する
   LEDが緑から黄、黄から赤に変わるときにブザー鳴動する
   タイマー時間がゼロならばブザー鳴動する
*/

/*
  LEDの明るさ調整のためdigitalWrite(PIN, HIGH)を
  analogWrite(PIN, 0-255)にしてある。
  LEDを消すときはdigitalWrite(PIN, LOW)を使っている
*/

#include <Arduino.h>
#include "pitch.h"    // 音程周波数定義ファイル

#define TIMER 10      // タイマー時間（秒）
int     halfTimer;    // タイマー時間の1/2
int     soonTimer;    // タイマー時間の1/4

const int BLUE_LED_PIN = 11;       // 青LED接続端子
const int GREEN_LED_PIN = 9;   // 緑LED接続端子
const int YELLOW_LED_PIN = 6;  // 黄LED接続端子
const int RED_LED_PIN = 5;     // 赤LED接続端子

const int lightingSecond = 50; // 点灯時間
const int delaySecond = 950;      // 消灯時間

#define SPEAKER_PIN A0 // 圧電スピーカー(パッシブスピーカー)接続端子
#define SW_PIN A5 // スイッチ接続端子
#define SW_OFF 1  // スイッチOFFのdigitalReadの値

void setRemainingLed(int position){
  // setRemainingLed関数定義
  //   positionで指定した位置の残り時間LEDのみをONにする

  // 最初に全部のLEDをOFFにしておく
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  // positionの値に応じて対応するLEDをONにする
  switch (position)
  {
  case 1:
    analogWrite(GREEN_LED_PIN, 32);
    break;
  case 2:
    analogWrite(YELLOW_LED_PIN, 64);
    break;
  case 3:
    analogWrite(RED_LED_PIN, 64);
    break;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP); // タクトスイッチ（A5）をプルアップ入力に設定
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  halfTimer = TIMER / 2;
  soonTimer = TIMER / 4;
}

void loop() {
  Serial.println("スイッチを押すまで待機"); // debug
  // スイッチが押されるまで待つ
  while( digitalRead(SW_PIN) == SW_OFF ) {
  }

  Serial.println("st,青ピカ"); //debug
  tone(SPEAKER_PIN, RA_4);   // パッシブスピーカーを鳴らす
  analogWrite(BLUE_LED_PIN, 64);
  delay(lightingSecond);
  digitalWrite(BLUE_LED_PIN, LOW);
  delay(delaySecond);
  noTone(SPEAKER_PIN); // パッシブスピーカーを止める

  for (int i = 0; i < TIMER; i++){          // タイマー時間だけLEDを点滅する
    int timeLeft = TIMER - i;

    if (timeLeft > halfTimer)
    {
      Serial.print(timeLeft); // debug
      Serial.println("緑ピカ"); // debug
      setRemainingLed(1);       //  充分時間があるので緑LED点灯
      }else if(timeLeft <= halfTimer && timeLeft > soonTimer){
      Serial.print(timeLeft); // debug
      Serial.println("黄ピカ"); // debug
      setRemainingLed(2); //  残り時間半分なので黄LED点灯
    }else if(timeLeft <= soonTimer && timeLeft > 0){
      Serial.print(timeLeft); // debug
      Serial.println("赤ピカ"); // debug
      setRemainingLed(3); //  残り時間1/4なので赤LED点灯
    }

    //  青LED点滅、ただしタイマー1/2または1/4はブザー鳴らす
    if(timeLeft == halfTimer || timeLeft == soonTimer){
      Serial.print(timeLeft);   // debug
      Serial.println("青ピカ"); // debug
      tone(SPEAKER_PIN, RA_4); // パッシブスピーカーを鳴らす
      analogWrite(BLUE_LED_PIN, 64);
      delay(lightingSecond);
      digitalWrite(BLUE_LED_PIN, LOW);
      delay(delaySecond);
      noTone(SPEAKER_PIN); // パッシブスピーカーを止める
    }else{
      analogWrite(BLUE_LED_PIN, 64);
      delay(lightingSecond);
      digitalWrite(BLUE_LED_PIN, LOW);
      delay(delaySecond);
    }
  }

  //残り時間ゼロのシーケンス
  Serial.println("全消灯"); // debug
  int melody[] =    {DO_4, RE_4, MI_4, REST, RE_4, REST, DO_4}; // メロディーを定義
  int duration[] =  {   2,    1,    4,    0,    1,    0,    2};// 音の長さを定義
  for (int i = 0; i < 7; i++)  {
    // melody[i]の値がREST(=0)の場合、音を止めて指定時間待つ
    // それ以外の場合は、通常通りtoneで音を出す
    if (melody[i] == REST) {
      noTone(SPEAKER_PIN);
      delay(duration[i] * 500);
    }else{
      tone(SPEAKER_PIN, melody[i]);
      delay(duration[i] * 500);
    }
    Serial.print("MELODY= "); // debug
    Serial.println(melody[i]); // debug
  }
  noTone(SPEAKER_PIN);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

/*
 参考 tool\lab.com
    Arduino入門 〜基礎編パート1〜
    https://tool-lab.com/arduino-basic-1-11/
    https://tool-lab.com/movie-arduino-basic-3/

    Arduino入門 （5）スイッチを追加する
    https://www.youtube.com/watch?v=fNV6DZtcccI&t=1280s
    https://tool-lab.com/movie-arduino-basic-5/

    Arduino入門 （6）スピーカー追加
    https://www.youtube.com/watch?v=t60KHACVg10
    https://tool-lab.com/movie-arduino-basic-6/

    Arduino入門 （7）残り時間目安の表示
    https://www.youtube.com/watch?v=ujLNQmCM-PU&t=1143s
    https://tool-lab.com/movie-arduino-basic-7/

    Arduino入門 (8) メロディーアラームの再生
    https://www.youtube.com/watch?v=FFuNVTBoPQo
    https://tool-lab.com/movie-arduino-basic-8/

    Arduino入門 (9) スケッチ仕上げ
    https://www.youtube.com/watch?v=TwQRm-ImXWc
    https://tool-lab.com/movie-arduino-basic-9/
*/
