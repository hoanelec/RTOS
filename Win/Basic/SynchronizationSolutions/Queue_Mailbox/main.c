#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
/*
	xQueueCreate()
	xQueueSend()
	xQueueReceive()
*/
void func_1(void);
void func_2(void);

TaskHandle_t TASK_1 = NULL;
TaskHandle_t TASK_2 = NULL;

xQueueHandle QueueHandle;

unsigned int number;

int main(void) {
	QueueHandle = xQueueCreate(5, sizeof(int));//array with 5 elements

	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
	for (;;);

}

void func_1(void) {
	TaskHandle_t tsk1;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();

		if (xQueueSend(QueueHandle, &number, portMAX_DELAY) == pdPASS){//If the data isn't written, waiting.
			
			printf("\n %s sent %d, Free: %d \n", pcTaskGetName(tsk1), number, uxQueueSpacesAvailable(QueueHandle));
			number++;
		}
		else {
			printf("%s sent failed", pcTaskGetName(tsk1));
		}

	//	vTaskDelay(pdMS_TO_TICKS(1000)); //give semaphore (1) /1000ms 
	}
}

void func_2(void) {

	TaskHandle_t tsk2;
	unsigned int rx;
	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();

		if (xQueueReceive(QueueHandle, &rx, pdMS_TO_TICKS(500)) == pdPASS) {//If the data isn't written, waiting.

			printf("\n %s received %d, Free: %d \n", pcTaskGetName(tsk2), rx, uxQueueSpacesAvailable(QueueHandle));
		}
		else {
			printf("%s received failed", pcTaskGetName(tsk2));
		}
	}
}
