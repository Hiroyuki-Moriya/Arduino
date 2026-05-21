// sketch name = TEMPandHUM_SENS
// Outline:温度と湿度センサー DHT11の値を液晶ディスプレイLCD1602に表示する
// V1.0 ぶらりweb走り書きのソースを転用
// V2.0 LCD_Displayのソースを併合
// >>  導入したライブラリ：DHT sensor library
// >>    adafruit/DHT sensor library@^1.4.7
// >>  導入したライブラリ：LiquidCrystal
// >>    arduino-libraries/LiquidCrystal@^1.0.7
// >>  技術的トピックス：

/* 参考資料
  V1.0
    ぶらりweb走り書き( https://burariweb.info/ )
    【Arduino入門編㉑】温湿度センサー(DHT11)を使い温度と湿度を計測する！
    https://burariweb.info/electronic-work/arduino-learning/arduino-temperature-humidity-sensor-dht11.html
*/
/* 参考文献
  V2.0
    エンジニアのための情報共有コミュニティ
      https://zenn.dev/
    dojinosuke 電子工作 その16（LCDディスプレイ：1602Aの使い方）
      https://zenn.dev/suzuky/articles/73552d9deccc79
*/

// LCD1602のライブラリをインクルード
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// DHT11のライブラリをインクルード
#include <DHT.h>

#define DHT_PIN 2       // DHT11のDATAピンをデジタルピン2に定義
#define DHT_MODEL DHT11 // 接続するセンサの型番を定義する(DHT11やDHT22など)

DHT dht(DHT_PIN, DHT_MODEL); // センサーの初期化

void setup()
{
  Serial.begin(9600); // シリアル通信の開始
  dht.begin(); // センサーの動作開始

  lcd.begin(16, 2); // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();      // LCD画面をクリア

  lcd.setCursor(0, 0); // カーソルの位置を指定(0桁0行の位置)
  lcd.print("Temp :"); // 文字の表示

  lcd.setCursor(0, 1); // カーソルの位置を指定(0桁1行目の位置)
  lcd.print("Humid:"); // 文字の表示

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

  //液晶ディスプレイに値を表示
  lcd.setCursor(7, 0);
  lcd.print(Temperature);
  lcd.setCursor(12, 0);
  lcd.print("C");

  lcd.setCursor(7, 1);
  lcd.print(Humidity);
  lcd.setCursor(12, 1);
  lcd.print("%");

  // シリアルモニタに温度&湿度を表示
  Serial.print("温度: ");
  Serial.print(Temperature);
  Serial.print("[℃]");

  Serial.print("  湿度: ");
  Serial.print(Humidity);
  Serial.println("[%]");
}
