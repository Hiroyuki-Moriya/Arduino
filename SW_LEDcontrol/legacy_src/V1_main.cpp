// sketch name = SW_LEDcontor
// Switch押下でLED点滅しブザー鳴動する
// Version 1.0

/* スイッチを押下したらブザー鳴動する
   タイマー時間がゼロでなければ青LEDを毎秒点滅する
   タイマー時間が1/2超ならば緑LEDを点滅する
   タイマー時間が1/2以下かつ1/4超ならば黄LEDを点滅する
   タイマー時間が1/4以下ならば赤LEDを点滅する
   LEDが緑から黄、黄から赤に変わるときにブザー鳴動する
   タイマー時間がゼロならばブザー鳴動する
*/

#include <Arduino.h>

#define TIMER 10      // タイマー時間（秒）
int     halfTimer;    // タイマー時間の1/2
int     soonTimer;    // タイマー時間の1/4

#define BLUE_LED_PIN 11 // 青LED接続端子
#define GREEN_LED_PIN 9 // 緑LED接続端子
#define YELLOW_LED_PIN 6 // 黄LED接続端子
#define RED_LED_PIN 5 // 赤LED接続端子
#define lightingSecond 50 // 点灯時間
#define delaySecond 950 // 消灯時間

#define SPEAKER_PIN A0 // 圧電スピーカー(パッシブスピーカー)接続端子
#define ALARM_TONE 440 // アラーム音の周波数
// #define ALARM_TONE 1760 // アラーム音の周波数

#define SW_PIN A5 // スイッチ接続端子
#define SW_OFF 1  // スイッチOFFのdigitalReadの値

void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP); // タクトスイッチ（A5）をプルアップ入力に設定
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  halfTimer = TIMER / 2;
  soonTimer = TIMER / 4;
}

void loop() {
  Serial.println("スイッチを押すまで待機"); // debug
  // スイッチが押されるまで待つ
  while( digitalRead(SW_PIN) == SW_OFF ) {
  }

  Serial.println("st,青ピカ"); //debug
  tone(SPEAKER_PIN, ALARM_TONE);   // パッシブスピーカーを鳴らす
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(lightingSecond);
  digitalWrite(BLUE_LED_PIN, LOW);
  delay(delaySecond);
  noTone(SPEAKER_PIN); // パッシブスピーカーを止める

  for (int i = 0; i < TIMER; i++){          // タイマー時間だけLEDを点滅する
    int timeLeft = TIMER - i;

    if (timeLeft > halfTimer){
        Serial.print(timeLeft); // debug
        Serial.println("緑ピカ"); // debug
        digitalWrite(GREEN_LED_PIN, HIGH);  //  充分時間があるので緑LED点灯
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
       }else if(timeLeft <= halfTimer && timeLeft > soonTimer){
        Serial.print(timeLeft); // debug
        Serial.println("黄ピカ"); // debug
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, HIGH); //  残り時間半分なので黄LED点灯
        digitalWrite(RED_LED_PIN, LOW);
      }else if(timeLeft <= soonTimer && timeLeft > 0){
        Serial.print(timeLeft); // debug
        Serial.println("赤ピカ"); // debug
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);    //  残り時間1/4なので赤LED点灯
      }

    //  青LED点滅、ただしタイマー1/2または1/4はブザー鳴らす
    if(timeLeft == halfTimer || timeLeft == soonTimer){
        Serial.print(timeLeft); // debug
        Serial.println("青ピカ"); // debug
        tone(SPEAKER_PIN, ALARM_TONE);   // パッシブスピーカーを鳴らす
        digitalWrite(BLUE_LED_PIN, HIGH);
        delay(lightingSecond);
        digitalWrite(BLUE_LED_PIN, LOW);
        delay(delaySecond);
        noTone(SPEAKER_PIN); // パッシブスピーカーを止める
    }else{
        digitalWrite(BLUE_LED_PIN, HIGH);
        delay(lightingSecond);
        digitalWrite(BLUE_LED_PIN, LOW);
        delay(delaySecond);
    }
  }

  //残り時間ゼロのシーケンス
  Serial.println("全消灯"); // debug
  tone(SPEAKER_PIN, ALARM_TONE);
  delay(60);
  noTone(SPEAKER_PIN);
  delay(60);

  tone(SPEAKER_PIN, ALARM_TONE);
  delay(60);
  noTone(SPEAKER_PIN);
  delay(60);

  tone(SPEAKER_PIN, ALARM_TONE);
  delay(120);
  noTone(SPEAKER_PIN);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

/*
 参考 tool\lab.com
    Arduino入門 〜基礎編パート1〜
    https://tool-lab.com/arduino-basic-1-11/
    https://tool-lab.com/movie-arduino-basic-3/

    Arduino入門 （5）スイッチを追加する
    https://www.youtube.com/watch?v=fNV6DZtcccI&t=1280s
    https://tool-lab.com/movie-arduino-basic-5/

    Arduino入門 （6）スピーカー追加
    https://www.youtube.com/watch?v=t60KHACVg10
    https://tool-lab.com/movie-arduino-basic-6/

    Arduino入門 （7）残り時間目安の表示
    https://www.youtube.com/watch?v=ujLNQmCM-PU&t=1143s
    https://tool-lab.com/movie-arduino-basic-7/
*/

/*
#include <Arduino.h>

#define SW_PIN A5 // スイッチ接続端子
#define SW_OFF 1  // スイッチOFFのdigitalReadの値

#define BLUE_LED_PIN BLUE_LED_PIN // LED接続端子
#define LED_ON_INTERVAL   50 // LEDを点灯する時間
#define LED_OFF_INTERVAL 950 // LEDを消灯する時間


void setup() {
  // LED接続端子を出力制御にする
  pinMode(BLUE_LED_PIN, OUTPUT);

  // スイッチ接続端子をプルアップ機能有効にする
  pinMode(SW_PIN, INPUT_PULLUP);

  // スイッチが押されるまで待つ
  // （スイッチがONの間、何もしない）
  while( digitalRead(SW_PIN) == SW_OFF ) {
  }
}

void loop() {
  // LEDをONにする
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(LED_ON_INTERVAL);

  // LEDをOFFにする
  digitalWrite(BLUE_LED_PIN, LOW);
  delay(LED_OFF_INTERVAL);
}
*/
