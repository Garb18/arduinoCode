// ======================================================
//
// RTOS_Release_6
// CBP 22-02-18
//
// Multiple outputs to Serial. Shows Task Switching
// Shows Round Robin scheduling of equal priorities
// BUT mashes Serial output
//
// ======================================================

#include <Arduino_FreeRTOS.h>
volatile int count1 = 0;
volatile int count2 = 0;
TickType_t ticksPerSec;
int msPerTick;

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
  xTaskCreate(MyTask1, "Task1", 200, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 200, NULL, 1, NULL);  
}

void loop(){
  // DO nothing
}

static void MyTask1(void* pvParameters){
  TickType_t tickNr;
  while(1) { // --------------------------------------
    while(count1 < 100) {
        Serial.print("Task 1: ");
        tickNr = xTaskGetTickCount();
        taskENTER_CRITICAL();
        Serial.print("Tick nr ");
        Serial.print(tickNr);
        Serial.print(" Count = ");
        Serial.println(count1);
        taskEXIT_CRITICAL();
      count1++;  
    }   
  }  // ----------------------------------------------
}

static void MyTask2(void* pvParameters){
  TickType_t tickNr;  
  while(1) { // --------------------------------------
    while(count2 < 100) {
        Serial.print("Task 2: ");
        tickNr = xTaskGetTickCount();
        taskENTER_CRITICAL();
        Serial.print("Tick nr ");
        Serial.print(tickNr);
        Serial.print(" Count = ");
        Serial.println(count2);
        taskEXIT_CRITICAL();
      count2++;  
    }  
  } // ------------------------------------------------
}
