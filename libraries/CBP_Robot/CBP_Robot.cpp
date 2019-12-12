//=============================================================================
//
// CBP_Robot.cpp
//
// Library for Discovery Day Robots and Comp3303
//
// 20-01-14
//
// Mods
// 17-03-14 Added moveForwardStep() and spinToRightStep() which exit by turning motors off
// 17-03-14 Reduced delay in IR sensor from 100 ms to 1 ms. Makes motors faster in moveForwardStep().
// 17-03-14 Removed Collision detection from MoveForwardStep() since State Code handles this.
// 17-03-14 spinToRightStep() now correctly implemented.
//
// 23-04-14 Removed turn off robot from moveForwardStep() etc
// 23-04-14 Major butchery of code.
// 24-04-14 Added Line sensor code
// 24-04-14 Starting to add compass code.
//
// 24-04-14	Need to check the direction of rotation of the motors. SpinRight 
// looks wrong (fix-up).
//
// 28-04-15 Hardware wiring of motor drive looks strange, assymetrical connections
// Need to review this and rationalise the code (or start again!) Nevertheless the
// student activities work fine.	
//
//=============================================================================

//#include <WProgram.h>
#include <Arduino.h>
#include <AFMotor.h>
#include "CBP_Robot.h"
//#include <HMC5883L.h>
//#include <Wire.h>

int val;
int range;
int defaultSpeed;
float currentHeading;	// in degrees. May be usful for simple move and turn cmds
float lineSensorThreshold;
HMC5883L compass;

//float FOREVER;

// motor time slicing
unsigned long startT;
unsigned long curT;
unsigned long prevT;
unsigned long curT1;
unsigned long prevT1;
unsigned long curT2;
unsigned long prevT2;

boolean firstPass1;
boolean firstPass2;

boolean collision;
boolean debug;
boolean bIsRunning;

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);

// PID variables for moveForward (F) and Rotate (R)
float Kp_F;
float Ki_F;
float Kd_F;
float e1_F,e2_F,error_F;
float u_F,du_F;
float Ts_F;
float fwdSpeed_F;

float Kp_R;
float Ki_R;
float Kd_R;
float e1_R,e2_R,error_R;
float u_R,du_R;
float Ts_R;
float fwdSpeed_R;

// =============== general functions ==========================================

// -------------------------------------------------------------
//
// Initialises robot with some reasonable parameters like speed
// and the sensor distance so studs do not need to do all of this
// initially.

// Smaller init for 2303 Nov 2015
void initRobotX() {

  debug = false;
  //debug = true;  
  bIsRunning = true;
  defaultSpeed = 180; // set max speed for movement
 // lineSensorThreshold = 100;
  //if(debug) Serial.begin(9600);          
 // if(debug) Serial.println("Motor test!");
 // pinMode(RxPin, INPUT);    
 // pinMode(TxPin, OUTPUT); 
  // turn on motor and turn off -----------------
  motorLeft.setSpeed(defaultSpeed);
  motorLeft.run(RELEASE);
  motorRight.setSpeed(defaultSpeed);
  motorRight.run(RELEASE);  
 // collision = isObstacleInRange(); //warn up collision sensor
 // collision = false;
 // setRange(30);  // default so users don't need to set
  startT = 0;
  prevT = millis();
 // firstPass1 = true;
  //firstPass2 = true;
  prevT1 = 0;
  prevT2 = 0;
  
  //Set up the compass stuff --------------------
 // Wire.begin();
 // compass = HMC5883L();
 // compass.SetScale(1.3);
 // compass.SetMeasurementMode(Measurement_Continuous);  
 // currentHeading = getHeadingInDegrees();  

}

void initRobot() {

  debug = false;
  //debug = true;  
  bIsRunning = true;
  defaultSpeed = 180; // set max speed for movement
  lineSensorThreshold = 100;
  //if(debug) Serial.begin(9600);          
 // if(debug) Serial.println("Motor test!");
  pinMode(RxPin, INPUT);    
  pinMode(TxPin, OUTPUT); 
  // turn on motor and turn off -----------------
  motorLeft.setSpeed(defaultSpeed);
  motorLeft.run(RELEASE);
  motorRight.setSpeed(defaultSpeed);
  motorRight.run(RELEASE);  
  collision = isObstacleInRange(); //warn up collision sensor
  collision = false;
  setRange(30);  // default so users don't need to set
  startT = 0;
  prevT = millis();
 // firstPass1 = true;
  //firstPass2 = true;
  prevT1 = 0;
  prevT2 = 0;
  
  //Set up the compass stuff --------------------
  Wire.begin();
  compass = HMC5883L();
  compass.SetScale(1.3);
  compass.SetMeasurementMode(Measurement_Continuous);  
  currentHeading = getHeadingInDegrees();  

}

