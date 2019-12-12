// ======================================================
//
// RTOS_Stud_Rel_2
// CBP 01-12-19
//
// Single Blinking LED with print-out of Idle Ticks
//
// ======================================================

#include <Arduino_FreeRTOS.h>

volatile uint32_t idleCount1 = 0;
volatile uint32_t idleCount2 = 0;
volatile uint32_t idleCount3 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("In Setup function"));
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  xTaskCreate(MyTask1, "Task1", 200, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 200, NULL, 2, NULL);
  xTaskCreate(MyTask3, "Task3", 200, NULL, 3, NULL);
}

void loop(){
  // DO nothing
}


static void MyTask1(void* pvParameters){
  while(1) {
    Serial.print("Task1 started ");
    Serial.print(" preceded by ");
    Serial.print(idleCount1);
    Serial.println(" Idle calls");
    // Reset idleCount ready for next iteration
    idleCount1 = 0;    
    digitalWrite(4,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(4,LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

static void MyTask2(void* pvParameters){
  while(1) {
    Serial.print("Task2 started ");
    Serial.print(" preceded by ");
    Serial.print(idleCount2);
    Serial.println(" Idle calls");
    // Reset idleCount ready for next iteration
    idleCount2 = 0;    
    digitalWrite(5,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(5,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}

static void MyTask3(void* pvParameters){
  while(1) {
    Serial.print("Task2 started ");
    Serial.print(" preceded by ");
    Serial.print(idleCount3);
    Serial.println(" Idle calls");
    // Reset idleCount ready for next iteration
    idleCount3 = 0;    
    digitalWrite(6,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(6,LOW);
    vTaskDelay(300/portTICK_PERIOD_MS);
  }
}

// The Idle Task calls this each iteration of the Idle loop
// Here we just count the number of times it is called.
void vApplicationIdleHook(void) {
    idleCount1++;
    idleCount2++;	
    idleCount3++;
}
