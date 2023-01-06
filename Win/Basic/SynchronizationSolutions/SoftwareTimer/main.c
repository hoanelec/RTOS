#include <stdio.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
/*
	#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) => Highest priority compared to all processes
	#define configTIMER_QUEUE_LENGTH				20 => Max timers support
	#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )
*/
#if (configUSE_TIMERS == 1)

void func_1(void);
void Tim1CallBackFunction(xTimerHandle TimHandle);

TaskHandle_t TASK_1 = NULL;

xTimerHandle Tim1Handle;


int main(void) {
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
	for (;;);

}

void func_1(void) {
	TaskHandle_t tsk1;

	tsk1 = xTaskGetCurrentTaskHandle();
	
	Tim1Handle = xTimerCreate("TIM1: One shot timer", pdMS_TO_TICKS(1000), pdFALSE/*One shot*/, 0/*Timer ID*/, Tim1CallBackFunction);
	xTimerStart(Tim1Handle, portMAX_DELAY);

	printf("\n NON_CS of task %s ", pcTaskGetName(tsk1));
}

void Tim1CallBackFunction(xTimerHandle TimHandle) {
	printf("I'm callback function\n");
}

#endif