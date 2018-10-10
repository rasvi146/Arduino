// Include the Neopixel library
#include <Adafruit_NeoPixel.h>

// Declare and initialise global GPIO pin constant for Neopixel ring
const byte neoPin = 2;
// Declare and initialise global constant for number of pixels
const byte neoPixels = 24;
// Declare and initialise variable for Neopixel brightness
byte neoBright = 20;
// Create new Neopixel ring object
Adafruit_NeoPixel ring = Adafruit_NeoPixel(neoPixels, neoPin, NEO_GRB);

// Declare buttons
  // Pins
  int blackPin = 4;
  int redPin = 6;
  int greenPin = 8;
  int bluePin = 10;
  // Digital value
  int blackVal = 0;
  int redVal = 0;
  int greenVal = 0;
  int blueVal = 0;

// LEDS with # of each color {red,green,blue}
// sum is = 24
  int LEDScount[3];
  int LEDS[24]; //values represents color

// Maximum winnings (or loss)
  int maxWinnings = 10;

void setup() {
  
  // Initialise the ring
  ring.begin();
  ring.setBrightness(neoBright); 
  ring.show();

  // Set buttons
  pinMode(blackPin,INPUT);
  pinMode(redPin,INPUT);
  pinMode(greenPin,INPUT);
  pinMode(bluePin,INPUT);
}

void loop() {

  int result = 0;
  int colorBet = 0;
  int bonus = 0;
  int bet = 1;
  int won_lost_leds = 0;
  LEDScount[0] = 8;
  LEDScount[1] = 8;
  LEDScount[2] = 8;
  updateRing();

  // Light up leds, 8 of each color
  lightLEDS();

  // First phase, choose amount of colors
  while(1){
    blackVal = digitalRead(blackPin);
    redVal = digitalRead(redPin);
    greenVal = digitalRead(greenPin);
    blueVal = digitalRead(bluePin);

    if (redVal == 1 || greenVal == 1 || blueVal == 1){
      updateLEDS();
      updateRing();
      delay(250);
    }
    else if (blackVal == 1)
    {
      shuffle_LEDS();
      //updateRing();
      delay(500);
      break;
    }
  }

  // Second phase, choose color
  while(1){
    blackVal = digitalRead(blackPin);
    redVal = digitalRead(redPin);
    greenVal = digitalRead(greenPin);
    blueVal = digitalRead(bluePin);

    if (redVal == 1){
      colorBet = 1; // The integer 1 symbolises red
      break;
    }
    else if (greenVal == 1){
      colorBet = 2; // 2 symbolises green
      break;
    }
    else if (blueVal == 1){
      colorBet = 3; // 3 symbolises blue
      break;
    }
    else if (blackVal == 1){
      colorBet = rand() % 3 + 1;
      bonus = 1;
      break;
    }
  }

  // Show the color choice
  showChoice(colorBet, bonus);
  updateRing();
  delay(300);

  // Spin!
  result = spin();
  // Could have showChoice + updateRing here, as visual feedback of result

  // Show amount won/lost
  won_lost_leds = won_lost(colorBet,result, bonus);
  updateRing();

  // Click any color to count down winnings/losses and click black to start over
  count_down_the_leds(won_lost_leds);

  delay(500);
  // Click to start over
  while(1){
    blackVal = digitalRead(blackPin);
    redVal = digitalRead(redPin);
    greenVal = digitalRead(greenPin);
    blueVal = digitalRead(bluePin);

    if (redVal == 1 || greenVal == 1 || blueVal == 1 || blackVal == 1){
      delay(500);
      break;
    }
  }
}





// Functions
void lightLEDS(){
  for(int i = 0; i < neoPixels; i++){
    if (i <= 7)
      ring.setPixelColor(i, ring.Color(255,0,0)); // Red
    else if (i <= 15)
      ring.setPixelColor(i, ring.Color(0,255,0)); // Green
    else
      ring.setPixelColor(i, ring.Color(0,0,255)); // Blue
  }
  ring.show();
}

int readButtons(){
  blackVal = digitalRead(blackPin);
  redVal = digitalRead(redPin);
  greenVal = digitalRead(greenPin);
  blueVal = digitalRead(bluePin);
  if (blackVal == 1 || redVal == 1 || greenVal == 1 || blueVal == 1)
    return 1;
  else
    return 0;
}

void updateLEDS(){
  if (redVal == 1 && (LEDScount[1] > 1 || LEDScount[2] > 1)){
    LEDScount[0]++;
    if (LEDScount[1] > 1)
      LEDScount[1]--;
    else
      LEDScount[2]--;
  }
  else if (greenVal == 1 && (LEDScount[0] > 1 || LEDScount[2] > 1)){
    LEDScount[1]++;
    if (LEDScount[2] > 1)
      LEDScount[2]--;
    else
      LEDScount[0]--;
  }
  else if (blueVal == 1 && (LEDScount[0] > 1 || LEDScount[1] > 1)){
    LEDScount[2]++;
  if (LEDScount[0] > 1)
      LEDScount[0]--;
    else
      LEDScount[1]--;
  }

  // Update green LEDS
  for(int i = 0; i < LEDScount[0]; i++){
    LEDS[i] = 1;
  }

  // Update green LEDS
  for(int i = LEDScount[0]; i < LEDScount[0] + LEDScount[1]; i++){
    LEDS[i] = 2;
  }

  // Update green LEDS
  for(int i = LEDScount[0] + LEDScount[1]; i < 24; i++){
    LEDS[i] = 3;
  }
}

