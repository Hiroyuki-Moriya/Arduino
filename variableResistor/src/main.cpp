// sketch name = variableResistor
// Outline:可変抵抗器の変化を読み取る

/*
  V1.0 初期バージョン
  v1.1 シリアルプロット表示
  V2.0 LED点滅
*/

#include <Arduino.h>

const int VOLUME_SOCKET = A0; // 可変抵抗の端子
const int GREEN_LED_PIN = 5; // 緑LED接続端子

void setup()
{
  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT);
  analogWrite(GREEN_LED_PIN, 0);
}

void loop()
{
  int analog_val;   // アナログ入力の値が 0～1023 で変化する
  float input_volt; // 電圧は 0.0V～5.0V で変化する
  float delay_time; // LEDの点滅間隔は 0.1秒から1.0秒まで変化する

  analog_val = analogRead(VOLUME_SOCKET);
  input_volt = float(analog_val) * (5.0 / 1024.0);

  delay_time = analog_val * (0.9/1023) + 0.1;
  analogWrite(GREEN_LED_PIN, 32);
  delay(delay_time * 1000);
  analogWrite(GREEN_LED_PIN, 0);
  delay(delay_time * 1000);

  //  アナログ入力値 : 電圧V で表示
  Serial.print(analog_val);
  Serial.print(" : ");
  Serial.print(input_volt);
  Serial.println("V");
  Serial.println(delay_time);
  delay(500);

  /*
  //  シリアルプロットで表示
  Serial.print(">VOLT:");
  Serial.println(input_volt);
  delay(500);
*/

}

/*
  参考
    福田和宏(著)これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter5-3 P122

    可変抵抗器のことを Variable Resistor と訳したが、
    日本では回転角に正確に応じた抵抗値を出力するものや多回転型のものを、特に「ポテンショメータ(potentiometer)」と呼ぶらしい。(Wikipedia ポテンショメータより一部抜粋)
*/

