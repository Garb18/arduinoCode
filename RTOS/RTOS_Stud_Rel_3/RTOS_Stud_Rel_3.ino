// ======================================================
//
// RTOS_Stud_Rel_3
// CBP 25-11-17
//
// Template to allow students to explore
//
// ======================================================

#include <Arduino_FreeRTOS.h>

volatile uint32_t idleCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("In Setup function"));
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  xTaskCreate(MyTask1, "Task1", 200, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 200, NULL, 2, NULL);  
}

void loop(){
  // DO nothing
}

static void MyTask1(void* pvParameters){
  while(1) {


  }
}

static void MyTask2(void* pvParameters){
  while(1) {


  }
}

// Uncomment below if you want to look at scheduling
//void vApplicationIdleHook(void) {
//    idleCount++;
//}

