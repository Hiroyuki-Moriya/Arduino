// sketch name = LCD_Display
// Outline:液晶ディスプレイ(Liquid Crystal Display Module) LCD1602A用
// V1.0 dojinosukeさんのソースを使用
//      
// >>  導入したライブラリ：LiquidCrystal
// >>  技術的トピックス：
/* 参考文献1
  エンジニアのための情報共有コミュニティ
    https://zenn.dev/
  dojinosuke 電子工作 その16（LCDディスプレイ：1602Aの使い方）
    https://zenn.dev/suzuky/articles/73552d9deccc79
*/

#include <LiquidCrystal.h>

// LCD ←→ Arduinoのピンの割り当て
// rs      →   D7
// rw      →   GND
// enable  →   D8
// d4      →   D9
// d5      →   D10
// d6      →   D11
// d7      →   D12

// [構文]LiquidCrystal(rs, rw,  enable, d0, d1, d2, d3, d4, d5, d6, d7)

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {

  lcd.begin(16, 2);          // LCDの桁数と行数を指定する(16桁2行)
  lcd.clear();               // LCD画面をクリア

  lcd.setCursor(0, 0);       // カーソルの位置を指定(0桁0行の位置)
  lcd.print("Hello!");       // 文字の表示

  lcd.setCursor(0, 1);       // カーソルの位置を指定(0桁1行目の位置)
  lcd.print("Arduino Uno");  // 文字の表示

}

void loop() {

  lcd.display();    // 画面を表示
  delay(500);

  lcd.noDisplay();  // 画面を非表示
  delay(500);

}
