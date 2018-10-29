#include "SPI.h"
#include "Adafruit_WS2801.h"
#include <stdlib.h>

uint8_t dataPin  = 4;    // Green wire
uint8_t clockPin = 5;    // Blue wire
uint16_t pixels = 9;
uint8_t Left = 0;
uint8_t Right = 1;

Adafruit_WS2801 strip = Adafruit_WS2801(pixels, dataPin, clockPin);

void setup() {  
  strip.begin();
  resetLeds();
//  srand(time(NULL));
}

void loop() {
  uint8_t extraSeconds;
  uint8_t side;
  
  side = rand() % 2;
  Led_LeftRight(side);
  delay(1000);
  resetLeds();

  extraSeconds = rand() % 21;
  
  delay(2000 + extraSeconds*1000);
}


void Led_LeftRight(uint8_t side){
  int x;
  if (side == Left){
    for (x=0; x<3; x++){
      strip.setPixelColor(x, 255, 0, 0);
      strip.show();
    }
  }
  else if (side == Right){
    for (x=6; x<9; x++){
      strip.setPixelColor(x, 255, 0, 0);
      strip.show();
    }
  }
}

void resetLeds(){
  uint16_t it;

  for (it=0; it<pixels; it++){
    strip.setPixelColor(it, 0, 0, 0);
    strip.show();
  }
}


