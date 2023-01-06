#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

#if( configUSE_COUNTING_SEMAPHORES == 1)
/*
	xSemaphoreCreateCounting()
	xSemaphoreGive() :+1: up()
	xSemaphoreTake() :-1: down()
*/
void func_1(void);
void func_2(void);
void func_3(void);

TaskHandle_t TASK_1 = NULL;
TaskHandle_t TASK_2 = NULL;
TaskHandle_t TASK_3 = NULL;

xSemaphoreHandle SemHandle;

unsigned int number;

int main(void) {
	SemHandle = xSemaphoreCreateCounting(2/*max*/, 0/*initial*/);

	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(func_2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(func_3, "TASK_3", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

	vTaskStartScheduler();
	for (;;);

}

void func_1(void) {
	TaskHandle_t tsk1;

	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();

		printf("\n %s is running \n", pcTaskGetName(tsk1));

		xSemaphoreGive(SemHandle);

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void func_2(void) {

	TaskHandle_t tsk2;

	while (1) {
		tsk2 = xTaskGetCurrentTaskHandle();

		printf("\n %s is running \n", pcTaskGetName(tsk2));

		xSemaphoreGive(SemHandle);

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void func_3(void) {

	TaskHandle_t tsk3;

	while (1) {
		tsk3 = xTaskGetCurrentTaskHandle();

		/* need 2 shemaphores*/
		xSemaphoreTake(SemHandle, portMAX_DELAY); //--semaphore. (BLOCKED if at the moment the semaphore is 0)
		xSemaphoreTake(SemHandle, portMAX_DELAY); //--semaphore. (BLOCKED if at the moment the semaphore is 0)

		printf("\n %s is running \n", pcTaskGetName(tsk3));
	}
}

#endif