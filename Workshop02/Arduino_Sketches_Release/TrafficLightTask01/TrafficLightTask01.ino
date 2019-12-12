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
#define REDLED 13
#define AMBERLED 12
#define GREENLED 11

void setup() {   
  pinMode (REDLED, OUTPUT);
  pinMode (AMBERLED, OUTPUT);
  pinMode (GREENLED, OUTPUT);  
}

void redBlink(){
  //Turns LED on
  digitalWrite(REDLED, HIGH);
  //0.5 second delay
  delay(10000);
  //Turns LED off
  digitalWrite(REDLED, LOW);
  //0.5 second delay
  delay(150); 
}

void amberBlink(){
  //Turns LED on
  digitalWrite(AMBERLED, HIGH);
  //0.5 second delay
  delay(2000);
  //Turns LED off
  digitalWrite(AMBERLED, LOW);
  //0.5 second delay
  delay(150); 
}

void greenBlink(){
  //Turns LED on
  digitalWrite(GREENLED, HIGH);
  //0.5 second delay
  delay(10000);
  //Turns LED off
  digitalWrite(GREENLED, LOW);
  //0.5 second delay
  delay(150); 
}

void loop() {
 redBlink();
 amberBlink();
 greenBlink(); 
 amberBlink();
}
