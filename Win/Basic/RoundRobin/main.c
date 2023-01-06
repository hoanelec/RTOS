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
	//With Non-preemptive and the same pritority, appropriate q, 2 tasks will be run one after the other.
	//If there are N processes in the Ready Queue, no process will wait more than (n-1)q time.
	//	ex: q = 10ms, process 1 takes 10 ms then process 2 shouln't take more 20ms.
	// To switch to other tasks, the current task  needs to be executed for at least 1q.
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