void updateRing(){
  // Fill LEDS
  for(int i = 0; i < 24; i++){
    if (LEDS[i] == 1)
      ring.setPixelColor(i,ring.Color(255,0,0));
    else if (LEDS[i] == 2)
      ring.setPixelColor(i,ring.Color(0,255,0));
    else if (LEDS[i] == 3)
      ring.setPixelColor(i,ring.Color(0,0,255));
    else if (LEDS[i] == 4)
      ring.setPixelColor(i,ring.Color(255,255,255));
    else 
      ring.setPixelColor(i,ring.Color(0,0,0));
  }
  ring.show();
}

void shuffle_LEDS(){
  int i = 0;
  int randomIndex;

  // Clear LEDS
  for(int i = 0; i < 24; i++)
    LEDS[i] = 0;

  // Place out red LEDS
  while(i < LEDScount[0]){
    randomIndex = rand() % 24;
    if (LEDS[randomIndex] == 0){
      LEDS[randomIndex] = 1;
      delay(100);
      updateRing();
      i++;
    }
  }
// Place out green LEDS
  while(i < LEDScount[0] + LEDScount[1]){
    randomIndex = rand() % 24;
    if (LEDS[randomIndex] == 0){
      LEDS[randomIndex] = 2;
      delay(100);
      updateRing();
      i++;
    }
  }
  // Place out blue LEDS
  while(i < 24){
    randomIndex = rand() % 24;
    if (LEDS[randomIndex] == 0){
      LEDS[randomIndex] = 3;
      delay(100);
      updateRing();
      i++;
    }
  }
}


void showChoice(int colorBet_, int bonus_){

for(int j = 0; j < 2; j++){
  if (colorBet_ == 1){ // If colorBet was red
    for(int i = 0; i < 24; i++){
      ring.setPixelColor(i,ring.Color(255,0,0));
    }
  }
  else if(colorBet_ == 2){ // If colorBet was green
    for(int i = 0; i < 24; i++){
      ring.setPixelColor(i,ring.Color(0,255,0));
    }
  }
  else{ // Otherwise it was blue
    for(int i = 0; i < 24; i++){
      ring.setPixelColor(i,ring.Color(0,0,255));
    }
  }
    ring.show();
    delay(200);
    updateRing();
    delay(200);
  }

  if (bonus_ == 1){
    for(int i = 0; i < 24; i++){
      ring.setPixelColor(i,ring.Color(255,255,255));
    }
  }
    ring.show();
    delay(200);
}


int spin(){
  int speedInv = 1;
  int steps;
  int temp_index;

  steps = rand() % 47 + 2*24;

  for(int i = rand() % 24; i < steps; i++){
    temp_index = i % 24;
    ring.setPixelColor(temp_index,ring.Color(255,255,255));
    ring.show();
    delay(40 + speedInv * i);
    updateRing();
  }

  for(int i = 0; i < 4; i++){
    ring.setPixelColor(temp_index,ring.Color(255,255,255));
    ring.show();
    delay(100);
    updateRing();
    delay(100);
  }

  if (LEDS[temp_index] == 1)
    return 1;
  else if (LEDS[temp_index] == 2)
    return 2;
  else
    return 3;
}


int won_lost(int colorBet_, int result_, int bonus_){
  double prob;
  int winnings;

  if (colorBet_ == 1)
    prob = LEDScount[0] / 24.d;
  else if (colorBet_ == 2)
    prob = LEDScount[1] / 24.d;
  else
    prob = LEDScount[2] / 24.d;

  winnings = round(1/prob) + bonus_;

  if (winnings > 10)
    winnings = 10;

  // Clear LEDS
  for(int i = 0; i < 24; i++)
    LEDS[i] = 0;


  if (colorBet_ == result_){             // Won!
    if (colorBet_ == 1){
      for(int i = 0; i < winnings; i++){
        LEDS[i] = 1;
      }
    }
    else if (colorBet_ == 2){
      for(int i = 0; i < winnings; i++){
        LEDS[i] = 2;
      }
    }
    else {
      for(int i = 0; i < winnings; i++){
        LEDS[i] = 3;
      }
    }
  }
  else{                                 // Lost
    for(int i = 0; ((i < winnings) && i < 3+bonus_); i++){
      LEDS[i] = 4;
    }
  }

}


void count_down_the_leds(int won_lost_leds_){
  int temp_led_color;
  int i = 0;


  // Wait for a button to be pressed
  while(1){
    temp_led_color = 0;
    blackVal = digitalRead(blackPin);
    redVal = digitalRead(redPin);
    greenVal = digitalRead(greenPin);
    blueVal = digitalRead(bluePin);

    if (redVal == 1 || greenVal == 1 || blueVal == 1){ // Colorbutton is pressed
      // Find where LEDS are unlit (value 0)
      while(temp_led_color != 0){
        temp_led_color = LEDS[i];
      }
      
      LEDS[i] = 0; // Change that led to unlit
      updateRing();
      i++;
      delay(250);
    }
    else if (blackVal == 1 || i == 24)     // Black button is pressed
      delay(250);
      break;
  }

}









