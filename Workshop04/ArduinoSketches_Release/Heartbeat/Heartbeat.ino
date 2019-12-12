// ==============================================================
// 
// Heartbeat sensor
//
// CBP 15-10-18
//
// Status = Devel
//
// ==============================================================

int sensorPin = 0;
double alpha = 0.75;
int period = 100;
double change = 0.0;
double minval = 0.0;
double val;

void setup () {
  Serial.begin (9600);
}

void loop (){
    static double oldValue = 0;
    static double oldChange = 0;
 
    int rawValue = analogRead(sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
 
    //Serial.print (rawValue);
    //Serial.print (",");
    val = 10*(rawValue - value);
    if(val > 200) val = 200;
    if(val < -200) val = -200;
    Serial.println (val);
    oldValue = value;

    delay (period);
}
