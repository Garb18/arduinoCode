// ======================================================
// ISR_0 Release
// CBP 06-10-19
// ======================================================

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

  if(pressed){
    digitalWrite(12, HIGH);
    delay(5000);
    digitalWrite(12, LOW);
    pressed = false;
  } else {
    digitalWrite(11,HIGH);
    delay(2000);
    digitalWrite(11,LOW);
    delay(2000);
  }
  
}

void ISRoutine() {
  digitalWrite(12,HIGH);
  digitalWrite(11,LOW);
  pressed = true;

}
