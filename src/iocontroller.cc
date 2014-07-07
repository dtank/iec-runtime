#include <native/task.h>
#include "iocontroller.h"
#include "debug.h"

static RT_TASK io_task;
char *io_shm = new char[IO_SHM_SIZE];

static void local_di_refresh() {
	//PRINT(DEBUG_TRC, "TRACE: io_shm .local_di = %d", *(uint8_t *)&io_shm[LDI_ADDR_OFFSET]);
}

static void local_do_refresh() {
	PRINT(DEBUG_TRC, "TRACE: io_shm .local_do = %d", *(uint8_t *)&io_shm[LDO_ADDR_OFFSET]);
}

static void local_ai_refresh() {
	//PRINT(DEBUG_TRC, "TRACE: io_shm .local_ai = %d", *(uint16_t *)&io_shm[LAI_ADDR_OFFSET]);
}

static void local_ao_refresh() {
	//PRINT(DEBUG_TRC, "TRACE: io_shm .local_ao = %d", *(uint16_t *)&io_shm[LAO_ADDR_OFFSET]);
}

static void io_refresh(void *config) {
	rt_task_set_periodic(NULL, TM_NOW, ((PLC_CONFIG *)config)->io_refresh_interval);
	while (1) {
		rt_task_wait_period(NULL);
		local_di_refresh();
		local_do_refresh();
		local_ai_refresh();
		local_ao_refresh();
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
