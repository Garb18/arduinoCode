// ===========================================================
//
// EOCS_GrogRxTest1a
//
// CBP 07-03-15
//
// Receives data from Arduino LinearResTest3
// Implements simple inputValluence approach to change Grog's speed
// according to position on the linear resistor
//
// ===========================================================

PImage pic;
PImage backPic;

// ............... dynamics
float locX = 00;
float locY = 200;
float velyX;
float velyY;
float time;
float dT;
int wwidth,hheight;
float inputVal;

import processing.serial.*;

Serial rxPort;
String rxString;

void setup() {
    backPic = loadImage("blank1a.jpg");  
    pic = loadImage("GrogR.png");
    wwidth = backPic.width; 
    hheight = backPic.height;
    size((int)wwidth,(int)hheight);
    dT = 0.1;
    velyX = 10.0;
    setUpSerial();
}

void draw() {
  image(backPic,0,0);
  image(pic,locX,locY);
  compute();
}

// This function computes the dynamics of Grog

void compute() {
   inputVal = readSerial();
   
   if(inputVal > 10) velyX += inputVal/10;
   if(inputVal < -10) velyX += inputVal/10;
   locX += velyX*dT;
   if(locX > wwidth) locX = 0;
   if(locX < 0) locX = wwidth;
   
   
}

// This function listens on the serial port for incoming from the
// Arduino

float readSerial() {
  
  float retVal;
 
  retVal = 0;
  if (rxPort.available() > 0) {
    rxString = rxPort.readStringUntil('\n');
    if (rxString != null) {
      print(rxString);
      retVal = float(rxString);
      print(" ");println(retVal);
    }
  }  
  return retVal;
  
}

// This function sets up a serial port to portName COM5
// You will have to change this portName

void setUpSerial() {
  String portName = Serial.list()[0];
  println(portName);
  portName = "COM22";
  rxPort = new Serial(this,portName,9600);
  rxPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  rxString = rxPort.readStringUntil('\n');
  rxString = null;   
  
}
