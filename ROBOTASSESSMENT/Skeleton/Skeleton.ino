// ==============================================================
//
// Status: Release
//
// ==============================================================

#include <AFMotor.h>
#include <CBP_Robot.h>
#include <IRremote.h>

#define TxPin 41
#define RxPin 43

//Echo travel time
long travelTime;
//Distance from object
float dist;
//Pin for recieving digital input from remote
const int RECV_PIN = 52;
//Holds rotation speed of each motor
float driveL,driveR;  
//Holds value of last remote button pressed
unsigned long key_value = 0;
//True/False based on distance to object
bool impact;

//Protocol and processing of the information from the receiver. 
IRrecv irrecv(RECV_PIN);
//Share the decoded information 
decode_results results;

void setup()// ----------------------------------------------
{ 
  Serial.begin(9600);
  //Setup pins for US sensor
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT); 
  //Enable IRIn    
  irrecv.enableIRIn();
  driveL = 0;
  driveR = 0;
}

//Move the robot based on input
void drive()// ----------------------------------------------
{
  if (irrecv.decode(&results)){
 
  if (results.value == 0XFFFFFFFF)
      results.value = key_value;          

        Serial.println(results.value, HEX);
        irrecv.resume();
        
        switch(results.value){
          
          //Stop
          case  0xFF38C7:
          driveL = 0;
          driveR = 0;
          irrecv.resume();
          break;
          
          //Forward
          case 0xFF18E7:                  
          driveL = 250;
          driveR = 250;
          irrecv.resume();          
          break;
          
          //Reverse
          case 0xFF4AB5:
          driveL = -250;
          driveR = -250;
          irrecv.resume();
          break;
          
          //Left
          case 0xFF10EF:
          driveL = 250;
          driveR = -250;          
          irrecv.resume();
          break;
          
          //Right
          case 0xFF5AA5:
          driveL = -250;
          driveR = 250;          
          irrecv.resume();
          break;
          
          //Do nothing
          default:
          irrecv.resume();  
          break;
        }
    }
}

//Calculate distance from front of robot
void distance()// ----------------------------------------------
{
  digitalWrite(TxPin,LOW);
  delayMicroseconds(5);
  digitalWrite(TxPin,HIGH);
  delayMicroseconds(10);  
  digitalWrite(TxPin,LOW);  
  
  travelTime = pulseIn(RxPin,HIGH);
  
  dist = (float)travelTime*330.0/20000.0;

}

void loop() { // ------------------------------------------------
  
  //Read sensor distance
  distance();
  
  //Read remote input and assign direction
  drive();

  //Spaghetti stopping code
  if (dist <= 40 && driveR == 250 && driveL == 250)
  {
    driveL = 0;
    driveR = 0;
    irrecv.resume(); 
  }  
  
  // Driving the motors ----------------------------
  driveMotors(driveL,driveR);
}
