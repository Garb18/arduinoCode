// ========================================================
//
// Investigation of max speed for stepper
// CBP 22-10-17
//
// ========================================================

#include <Stepper.h>

const int stepsPerRevolution = 2048; 
 
Stepper stepperL(stepsPerRevolution, 4, 6, 5, 7);

int speed;

void setup() {

   Serial.begin(9600); 
   speed = 1;
}

// slowly rack up the speed

void loop() {
  
  stepperL.setSpeed(speed);

  Serial.print("Speed = ");
  Serial.println(speed);

} 

 
