#include <Arduino.h>

// sketch name = pinMode13
// LEDを点滅させる

int outPin = 13;

void setup() {
  pinMode(outPin, OUTPUT);
}

void loop() {
  // LEDを1秒点灯、1秒消灯する
  digitalWrite(outPin,HIGH);  // LEDを点灯
  delay(1000);
  digitalWrite(outPin,LOW) ;  // LEDを消灯
  delay(1000);
}
