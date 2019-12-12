// ==========================================================
//
// HC_SR04 Ultrasonic distance measurement (2cm - 4m)
//
// CBP 14-03-15
//
// ==========================================================
  
#define TxPin 10
#define drivePin 11

int count = 0;
int pulses = 0;

void setup() {                
  pinMode(drivePin, OUTPUT); 
  pinMode(2,INPUT);  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine,RISING);  
}

void loop() {
 
  analogWrite(drivePin,count);
 // count+=10;
 count = 40;
  if(count > 255) count = 255;
  delay(500);
    Serial.println(pulses);
}

void ISRoutine(){
  pulses++;
  
}

