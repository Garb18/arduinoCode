//--------------------------------------------------------------
// SwitchInput
//
// CBP 15-02-15
//
// Student Release
//
// -------------------------------------------------------------

// Declare Variables

int pinLed1 = 9;
int pinSw1 = 10;

void setup() {                
  // Set pin 13 to output (pinLed1)

  // set pin 10 to input (pinSw1)
  pinMode (10, INPUT);
  pinMode (9, OUTPUT);
  Serial.begin(9600);
  }



void loop() {

int val = digitalRead(10);
int led = val;


delay(500);


Serial.println(val); 
Serial.println(led);  
}
