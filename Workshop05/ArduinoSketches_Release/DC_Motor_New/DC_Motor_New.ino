
#include <AFMotor.h>

AF_DCMotor motor(1);

int defaultSpeed;
int clk;
int lastCLK = 0;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  defaultSpeed = 180;
  motor.setSpeed(defaultSpeed);
  motor.run(RELEASE);
  Serial.begin(9600); 
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), ClockChanged, RISING);  
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.run(FORWARD);
  Serial.println(count);
  delay(500);
}

void ClockChanged()
{
  int clkValue = digitalRead(2);//Read the CLK pin level
    //count += (clkValue != dtValue ? 1 : -1);//CLK and inconsistent DT + 1, otherwise - 1
    count++;

}
