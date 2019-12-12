

//#include <AFMotor.h>
//#include <WProgram.h>
#include <Arduino.h>
#include <HMC5883L.h>
#include <Wire.h>

#define TxPin A0
#define RxPin A1
#define LeftLightSensePin A2
#define RightLightSensePin A3


void turnRight(float time);
void turnLeft(float time);
void reallyStop();
void moveForward(float time);
boolean moveForwardStep(float time);
void moveBackward(float time);
void setSpeed(int val);
void spinToRight(float time);
boolean spinToRightStep(float time);
boolean isObstacleInRange();
void setRange(int rrange);
void halt(float time);
void initRobot();
void initRobotX();
void setDebug(boolean val);
void pause(float time);
boolean obstacleDetected();
void moveForwardKill();
float readLineSensorLeft();
bool checkLineSensorLeft();
float readLineSensorRight();
bool checkLineSensorRight();
void bearRight();
void bearLeft();
void bearForward();
void spinClockwise(float speed);
float getHeadingInDegrees();
void driveMotors(float speedL, float speedR);
float normalizeHeading(float inputHead);
void moveForwardPID(float desiredHeading, float speed);
void initMoveForwardPID(float P, float I, float D, float Tss);



