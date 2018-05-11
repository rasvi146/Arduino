int InPin = 2;

long BreakTime = 0;
//int DataStatus = 1; //0=Avstängd, 1=Väntar på data, 2=Samplar
enum DataStatus_enum
{
  Turned_off,
  Waiting_for_data,
  Sampling
};

enum DataStatus_enum DataStatus = Waiting_for_data;
int DataPointer = 0;
long DataBuffer[100];
int Button = 0;
unsigned long lastClicked = 0;

void setup() {
  pinMode(InPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, SampleData, FALLING);
}

void loop() {
  if(DataStatus == Sampling){
    BreakTime = (micros() - DataBuffer[DataPointer-1]);
    
    if (BreakTime > 5000){
      DataStatus = Turned_off;
      Decode();
      if ((micros() - lastClicked) > 500000){  // 0.5 sec
        Serial.print("You pressed button: ");
        ButtonStr(Button);
        lastClicked = micros();
      }
      DataPointer = Turned_off;
      DataStatus = Waiting_for_data;
    }
  }
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

int ButtonStr(int Button_){

  switch(Button_){
    case 93:
      Serial.println("1");
      break;
    case 157:
      Serial.println("2");
      break;
    case 29:
      Serial.println("3");
      break;
    case 221:
      Serial.println("4");
      break;
    case 253:
      Serial.println("5");
      break;
    case 61:
      Serial.println("6");
      break;
    case 31:
      Serial.println("7");
      break;
    case 87:
      Serial.println("8");
      break;
    case 111:
      Serial.println("9");
      break;
    case 151:
      Serial.println("*");
      break;
    case 103:
      Serial.println("0");
      break;
    case 79:
      Serial.println("#");
      break;
    case 231:
      Serial.println("Up");
      break;
    case 239:
      Serial.println("Left");
      break;
    case 199:
      Serial.println("OK");
      break;
    case 165:
      Serial.println("Right");
      break;
    case 181:
      Serial.println("Down");
      break;
  }
}










