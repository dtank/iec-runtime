#include "parser.h"
#include "debug.h"

extern int DEBUG_LEVEL;

task_count_t read_task_count(FILE *fp) {
	task_count_t count;
	fread(&count, sizeof(task_count_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_count = %d", count);
	return count;
}

/* PLC Task Property Parser */
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
PLC_TASK_PROP *parse_plc_task_property(FILE *fp) {
	PLC_TASK_PROP *property = new PLC_TASK_PROP;
	BIN_TPS_HEADER *tps_header  = read_tps_header(fp);
	property->name = read_task_name(fp, tps_header->name_size);
	property->priority = read_task_priority(fp);
	property->interval = read_task_interval(fp);
	PRINT(DEBUG_TRC, "TRACE: plc_task_property .name = %s; .priority = %d; .interval = %d", property->name, property->priority, property->interval);
	return property;
}

/* PLC Task Data Parser */
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
PLC_TASK_DATA *parse_plc_task_data(FILE *fp) {
	BIN_TDS_HEADER *tds_header = read_tds_header(fp);
	PLC_TASK_DATA *data = new PLC_TASK_DATA[tds_header->size];
	fread(data, tds_header->size, 1, fp);
	PRINT(DEBUG_TRC, "TRACE: plc_task_data .first = %d; .last = %d", data[0], data[tds_header->size - 1]);
	return data;
}
