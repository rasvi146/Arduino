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

void setup() {
  pinMode(InPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, SampleData, FALLING);
}

void loop() {
  if(DataStatus == Sampling){
    BreakTime = (micros() - DataBuffer[DataPointer-1]);
    
    if( BreakTime > 5000){
      DataStatus = Turned_off;
      Decode();
      Serial.print("You pressed button with code = ");
      Serial.println(Button);
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