void setDebug(boolean val) {

  if(val == true) {
	  debug = true;
    if(debug) Serial.begin(9600);          
    if(debug) Serial.println("Debug is now ON!");		
	}

}
// PID Movement Stuff =========================================================

void initMoveForwardPID(float P, float I, float D, float Tss) {
  Kp_F = P;
  Ki_F = I;
  Kd_F = D;
  Ts_F = Tss;
  error_F = 0.0;
  e1_F = 0.0;
  e2_F = 0.0;
  u_F = 0;
}

void moveForwardPID(float desiredHeading, float speed) {

  float actualHeading;
  float speedL, speedR;
  
  fwdSpeed_F = speed;

    e2_F = e1_F;
    e1_F = error_F;

    actualHeading = getHeadingInDegrees();
    error_F = desiredHeading - actualHeading;
    error_F = normalizeHeading(error_F);  
	
    du_F = Kp_F*(error_F - e1_F) + (Ki_F*Ts_F)*error_F + (Kd_F/Ts_F)*(error_F - 2*e1_F + e2_F);
    u_F += du_F;	
	
    speedL = fwdSpeed_F + u_F;
    speedR = fwdSpeed_F - u_F;      
    if(speedL > 220) speedL = 220;
    if(speedL < -220) speedL = -220;
    if(speedR > 220) speedR = 220;
    if(speedR < -220) speedR = -220;
    
    driveMotors(speedL,speedR);	

}


// ================== Sensing Functions =======================================

// Compass related stuff ------------------------------------------------------

float getHeadingInDegrees() {

  MagnetometerScaled scaled = compass.ReadScaledAxis();
  float xHeading = atan2(scaled.YAxis, scaled.XAxis);
  if(xHeading < 0)    xHeading += 2*PI;
  if(xHeading > 2*PI)    xHeading -= 2*PI;
  float xDegrees = xHeading * 180/M_PI; 
  return xDegrees;  
  
}

float normalizeHeading(float inputHead) {
  float outputHead;
  outputHead = inputHead;
  if(outputHead < -180) outputHead += 360;
  return outputHead;
}

// Line sensor related stuff --------------------------------------------------

bool checkLineSensorLeft() {
  float val;
  val = analogRead(LeftLightSensePin);
  if(val < lineSensorThreshold) return true;
  else return false;
}

float readLineSensorLeft() {
  float val;
  val = analogRead(LeftLightSensePin);
  return val;
}

bool checkLineSensorRight() {
  float val;
  val = analogRead(RightLightSensePin);
  if(val < lineSensorThreshold) return true;
  else return false;
}

float readLineSensorRight() {
  float val;
  val = analogRead(RightLightSensePin);
  return val;
}


// ================= Non-Latent functions -------------------------------------

void bearRight() {
  motorLeft.setSpeed(defaultSpeed);
  motorRight.setSpeed(defaultSpeed/2); 
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);  
}

void bearLeft() {
  motorRight.setSpeed(defaultSpeed);
  motorLeft.setSpeed(defaultSpeed/2); 
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);  
}

void bearForward() {
  motorLeft.setSpeed(defaultSpeed);
  motorRight.setSpeed(defaultSpeed); 
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);  
}

void spinClockwise(float speed) {
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(speed); 
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);  
}

void driveMotors(float speedL, float speedR) {
  motorLeft.setSpeed(abs(speedL));
  motorRight.setSpeed(abs(speedR)); 
  if(speedL > 0) motorLeft.run(FORWARD);
  else motorLeft.run(BACKWARD);
  if(speedR > 0) motorRight.run(FORWARD);
  else motorRight.run(BACKWARD);
}

// New functions for simple move forward and rotate. THIS NEEDS TO BE REPLACED. See DDA_Compass_3

void moveForwardStraight() {
  float actualHeading;
  actualHeading = getHeadingInDegrees();
  if( abs(currentHeading - actualHeading < 2.0) )
    spinClockwise(50.0);
  else
    bearForward();
}

// very simple minded. Could easily make more sophisticated.

void rotate(float angle) {

  float actualHeading;
  float desiredHeading;
  actualHeading = getHeadingInDegrees();
  currentHeading = actualHeading;
  desiredHeading = actualHeading + angle;
  if( abs(desiredHeading - actualHeading < 2.0) )
    spinClockwise(50.0);
}

void reallyStop() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);  
}

// ================= recent Latent Functions ==================================

