// ============================================================
//
// EOCS_LinearResTest3
//
// CBP 07-03-15
//
// Status: student release
//
// ============================================================

int val;

void setup() {
 Serial.begin(9600); 
}

void loop() {
  val = analogRead(A0);
  Serial.println(val);
  delay(100);
  
  
  
}


