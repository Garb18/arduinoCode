//--------------------------------------------------------------
//
// BlinkingLight
//
// CBP 15-02-15
//
// Stud Release.
//
// -------------------------------------------------------------

// Declare Variables
int pinLed1;

void setup() {              
  pinLed1 = 13;
  pinMode (pinLed1, OUTPUT);
  
}

void loop() {
  //Turns LED on
  digitalWrite(pinLed1, HIGH);
  //0.5 second delay
  delay(500);
  //Turns LED off
  digitalWrite(pinLed1, LOW);
  //0.5 second delay
  delay(500);  
  
}
