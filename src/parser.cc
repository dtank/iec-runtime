#include "parser.h"
#include "debug.h"

extern int DEBUG_LEVEL;

static task_count_t read_task_count(FILE *fp) {
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
static PLC_TASK_PROP *read_plc_task_property(FILE *fp) {
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
static PLC_TASK_DATA *read_plc_task_data(FILE *fp) {
	BIN_TDS_HEADER *tds_header = read_tds_header(fp);
	PLC_TASK_DATA *data = new PLC_TASK_DATA[tds_header->size];
	fread(data, tds_header->size, 1, fp);
	PRINT(DEBUG_TRC, "TRACE: plc_task_data .first = %d; .last = %d", data[0], data[tds_header->size - 1]);
	return data;
}

/* PLC Task Code Parser */
static inst_count_t read_inst_count(FILE *fp) {
	inst_count_t count;
	fread(&count, sizeof(inst_count_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: inst_count = %d", count);
	return count;
}
static inst_id_t read_inst_id(FILE *fp) {
	inst_id_t id;
	fread(&id, sizeof(inst_id_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: inst_id = %d", id);
	return id;
}
static inst_arg_t read_inst_arg(FILE *fp) {
	inst_arg_t arg;
	fread(&arg, sizeof(inst_arg_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: inst_arg = %d", arg);
	return arg;
}
static BIN_TCS_HEADER *read_tcs_header(FILE *fp) {
	BIN_TCS_HEADER *tcs_header = new BIN_TCS_HEADER;
	tcs_header->inst_count = read_inst_count(fp);
	PRINT(DEBUG_TRC, "TRACE: tcs_header .inst_count = %d", tcs_header->inst_count);
	return tcs_header;
}
static PLC_TASK_INST *read_plc_task_inst(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK_INST *inst = new PLC_TASK_INST;
	inst->id = read_inst_id(fp);
	inst->arg_list = new inst_arg_t[(*inst_desc)[inst->id].args_count];
	for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
		inst->arg_list[i] = read_inst_arg(fp);
	}
	return inst;
}
static PLC_TASK_CODE *read_plc_task_code(FILE *fp, inst_desc_map_t *inst_desc) {
	BIN_TCS_HEADER *tcs_header = read_tcs_header(fp);
	PLC_TASK_CODE *code = new PLC_TASK_CODE;
	code->inst_list = new PLC_TASK_INST*[tcs_header->inst_count];
	for (int i = 0; i < tcs_header->inst_count; ++i) {
		code->inst_list[i] = read_plc_task_inst(fp, inst_desc);
	}
	return code;
}
static PLC_TASK_PROG *read_plc_task_program(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK_PROG *program = new PLC_TASK_PROG;
	program->data = read_plc_task_data(fp);
	program->code = read_plc_task_code(fp, inst_desc);
	return program;
}
static PLC_TASK *read_plc_task(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK *task = new PLC_TASK;
	task->property = read_plc_task_property(fp);
	task->program = read_plc_task_program(fp, inst_desc);
	return task;
}
PLC_TASK_LIST *read_plc_task_list(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK_LIST *task_list = new PLC_TASK_LIST;
	task_list->task_count = read_task_count(fp);
	task_list->rt_task = new RT_TASK[task_list->task_count];
	task_list->plc_task = new PLC_TASK*[task_list->task_count];
	for (int i = 0; i < task_list->task_count; ++i) {
		task_list->plc_task[i] = read_plc_task(fp, inst_desc);
	}
	return task_list;
}
