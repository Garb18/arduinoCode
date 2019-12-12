// ==========================================================
//
// IRed_Naieve Example of bad code. Loop is used to generate
// 38kHz signal, using up all CPU cycles.
//
// CBP 20-10-15
//
// ==========================================================
  
#define TxPin 11
#define RxPin 10

int Rx;

void setup() {                
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT);   
  Serial.begin(9600);
}

void loop() {
 
  for(int i=0;i<1000;i++) {
    digitalWrite(TxPin,LOW);
    delayMicroseconds(13);
    digitalWrite(TxPin,HIGH);
    delayMicroseconds(13);  
  
    Rx = digitalRead(RxPin);
  }
  
  Serial.println(Rx);
  
  delay(500);
}

