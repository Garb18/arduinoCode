void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int val1 = analogRead(A0);
 int val2 = analogRead(A1);
 Serial.println(val1-val2);
// Serial.print(" ");
// Serial.println(val2);
 delay(500);
}
