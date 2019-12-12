// ============================================================
//
// EOCS_LinearResTest3
//
// CBP 07-03-15
//
// Status: student release
//
// ============================================================

unsigned long val;
int drive;

void setup() {
 Serial.begin(9600); 
 pinMode(7,INPUT);
 pinMode(11,OUTPUT);
 drive = 100;
}

void loop() {
  // drive the motor
  analogWrite(11,drive);
  
  val = pulseIn(7,HIGH);
  Serial.println(val);
  
  val = val/100;
  if(val > 0) drive = val;
  else drive = 100;
  
  
  
}


