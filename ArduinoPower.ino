
/*
 * 端末が眠る場合の眠りの深さの指定
 */

//#define STANDBY_MODE SLEEP_MODE_IDLE
//#define STANDBY_MODE SLEEP_MODE_ADC
//#define STANDBY_MODE SLEEP_MODE_PWR_SAVE
//#define STANDBY_MODE SLEEP_MODE_STANDBY
#define STANDBY_MODE SLEEP_MODE_PWR_DOWN

/*
 * 各種のインクルードファイルのロード
 */
#include <avr/sleep.h>
#include <stdio.h>

unsigned long startTime;
int state;

/*
 * システム初期化関数
 */
void setup()
{
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
  }
  Serial.println(" 1 : IDLE state");
  Serial.println(" 2 : ADC state");
  Serial.println(" 3 : PWR_SAVE state");
  Serial.println(" 4 : STANDBY state");
  Serial.println(" 5 : PWR_DOWN state");
  startTime = millis();
  state=STANDBY_MODE;
}

/*
 * メインループ
 */
void loop()
{
  unsigned long now = millis();
  if ((now - startTime) > 15*1000) {
    goodNight(state);// 割込みが発生したか？
  };
  if (Serial.available() > 0) {
    int select = Serial.parseInt();
    switch (select) {
    case 1:
      Serial.println("you select IDLE state");
      state=SLEEP_MODE_IDLE;
      break;
    case 2:
      Serial.println("you select ADC state");
      state=SLEEP_MODE_ADC;
      break;
    case 3:
      Serial.println("you select PWR_SAVE state");
      state=SLEEP_MODE_PWR_SAVE;
      break;
    case 4:
      Serial.println("you select STANDBY state");
      state=SLEEP_MODE_STANDBY;
      break;
    case 5:
      Serial.println("you select PWR_DOWN state");
      state=SLEEP_MODE_PWR_DOWN;
      break;
    default:
      Serial.println("please select again");
      Serial.println(" 1 : IDLE state");
      Serial.println(" 2 : ADC state");
      Serial.println(" 3 : PWR_SAVE state");
      Serial.println(" 4 : STANDBY state");
      Serial.println(" 5 : PWR_DOWN state");
    }
  }
}

/*
 * 端末のCPUを寝かせる(低電力モードに設定する)処理
 */
void goodNight(int i) {
  Serial.println("  Good Night");
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


