#include <native/task.h>
#include "iocontroller.h"
#include "debug.h"

static RT_TASK io_task;
void *io_shm;
static void io_refresh(void *config) {
	rt_task_set_periodic(NULL, TM_NOW, ((PLC_CONFIG *)config)->io_refresh_interval);
	while (1) {
		rt_task_wait_period(NULL);
		PRINT(DEBUG_INF, "stub code in io_refresh...", 0);
	}
}

void io_task_create() {
	if (rt_task_create(&io_task, IO_TASK_NAME, 0, IO_TASK_PRIORITY, 0)) {
		PRINT(DEBUG_ERR, "ERROR: creating io task...", 0);
	}
}

void io_task_start(PLC_CONFIG *config) {
	if (rt_task_start(&io_task, &io_refresh, (void *)config)) {
		PRINT(DEBUG_ERR, "ERROR: starting io task...", 0);
	}
}

void io_task_delete() {
	if (rt_task_delete(&io_task)) {
		PRINT(DEBUG_ERR, "ERROR: deleting io task...", 0);
	}
}
