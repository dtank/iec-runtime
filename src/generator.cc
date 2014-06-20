#include <string.h> 
#include "generator.h"
#include "debug.h"

extern int DEBUG_LEVEL;
void generate_task_count(FILE *fp, task_count_t count) {
	PRINT(DEBUG_TRC, "Trace: task count = %d", count);
	if (fwrite(&count, sizeof(task_count_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task count (%d)...", count);
	}
}

void generate_task_name_size(FILE *fp, task_name_size_t size) {
	PRINT(DEBUG_TRC, "Trace: task name size = %d", size);
	if (fwrite(&size, sizeof(task_name_size_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task name size (%d)...", size);
	}
}
void generate_task_name(FILE *fp, task_name_t *name) {
	PRINT(DEBUG_TRC, "Trace: task name = %s", name);
	if (fwrite(name, strlen(name), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task name (%s)...", name);
	}
}
void generate_task_priority(FILE *fp, task_priority_t priority) {
	PRINT(DEBUG_TRC, "Trace: task priority = %d", priority);
	if (fwrite(&priority, sizeof(task_priority_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task priority (%d)...", priority);
	}
}
void generate_task_interval(FILE *fp, task_interval_t interval) {
	PRINT(DEBUG_TRC, "Trace: task interval = %d", interval);
	if (fwrite(&interval, sizeof(task_interval_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task interval (%d)...", interval);
	}
}
void generate_task_property_seg_header(FILE *fp, task_property_seg_header property_seg_header) {
	generate_task_name_size(fp, property_seg_header.name_size);
}
void generate_task_property_seg(FILE *fp, task_property_seg property_seg) {
	generate_task_name(fp, property_seg.name);
	generate_task_priority(fp, property_seg.priority);
	generate_task_interval(fp, property_seg.interval);
}
