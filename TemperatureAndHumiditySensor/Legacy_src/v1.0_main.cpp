// sketch name = TemperatureAndHumiditySensor
// Outline:温度と湿度センサー SHT31-DIS用

// V1.0 参考文献1のロジックをほぼそのまま作成
//  >>  ライブラリ導入 adafruit/Adafruit SHT31 Library@^2.2.2
/* ライブラリはメーカー純正の Sensirion I2C SHT3x by Sensirion のほうが
   良かったのかもしれない
*/
/* 参考文献1
  福田和宏(著)
    これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter6-2 P153
*/

#include <Arduino.h>
#include <Wire.h>

#define SHT31_ADDR 0x45  // I2Cデバイスのアドレス

void setup() {
  Serial.begin(9600); // シリアル通信の初期化
  Wire.begin();

  // SHT31_DISをリセットする
  Wire.beginTransmission( SHT31_ADDR );
  Wire.write( 0x30 );
  Wire.write( 0xa2 );
  Wire.endTransmission();
  delay( 500 );

  Wire.beginTransmission( SHT31_ADDR );
  Wire.write( 0x30 );
  Wire.write( 0x41 );
  Wire.endTransmission();
  delay( 500 );
}

void loop() {
  unsigned int dac[ 6 ]; //温度データは配列の0,1に、湿度データは配列の3,4に入る
  unsigned int i, t, h;  // iは配列dacのインデックス。
  float temp, humi;

  Wire.beginTransmission( SHT31_ADDR );
  Wire.write( 0x24 );
  Wire.write( 0x00 );
  Wire.endTransmission();
  delay( 300 );

  //データを６回読み取って配列dacに格納する
  Wire.requestFrom( SHT31_ADDR, 6 );
  for ( i = 0; i<6 ; i++){
    dac[i] = Wire.read();
  }
  Wire.endTransmission();

  //温度を求める
  t = ( dac[0] << 8 ) | dac[1]; //dac[0]を8ビット左シフトして、dac[1]と結合して全体を16ビットの数値にしている。
  temp = (float)(t) * 175 / 65535.0 - 45.0;

  // 湿度を求める
  h = ( dac[3] << 8) | dac[4];
  humi = (float)(h) / 65535.0 * 100.0;

  //シリアルプロッタ用
  /*
  Serial.print(temp);
  Serial.print(",");
  Serial.println(humi);
  */

  //シリアルモニター用
  
  Serial.print(" / Temperature : ");
  Serial.print( temp );
  Serial.print(" C / ");

  Serial.print("Humidity : ");
  Serial.print( humi );
  Serial.println(" %"); //見やすいように改行
  

  delay( 1000 );
}
