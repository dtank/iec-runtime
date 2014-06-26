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
static tds_size_t read_tds_size(FILE *fp) {
	tds_size_t size;
	fread(&size, sizeof(tds_size_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: tds_size = %d", size);
	return size;
}
static inst_count_t read_inst_count(FILE *fp) {
	inst_count_t count;
	fread(&count, sizeof(inst_count_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: inst_count = %d", count);
	return count;
}

static PLC_TASK_PROP *read_plc_task_property(FILE *fp) {
	PLC_TASK_PROP *property = new PLC_TASK_PROP;
	property->name_size = read_task_name_size(fp);
	property->name = read_task_name(fp, property->name_size);
	property->priority = read_task_priority(fp);
	property->interval = read_task_interval(fp);
	property->tds_size = read_tds_size(fp);
	property->inst_count = read_inst_count(fp);
	return property;
}

/* PLC Task Data Parser */
static PLC_TASK_DATA *read_plc_task_data(FILE *fp, PLC_TASK_PROP *property) {
	PLC_TASK_DATA *data = new PLC_TASK_DATA[property->tds_size];
	fread(data, property->tds_size, 1, fp);
	PRINT(DEBUG_TRC, "TRACE: plc_task_data .first = %d; .last = %d", data[0], data[property->tds_size - 1]);
	return data;
}

/* PLC Task Code Parser */
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
static PLC_TASK_INST *read_plc_task_inst(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK_INST *inst = new PLC_TASK_INST;
	inst->id = read_inst_id(fp);
	inst->argv = new inst_arg_t[(*inst_desc)[inst->id].args_count];
	for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
		inst->argv[i] = read_inst_arg(fp);
	}
	return inst;
}
static PLC_TASK_CODE *read_plc_task_code(FILE *fp, PLC_TASK_PROP *property, inst_desc_map_t *inst_desc) {
	PLC_TASK_CODE *code = new PLC_TASK_CODE;
	code->inst = new PLC_TASK_INST*[property->inst_count];
	for (int i = 0; i < property->inst_count; ++i) {
		code->inst[i] = read_plc_task_inst(fp, inst_desc);
	}
	return code;
}
static PLC_TASK *read_plc_task(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK *task = new PLC_TASK;
	task->property = read_plc_task_property(fp);
	task->data = read_plc_task_data(fp, task->property);
	task->code = read_plc_task_code(fp, task->property, inst_desc);
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
