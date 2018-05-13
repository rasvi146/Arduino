#include "SPI.h"
#include "Adafruit_WS2801.h"


// IR-receiver items
int InPin = 2;
long BreakTime = 0;

//0=Avstängd, 1=Väntar på data, 2=Samplar
enum DataStatus_enum{
  Turned_off,
  Waiting_for_data,
  Sampling
};

// LED-pins
uint8_t dataPin = 4;
uint8_t clockPin = 5;
const uint8_t pixels = 9;

// Buttons decoded int-value
const int button_One = 93;
const int button_Two = 157;
const int button_Three = 29;
const int button_Four = 221;
const int button_Five = 253;
const int button_Six = 61;
const int button_Seven = 31;
const int button_Eight = 87;
const int button_Nine = 111;
const int button_Zero = 103;
const int button_Star = 151;
const int button_Hashtag = 79;
const int button_OK = 199;
const int button_Up = 231;
const int button_Down = 181;
const int button_Left = 239;
const int button_Right = 165;

int last_button_pressed = 0; // 0 is not a button, will only happen in initiation
int brightness = 0;
uint8_t RBG_arr[3] = {1, 1, 1};

/**************************************************************/
/****************************EDITOR****************************/
/**************************************************************/

bool edit_Mode = false;
uint8_t current_i = 0;
int editor_Brightness[pixels];
enum single_Color_Enum{
  nothing,
  red,
  blue,
  green,
  white
};
single_Color_Enum LED_arr[pixels];

// LED-strip item
Adafruit_WS2801 strip = Adafruit_WS2801(pixels, dataPin, clockPin);

// IR reader
enum DataStatus_enum DataStatus = Waiting_for_data;
int DataPointer = 0;
long DataBuffer[100];
int Button = 0;
unsigned long lastClicked = 0;

// Environmentally friendly
const unsigned long timer_Off = 8388608; // (= 2^9) millisecs is about 140 minutes
bool turned_Off = false;

void setup() {
  pinMode(InPin, INPUT);
  attachInterrupt(0, SampleData, FALLING);

  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  editor_Reset_LEDs();
}

void loop() {
  if(DataStatus == Sampling){
    BreakTime = (micros() - DataBuffer[DataPointer-1]);
    
    if (BreakTime > 5000){
      DataStatus = Turned_off;
      Decode();
      if ((millis() - lastClicked) > 500){// This will prevent clicks within 0.5 secs
        ChooseSequence(Button);
        lastClicked = millis();
        turned_Off = false;
      }
      DataPointer = Turned_off;
      DataStatus = Waiting_for_data;
    }
  }

  // Will cause LEDs to turn off
  if (((millis()-lastClicked) > timer_Off) && (turned_Off == false)){
    reset_LEDs();
    turned_Off = true;
  }
  else if (millis() < lastClicked) // millis()-function rolled over
    lastClicked = 0;
}

void reset_LEDs(){
  for (int it = 0; it<pixels; it++){
    strip.setPixelColor(it, 0, 0, 0);
    strip.show();
  }
}

void editor_Reset_LEDs(){
  for (int it = 0; it<pixels; it++){
    editor_Brightness[it] = 0;
    LED_arr[it] = nothing;
    strip.setPixelColor(it, 0, 0, 0);
    strip.show();
  }
  current_i = 0;
}

void Decode(){
  Button = 0;
  
  for (int i=35; i <= 35+15; i=i+2){
  
    Button = Button << 1;
    
    if(DataBuffer[i + 1] - DataBuffer[i] < 1100){
      Button = Button | 1;
    }
  }
}

void SampleData() {
  if(DataStatus == 0){
    return;
  }
  
  DataBuffer[DataPointer] = micros();
  DataPointer ++;
  
  do{}
    while (digitalRead(InPin) == 0);
    DataBuffer[DataPointer] = micros();
    DataPointer ++;
    DataStatus = Sampling;
}

