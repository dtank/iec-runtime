#include "executor.h"
#include "instruction.h"
#include "debug.h"

extern inst_desc_map_t inst_desc;
extern char *io_shm;

static void plc_task_execute(void *plc_task) {
	PLC_TASK *task = (PLC_TASK *)plc_task;
	rt_task_set_periodic(NULL, TM_NOW, task->property->interval);
	while (1) {
		rt_task_wait_period(NULL);
		for (int i = 0; i < task->property->inst_count; ++i) {
			((inst_3op_t)inst_desc[task->code->inst[i]->id].inst_addr)(
				(void *)task->code->inst[i]->arg_addr[0],
				(void *)task->code->inst[i]->arg_addr[1],
				(void *)task->code->inst[i]->arg_addr[2]);
			/*PRINT(DEBUG_TRC, "arg1_value = %d", *(uint32_t *)task->code->inst[i]->arg_addr[0]);*/
		}
	}
}

void plc_task_create(PLC_TASK_LIST *task_list, PLC_CONFIG *config) {
	for (int i = 0; i < config->task_count; ++i) {
		if (rt_task_create(&task_list->rt_task[i], task_list->plc_task[i]->property->name, 0, task_list->plc_task[i]->property->priority, 0)) {
			PRINT(DEBUG_ERR, "ERROR: creating PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}

void plc_task_start(PLC_TASK_LIST *task_list, PLC_CONFIG *config) {
	for (int i = 0; i < config->task_count; ++i) {
		if (rt_task_start(&task_list->rt_task[i], &plc_task_execute, (void *)task_list->plc_task[i])) {
			PRINT(DEBUG_ERR, "ERROR: starting PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}
void plc_task_delete(PLC_TASK_LIST *task_list, PLC_CONFIG *config) {
	for (int i = 0; i < config->task_count; ++i) {
		if (rt_task_delete(&task_list->rt_task[i])) {
			PRINT(DEBUG_ERR, "ERROR: deleting PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
		}
	}
}
