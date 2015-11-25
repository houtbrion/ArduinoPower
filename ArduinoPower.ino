
/*
 * 端末が眠る場合の眠りの深さの指定
 */
#define ACTIVE_STATE 9999
//#define STANDBY_MODE SLEEP_MODE_IDLE
#define STANDBY_MODE SLEEP_MODE_ADC
//#define STANDBY_MODE SLEEP_MODE_PWR_SAVE
//#define STANDBY_MODE SLEEP_MODE_STANDBY
//#define STANDBY_MODE SLEEP_MODE_PWR_DOWN
//#define STANDBY_MODE ACTIVE_STATE

#define THRESHOLD_LOW 15
#define THRESHOLD_HIGH 60

#define LED_PIN 13

#define ON_LED

/*
 * 各種のインクルードファイルのロード
 */
#include <avr/sleep.h>
#include <stdio.h>
#include <Time.h>

unsigned long startTime;
int state;
int threshold=THRESHOLD_LOW;

/*
 * システム初期化関数
 */
void setup()
{
#ifdef ON_LED
  pinMode(LED_PIN,OUTPUT);
#endif
  delay(5000);
  Serial.begin(9600) ;                    // シリアル通信の初期化
  Serial.println("Select standby state of Arduino within 15 sec.");
  switch (STANDBY_MODE) {
    case SLEEP_MODE_IDLE:
      Serial.println("default is IDLE state");
      break;
    case SLEEP_MODE_ADC:
      Serial.println("default is ADC state");
      break;
    case SLEEP_MODE_PWR_SAVE:
      Serial.println("default is PWR_SAVE state");
      break;
    case SLEEP_MODE_STANDBY:
      Serial.println("default is STANDBY state");
      break;
    case SLEEP_MODE_PWR_DOWN:
      Serial.println("default is PWR_DOWN state");
      break;
    case ACTIVE_STATE:
      Serial.println("default is ACTIVE_STATE state");
      break;
  }
  Serial.println(" 1 : IDLE state");
  Serial.println(" 2 : ADC state");
  Serial.println(" 3 : PWR_SAVE state");
  Serial.println(" 4 : STANDBY state");
  Serial.println(" 5 : PWR_DOWN state");
  Serial.println(" ..................");
  Serial.println(" 9 : infinite loop");
  Serial.println(" ..................");
  Serial.println(" 0 : wait 60 sec");
  startTime = now();
  state=STANDBY_MODE;
#ifdef ON_LED
  digitalWrite(LED_PIN,LOW);
#endif
}

/*
 * メインループ
 */
void loop()
{
  unsigned long currentTime = now();
  if ((currentTime - startTime) > threshold) {
    if (state==ACTIVE_STATE) {
      infinite_loop();
    } else {
      goodNight(state);// 割込みが発生したか？
    }
  };
  if (Serial.available() > 0) {
    int select = Serial.parseInt();
    switch (select) {
    case 1:
      Serial.println("you select IDLE state");
      state=SLEEP_MODE_IDLE;
      threshold=THRESHOLD_LOW;
      break;
    case 2:
      Serial.println("you select ADC state");
      state=SLEEP_MODE_ADC;
      threshold=THRESHOLD_LOW;
      break;
    case 3:
      Serial.println("you select PWR_SAVE state");
      state=SLEEP_MODE_PWR_SAVE;
      threshold=THRESHOLD_LOW;
      break;
    case 4:
      Serial.println("you select STANDBY state");
      state=SLEEP_MODE_STANDBY;
      threshold=THRESHOLD_LOW;
      break;
    case 5:
      Serial.println("you select PWR_DOWN state");
      state=SLEEP_MODE_PWR_DOWN;
      threshold=THRESHOLD_LOW;
      break;
    case 9:
      Serial.println("you select infinite loop");
      state=ACTIVE_STATE;
      threshold=THRESHOLD_LOW;
      break;
    case 0:
      threshold=THRESHOLD_HIGH;
      Serial.println(" wait 60 sec.");
      break;
    default:
      Serial.println("please select again");
      Serial.println(" 1 : IDLE state");
      Serial.println(" 2 : ADC state");
      Serial.println(" 3 : PWR_SAVE state");
      Serial.println(" 4 : STANDBY state");
      Serial.println(" 5 : PWR_DOWN state");
      Serial.println(" ..................");
      Serial.println(" 9 : infinite loop");
      Serial.println(" ..................");
      Serial.println(" 0 : wait 60 sec");
    }
  }
}

/*
 * 端末のCPUを寝かせる(低電力モードに設定する)処理
 */
void goodNight(int i) {
  //Serial.println("  Good Night");
  switch (i) {
    case SLEEP_MODE_IDLE:
      Serial.println("Arduino going down to IDLE state");
      break;
    case SLEEP_MODE_ADC:
      Serial.println("Arduino going down to ADC state");
      break;
    case SLEEP_MODE_PWR_SAVE:
      Serial.println("Arduino going down to PWR_SAVE state");
      break;
    case SLEEP_MODE_STANDBY:
      Serial.println("Arduino going down to STANDBY state");
      break;
    case SLEEP_MODE_PWR_DOWN:
      Serial.println("Arduino going down to PWR_DOWN state");
      break;
  }
  Serial.println("  Good Night");
  delay(100);
  noInterrupts();
  set_sleep_mode(i);
  sleep_enable();
  interrupts();
  sleep_cpu();
  sleep_disable();
}
/*
 * 無限ループ
 */
void infinite_loop()
{
  Serial.println("Arduino do infinite loop");
  while(1){
  }
}