boolean moveForwardStep(float time) { // --------------------------------------
  long interval;
  boolean bCollided;

 //if(debug) Serial.println("MoveForward enterc Y");
 
 bCollided = isObstacleInRange();
 if(bCollided) {
    motorLeft.run(RELEASE);
   motorRight.run(RELEASE);
   firstPass1 = true;
  // return true;
 }
 
 motorLeft.setSpeed(defaultSpeed);
 motorRight.setSpeed(defaultSpeed); 
 
 if(firstPass1) {
   prevT1 = millis();
   firstPass1 = false;
 }
 
 curT1 = millis();  
 interval = int(time*1000); 
 if ((curT1 - prevT1) < interval) {
   if(bIsRunning) motorLeft.run(FORWARD);
   if(bIsRunning) motorRight.run(FORWARD); 
   return false;
 //  prevT1 = curT1;
 } else {
   motorLeft.run(RELEASE);
   motorRight.run(RELEASE);
   firstPass1 = true;
   return true;
 }	 
 //if(debug) Serial.println("MoveForward exit"); 
 //if(debug) Serial.println(" ");  
}

boolean spinToRightStep(float time) { // --------------------------------------
   long interval;
   
 //  if(debug) Serial.println("spinToRight");  
 //  if(debug) Serial.println(" "); 
 
 motorLeft.setSpeed(defaultSpeed);
 motorRight.setSpeed(defaultSpeed); 
 
 if(firstPass2) {
   prevT2 = millis();
   firstPass2 = false;
 }
 
 curT2 = millis(); 
 interval = int(time*1000); 

   if ((curT2 - prevT2) < interval) {
     if(bIsRunning) motorLeft.run(FORWARD);
     if(bIsRunning) motorRight.run(BACKWARD);
//     prevT2 = curT2;
     return false;
   } else {
   motorLeft.run(RELEASE);
   motorRight.run(RELEASE);
   firstPass2 = true;
   return true;
 }	
 
  // motorLeft.run(RELEASE);
  // motorRight.run(RELEASE);    
}

void moveForwardKill() {
   motorLeft.run(RELEASE);
   motorRight.run(RELEASE);
   firstPass1 = true;
}



// ================= older functions, need to revise ==========================

// ----------------------------------------------------------------------------

void turnRight(float time) {
  long interval;
  boolean result;
 
 Serial.println("turnRight enter");
 
  motorLeft.setSpeed(defaultSpeed);
  motorRight.setSpeed(defaultSpeed/2); 
  
 prevT = millis();
 //delay(10);
 //curT = millis(); 
 curT = prevT + 10;  

 interval = int(time*1000); 
 
 //if(debug) Serial.print("turnRight interval =");
 //if(debug) Serial.println(interval);
 //if(debug) Serial.print("curT - prevT =");
 //if(debug) Serial.println(curT - prevT); 

 while ((curT - prevT) < interval) {
   
   if(bIsRunning) motorLeft.run(FORWARD);
   if(bIsRunning) motorRight.run(FORWARD);
   result = isObstacleInRange();   
 
   if(result == true) {
     if(debug) Serial.println("turnRight(): Collision Detected");
     if(debug) Serial.println(" ");  
     return;
   }   
   
   curT = millis();
 }
 
  motorLeft.setSpeed(defaultSpeed);
  motorRight.setSpeed(defaultSpeed); 
  
 if(debug) Serial.println("turnRight exit"); 
 if(debug) Serial.println(" ");   
}

// -------------------------------------------------------------
//
// Turns Left for a requested time in seconds unless the
// sensor detects an obstacle, in which case the movement is 
// aborted. Turning means driving motors at different speeds

void turnLeft(float time) {
  long interval;
  boolean result;
 
 Serial.println("turnRight enter");
 
  motorLeft.setSpeed(defaultSpeed/2);
  motorRight.setSpeed(defaultSpeed); 
  
 prevT = millis();
 //delay(10);
 //curT = millis(); 
 curT = prevT + 10;  

 interval = int(time*1000); 
 
 //if(debug) Serial.print("turnLeft interval =");
 //if(debug) Serial.println(interval);
 //if(debug) Serial.print("curT - prevT =");
 //if(debug) Serial.println(curT - prevT); 

 while ((curT - prevT) < interval) {
   
   if(bIsRunning) motorLeft.run(FORWARD);
   if(bIsRunning) motorRight.run(FORWARD);
   result = isObstacleInRange();   
 
   if(result == true) {
     if(debug) Serial.println("turnLeft(): Collision Detected");
     if(debug) Serial.println(" ");  
     return;
   }   
   
   curT = millis();
 }
 
  motorLeft.setSpeed(defaultSpeed);
  motorRight.setSpeed(defaultSpeed); 
  
 if(debug) Serial.println("turnLeft exit"); 
 if(debug) Serial.println(" ");   
 
}

