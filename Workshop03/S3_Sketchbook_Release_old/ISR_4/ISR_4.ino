

unsigned long previousMillis = 0;   
boolean pressed = false;
int ledState = LOW;
int ledPin = 11;
int buttPin = 2;
void setup() {
  pinMode(ledPin,OUTPUT);
  pinMode(buttPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine,RISING);
}


void loop() {
  if(pressed == true)
    off_for_time(1000);
  else
    blinker(1000);
}

void blinker(long interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }   
    digitalWrite(ledPin, ledState);
  }
}

void off_for_time(long interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    digitalWrite(ledPin, LOW);
  } 
}
void ISRoutine() {
  pressed = true;
}

