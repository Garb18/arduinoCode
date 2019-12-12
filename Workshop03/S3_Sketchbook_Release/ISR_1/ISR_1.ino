// ======================================================
// ISR_1 FSM Approach Release
// CBP 06-10-19
// ======================================================

#define STATE_PRESSED 1
#define STATE_RELEASED 2

int state = 2;
bool pressed;

void setup() {
  // put your setup code here, to run once:
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine,CHANGE);

}

void loop() {
  //The following line is the INCORRECT way of doing things
  //pressed = digitalRead(2);


  switch(state){

    case STATE_RELEASED:    
    delay(2000);
    digitalWrite(11, HIGH);
    delay(2000);
    digitalWrite(11, LOW);
     
    break;

    case STATE_PRESSED:
    digitalWrite(12,HIGH);
    delay(5000);
    digitalWrite(12,LOW); 
    state= 2;
    
    break;
  }
  
}

void ISRoutine() {
    digitalWrite(12,HIGH);
    digitalWrite(11,LOW);
    state = 1;

}
