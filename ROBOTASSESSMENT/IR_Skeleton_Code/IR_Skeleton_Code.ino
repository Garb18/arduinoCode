// ==============================================================
// 
// IR_Obstacle_Sensor
//
// CBP 15-10-18
//
// Status = Devel
//
// ==============================================================

int Led=13;//define LED 
int buttonpin=3; //define switch port
int  val;//define digital variable val

void  setup(){
pinMode(Led,OUTPUT);//define LED as a output port
pinMode(buttonpin,INPUT);//define switch as a output port
Serial.begin(9600);
}

void  loop() { 
  val=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val 
  Serial.println(val);
  if(val==HIGH) {
    digitalWrite(Led,HIGH);
  }else{
    digitalWrite(Led,LOW);
  }
  delay(100);
}
