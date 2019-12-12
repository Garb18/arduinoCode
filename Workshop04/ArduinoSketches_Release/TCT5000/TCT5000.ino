// ============================================================
//
// TCT5000 Line Follower
//
// CBP 20-10-15
//
// Status: student release
//
// ============================================================

int val1,val2;
int diff;

void setup() {
 Serial.begin(9600); 
 
}

void loop() {

  val1 = analogRead(A0);
  val2 = analogRead(A1);
  val1 = map(val1, 0, 1023, 0.0, 10.0);
  val2 = map(val2, 0, 1023, 0.0, 10.0); 
  
  
  Serial.print(val1);
  Serial.print(" ");
  Serial.println(val2);
 
  delay(100);
  
  
  
}
