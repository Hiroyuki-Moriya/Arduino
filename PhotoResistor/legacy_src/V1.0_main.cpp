
// sketch name = PhotoResistor
// Outline:明るさを検知する

#include <Arduino.h>

int CDS_SOCKET = A0;

void setup() {
  Serial.begin( 9600 );
}

void loop() {
  int analog_val;
  float input_volt;
  String message = "";

  analog_val = analogRead( CDS_SOCKET );

  input_volt = float( analog_val ) * ( 5.0 / 1024.0 );
  if ( input_volt > 1.0 ){
      message = "Lighted : ";
    } else {
      message = "Dark : ";
  }
  
  Serial.print( message );
  Serial.print( input_volt );
  Serial.println( "V" );
  delay ( 500 );

}

/*
  参考
    福田和宏(著)これ1冊でできる！Arduinoではじめる電子工作 超入門 改訂第6版
    chapter5-4 P128

    Wikipediaより抜粋
      フォトレジスタ（英: photoresistor）とは、入射する光の強度が増加すると電気抵抗が低下する電子部品である。光依存性抵抗（LDR）や 光導電体、フォトセルとも呼ばれる。

      フォトレジスタは、高抵抗の半導体でできている。充分に周波数の高い光が素子に入ると、半導体に吸収された光子のエネルギーにより束縛電子が伝導帯に飛び込む。結果として生じる自由電子（と対になるホール）によって電流が流れ、電気抵抗が低くなる。

      硫化カドミウム (CdS) セルは、当たる光の量に従って抵抗値が変化する CdS の性質を利用している。セルに当たる光が多ければ、抵抗値は低くなる。シンプルな CdS セルでも、受光部が明るい時に約600Ω、暗い時に1～2MΩと、抵抗値の変化幅が広い。さらに、赤外線や可視光線や紫外線など、広範囲の波長の光に反応する。街灯を自動的にオン・オフさせるスイッチとしてよく使われている。熱追尾ミサイルで目標を探知するのに使われたこともある。低価格で、入手も容易であることから、販売店等においてもフォトレジスタという名称より「CdSセル」あるいは単に「CdS」という呼び名が一般化している
*/