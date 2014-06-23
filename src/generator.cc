#include <string.h> 
#include "generator.h"
#include "debug.h"

extern int DEBUG_LEVEL;

void generate_task_count(FILE *fp, task_count_t count) {
	PRINT(DEBUG_TRC, "TRACE: task_count = %d", count);
	if (fwrite(&count, sizeof(task_count_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task count (%d)...", count);
	}
}

/* Task Property Segment Generator */
static void generate_task_name_size(FILE *fp, task_name_size_t size) {
	PRINT(DEBUG_TRC, "TRACE: task_name_size = %d", size);
	if (fwrite(&size, sizeof(task_name_size_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating size of task name (%d)...", size);
	}
}
static void generate_task_name(FILE *fp, task_name_t *name) {
	PRINT(DEBUG_TRC, "TRACE: task_name = %s", name);
	if (fwrite(name, strlen(name), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task name (%s)...", name);
	}
}
static void generate_task_priority(FILE *fp, task_priority_t priority) {
	PRINT(DEBUG_TRC, "TRACE: task_priority = %d", priority);
	if (fwrite(&priority, sizeof(task_priority_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task priority (%d)...", priority);
	}
}
static void generate_task_interval(FILE *fp, task_interval_t interval) {
	PRINT(DEBUG_TRC, "TRACE: task_interval = %d", interval);
	if (fwrite(&interval, sizeof(task_interval_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task interval (%d)...", interval);
	}
}
void generate_task_property_seg_header(FILE *fp, TASK_PROPERTY_SEG_HEADER *property_seg_header) {
	generate_task_name_size(fp, property_seg_header->name_size);
}
void generate_task_property_seg(FILE *fp, TASK_PROPERTY_SEG *property_seg) {
	generate_task_name(fp, property_seg->name);
	generate_task_priority(fp, property_seg->priority);
	generate_task_interval(fp, property_seg->interval);
}

/* Data Segment Generator */
static void generate_seg_size(FILE *fp, seg_size_t size) {
	if (fwrite(&size, sizeof(seg_size_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating size of segment (%d)...", size);
	}
}

void generate_data_seg_header(FILE *fp, DATA_SEG_HEADER *data_seg_header) {
	generate_seg_size(fp, data_seg_header->size);
}
void generate_data_seg(FILE *fp, DATA_SEG_HEADER *data_seg_header, DATA_SEG *data_seg) {
	PRINT(DEBUG_TRC, "TRACE: data_seg_size = %d", data_seg_header->size);
	if (fwrite(data_seg, data_seg_header->size, 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating data segment...", 0);
	}
}
