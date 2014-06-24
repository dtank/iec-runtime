#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <native/task.h>
#include <native/timer.h>
#include "executor.h"
#include "debug.h"


void plc_task_execute(void *task) {

	rt_task_set_periodic(NULL, TM_NOW, ((PLC_TASK *)task)->property->interval);
	while (1) {
		rt_task_wait_period(NULL);
		printf("stub code in plc_executor\n");
	}
}

void plc_task_create(PLC_TASK_LIST *task_list) {
	for (int i = 0; i < task_list->task_count; ++i) {
		if (rt_task_create(&task_list->rt_task[i], task_list->plc_task[i]->property->name, 0, task_list->plc_task[i]->property->priority, 0)) {
			fprintf(stderr, "ERROR: creating PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}

void plc_task_start(PLC_TASK_LIST *task_list) {
	for (int i = 0; i < task_list->task_count; ++i) {
		if (rt_task_start(&task_list->rt_task[i], &plc_task_execute, (void *)task_list->plc_task[i])) {
			fprintf(stderr, "ERROR: starting PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}
