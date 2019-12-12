// ==========================================================
//
// DC_Motor_Controller
// CBPrice 21-10-17
// When switch is pressed (interrupt on pin1) motor completes
// one revolution (interrupt on pin 2 to get encoder info)
//
// ==========================================================
  
#define drivePin 11
#define PULSES_PER_REV 12 // Number of segments on encoder

int speed = 40;
int pulses = 0;
boolean running = false;

void setup() {                
  pinMode(drivePin, OUTPUT); 
  pinMode(2,INPUT);  
  pinMode(1,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine1,RISING);  
 
}

void loop() {
  if(running) {


  }
  if(pulses == PULSES_PER_REV) {


  }
}

void ISRoutine1(){

}

void ISRoutine2(){

}
