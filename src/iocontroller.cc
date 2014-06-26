#include <native/task.h>
#include "iocontroller.h"
#include "debug.h"

RT_TASK io_task;
void *io_shm;
static void io_refresh(void *io_shm) {
	rt_task_set_periodic(NULL, TM_NOW, 10000000);
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

void io_task_start() {
	if (rt_task_start(&io_task, &io_refresh, io_shm)) {
		PRINT(DEBUG_ERR, "ERROR: starting io task...", 0);
	}
}

void io_task_delete() {
	if (rt_task_delete(&io_task)) {
		PRINT(DEBUG_ERR, "ERROR: deleting io task...", 0);
	}
}
