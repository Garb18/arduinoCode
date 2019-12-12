// ==========================================================
//
// DC_Motor_Speed_Ramp
// CBPrice 21-10-17
// Ramps up the motor speed using PWM
//
// ==========================================================
  
#define drivePin 11

int speed = 0;

void setup() {                
  pinMode(drivePin, OUTPUT); 
 
}

void loop() {
 
  analogWrite(drivePin,speed);


}