/*
* A button is clicked!
*/
void ChooseSequence(int Button_){
  switch(Button_){
    case button_One:
      if (edit_Mode)
        editor_Single_Color(Button_);
      else
        sequence_Single_Color(Button_);
      break;
    case button_Two:
      if (edit_Mode)
        editor_Single_Color(Button_);
      else
        sequence_Single_Color(Button_);
      break;
    case button_Three:
      if (edit_Mode)
        editor_Single_Color(Button_);
      else
        sequence_Single_Color(Button_);
      break;
    case button_Four:
      if (edit_Mode)
        editor_Single_Color(Button_);
      else
        sequence_Single_Color(Button_);
      break;
    case button_Five:
      break;
    case button_Six:
      break;
    case button_Seven:
      break;
    case button_Eight:
      break;
    case button_Nine:
      break;
    case button_Star:
      sequence_Star();
      break;
    case button_Zero:
      sequence_Zero();
      break;
    case button_Hashtag:
      if (edit_Mode)
        sequence_Hashtag();
      break;
    case button_Up:
      if (edit_Mode)
        editor_Up_Down(Button_);
      else
        sequence_Up_Down(Button_);
      break;
    case button_Left:
      sequence_Left();
      break;
    case button_OK:
      if (edit_Mode)
        editor_Single_Color(Button_);
      else
        sequence_Single_Color(Button_);
      break;
    case button_Right:
      sequence_Right();
      break;
    case button_Down:
      if (edit_Mode)
        editor_Up_Down(Button_);
      else
        sequence_Up_Down(Button_);
      break;
  }
}


/*
* This will be a single color function
*  red (1), green (2), blue (3) or white (OK)
* Pressing the same button again will turn LEDs on or off
*/
void sequence_Single_Color(int single_Color_Pressed){

  switch (single_Color_Pressed){
    case button_One:
      RBG_arr[0] = 1;
      RBG_arr[1] = 0;
      RBG_arr[2] = 0;
      brightness = on_off(single_Color_Pressed);
      last_button_pressed = button_One;
      break;
    case button_Two:
      RBG_arr[0] = 0;
      RBG_arr[1] = 1;
      RBG_arr[2] = 0;
      brightness = on_off(single_Color_Pressed);
      last_button_pressed = button_Two;
      break;
    case button_Three:
      RBG_arr[0] = 0;
      RBG_arr[1] = 0;
      RBG_arr[2] = 1;
      brightness = on_off(single_Color_Pressed);
      last_button_pressed = button_Three;
      break;
    case button_OK:
      RBG_arr[0] = 1;
      RBG_arr[1] = 1;
      RBG_arr[2] = 1;
      brightness = on_off(single_Color_Pressed);
      last_button_pressed = button_OK;
      break;
  } /* switch */

  render_LEDs();
}

void sequence_Zero(){
  last_button_pressed = button_Zero;
  
  if (edit_Mode)
    editor_Reset_LEDs();
  else
    reset_LEDs();
}

/*
* This function will only adjust brightness
*/
void sequence_Up_Down(int Up_Down_Pressed){

  switch (Up_Down_Pressed){
    case button_Up:
      last_button_pressed = button_Up;
      if (brightness == 255)
        brightness = 0;
      else if (brightness == 200)
        brightness = 255;
      else
        brightness += 40;
      break;
    case button_Down:
      last_button_pressed = button_Down;
      if (brightness == 0)
        brightness = 255;
      else if (brightness == 255)
        brightness = 200;
      else
        brightness -= 40;
      break;
  }
  render_LEDs();
}


/*
* Turn the LED(s) on or off?
* (will implementwise adjust brightness)
*/
int on_off(int button_pressed){

  if (edit_Mode){
    if (editor_Brightness[current_i] == 0)
      return 120;
    else if (button_pressed == last_button_pressed)
      return 0;
    else
      return editor_Brightness[current_i];
  }
  else{
    if (brightness == 0)
      return 120;
    else if (button_pressed == last_button_pressed)
      return 0;
    else
      return brightness;
  }
}


