// ==========================================================
//
// HC_SR04_1 Ultrasonic distance measurement (2cm - 4m)
//
// CBP 07-10-19 Release
//
// ==========================================================
  
#define TxPin 10
#define RxPin 2

long travelTime;
float dist;

void setup() {                
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT);   
  Serial.begin(9600);
}

void loop() {
  ping();
  calculate();
  delay(500);
}

void ping() {
  digitalWrite(10, LOW);
  delayMicroseconds(5);
  digitalWrite(10,HIGH);
  delayMicroseconds(10);
}

void calculate() {
  travelTime = pulseIn(RxPin,HIGH);
  dist = (float)travelTime*330.0/20000.0;
  Serial.println(dist);
}
