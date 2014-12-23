#include <native/task.h>
#include <native/heap.h>
#include "rc.h"
#include "logger.h"

static RT_TASK rc_task;
RT_HEAP rc_heap_desc;
char *rc_shm;

static void interp_calculate(void *config) {
    LOGGER_INF("STUB: Calculate interpolation value...", 0);
}
static void rc_task_create() {
	if (rt_task_create(&rc_task, RC_TASK_NAME, 0, RC_TASK_PRIORITY, 0)) {
        LOGGER_ERR(EC_RC_TASK_CREATE, "");
	}
}
void rc_task_init(RobotConfig *config) {
    int size = config->axis_count * sizeof(INTERP_DATA);
	rt_heap_create(&rc_heap_desc, "rc_shm", size, H_SHARED);
    rt_heap_alloc(&rc_heap_desc, size, TM_INFINITE, (void **)&rc_shm);
    rc_task_create();
}
void rc_task_start(RobotConfig *config) {
	if (rt_task_start(&rc_task, &interp_calculate, (void *)config)) {
        LOGGER_ERR(EC_RC_TASK_START, "");
	}
}
void rc_task_delete() {
	if (rt_task_delete(&rc_task)) {
        LOGGER_ERR(EC_RC_TASK_DELETE, "");
	}
}
