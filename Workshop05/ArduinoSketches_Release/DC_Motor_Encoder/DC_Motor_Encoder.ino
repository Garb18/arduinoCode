// ==========================================================
//
// DC_Motor_Encoder
// CBPrice 21-10-17
// Drives motor at constant speed. Counts encoder steps
// using ISR on pin 2.
//
// ==========================================================
  
#define drivePin 11

int speed = 0;
int pulses = 0;

void setup() {                
  pinMode(drivePin, OUTPUT); 
  pinMode(2,INPUT);  
  Serial.begin(9600);


}

void loop() {

  speed = 30; // constant speed.
  analogWrite(drivePin,count);


}

void ISRoutine(){


}

