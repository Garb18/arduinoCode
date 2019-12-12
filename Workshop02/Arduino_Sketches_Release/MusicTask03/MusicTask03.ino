//--------------------------------------------------------------
// Pulse Width Modulation
//
// CBP 20-09-17
//
// Student Release
//
// -------------------------------------------------------------


int p;
int l;

int pitch[] = {262,262,392,392};
int Length[] = {1,1,1,1};

int nrNotes = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode (11, OUTPUT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < nrNotes; i++){
    p = pitch[i];
    l = 500*Length[i];
    
    tone(11,p); 
    delay(l);
    noTone(11);
    delay(l);
  }
}
