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

void increment(){
  delay(500);
  duty_cycle += 10;
}


void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(11,duty_cycle);
  increment();
  if (duty_cycle >= 255){
    duty_cycle == 5;
  }
}
