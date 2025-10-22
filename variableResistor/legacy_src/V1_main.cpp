// sketch name = variableResistor
// Outline:可変抵抗器の変化を読み取る

#include <Arduino.h>

int VOLUME_SOCKET = A0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int analog_val;   // アナログ入力の値が 0～1023 で変化する
  float input_volt; // 電圧は 0.0V～5.0V で変化する

  analog_val = analogRead(VOLUME_SOCKET);

  input_volt = float(analog_val) * (5.0 / 1024.0);

  Serial.print(analog_val);  // 表示は 「アナログ入力値 : 0.0V」になる
  Serial.print(" : ");
  Serial.print(input_volt);
  Serial.println("V");

  delay(500);
}

/*
  参考
    福田和宏(著)これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter5-3 P122

    可変抵抗器のことを Variable Resistor と訳したが、
    日本では回転角に正確に応じた抵抗値を出力するものや多回転型のものを、特に「ポテンショメータ(potentiometer)」と呼ぶらしい。(Wikipedia ポテンショメータより一部抜粋)
*/

