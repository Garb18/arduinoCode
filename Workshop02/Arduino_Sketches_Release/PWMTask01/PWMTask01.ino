//--------------------------------------------------------------
// Pulse Width Modulation
//
// CBP 20-09-17
//
// Student Release
//
// -------------------------------------------------------------

#define LED 11

int t_high = 1;
int t_low = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode (LED, OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(t_high);
  digitalWrite(LED, LOW);
  delay(t_low);
}
