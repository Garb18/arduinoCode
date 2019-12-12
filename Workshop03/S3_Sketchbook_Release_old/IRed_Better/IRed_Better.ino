// ==========================================================
//
// IRed_Better. HArdware timer used to create 38kHz freeing
// CPU to do other tasks.
//
// CBP 20-10-15
//
// ==========================================================
  
#define TxPin 11
#define RxPin 10
#define IR_CLOCK_RATE    38000L

int Rx;

void setup() {                
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT);   
  Serial.begin(9600);
   // toggle on compare, clk/1
  TCCR2A = _BV(WGM21) | _BV(COM2A0);
  TCCR2B = _BV(CS20);
  // 36kHz carrier/timer
  OCR2A = (F_CPU/(IR_CLOCK_RATE*2L)-1); 
}

void loop() {
 
  Rx = digitalRead(RxPin);
  
  Serial.println(Rx);
  
  delay(500);
}

