// =============================================================================
//
// RTOS_Stud_Devel_New_1o
//
// Software Timer
// CBP 22-02-18
//
// =============================================================================

#include <Arduino_FreeRTOS.h>
#include <timers.h>

BaseType_t xTimerStarted;
TimerHandle_t xTimer;

void setup() {  
    Serial.begin(115200);
    Serial.println(F("In Setup function")); 
    // Create a timer 
    xTimer = xTimerCreate("MyTimer",1000/portTICK_PERIOD_MS,pdTRUE,NULL,timerCallBack);    
    // Start the timer here. Could be done in any task.
    xTimerStarted = xTimerStart(xTimer,0);    
}

static void timerCallBack(TimerHandle_t xTimer) {
  Serial.print("SysTick = ");
  Serial.print(xTaskGetTickCount());
  Serial.println(" Timer CallBack");
}

void loop() {

}
