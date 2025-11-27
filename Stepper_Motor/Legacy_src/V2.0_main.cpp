// sketch name = Stepper_Motor
// Outline:ステッパーモーター(ステッピングモーター)を制御する
// V1.0 ELEGOO社のスケッチをそのまま使用
//      >> ライブラリ導入 Stepper
// V2.0 参考資料2をもとにライブラリを使用しない方式に書き直した
//      >> switch caseとbreak文

#include <Arduino.h>

#define IN1 11 // Arduino PD~11 → ULN2003APG pin1 (IN1) → (OUT1) pin16 Blue
#define IN2 10 // Arduino PD~10 →            pin2 (IN2) → (OUT2) pin15 Pink
#define IN3 9  // Arduino PD~9  →            pin3 (IN3) → (OUT3) pin14 Yellow
#define IN4 8  // Arduino PD8   →            pin4 (IN4) → (OUT4) pin13 Orange

int MotorPhase = 0; // モータ内のONにする磁石を指定する。閾値0～8(0は停止)

/* ステッパーモーターを制御するために各コイルに電圧を与えるシーケンス ※１ 
  | IN | Color   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
  -----|---------|---|---|---|---|---|---|---|---|
  | 4  | Ortange | H | H |   |   |   |   |   | H |
  | 3  | Yellow  |   | H | H | H |   |   |   |   |
  | 2  | Pink    |   |   |   | H | H | H |   |   |
  | 1  | Blue    |   |   |   |   |   | H | H | H |
*/
void stepperMotor(int MotorPhase)
{
  switch (MotorPhase)
  {
  case 0:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; // switchの各caseにbreakをつけないとフォールスルーしてcase8だけが有効になる。
  case 1:
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break;
  case 2:
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break;
  case 3:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break;
  case 4:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break;
  case 5:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break;
  case 6:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    break;
  case 7:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break;
  case 8:
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break;
  }
}

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stepperMotor(MotorPhase); // モーター停止
  Serial.begin(9600);  // for debug
  Serial.println("V2.0 Start");
}

void loop()
{
  for (int MotorPhase = 1; MotorPhase < 9; MotorPhase++)
  {
    stepperMotor(MotorPhase);
    delay(10); // 5より小さくするとモーターに負荷がかかるので注意
  }
}

/* V2.0 参考資料2
  ELEGOO社の資料より
  ステッパーモーターを制御するために各コイルに電圧を与えるシーケンス
  ※１ シーケンスはスケッチ内に記載した

なかしーの電子工作部
【Arduino入門講座】ステッピングモーター #19
 https : // www.youtube.com/watch?v=VtxLILIZMEY
  ※ビットシフトするロジックが興味深く面白かったが、
    素人に対して理解できるように説明するのが難しいので、
        アレンジした。

よみや
低価格 4層5線ステッピングモーターの紹介 https : // www.youtube.com/watch?v=kK7qlKXoTs4
  ※動画が進むと早口になり聞きづらい。 スケッチの説明が足りない。スケッチ全体を例示してほしかった。
*/

/* V2.0参考 AIとのチャットで、位相を配列で定義して安定化する修正案あり。
            main.cpp の stepperMotor 関数を以下に置き換えてください。

// ...existing code...
void stepperMotor(int MotorPhase)
{
  // MotorPhase: 0 = stop, 1..8 = half-step sequence
  static const uint8_t phases[8][4] = {
    {HIGH, LOW,  LOW,  LOW }, // 1: IN1
    {HIGH, HIGH, LOW,  LOW }, // 2: IN1+IN2
    {LOW,  HIGH, LOW,  LOW }, // 3: IN2
    {LOW,  HIGH, HIGH, LOW }, // 4: IN2+IN3
    {LOW,  LOW,  HIGH, LOW }, // 5: IN3
    {LOW,  LOW,  HIGH, HIGH}, // 6: IN3+IN4
    {LOW,  LOW,  LOW,  HIGH}, // 7: IN4
    {HIGH, LOW,  LOW,  HIGH}  // 8: IN1+IN4
  };

  if (MotorPhase <= 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    return;
  }
  if (MotorPhase >= 1 && MotorPhase <= 8) {
    uint8_t idx = MotorPhase - 1;
    digitalWrite(IN1, phases[idx][0]);
    digitalWrite(IN2, phases[idx][1]);
    digitalWrite(IN3, phases[idx][2]);
    digitalWrite(IN4, phases[idx][3]);
  }
}
// ...existing code...

*/

/* V1.0 参考資料1
  ELEGOO社のコメント
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.

*/