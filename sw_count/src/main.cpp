#include <Arduino.h>

// sketch name = sw_count
// スイッチの状態（押されているかどうか）を表示する

int SWITCH_SOCKET = 2; // スイッチの接続ピン番号

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_SOCKET, INPUT_PULLUP); // スイッチ（PD2）を内部プルアップ入力に設定
}

void loop() {

  Serial.println( digitalRead( SWITCH_SOCKET ) ); // スイッチの状態をシリアルモニタに出力

  delay(3000); // 3秒待機
}

//void loop() {
////  タクトスイッチを押している状態を読み取り、シリアルモニタに表示する
////  押されていれば 1、押されていなければ 0 を表示
//  Serial.println( digitalRead( SWITCH_SOCKET ) ); // カウントをシリアルモニタに出力
//
//  delay(3000); // 3秒待機
//}