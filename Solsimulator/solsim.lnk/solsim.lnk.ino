
#include "SPI.h"
#include "Adafruit_WS2801.h"
#include <DS3231.h>

uint8_t dataPin  = 2;    // Green wire
uint8_t clockPin = 3;    // Blue wire
uint16_t pixels = 17;
uint8_t wakeUpHour = 18;
uint8_t wakeUpMinute = 41;
uint8_t LED_time_limit = 30;  // LEDS will light up for 30 minutes

Adafruit_WS2801 strip = Adafruit_WS2801(pixels, dataPin, clockPin);
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
Time RTC_time;

void setup() {

              Serial.begin(9600);

    
  strip.begin();
  resetLeds(pixels);

  // Initialize the rtc object
  rtc.begin();

}

void loop() {

  // wait until it's time to light up
  while(1)
  {
    delay(30000);
    RTC_time = rtc.getTime();
    
    // CRAP STARTS HERE
    // Send Day-of-Week
      Serial.print(rtc.getDOWStr());
      Serial.print(" ");
      
      // Send date
      Serial.print(rtc.getDateStr());
      Serial.print(" -- ");
    
      // Send time
      Serial.println(rtc.getTimeStr());
    // CREP ENDS HERE

    

    if ((RTC_time.hour == wakeUpHour) && (RTC_time.min == wakeUpMinute))
    {
      myBrightness(pixels, 1000);
      break;
    }
  }

  while(1)
  {
    delay(30000);
    RTC_time = rtc.getTime();
    if ((RTC_time.hour == wakeUpHour) && ((RTC_time.min == wakeUpMinute + LED_time_limit)))
    {
      resetLeds(pixels);
      break;
    }
  }

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
    if (bright < 10)
      delay(wait*5);
    else
      delay(wait);
  }
}

void resetLeds(uint8_t pixels_){
  uint16_t it;

  for (it=0; it<pixels_; it++){
    strip.setPixelColor(it, 0, 0, 0);
    strip.show();
  }
}


