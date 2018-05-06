
// just to have autocompletion:
int sequence;


const int button_One = // whatever that is
const int button_Two =
const int button_Three =
const int button_Four =
const int button_Five =
const int button_Six =
const int button_Seven =
const int button_Eight =
const int button_Nine =
const int button_Hashtag =
const int button_Star =
const int button_OK =
const int button_Up =
const int button_Down =
const int button_Left =
const int button_Right =

const int pixels = // whatever that is
int last_button_pressed = 0; // 0 is not a button, will only happen in initiation
int brightness = 0;
uint8_t RGB_array[3] = [1, 1, 1];



// Put this in void setup()
for (int it = 0; it<pixels; it++){
  editor_Brightness[it] = 0;
  LED_arr[it] = nothing;
}


/*
* This will be a single color function
*  red (1), green (2), blue (3) or white (OK)
* Pressing the same button again will turn LEDs on or off
*/
void sequence_Single_Color(int single_Color_Pressed){

  switch (single_Color_Pressed){
    case button_One
      RGB_array = [1, 0, 0];
      if (last_button_pressed == button_One)
        brightness = on_off();
      last_button_pressed = button_One;
      break;
    case button_Two
      RGB_array = [0, 1, 0];
      if (last_button_pressed == button_Two)
        brightness = on_off();
      last_button_pressed = button_Two;
      break;
    case button_Three
      RGB_array = [0, 0, 1];
      if (last_button_pressed == button_Three)
        brightness = on_off();
      last_button_pressed = button_Three;
      break;
    case button_OK:
      RGB_array = [1, 1, 1];
      if (last_button_pressed == button_OK)
        brightness = on_off();
      last_button_pressed = button_OK;
      break;
  } /* switch */

  render_LEDs();
}

/*
* This function will only adjust brightness
*/
void sequence_Up_Down(int Up_Down){

  switch (Up_Down_Pressed){
    case button_Up:
      last_button_pressed = button_Up;
      if (brightness <= 160)
        brightness += 40;
      else if ((brightness >= 200) && (brightness < 256))
        brightness = 256;
      else
        brightness = 0;
      break;
    case button_Down:
      last_button_pressed = button_Down;
      if (brightness == 256)
        brightness = 200;
      else if (brightness >= 0)
        brightness = 256;
      else
        brightness -= 40;
      break;
  }

  render_LEDs();
}

/*
* Turn the LEDs on or off?
* (will implementwise adjust brightness)
*/
int on_off(){
  if (brightness == 0)
    return 160;
  else
    return 0;
}


/* special sequence */
void sequence_Four(){
  last_button_pressed = button_Four;

  for (uint8_t it_out = 0; it_out<pixels; it_out++){

    for (uint8_t it=0; it<pixels_; it++){
      strip.setPixelColor(it, brightness, brightness, brightness);
      strip.show();
    }
  }
}



/*
* Render the current/chosen LEDs (RGB_array)
*  with the current/chosen brightness
*/
void render_LEDs(){
  for (uint8_t it=0; it<pixels_; it++){
    strip.setPixelColor(it, brightness*RGB_array[0], brightness*RGB_array[1], brightness*RGB_array[2]);
    strip.show();
  }
}











/**************************************************************/
/****************************EDITOR****************************/
/**************************************************************/


bool edit_Mode = false;
uint8_t current_i = 0;
int editor_Brightness[pixels];
enum single_Color_Enum{
  nothing,
  red,
  green,
  blue,
  white
};
uint8_t LED_arr[single_Color_Enum];






/*
* This function will start
*  edit LEDs mode
*/
void sequence_Hashtag(){
  last_button_pressed = button_Hashtag;

  edit_Mode = true;
}

/*
* This function will end
*  edit LEDs mode
*/
void sequence_Star(){
  last_button_pressed = button_Star;

  edit_Mode = false;
}

void sequence_Left(){
  last_button_pressed = button_Left;

  if ((edit_Mode == false) && (current_i <= 0))
    return;
  else
    current_i--;

  render_LEDs_Editor();
}

void sequence_Right(){
  last_button_pressed = button_Right;

  if ((edit_Mode == false) && (current_i >= pixels-1))
    return;
  else
    current_i++;

  render_LEDs_Editor();
}

void render_LEDs_Editor(){

  for (uint8_t it=0; it<pixels_; it++){
    switch(LED_arr[it]){
      case nothing:
        RGB_array = [0, 0, 0];
        break;
      case red:
        RGB_array = [1, 0, 0];
        break;
      case green:
        RGB_array = [0, 1, 0];
        break;
      case blue:
        RGB_array = [0, 0, 1];
        break;
      case white:
        RGB_array = [1, 1, 1];
        break;
    }/* switch */

    strip.setPixelColor(it, editor_Brightness[it]*RGB_array[0], editor_Brightness[it]*RGB_array[1], editor_Brightness[it]*RGB_array[2]);
    strip.show();
  }
}





void editor_Single_Color(){

  switch (single_Color_Pressed){
    case button_One
      LED_arr[current_i] = red;
      if (last_button_pressed == button_One)
        editor_Brightness[current_i] = on_off();
      last_button_pressed = button_One;
      break;
    case button_Two
      LED_arr[current_i] = green;
      if (last_button_pressed == button_Two)
        editor_Brightness[current_i] = on_off();
      last_button_pressed = button_Two;
      break;
    case button_Three
      LED_arr[current_i] = blue;
      if (last_button_pressed == button_Three)
        editor_Brightness[current_i] = on_off();
      last_button_pressed = button_Three;
      break;
    case button_OK:
      LED_arr[current_i] = white;
      if (last_button_pressed == button_OK)
        editor_Brightness[current_i] = on_off();
      last_button_pressed = button_OK;
      break;
  } /* switch */

  render_LEDs_Editor();
}

void editor_Up_Down(int Up_Down){

  switch (Up_Down_Pressed){
    case button_Up:
      last_button_pressed = button_Up;
      if (editor_Brightness[current_i] <= 160)
        editor_Brightness[current_i] += 40;
      else if ((editor_Brightness[current_i] >= 200) && (editor_Brightness[current_i] < 256))
        editor_Brightness[current_i] = 256;
      else
        editor_Brightness[current_i] = 0;
      break;
    case button_Down:
      last_button_pressed = button_Down;
      if (editor_Brightness[current_i] == 256)
        editor_Brightness[current_i] = 200;
      else if (editor_Brightness[current_i] >= 0)
        editor_Brightness[current_i] = 256;
      else
        editor_Brightness[current_i] -= 40;
      break;
  }

  render_LEDs_Editor();
}