// =============================================================
//
// TestBench2
//
// CBP 29-09-15
//
// Analogue signal (cia PWM) drive for cpt test
//
// =============================================================

int opPin = 11;
int opVal = 0;
float chipOp;
int count = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  opVal=0;
}

void loop() {
  analogWrite(opPin,opVal);
  delay(1000);
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  chipOp = analogRead(A1)*(5.0/1023.0);
  // print out the value you read:
  if(count < 30) {
    Serial.print(voltage);
    Serial.print(", ");
    Serial.println(chipOp);
  }
  //delay(1000);
  opVal += 10;
  count++;
}
