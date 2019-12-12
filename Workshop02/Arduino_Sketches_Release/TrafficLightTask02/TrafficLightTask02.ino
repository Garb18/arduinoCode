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
#define PINSW1 10

int mPin1Value;

void setup() {   
  pinMode (REDLED, OUTPUT);
  pinMode (AMBERLED, OUTPUT);
  pinMode (GREENLED, OUTPUT);
  pinMode (PINSW1, INPUT);
}

void redBlink(){
  //Turns LED on
  digitalWrite(REDLED, HIGH);
  //0.5 second delay
  delay(3000);
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


void loop() {
 mPin1Value = digitalRead(PINSW1);
 if (mPin1Value == HIGH){  
    digitalWrite(GREENLED, LOW);
    amberBlink();
    redBlink(); 
    amberBlink();
  }
 else if (mPin1Value == LOW){
    //Turns LED on
    digitalWrite(GREENLED, HIGH);
  };
 
 

 
 
}