/*
* Render the current/chosen LEDs (RBG_arr)
*  with the current/chosen brightness
*/
void render_LEDs(){
  for (uint8_t it=0; it<pixels; it++){
    strip.setPixelColor(it, brightness*RBG_arr[0], brightness*RBG_arr[1], brightness*RBG_arr[2]);
    strip.show();
  }
}


/**************************************************************/
/****************************EDITOR****************************/
/**************************************************************/

void editor_Single_Color(int single_Color_Pressed){

  switch (single_Color_Pressed){
    case button_One:
      LED_arr[current_i] = red;
      editor_Brightness[current_i] = on_off(single_Color_Pressed);
      last_button_pressed = button_One;
      break;
    case button_Two:
      LED_arr[current_i] = green;
      editor_Brightness[current_i] = on_off(single_Color_Pressed);
      last_button_pressed = button_Two;
      break;
    case button_Three:
      LED_arr[current_i] = blue;
      editor_Brightness[current_i] = on_off(single_Color_Pressed);
      last_button_pressed = button_Three;
      break;
    case button_OK:
      LED_arr[current_i] = white;
      editor_Brightness[current_i] = on_off(single_Color_Pressed);
      last_button_pressed = button_OK;
      break;
  } /* switch */

  render_LEDs_Editor();
}


/*
* Render the editor chosen LEDS
*/
void render_LEDs_Editor(){

  for (uint8_t it=0; it<pixels; it++){
    switch(LED_arr[it]){
      case nothing:
        RBG_arr[0] = 0;
        RBG_arr[1] = 0;
        RBG_arr[2] = 0;
        break;
      case red:
        RBG_arr[0] = 1;
        RBG_arr[1] = 0;
        RBG_arr[2] = 0;
        break;
      case blue:
        RBG_arr[0] = 0;
        RBG_arr[1] = 1;
        RBG_arr[2] = 0;
        break;
      case green:
        RBG_arr[0] = 0;
        RBG_arr[1] = 0;
        RBG_arr[2] = 1;
        break;
      case white:
        RBG_arr[0] = 1;
        RBG_arr[1] = 1;
        RBG_arr[2] = 1;
        break;
    }/* switch */

    strip.setPixelColor(it, editor_Brightness[it]*RBG_arr[0], editor_Brightness[it]*RBG_arr[1], editor_Brightness[it]*RBG_arr[2]);
    strip.show();
  }
}

/*
* This function will start
*  edit LEDs mode
*/
void sequence_Star(){
  last_button_pressed = button_Star;

  edit_Mode = true;
}

/*
* This function will end
*  edit LEDs mode
*/
void sequence_Hashtag(){
  last_button_pressed = button_Hashtag;

  edit_Mode = false;
}

/*
* Change the current LED one step left
*/
void sequence_Left(){
  last_button_pressed = button_Left;

  if ((edit_Mode == false) || (current_i <= 0))
    return;
  else
    current_i--;

  render_LEDs_Editor();
}

/*
* Change the current LED one step right
*/
void sequence_Right(){
  last_button_pressed = button_Right;

  if ((edit_Mode == false) || (current_i >= pixels-1))
    return;
  else
    current_i++;

  render_LEDs_Editor();
}

/*
* This function allows the user to
*  choose the brightness of the current LED
*/
void editor_Up_Down(int Up_Down_Pressed){
  switch (Up_Down_Pressed){
    case button_Up:
      last_button_pressed = button_Up;
      if (editor_Brightness[current_i] <= 160)
        editor_Brightness[current_i] += 40;
      else if ((editor_Brightness[current_i] >= 200) && (editor_Brightness[current_i] < 255))
        editor_Brightness[current_i] = 255;
      else
        editor_Brightness[current_i] = 0;
      break;
    case button_Down:
      last_button_pressed = button_Down;
      if (editor_Brightness[current_i] == 255)
        editor_Brightness[current_i] = 200;
      else if (editor_Brightness[current_i] <= 0)
        editor_Brightness[current_i] = 255;
      else
        editor_Brightness[current_i] -= 40;
      break;
  }
  render_LEDs_Editor();
}







