#include "parser.h"
#include "debug.h"

extern int DEBUG_LEVEL;
extern char *io_shm;

/*-----------------------------------------------------------------------------
 * PLC Object File Header Parser
 *---------------------------------------------------------------------------*/
OBJ_HEADER *read_obj_header(FILE *fp) {
	OBJ_HEADER *header = new OBJ_HEADER;
	if (header != NULL) {
		fread(header->magic, MAGIC_SIZE, 1, fp);
		fread(&header->type, sizeof(header->type), 1, fp);
		fread(&header->order, sizeof(header->order), 1, fp);
		fread(&header->version, sizeof(header->version), 1, fp);
		fread(&header->machine, sizeof(header->machine), 1, fp);
		PRINT(DEBUG_TRC, "TRACE: obj_header:\n .magic = %s\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
				header->magic, header->type, header->order, header->version, header->machine);
		return header;
	}
	return NULL;
}
/* PLC Configuration Parser */
static io_refresh_interval_t read_io_refresh_interval(FILE *fp) {
	io_refresh_interval_t interval;
	fread(&interval, sizeof(interval), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: io_refresh_interval = %d", interval);
	return interval;
}
static task_count_t read_task_count(FILE *fp) {
	task_count_t count;
	fread(&count, sizeof(task_count_t), 1, fp);
	PRINT(DEBUG_TRC, "TRACE: task_count = %d", count);
	return count;
}
PLC_CONFIG *read_plc_config(FILE *fp) {
	PLC_CONFIG *config = new PLC_CONFIG;
	config->io_refresh_interval = read_io_refresh_interval(fp);
	config->task_count = read_task_count(fp);
	return config;
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
static inst_arg_addr_t *read_inst_arg_addr(FILE *fp, PLC_TASK_DATA *data) {
	inst_arg_va_t arg_va;
	inst_arg_addr_t *arg_addr;
	fread(&arg_va, sizeof(inst_arg_va_t), 1, fp);
	int flag = arg_va & ARG_ADDR_FLAG_MASK;
	uint32_t arg_addr_offset = arg_va >> ARG_ADDR_FLAG_SIZE;
	switch (flag) {
		case ARG_ADDR_DATA: arg_addr = &data[arg_addr_offset];break;
		case ARG_ADDR_IO:   arg_addr = &io_shm[arg_addr_offset];break;
		default: PRINT(DEBUG_ERR, "ERROR: instruction argument virtual address is valid...", 0);break;
	}
	PRINT(DEBUG_TRC, "TRACE: inst_arg_addr = %d", arg_addr);
	return arg_addr;
}
static PLC_TASK_INST *read_plc_task_inst(FILE *fp, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc) {
	PLC_TASK_INST *inst = new PLC_TASK_INST;
	inst->id = read_inst_id(fp);
	inst->arg_addr = new inst_arg_addr_t*[(*inst_desc)[inst->id].args_count];
	for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
		inst->arg_addr[i] = read_inst_arg_addr(fp, data);
	}
	return inst;
}
static PLC_TASK_CODE *read_plc_task_code(FILE *fp, PLC_TASK_PROP *property, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc) {
	PLC_TASK_CODE *code = new PLC_TASK_CODE;
	code->inst = new PLC_TASK_INST*[property->inst_count];
	for (int i = 0; i < property->inst_count; ++i) {
		code->inst[i] = read_plc_task_inst(fp, data, inst_desc);
	}
	return code;
}
static PLC_TASK *read_plc_task(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK *task = new PLC_TASK;
	task->property = read_plc_task_property(fp);
	task->data = read_plc_task_data(fp, task->property);
	task->code = read_plc_task_code(fp, task->property, task->data, inst_desc);
	return task;
}
PLC_TASK_LIST *read_plc_task_list(FILE *fp, PLC_CONFIG *config, inst_desc_map_t *inst_desc) {
	PLC_TASK_LIST *task_list = new PLC_TASK_LIST;
	task_list->rt_task = new RT_TASK[config->task_count];
	task_list->plc_task = new PLC_TASK*[config->task_count];
	for (int i = 0; i < config->task_count; ++i) {
		task_list->plc_task[i] = read_plc_task(fp, inst_desc);
	}
	return task_list;
}
