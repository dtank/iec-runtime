#include "parser.h"
#include "debug.h"

extern int DEBUG_LEVEL;

task_count_t read_task_count(FILE *fp) {
	task_count_t count;
	fread(&count, sizeof(task_count_t), 1, fp);
	PRINT(DEBUG_TRC, "Trace: task count = %d", count);
	return count;
}

task_name_size_t read_task_name_size(FILE *fp) {
	task_name_size_t size;
	fread(&size, sizeof(task_name_size_t), 1, fp);
	PRINT(DEBUG_TRC, "Trace: task name size = %d", size);
	return size;
}
task_name_t *read_task_name(FILE *fp, task_name_size_t size) {
	task_name_t *name = new task_name_t[size];
	fread(name, size, 1, fp);
	PRINT(DEBUG_TRC, "Trace: task name = %s", name);
	return name;
}
task_priority_t read_task_priority(FILE *fp) {
	task_priority_t priority;
	fread(&priority, sizeof(task_priority_t), 1, fp);
	PRINT(DEBUG_TRC, "Trace: task priority = %d", priority);
	return priority;
}
task_interval_t read_task_interval(FILE *fp) {
	task_interval_t interval;
	fread(&interval, sizeof(task_interval_t), 1, fp);
	PRINT(DEBUG_TRC, "Trace: task interval = %d", interval);
	return interval;
}
task_property_seg_header read_task_property_seg_header(FILE *fp) {
	task_property_seg_header property_seg_header;
	property_seg_header.name_size= read_task_name_size(fp);
	return property_seg_header;
}
task_property_seg read_task_property_seg(FILE *fp) {
	task_property_seg property_seg;
	task_name_size_t size  = read_task_property_seg_header(fp).name_size;
	property_seg.name = read_task_name(fp, size);
	PRINT(DEBUG_TRC, "Trace: task_property_seg.name = %s", property_seg.name);
	property_seg.priority = read_task_priority(fp);
	property_seg.interval = read_task_interval(fp);
	return property_seg;
}
