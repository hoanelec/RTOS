#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
/*
	xSemaphoreCreateMutex() : 0,1
	xSemaphoreGive() :++: up()
	xSemaphoreTake() :--: down()
	By default SEM = 1
*/
#if (configUSE_MUTEXES == 1)

void func_1(void);
void func_2(void);

TaskHandle_t TASK_1 = NULL;
TaskHandle_t TASK_2 = NULL;

xSemaphoreHandle SemHandle;

unsigned int number;

int main(void) {
	SemHandle = xSemaphoreCreateMutex();

	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
	for (;;);

}

void func_1(void) {
	TaskHandle_t tsk1;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();

		if (xSemaphoreTake(SemHandle, pdMS_TO_TICKS(portMAX_DELAY))) {
			printf("\n %s prints an even number : %d \n", pcTaskGetName(tsk1), number);
			number++;

			xSemaphoreGive(SemHandle);
		}

		printf("\n NON_CS of task %s ", pcTaskGetName(tsk1));

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void func_2(void) {

	TaskHandle_t tsk2;

	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();

		if (xSemaphoreTake(SemHandle, pdMS_TO_TICKS(portMAX_DELAY))) {
			printf("\n %s prints an odd number : %d \n", pcTaskGetName(tsk2), number);
			number++;

			xSemaphoreGive(SemHandle);
		}

		printf("\n NON_CS of task %s ", pcTaskGetName(tsk2));

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

#endif