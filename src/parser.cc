#include "parser.h"
#include "debug.h"

extern int DEBUG_LEVEL;

task_count_t read_task_count(FILE *fp) {
	task_count_t count;
	fread(&count, sizeof(task_count_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_count = %d", count);
	return count;
}

/* Task Property Segment Parser */
static task_name_size_t read_task_name_size(FILE *fp) {
	task_name_size_t size;
	fread(&size, sizeof(task_name_size_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_name_size = %d", size);
	return size;
}
static task_name_t *read_task_name(FILE *fp, task_name_size_t size) {
	task_name_t *name = new task_name_t[size];
	fread(name, size, 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_name = %s", name);
	return name;
}
static task_priority_t read_task_priority(FILE *fp) {
	task_priority_t priority;
	fread(&priority, sizeof(task_priority_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_priority = %d", priority);
	return priority;
}
static task_interval_t read_task_interval(FILE *fp) {
	task_interval_t interval;
	fread(&interval, sizeof(task_interval_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_interval = %d", interval);
	return interval;
}
static TASK_PROPERTY_SEG_HEADER *read_task_property_seg_header(FILE *fp) {
	TASK_PROPERTY_SEG_HEADER *property_seg_header = new TASK_PROPERTY_SEG_HEADER;
	property_seg_header->name_size = read_task_name_size(fp);
	PRINT(DEBUG_TRC, "TRACE: task_property_seg_header .name_size = %d", property_seg_header->name_size);
	return property_seg_header;
}
TASK_PROPERTY_SEG *read_task_property_seg(FILE *fp) {
	TASK_PROPERTY_SEG *property_seg = new TASK_PROPERTY_SEG;
	TASK_PROPERTY_SEG_HEADER *property_seg_header  = read_task_property_seg_header(fp);
	property_seg->name = read_task_name(fp, property_seg_header->name_size);
	property_seg->priority = read_task_priority(fp);
	property_seg->interval = read_task_interval(fp);
	PRINT(DEBUG_TRC, "TRACE: task_property_seg .name = %s; .priority = %d; .interval = %d", property_seg->name, property_seg->priority, property_seg->interval);
	return property_seg;
}

/* Constant/Data Segment Parser */
static seg_size_t read_seg_size(FILE *fp) {
	seg_size_t size;
	fread(&size, sizeof(seg_size_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: seg_size = %d", size);
	return size;
}

static DATA_SEG_HEADER *read_data_seg_header(FILE *fp) {
	DATA_SEG_HEADER *data_seg_header = new DATA_SEG_HEADER;
	data_seg_header->size = read_seg_size(fp);
	PRINT(DEBUG_TRC, "TRACE: data_seg_header .size = %d", data_seg_header->size);
	return data_seg_header;
}
DATA_SEG *read_data_seg(FILE *fp) {
	DATA_SEG_HEADER *data_seg_header = read_data_seg_header(fp);
	DATA_SEG *data_seg = new DATA_SEG[data_seg_header->size];
	fread(data_seg, data_seg_header->size, 1, fp);
	PRINT(DEBUG_TRC, "TRACE: data_seg .first = %d; .last = %d", data_seg[0], data_seg[data_seg_header->size - 1]);
	return data_seg;
}
