// sketch name = TEMPandHUM_SENS
// Outline:温度と湿度センサー DHT11用
// V1.0 ぶらりweb走り書きのソースを転用
// >>  ライブラリ導入 DHT sensor library
// >>   adafruit/DHT sensor library@^1.4.7
// >>

/* 参考資料
  V1.0
    ぶらりweb走り書き( https://burariweb.info/ )
    【Arduino入門編㉑】温湿度センサー(DHT11)を使い温度と湿度を計測する！
    https://burariweb.info/electronic-work/arduino-learning/arduino-temperature-humidity-sensor-dht11.html
*/
/* 参考資料
  V0.0 ELGOO社のライブラリがうまく使えず断念
    ELEGOO社
    Lesson 11 DHT11 Temperature and Humidity Sensor
      取説 P85
      ソース  DHT11_Example > DHT11_Example.ino
*/

#include <DHT.h> // ライブラリのインクルード

#define DHT_PIN 7       // DHT11のDATAピンをデジタルピン7に定義
#define DHT_MODEL DHT11 // 接続するセンサの型番を定義する(DHT11やDHT22など)

DHT dht(DHT_PIN, DHT_MODEL); // センサーの初期化

void setup()
{

  Serial.begin(9600); // シリアル通信の開始

  dht.begin(); // センサーの動作開始
}

void loop()
{

  delay(2000); // センサーの読み取りを2秒間隔に

  float Humidity = dht.readHumidity();       // 湿度の読み取り
  float Temperature = dht.readTemperature(); // 温度の読み取り(摂氏)

  if (isnan(Humidity) || isnan(Temperature))
  { // 読み取りのチェック(どちらか一方が「数値ではない (NaN)」なら真)
    Serial.println("ERROR");
    return;
  }

  // シリアルモニタに温度&湿度を表示
  Serial.print("温度: ");
  Serial.print(Temperature);
  Serial.print("[℃]");

  Serial.print("  湿度: ");
  Serial.print(Humidity);
  Serial.println("[%]");
}