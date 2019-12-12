// ======================================================
//
// RTOS_Stud_Rel_1
// CBP 25-11-17
//
// Blinking LEDs
//
// ======================================================

#include <Arduino_FreeRTOS.h>

void setup() {
  Serial.begin(115200); // Note the BAUD rate
  Serial.println(F("In Setup function"));
  // Usual stuff to drive the LEDs
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  // Create a task with stack=200 and priority=1
  xTaskCreate(MyTask1, "Task1", 200, NULL, 1, NULL);

  // Create a task with stack=200 and priority=1
  xTaskCreate(MyTask2, "Task2", 200, NULL, 2, NULL);
 
}

void loop(){
  // Nothing should go in here
}

// Here's the Task. Code must go inside the while loop
static void MyTask1(void* pvParameters){
  while(1) {
    // Code must go here (apart from local declarations etc)
   digitalWrite(4, HIGH);
   delay(1000);
   digitalWrite(4, LOW);
   delay(1000);
  }
}
// Here's the Task. Code must go inside the while loop
static void MyTask2(void* pvParameters){
  while(1) {
    // Code must go here (apart from local declarations etc)
   digitalWrite(5, HIGH);
   delay(500);
   digitalWrite(5, LOW);
   delay(500);
  }
}
