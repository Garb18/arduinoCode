// =============================================================
//
// EOCS_CapTest2
//
// CBP 08-03-15
//
// Capacitive Touch sensor on Arduino digi pin 2
// Status: student release
//
// ==============================================================

int val;

void setup() {
 Serial.begin(9600); 
}

void loop() {
  val = sensePad();
  Serial.println(val);
  delay(50);
}

int sensePad() {
  
  uint8_t cycles;
  // Write your code underneath here ---------------------------
  
  return cycles;
  
}
