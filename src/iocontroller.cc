#include <native/task.h>
#include "iocontroller.h"
#include "debug.h"

static RT_TASK io_task;
char *io_shm = new char[IO_SHM_SIZE];

static void local_di_update() {
	//PRINT(DEBUG_TRC, "TRACE: io_shm .local_di = %d", *(uint8_t *)&io_shm[LDI_ADDR_OFFSET]);
}

static void local_do_update() {
	PRINT(DEBUG_TRC, "TRACE: io_shm .local_do = %d", *(uint8_t *)&io_shm[LDO_ADDR_OFFSET]);
}

static void local_ai_update() {
	//PRINT(DEBUG_TRC, "TRACE: io_shm .local_ai = %d", *(uint16_t *)&io_shm[LAI_ADDR_OFFSET]);
}

static void local_ao_update() {
	//PRINT(DEBUG_TRC, "TRACE: io_shm .local_ao = %d", *(uint16_t *)&io_shm[LAO_ADDR_OFFSET]);
}

static void io_update(void *config) {
	rt_task_set_periodic(NULL, TM_NOW, ((IO_CONFIG *)config)->update_interval);
	while (1) {
		rt_task_wait_period(NULL);
		local_di_update();
		local_do_update();
		local_ai_update();
		local_ao_update();
	}
}

void io_task_create() {
	if (rt_task_create(&io_task, IO_TASK_NAME, 0, IO_TASK_PRIORITY, 0)) {
		PRINT(DEBUG_ERR, "ERROR: creating io task...", 0);
	}
}

void io_task_start(IO_CONFIG *config) {
	if (rt_task_start(&io_task, &io_update, (void *)config)) {
		PRINT(DEBUG_ERR, "ERROR: starting io task...", 0);
	}
}

void io_task_delete() {
	if (rt_task_delete(&io_task)) {
		PRINT(DEBUG_ERR, "ERROR: deleting io task...", 0);
	}
}
