// ====================================================
// ISR3
// Uses a Hardware Interrupt to count button presses.
// Shows that the ISR is called even during a blocking
// delaay() function.
// CBPrice 08-10-12 Status Release
// ====================================================

int count;

void setup() {
  count = 0;
  pinMode(11,OUTPUT);
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine,RISING);
}


void loop() {



}

void ISRoutine() {

}

