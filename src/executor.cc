#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <native/task.h>
#include <native/timer.h>
#include "executor.h"
#include "debug.h"

RT_TASK plc_tasks[MAX_PLC_TASK_COUNT];

void plc_task_execute(void *task) {

	rt_task_set_periodic(NULL, TM_NOW, ((TASK *)task)->property.interval);
	while (1) {
		rt_task_wait_period(NULL);
		printf("stub code in plc_executor\n");
	}
}

void plc_task_create(TASK_LIST *task_list) {
	PRINT(DEBUG_TRC, "Trace: task count = %d", task_list->task_count);
	for (int i = 0; i < task_list->task_count; ++i) {
		PRINT(DEBUG_TRC, "Trace: task name = %s", task_list->task[i]->property.name);
		PRINT(DEBUG_TRC, "Trace: task priority = %d", task_list->task[i]->property.priority);
		if (rt_task_create(&plc_tasks[i], task_list->task[i]->property.name, 0, task_list->task[i]->property.priority, 0)) {
			fprintf(stderr, "FAILED: creating PLC task \"%s\"\n", task_list->task[i]->property.name);
		}
	}
}

void plc_task_start(TASK_LIST *task_list) {
	for (int i = 0; i < task_list->task_count; ++i) {
		if (rt_task_start(&plc_tasks[i], &plc_task_execute, (void *)task_list->task[i])) {
			fprintf(stderr, "FAILED: starting PLC task \"%s\"\n", task_list->task[i]->property.name);
		}
	}
}
