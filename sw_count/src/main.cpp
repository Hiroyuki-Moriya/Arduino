#include <Arduino.h>

// sketch name = sw_count
// スイッチの状態（押されているかどうか）を表示する
// 参考 chapter5-2 P113

int SWITCH_SOCKET = 2; // スイッチの接続ピン番号
int count = 0; // スイッチが押された回数をカウントする変数  

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_SOCKET, INPUT); // スイッチ（PD2）を入力に設定
}

void loop() {
  if ( digitalRead( SWITCH_SOCKET ) == 1) { // スイッチが押されたら
    count = count + 1;                      // カウントを1増やす  
    Serial.print("Count:");
    Serial.println(count);                  // カウントを表示
    while ( digitalRead ( SWITCH_SOCKET ) == 1){ // スイッチが押されている間は
      delay(100);                          // 100ms待つ (チャタリング対策)
    }
  }
  // スイッチが押されていないときは何もしない
}
