#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

void func_1(void);
void func_2(void);

TaskHandle_t TASK_1 = NULL;
TaskHandle_t TASK_2 = NULL;

int main(void) {
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
	for (;;);
	//Task1 will be run first and not release the CPU for task2 running.
}

void func_1(void) {
	//Task 1 will never go to blocked state.
	TaskHandle_t tsk1;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk1));
	}
	//vTaskDelay(1000);
}

void func_2(void) {
	//Task 2 will be added to the ready list and then go to blocked state.
	TaskHandle_t tsk2;

	vTaskDelay(1000);

	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk2));
	}
}
