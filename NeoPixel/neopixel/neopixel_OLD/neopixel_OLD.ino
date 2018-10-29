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
  int reset_pin = 4;
  int red_pin = 6;
  int green_pin = 8;
  int blue_pin = 10;
  // Digital value
  int reset_val = 0;
  int red_val = 0;
  int green_val = 0;
  int blue_val = 0;
  // Modes
  int game_mode = 1;

void setup() {
  
  // Initialise the ring
  ring.begin();
  ring.setBrightness(neoBright); 
  ring.show();

  // Set buttons
  pinMode(red_b,INPUT);
  pinMode(green_b,INPUT);
  pinMode(blue_b,INPUT);
  pinMode(reset_b,INPUT);
}

void loop() {

  reset_val = digitalRead(reset_b_val);
  red_val = digitalRead(red_b);  
  green_val = digitalRead(green_b);
  blue_val = digitalRead(blue_b);

  if (reset_val == 1){
    toggle_game_mode();
  
  
    // Game mode 1
    if (game_mode == 1){
      8R_8G_8B();
    }
    else // Game mode 2
      8R_8G_8B_rnd();
  }

  // Turn on pixels
  if (red_b_val == 1){
    for(int i = 0; i < neoPixels; i++){
      ring.setPixelColor(i, ring.Color(0,118,189));
      ring.show();
      delay(42);
    }
  }

  if (blue_b_val == 1) {
    // Turn off pixels
    for(int i = 0; i < neoPixels; i++){
      ring.setPixelColor(i, ring.Color(0,0,0));
      ring.show();
      delay(42);
    }
  }
}





// Functions
int toggle_game_mode(){
  if (game_mode == 1)
    game_mode = 0;
  else
    game_mode = 1;
}





