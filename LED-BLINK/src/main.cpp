#include <Arduino.h>

// sketch name = LED-BLINK
// PD10に接続したLEDを点滅させる

int LED_SOCKET = 10;
int INTERVAL = 1000; // 点滅間隔（ミリ秒）

void setup() {
  pinMode(LED_SOCKET, OUTPUT);
}

void loop() {
  // LEDを1秒点灯、1秒消灯する
  digitalWrite(LED_SOCKET,HIGH);  // LEDを点灯
  delay(INTERVAL);
  digitalWrite(LED_SOCKET,LOW) ;  // LEDを消灯
  delay(INTERVAL);
}
