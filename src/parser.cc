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
task_name_t read_task_name(FILE *fp) {
	task_name_t name;
	task_name_size_t size = read_task_name_size(fp);
	fread(&name, size, 1, fp);
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
PROPERTY read_task_property(FILE *fp) {
	PROPERTY property;
	property.name= read_task_name(fp);
	property.priority= read_task_priority(fp);
	property.interval= read_task_interval(fp);
	return property;
}
