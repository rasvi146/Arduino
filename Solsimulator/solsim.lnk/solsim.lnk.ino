
#include "SPI.h"
#include "Adafruit_WS2801.h"
#include <RTCZero.h>


uint8_t dataPin  = 2;    // Green wire
uint8_t clockPin = 3;    // Blue wire
uint16_t pixels = 15;

RTCZero rtc;

// Time
const byte seconds = 0;
const byte minutes = 16;
const byte hours = 21;

// Date
const byte day = 19;
const byte month = 11;
const byte year = 2017;


Adafruit_WS2801 strip = Adafruit_WS2801(pixels, dataPin, clockPin);

void setup() {
    
  strip.begin();
  rtc.begin();

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  rtc.setAlarmTime(21,18,00);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);

  rtc.attachInterrupt(alarmMatch);

  rtc.standbyMode();
}

void loop() {

  // wait until it's time to light up
  rtc.standbyMode();
  
  //myBrightness(pixels,100);
  //delay(1000);
}

void alarmMatch(){
  myBrightness(pixels, 100)
}

void myBrightness(uint8_t pixels_, uint8_t wait){
  uint16_t bright;
  uint16_t x;
  uint16_t mult;
  mult = 1;
  for (bright=1; bright<256; bright++){
    for (x=0; x<pixels_; x++){
      strip.setPixelColor(x, bright*mult, bright*mult, bright*mult);
      strip.show();
    }
    delay(wait);
  }
}

void drawSun(uint8_t pixels_, uint8_t wait){
  uint16_t it;

  for (it=0; it<pixels_; it++){
    strip.setPixelColor(it, 253, 184, 19);
    strip.show();
  }
}


