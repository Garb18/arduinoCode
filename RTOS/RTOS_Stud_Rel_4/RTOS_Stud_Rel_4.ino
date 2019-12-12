// ======================================================
//
// RTOS_Stud_Rel_4
// CBP 24-11-17
//
// Plotting out running, blocked and Idle Task
// Task1 increments and outputs the value of "i" and
// Task2 increments and outputs the value of "j". Both
// increments happen on each call to the Tasks
//
// ======================================================

#include <Arduino_FreeRTOS.h>

volatile uint32_t idleCount = 0;
volatile uint32_t i = 0;
volatile uint32_t j = 0;
volatile uint32_t k = 0;
volatile uint32_t calc;

TickType_t ticksPerSec;

void setup() {
  Serial.begin(115200);
  Serial.println(F("In Setup function"));
  ticksPerSec = 1000/portTICK_PERIOD_MS;
  Serial.print("Ticks per sec = ");
  Serial.println(ticksPerSec);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  xTaskCreate(MyTask1, "Task1", 200, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 200, NULL, 1, NULL);
}

void loop(){
  // DO nothing
}

void vApplicationIdleHook(void) {
    idleCount++;
}

static void MyTask1(void* pvParameters){
  TickType_t startTicks;
  TickType_t endTicks;
  while(1) {
    startTicks = xTaskGetTickCount();
    Serial.print("SysTick = ");
    Serial.print(xTaskGetTickCount());
    Serial.print(" Task1 called i = ");
    Serial.print(i);
    Serial.print(" preceded by ");
    Serial.print(idleCount); 
    Serial.print(" = Idle calls approx ");
    calc = (uint32_t)((double)idleCount*22.0/168477.0);
    Serial.print(calc);
    idleCount = 0;       
    Serial.println(" Ticks");
    // Now do some 'real' work, burn up some CPU cycles
    i++;
    k=0;
    while(k < 100000) k++;
    k=0;
    Serial.print("SysTick = ");
    Serial.print(xTaskGetTickCount());    
    Serial.println(" Task1 entering blocking state ");
    vTaskDelay(pdMS_TO_TICKS(161292/100));
    Serial.print("SysTick = ");
    Serial.print(xTaskGetTickCount());    
    Serial.print(" Task1 leaving blocking state");    
    endTicks = xTaskGetTickCount();    
    Serial.print(" Ticks for Task1 = ");
    Serial.println(endTicks - startTicks);
  }
}

static void MyTask2(void* pvParameters){
  TickType_t startTicks;
  TickType_t endTicks;
  while(1) {
    startTicks = xTaskGetTickCount();
    Serial.print("SysTick = ");
    Serial.print(xTaskGetTickCount());    
    Serial.print(" Task2 called j = ");
    Serial.print(j);
    Serial.print(" preceded by ");
    Serial.print(idleCount);
    Serial.print(" = Idle calls approx ");
    calc = (uint32_t)((double)idleCount*22.0/168477.0);
    Serial.print(calc);
    idleCount = 0;       
    Serial.println(" Ticks");    
    // Now do some 'real' work burn up some CPU cycles
    j++;
    k=0;
    while(k < 100000) k++;
    k=0;
    Serial.print("SysTick = ");
    Serial.print(xTaskGetTickCount());
    Serial.println(" Task2 entering blocking state ");
    vTaskDelay(pdMS_TO_TICKS(161292/100));
    Serial.print("SysTick = ");
    Serial.print(xTaskGetTickCount());    
    Serial.print(" Task2 leaving blocking state ");    
    endTicks = xTaskGetTickCount();    
    Serial.print(" Ticks for Task2 = ");
    Serial.println(endTicks - startTicks);
  }
}
