#include <native/task.h>
#include <native/heap.h>
#include "servo.h"
#include "logger.h"

static RT_TASK servo_task;
RT_HEAP servo_heap_desc;
char *servo_shm;
ServoConfig *g_svconfig;


static void servo_update(void *config) {
    ServoConfig *servo_config = (ServoConfig *)config;
	rt_task_set_periodic(NULL, TM_NOW, servo_config->update_interval);
	while (1) {
		rt_task_wait_period(NULL);
        LOGGER_INF("STUB: Update servo data...", 0);
	}
}
static void servo_task_create() {
	if (rt_task_create(&servo_task, SERVO_TASK_NAME, 0, SERVO_TASK_PRIORITY, 0)) {
        LOGGER_ERR(EC_SERVO_TASK_CREATE, "");
	}
}

void servo_task_init(ServoConfig *config) {
    LOGGER_INF("STUB: Configure servo driver...", 0);
    int size = config->axis_count * sizeof(AXIS_DATA);
	rt_heap_create(&servo_heap_desc, "servo_shm", size, H_SHARED);
    rt_heap_alloc(&servo_heap_desc, size, TM_INFINITE, (void **)&servo_shm);
    servo_task_create();
}
void servo_task_start(ServoConfig *config) {
	if (rt_task_start(&servo_task, &servo_update, (void *)config)) {
        LOGGER_ERR(EC_SERVO_TASK_START, "");
	}
}

void servo_task_delete() {
	if (rt_task_delete(&servo_task)) {
        LOGGER_ERR(EC_SERVO_TASK_DELETE, "");
	}
}
