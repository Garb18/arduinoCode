// ====================================================
// Blocking
// Shows how NOT to code. Sketch tries to change the
// behaviour of a LED when a button is pressed.
// CBPrice 08-10-12 Status Release
// ====================================================

int pressed;

void setup() {
  // put your setup code here, to run once:
  pinMode(11,OUTPUT);
  pinMode(2,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  pressed = digitalRead(2);

  if(pressed){
    digitalWrite(11,LOW);
    delay(1000);
  } else {
    digitalWrite(11,HIGH);
    delay(1000);
    digitalWrite(11,LOW);
    delay(1000);
  }
}
