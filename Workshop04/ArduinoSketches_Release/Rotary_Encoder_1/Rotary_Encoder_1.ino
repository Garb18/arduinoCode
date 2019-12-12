// ==============================================================
// 
// Rotary Encoder 2
//
// CBP 15-10-18
//
// Status = Devel
//
// ==============================================================

//Define the pin connection
int CLK = 2;//CLK->D2
int DT = 3;//DT->D3
int SW = 4;//SW->D4
const int interrupt0 = 0;// Interrupt 0 在 pin 2 上
int count = 0;//Define the count
int lastCLK = 0;//CLK initial value
 
void setup() {
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
//  attachInterrupt(interrupt0, ClockChanged, CHANGE);//Set the interrupt 0 handler, trigger level change

  Serial.begin(9600);
}
 
void loop() {
  int clkValue = digitalRead(CLK);//Read the CLK pin level
  int dtValue = digitalRead(DT);//Read the DT pin level
  Serial.print(clkValue);
  Serial.println(dtValue);
  Serial.println(" ");
  delay(500); 
}
 
