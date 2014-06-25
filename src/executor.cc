#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <native/task.h>
#include <native/timer.h>
#include "executor.h"
#include "stdinst.h"
#include "instruction.h"
#include "debug.h"


extern inst_desc_map_t inst_desc;
void plc_task_execute(void *plc_task) {
	PLC_TASK *task = (PLC_TASK *)plc_task;
	rt_task_set_periodic(NULL, TM_NOW, task->property->interval);
	while (1) {
		rt_task_wait_period(NULL);
		printf("stub code in plc_executor\n");
//TODO: how to get instruction count
		//for (int i = 0; i < task->program->code->)
		//((inst_3op_t)inst_desc[STD_ADD].inst_addr)((void *)task->program->code, (void *)&op2, (void *)&op3);
		PRINT(DEBUG_TRC, "op3 = %d", op3);
	}
}

void plc_task_create(PLC_TASK_LIST *task_list) {
	for (int i = 0; i < task_list->task_count; ++i) {
		if (rt_task_create(&task_list->rt_task[i], task_list->plc_task[i]->property->name, 0, task_list->plc_task[i]->property->priority, 0)) {
			PRINT(DEBUG_ERR, "ERROR: creating PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}

void plc_task_start(PLC_TASK_LIST *task_list) {
	for (int i = 0; i < task_list->task_count; ++i) {
		if (rt_task_start(&task_list->rt_task[i], &plc_task_execute, (void *)task_list->plc_task[i])) {
			PRINT(DEBUG_ERR, "ERROR: starting PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}
void plc_task_delete(PLC_TASK_LIST *task_list) {
	for (int i = 0; i < task_list->task_count; ++i) {
		if (rt_task_delete(&task_list->rt_task[i])) {
			PRINT(DEBUG_ERR, "ERROR: deleting PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}
