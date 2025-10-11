// sketch name = UltrasonicDistanceSensor
// 超音波センサー(HCSR04)でLED点滅しブザー鳴動する

/*
  Version 1.0
   * ライブラリ HCSR04 ultrasonic sensor 導入
   * シリアルプロッタ Teleplot導入
   * LEDの明るさ調整のためdigitalWrite(PIN, HIGH)を
     analogWrite(PIN, 0-255)に変更
   * メロディを入れるためpitch.hと
     圧電スピーカー(パッシブスピーカー)追加
   * LEDを順に点灯しながら音を出すdemonstration関数追加
*/

#include <Arduino.h>

const int BLUE_LED_PIN = 10;  // 青LED接続端子
const int GREEN_LED_PIN = 9;  // 緑LED接続端子,遠い
const int YELLOW_LED_PIN = 6; // 黄LED接続端子,中間
const int RED_LED_PIN = 5;    // 赤LED接続端子,近い

#define SW_PIN A5 // スイッチ接続端子
#define SW_OFF 1  // スイッチOFFのdigitalReadの値

#include <HCSR04.h>

#define TRIG_PIN 2 // トリガーピンの接続端子
#define ECHO_PIN 3 // エコーピンの接続端子

#define NEAR 10.0 // この値以下だったら「近い」判定（単位:cm）
#define MID 20.0  // この値以下だったら「中間」判定（単位:cm）
#define FAR 30.0  // この値以下だったら「遠い」判定（単位:cm）

HCSR04 kyoriSensor(TRIG_PIN, ECHO_PIN); // 距離センサーオブジェクト生成

#include "pitch.h" // 音程周波数定義ファイル
#define SPEAKER_PIN A0 // 圧電スピーカー(パッシブスピーカー)接続端子

void demonstration(){
  noTone(SPEAKER_PIN);     // パッシブスピーカーを止める

  tone(SPEAKER_PIN, DO_4); // パッシブスピーカーを鳴らす
  analogWrite(BLUE_LED_PIN, 64);
  delay(200);

  tone(SPEAKER_PIN, RE_4);
  analogWrite(GREEN_LED_PIN, 32);
  delay(200);

  tone(SPEAKER_PIN, MI_4);
  analogWrite(YELLOW_LED_PIN, 64);
  delay(200);

  tone(SPEAKER_PIN, SO_4);
  analogWrite(RED_LED_PIN, 64);
  delay(200);

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  noTone(SPEAKER_PIN); // パッシブスピーカーを止める
}

void setup()
{
  // シリアルモニタ初期化
  Serial.begin(9600);

  // 端子設定
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  pinMode(SW_PIN, INPUT_PULLUP); // タクトスイッチ（A5）をプルアップ入力に設定

  // 準備OK
  demonstration();

  // スイッチが押されるまで待つ
  Serial.println("スイッチを押すまで待機"); // debug
  while (digitalRead(SW_PIN) == SW_OFF){
        }
  }

void loop()
{
  // 距離測定＆シリアルモニタ表示
  float distance = kyoriSensor.dist();

  // Plot a distance
  Serial.print(">distance:");
  Serial.println(distance);

  if (distance > 0.0)
  { // 測定できた時の処理
    if (distance <= NEAR)
    { // 近い場合
      analogWrite(RED_LED_PIN, 64);
      digitalWrite(YELLOW_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      tone(SPEAKER_PIN, SO_4);
      delay(500);
    }
    else if (distance <= MID)
    { // 中間の場合
      digitalWrite(RED_LED_PIN, LOW);
      analogWrite(YELLOW_LED_PIN, 64);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      tone(SPEAKER_PIN, MI_4);
      delay(500);
    }
    else if (distance <= FAR)
    { // 遠い場合
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, LOW);
      analogWrite(GREEN_LED_PIN, 32);
      digitalWrite(BLUE_LED_PIN, LOW);
      tone(SPEAKER_PIN, RE_4);
      delay(500);
    }
    else
    { // それ以外の場合(つまりとても遠いso farの場合)
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      analogWrite(BLUE_LED_PIN, 64);
      tone(SPEAKER_PIN, DO_4);
      delay(500);
    }
  }
  else
  {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    noTone(SPEAKER_PIN);
    delay(500);
  }

  // 時間待ち
  noTone(SPEAKER_PIN);
  delay(200);
}

  /*
   参考 tool\lab.com
      Arduino ライブラリとは？（解説編）
        https://www.youtube.com/watch?v=Zq72-m4PpFI&t=332s
        https://tool-lab.com/movie-what-is-arduino-libraries-make/

      Arduino ライブラリとは？（製作編）
      https://www.youtube.com/watch?v=RI5FF69nqV4&t=1501s


      Wokwi
      https://wokwi.com/


      PlatformIOでシリアルプロッタのような機能が使いたい(Teleplot)
      https://zenn.dev/yuji_miyano/articles/ebf40a9f31df28

      PlatformIOでシリアルプロットを使ってみる
      https://ds-blog.tbtech.co.jp/entry/2023/04/28/PlatformIOでシリアルプロットを使ってみる

      Teleplot for VSCode
      https://marketplace.visualstudio.com/items?itemName=alexnesnes.teleplot

      VS Codeの拡張機能でTeleplotを検索してインストール
      VS Code画面左下のTeleplotをクリック
      Teleplot画面で、COM3 9600を選択してOPENをクリック
      （COMポートは 設定>Blutoothとデバイス>デバイス でポートを調査)

  */
