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
static BIN_TPS_HEADER *read_tps_header(FILE *fp) {
	BIN_TPS_HEADER *tps_header = new BIN_TPS_HEADER;
	tps_header->name_size = read_task_name_size(fp);
	PRINT(DEBUG_TRC, "TRACE: task_tps_header .name_size = %d", tps_header->name_size);
	return tps_header;
}
BIN_TPS *read_tps(FILE *fp) {
	BIN_TPS *tps = new BIN_TPS;
	BIN_TPS_HEADER *tps_header  = read_tps_header(fp);
	tps->name = read_task_name(fp, tps_header->name_size);
	tps->priority = read_task_priority(fp);
	tps->interval = read_task_interval(fp);
	PRINT(DEBUG_TRC, "TRACE: task_tps .name = %s; .priority = %d; .interval = %d", tps->name, tps->priority, tps->interval);
	return tps;
}

/* Data Segment Parser */
static seg_size_t read_seg_size(FILE *fp) {
	seg_size_t size;
	fread(&size, sizeof(seg_size_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: seg_size = %d", size);
	return size;
}

static BIN_TDS_HEADER *read_tds_header(FILE *fp) {
	BIN_TDS_HEADER *tds_header = new BIN_TDS_HEADER;
	tds_header->size = read_seg_size(fp);
	PRINT(DEBUG_TRC, "TRACE: tds_header .size = %d", tds_header->size);
	return tds_header;
}
BIN_TDS *read_tds(FILE *fp) {
	BIN_TDS_HEADER *tds_header = read_tds_header(fp);
	BIN_TDS *tds = new BIN_TDS[tds_header->size];
	fread(tds, tds_header->size, 1, fp);
	PRINT(DEBUG_TRC, "TRACE: tds .first = %d; .last = %d", tds[0], tds[tds_header->size - 1]);
	return tds;
}
