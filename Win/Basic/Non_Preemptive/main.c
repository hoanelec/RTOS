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
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

	vTaskStartScheduler();
	for (;;);
	//Task1 will be run first and not release the CPU for task2 running.
}

void func_1(void) {
	//Task 1 will never go to blocked state.
	TaskHandle_t tsk1;

	int x;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk1));
		Sleep(5);
	}
}

void func_2(void) {
	//Task 2 will be added to the ready list and then go to blocked state.
	TaskHandle_t tsk2;

	vTaskDelay(pdMS_TO_TICKS(5000));

	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk2));
	}
}
