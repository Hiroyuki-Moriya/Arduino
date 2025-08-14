#include <Arduino.h>

// sketch name = calc
// 計算結果をターミナルとLEDで表示する

void LED_blink(int count, int interval);
int LED_pin = 13; 

void setup() {
  Serial.begin(9600); // シリアル通信を9600ボーで開始
  // platformio.iniに 'monitor_speed = 9600' を追加すること
  pinMode(LED_pin, OUTPUT);  // LEDの13番pinを準備
}

void loop() {
  int i,j,count, interval;

  i=10;
  j=3;

  count = i + j;

  Serial.print(i);
  Serial.print("+");
  Serial.print(j);
  Serial.print("=");
  Serial.println(count);

  interval = 1000;
  LED_blink(count , interval);  // count回LEDを点滅(1秒点灯1秒消灯1秒待つ)する

  delay(10000); // 次のloop関数実行まで10秒待つ
                // loopから抜けるにはターミナル上でCtrl+Cを入力する
}
   
void LED_blink(int count, int interval) {
  int k = 0;
  while (k < count) {
    digitalWrite(LED_pin, HIGH);  // LEDを点灯
    delay(1000); // 1秒待つ
    digitalWrite(LED_pin, LOW);  // LEDを消灯
    delay(1000); // 1秒待つ
    Serial.println(k);
    delay(interval);
    k++;
  } 
}