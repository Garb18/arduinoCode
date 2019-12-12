// ==========================================================
//
// HC_SR04 Ultrasonic distance measurement (2cm - 4m)
//
// CBP 14-03-15
//
// ==========================================================
  
#define TxPin 10
#define RxPin 11

long travelTime;
float dist;

void setup() {                
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT);   
  Serial.begin(9600);
}

void loop() {
 

  
  
  
  
  
  Serial.println(dist);
  
  delay(500);
}

