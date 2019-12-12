// =============================================================================
//
// RTOS_Release_Susp
//
// Suspending and Resuming Tasks
// CBP 05-12-18
//
// =============================================================================

#include <Arduino_FreeRTOS.h>
#include <timers.h>

// Variables for the timer
BaseType_t xTimerStarted;
TimerHandle_t xTimer;

// Handles for vTaskSuspend(&handle);
TaskHandle_t handle1;
TaskHandle_t handle2;
TaskHandle_t handle3;

volatile bool suspendTask1;
volatile bool suspendTask2;

void setup() {  
    Serial.begin(115200);
    Serial.println(F("In Setup function")); 
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    suspendTask1 = false; // Boolean to indicate if we want to suspend MyTask1
    suspendTask2 = false;    
    // Create three tasks 
    xTaskCreate(MyTask1, "Task1", 200, NULL, 1, &handle1); // Note use of handles
    xTaskCreate(MyTask2, "Task2", 200, NULL, 1, &handle2); 
    xTaskCreate(MyTask3, "Task3", 200, NULL, 1, &handle3); 
    // Create a timer 
    xTimer = xTimerCreate("MyTimer",2000/portTICK_PERIOD_MS,pdTRUE,NULL,timerCallBack);    
    // Start the timer here. Could be done in any task.
    xTimerStarted = xTimerStart(xTimer,0);    
}

static void timerCallBack(TimerHandle_t xTimer) {
  Serial.print("SysTick = ");
  Serial.print(xTaskGetTickCount());
  Serial.println(" Timer CallBack");
  if(suspendTask1 == true) 
    suspendTask1 = false;
  else 
    suspendTask1 = true;
}

static void MyTask1(void* pvParameters){
  while(1) { // --------------------------------------
    digitalWrite(4,HIGH);
    vTaskDelay(100/portTICK_PERIOD_MS);
    digitalWrite(4,LOW);
    vTaskDelay(100/portTICK_PERIOD_MS);    
   
  }  // ----------------------------------------------
}

static void MyTask2(void* pvParameters){
  while(1) { // --------------------------------------
    digitalWrite(5,HIGH);
    vTaskDelay(100/portTICK_PERIOD_MS);
    digitalWrite(5,LOW);
    vTaskDelay(100/portTICK_PERIOD_MS);
   
  }  // ----------------------------------------------
}

static void MyTask3(void* pvParameters){
  while(1) { // --------------------------------------
    if(suspendTask1 == true)
      vTaskSuspend(handle1);
    else
      vTaskResume(handle1);    
    vTaskDelay(20/portTICK_PERIOD_MS);       
  }  // ----------------------------------------------
}

void loop() {

}
