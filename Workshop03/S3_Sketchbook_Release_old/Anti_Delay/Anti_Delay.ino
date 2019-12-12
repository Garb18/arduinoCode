// ====================================================
// Anti_Delay
// Shows how to get a delay without blocking the CPU
// CBPrice 08-10-12 Status Release
// ====================================================

int ledPin =  11;

int ledState = LOW;   
unsigned long previousMillis_blinker = 0;        
int interval = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  blinker();
}

void blinker() {
  
  unsigned long currentMillis_blinker = millis();

  if (currentMillis_blinker - previousMillis_blinker >= interval) {
    previousMillis_blinker = currentMillis_blinker;    
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }    
    digitalWrite(ledPin, ledState);
  }
}


