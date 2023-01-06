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
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

	vTaskStartScheduler();
	for (;;);

}

void func_1(void) {
	TaskHandle_t tsk1;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk1));
		Sleep(10);
	}
}

void func_2(void) {

	TaskHandle_t tsk2;

	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();
		printf("\n %s IS RUNNING \n", pcTaskGetName(tsk2));
		Sleep(10);
	}
}
