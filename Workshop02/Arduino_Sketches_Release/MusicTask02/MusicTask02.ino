//--------------------------------------------------------------
// Pulse Width Modulation
//
// CBP 20-09-17
//
// Student Release
//
// -------------------------------------------------------------



int pitch;
int sense;

int A = 74;
int B =379;
int X = 440;
int Y = 1760;

void setup() {
  // put your setup code here, to run once:
  pinMode (11, OUTPUT);
  Serial.begin(9600);
  }

void note(){
  sense = analogRead(A0);
  //Change x to change the pitch
  pitch = map(sense,A,B,X,Y);  
}

void loop() {
  // put your main code here, to run repeatedly:#

  note();
  Serial.println(sense);
    
  tone(11, pitch); 
  delay(100);
  noTone(11);
  delay(100);  
}
