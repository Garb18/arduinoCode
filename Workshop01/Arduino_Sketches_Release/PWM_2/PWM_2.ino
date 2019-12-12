//--------------------------------------------------------------
// Pulse Width Modulation
//
// CBP 20-09-17
//
// Student Release
//
// -------------------------------------------------------------

int duty_cycle;

void setup() {
  // put your setup code here, to run once:
  pinMode(11,OUTPUT);
  duty_cycle = 128;
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(11,duty_cycle);
}