// -------------------------------------------------------------
//
// Stops motion. Even though loop() is running the robot will 
// not move.



// -------------------------------------------------------------
//
// Moves forwards for a requested time in seconds unless the
// sensor detects an obstacle, in which case the movement is 
// aborted.


void moveForward(float time) {
  long interval;
  boolean result;
 
 if(debug) Serial.println("MoveForward enter X");
 
 prevT = millis();
 //delay(10);
 //curT = millis(); 
 curT = prevT + 10;  

 interval = int(time*1000); 
 
 //if(debug) Serial.print("MoveForward interval =");
 //if(debug) Serial.println(interval);
 //if(debug) Serial.print("curT - prevT =");
 //if(debug) Serial.println(curT - prevT); 

 while ((curT - prevT) < interval) {
   if(bIsRunning) motorLeft.run(FORWARD);
   if(bIsRunning) motorRight.run(FORWARD);
   result = isObstacleInRange();   
 
   if(result == true) {
     if(debug) Serial.println("MoveForward(): Collision Detected");
     if(debug) Serial.println(" ");  
     return;
   }   
   
   curT = millis();
 }
 if(debug) Serial.println("MoveForward exit"); 
 if(debug) Serial.println(" ");  
}


void moveBackward(float time) {
   if(debug) Serial.println("MoveBackward");
   if(debug) Serial.println(" ");     
   if(bIsRunning) motorLeft.run(BACKWARD);
   if(bIsRunning) motorRight.run(BACKWARD);
   delay(time*1000);
}

void setSpeed(int val) {
  if(debug) Serial.println("setSpeed");  
  if(debug) Serial.println(" ");    
  motorLeft.setSpeed(val);
//  motorLeft.run(RELEASE);
  motorRight.setSpeed(val);
//  motorRight.run(RELEASE);   
  
}

// OK Obstacle detection functions ============================================

boolean isObstacleInRange() {
  
  int measuredRange;
  int desiredRange;
  long travelTime;
  
  digitalWrite(TxPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TxPin,HIGH);
  delayMicroseconds(10);  
  digitalWrite(TxPin,LOW);  
  
 // Serial.println("isObstacleInRangeX");
 
  travelTime = pulseIn(RxPin,HIGH);
  
  measuredRange = travelTime/58;
  desiredRange = range;
  
  delay(1);
  
  //Serial.println(measuredRange);
  if(measuredRange <= desiredRange) {
    if(debug) Serial.print("Range: Collision True. Actual Range");  
    if(debug) Serial.println(measuredRange);
    if(debug) Serial.println(" ");      
    return true;
  } else 
    return false;
  
} 
// -------------------------------------------------------------

boolean obstacleDetected() {
  
  int measuredRange;
  int desiredRange;
  long travelTime;
  
  digitalWrite(TxPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TxPin,HIGH);
  delayMicroseconds(10);  
  digitalWrite(TxPin,LOW);  
  
 // Serial.println("isObstacleInRangeX");
 
  travelTime = pulseIn(RxPin,HIGH);
  
  measuredRange = travelTime/58;
  desiredRange = range;
  
  delay(100);
  
  //Serial.println(measuredRange);
  if(measuredRange <= desiredRange) {
    if(debug) Serial.print("Range: Collision True. Actual Range");  
    if(debug) Serial.println(measuredRange);
    if(debug) Serial.println(" ");      
    return true;
  } else 
    return false;
  
} 
// -------------------------------------------------------------
void setRange(int rrange) {
  if(debug) Serial.print("Range set to ");
  if(debug) Serial.println(rrange);
  if(debug) Serial.println(" ");    
  range = rrange;
} 

// ============================================================================

void halt(float time) {
  if(bIsRunning) motorLeft.run(RELEASE);
  if(bIsRunning) motorRight.run(RELEASE);  
  if(debug) Serial.print("Halt time set to ");
  if(debug) Serial.println(time);  
  if(debug) Serial.println(" ");    
  delay(1000*time); // temp
}

// -------------------------------------------------------------

void pause(float time) {
  if(bIsRunning) motorLeft.run(RELEASE);
  if(bIsRunning) motorRight.run(RELEASE);  
  if(debug) Serial.print("Pause time set to ");
  if(debug) Serial.println(time);  
  if(debug) Serial.println(" ");    
  delay(1000*time); // temp
}