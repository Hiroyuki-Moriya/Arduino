#include <Arduino.h>

// sketch name = serial_msg
// Arduinoのカウントをメッセージとして受信し、シリアルモニターに表示するスケッチ

int count;  // 変数countを整数型宣言

void setup() {
  Serial.begin(9600); // シリアル通信を9600ボーで開始
  // platformio.iniに 'monitor_speed = 9600' を追加すること
}

void loop() {
  count=0;  // 変数countを0に初期化。
            // 型宣言で初期化するとloopのたびに0に戻らないので注意。

  Serial.println("start:count=" + String(count) );

  while ( count < 3 ){
    Serial.println("From Arduino Message.");
    count++;
  }

  Serial.println("end:count=" + String(count) );
  Serial.println("count is 3 or more, 10second wait.");
  delay(10000); // 次のloop関数実行まで10秒待つ
                // loopから抜けるにはターミナル上でCtrl+Cを入力する
}



