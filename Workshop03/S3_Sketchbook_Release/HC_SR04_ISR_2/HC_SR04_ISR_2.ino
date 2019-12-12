// ==========================================================
//
// HC_SR04_ISR_2 Ultrasonic distance measurement (2cm - 4m)
// using Interrupts and FSM
// CBP 07-10-19
//
// ==========================================================
  
#define TxPin 10
#define RxPin 2

#define STATE_SEND 1
#define STATE_RISING 2
#define STATE_FALLING 3
#define STATE_DONE 4

int state = 1;
long startTime;
long endTime;
float dist;


void setup() {                
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT);   
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),ISRoutine,CHANGE);
  state = STATE_SEND;
}  


void loop() {

  switch(state) {

    case STATE_SEND:
    ping();
    state = 2;

    break;

    case STATE_DONE:
    calculate();
    state =1;
    break;
    
  }

  delay(500);

}

void calculate() {
  dist = (float)(endTime - startTime)*330.0/20000.0;
  Serial.println(dist);
}

void ping() {
  digitalWrite(10, LOW);
  delayMicroseconds(5);
  digitalWrite(10,HIGH);
  delayMicroseconds(10);
}

void ISRoutine() {

  switch(state) {
    case STATE_RISING:
      startTime = micros();
      state =3;


    break;

    case STATE_FALLING:
      endTime = micros();
      state = 4;


    break;
    
  }

}
