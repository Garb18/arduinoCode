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
int CLK = 2;
int DT = 3;
int SW = 4;
int in = LOW;
int count = 0;
int lastIn = LOW;
void setup() {
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  Serial.begin(9600);
}
 
void loop() {




}
 
