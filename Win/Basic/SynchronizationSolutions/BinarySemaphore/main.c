#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
/*
	xSemaphoreCreateBinary() : 0,1
	xSemaphoreGive() :1: up()
	xSemaphoreTake() :0: down()
*/
void func_1(void);
void func_2(void);

TaskHandle_t TASK_1 = NULL;
TaskHandle_t TASK_2 = NULL;

xSemaphoreHandle SemHandle;

unsigned int number;

int main(void) {
	SemHandle = xSemaphoreCreateBinary();

	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

	vTaskStartScheduler();
	for (;;);

}

void func_1(void) {
	TaskHandle_t tsk1;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s prints an even number : %d \n", pcTaskGetName(tsk1), number);
		number++;

		xSemaphoreGive(SemHandle);

	//	vTaskDelay(pdMS_TO_TICKS(1000)); //give semaphore (1) /1000ms 
	}
}

void func_2(void) {

	TaskHandle_t tsk2;

	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();

		xSemaphoreTake(SemHandle, portMAX_DELAY); //waiting until get the semaphore as 1. (BLOCKED if at the moment the semaphore is 0)

		printf("\n %s prints an odd number : %d \n", pcTaskGetName(tsk2), number);
		number++;
	}
}
