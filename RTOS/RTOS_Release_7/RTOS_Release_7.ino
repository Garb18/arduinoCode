// ======================================================
//
// RTOS_Release_7
// CBP 22-02-18
//
// Another mutex example this time protecting a shared
// variable. The value of sum should be zero.
// Task1 increments sum Task2 decrements sum and Task3
// prints out sum.
//
// ======================================================

#include <Arduino_FreeRTOS.h>

TickType_t ticksPerSec;
float msPerTick;
TaskHandle_t handle1;
TaskHandle_t handle2;
TaskHandle_t handle3;
volatile int32_t sum = 0;
volatile boolean done1 = false;
volatile boolean done2 = false;

void setup() {
  Serial.begin(250000);
  Serial.println(F("In Setup function"));
  ticksPerSec = 1000/portTICK_PERIOD_MS;
  Serial.print("Ticks per sec = ");
  Serial.println(ticksPerSec); 
  msPerTick = 1000/ticksPerSec;
  Serial.print("Millisec/tick = ");
  Serial.println(msPerTick);    
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  // Create two tasks 
  xTaskCreate(MyTask1, "Task1", 200, NULL, 1, &handle1);
  xTaskCreate(MyTask2, "Task2", 200, NULL, 1, &handle2); 
  xTaskCreate(MyTask3, "Task3", 200, NULL, 1, &handle3);

  sum = 0;
}

void loop(){
  // DO nothing
}

static void MyTask1(void* pvParameters){
  while(1) { // --------------------------------------
    for(int i=0;i<10000;i++) {
      sum = sum + 1;
    }
    done1 = true;
    vTaskSuspend(NULL);
  }  // ----------------------------------------------
}

static void MyTask2(void* pvParameters){
  while(1) { // --------------------------------------
    for(int i=0;i<10000;i++) {
      sum = sum - 1;
    }
    done2 = true;
    vTaskSuspend(NULL);  
  }  // ----------------------------------------------
}

static void MyTask3(void* pvParameters){
  while(1) { // --------------------------------------
    if( done1 && done2) {
      Serial.print("Task3 Sum = "); Serial.println(sum);
      sum = 0;
      vTaskDelay(1000/portTICK_PERIOD_MS);     
    }
    vTaskResume(handle1);
    vTaskResume(handle2);

  }  // ----------------------------------------------
}
