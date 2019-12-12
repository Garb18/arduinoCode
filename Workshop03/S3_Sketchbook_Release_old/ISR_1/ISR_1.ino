// ====================================================
// ISR1
// Uses a Hardware Interrupt to change the behaviour of
// a LED.
// CBPrice 08-10-12 Status Release
// ====================================================

bool pressed;

void setup() {
  pinMode(11,OUTPUT);
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine,CHANGE);
}


void loop() {

  if(pressed){

  } else {

  }
}

void ISRoutine() {
    pressed = true;
}
