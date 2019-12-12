// ========================================================
//
// Checks stepsPerRevolution.
// CBP 22-10-17

// Max speed around 20.
//
// ========================================================

#include <Stepper.h>

const int stepsPerRevolution = 2048; 
 
Stepper stepperL(stepsPerRevolution, 4, 6, 5, 7);

int speed;

void setup() {
  stepperL.step(stepsPerRevolution);    
    
}


void loop() {

 
} 

 
