#include <string.h>
#include "loader.h"
#include "logger.h"

extern char *io_shm;
extern ec_map_t ec_msg;
/*-----------------------------------------------------------------------------
 * PLC Object File Header Loader
 *---------------------------------------------------------------------------*/
OBJ_HEADER *load_obj_header(FILE *fp) {
	OBJ_HEADER *header = new OBJ_HEADER;
	if (header != NULL) {
		fread(header->magic, MAGIC_SIZE, 1, fp); /* read magic number */
		if (strcmp(header->magic, MAGIC) != 0) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_PLC_FILE], EC_PLC_FILE);
			//return NULL;
		}
		fread(&header->type, sizeof(header->type), 1, fp);
		if (header->type != SYS_TYPE) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_SYS_TYPE], EC_SYS_TYPE);
			//return NULL;
		}
		fread(&header->order, sizeof(header->order), 1, fp);
		if (header->order != SYS_BYTE_ORDER) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_BYTE_ORDER], EC_BYTE_ORDER);
			//return NULL;
		}
		fread(&header->version, sizeof(header->version), 1, fp);
		if (SYS_VERSION < header->version) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_SYS_VERSION], EC_SYS_VERSION);
			//return NULL;
		}
		fread(&header->machine, sizeof(header->machine), 1, fp);
		if (header->machine != SYS_MACHINE) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_SYS_MACHINE], EC_SYS_MACHINE);
			//return NULL;
		}
		LOGGER(LOGGER_DBG,
				"OBJ_HEADER:\n .magic = %s\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
				header->magic, header->type, header->order, header->version, header->machine);
		return header;
	}
    LOGGER(LOGGER_ERR, ec_msg[EC_OBJ_HEADER], EC_OBJ_HEADER);
	return NULL;
}
/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
IO_CONFIG *load_io_config(FILE *fp) {
	IO_CONFIG *io_config = new IO_CONFIG;
	if (io_config != NULL) {
		fread(&io_config->update_interval, sizeof(io_config->update_interval), 1, fp);
		if (io_config->update_interval < SYS_MIN_IO_INTERVAL) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_IO_INTERVAL], EC_IO_INTERVAL);
			//return NULL;
		}
		fread(&io_config->ldi_count, sizeof(io_config->ldi_count), 1, fp);
		if (SYS_MAX_LDI_COUNT < io_config->ldi_count) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_LDI_COUNT], EC_LDI_COUNT);
			//return NULL;
		}
		fread(&io_config->ldo_count, sizeof(io_config->ldo_count), 1, fp);
		if (SYS_MAX_LDO_COUNT < io_config->ldo_count) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_LDO_COUNT], EC_LDO_COUNT);
			//return NULL;
		}
		fread(&io_config->lai_count, sizeof(io_config->lai_count), 1, fp);
		if (SYS_MAX_LAI_COUNT < io_config->lai_count) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_LAI_COUNT], EC_LAI_COUNT);
			//return NULL;
		}
		fread(&io_config->lao_count, sizeof(io_config->lao_count), 1, fp);
		if (SYS_MAX_LAO_COUNT < io_config->lao_count) {
		    LOGGER(LOGGER_ERR, ec_msg[EC_LAO_COUNT], EC_LAO_COUNT);
			//return NULL;
		}
		LOGGER(LOGGER_DBG,
				"IO_CONFIG:\n .update_interval = %d\n .ldi_count = %d\n .ldo_count = %d\n .lai_count = %d\n .lao_count = %d",
				io_config->update_interval, io_config->ldi_count, io_config->ldo_count, io_config->lai_count, io_config->lao_count);
		return io_config;
	}
    LOGGER(LOGGER_ERR, ec_msg[EC_SYS_IOC], EC_SYS_IOC);
	return NULL;
}
/* PLC Configuration Loader */
static io_refresh_interval_t load_io_refresh_interval(FILE *fp) {
	io_refresh_interval_t interval;
	fread(&interval, sizeof(interval), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: io_refresh_interval = %d", interval);
	return interval;
}
static task_count_t load_task_count(FILE *fp) {
	task_count_t count;
	fread(&count, sizeof(task_count_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: task_count = %d", count);
	return count;
}
PLC_CONFIG *load_plc_config(FILE *fp) {
	PLC_CONFIG *config = new PLC_CONFIG;
	config->io_refresh_interval = load_io_refresh_interval(fp);
	config->task_count = load_task_count(fp);
	return config;
}

/* PLC Task Property Loader */
static task_name_size_t load_task_name_size(FILE *fp) {
	task_name_size_t size;
	fread(&size, sizeof(task_name_size_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: task_name_size = %d", size);
	return size;
}
static task_name_t *load_task_name(FILE *fp, task_name_size_t size) {
	task_name_t *name = new task_name_t[size];
	fread(name, size, 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: task_name = %s", name);
	return name;
}
static task_priority_t load_task_priority(FILE *fp) {
	task_priority_t priority;
	fread(&priority, sizeof(task_priority_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: task_priority = %d", priority);
	return priority;
}
static task_interval_t load_task_interval(FILE *fp) {
	task_interval_t interval;
	fread(&interval, sizeof(task_interval_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: task_interval = %d", interval);
	return interval;
}
static tds_size_t load_tds_size(FILE *fp) {
	tds_size_t size;
	fread(&size, sizeof(tds_size_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: tds_size = %d", size);
	return size;
}
static inst_count_t load_inst_count(FILE *fp) {
	inst_count_t count;
	fread(&count, sizeof(inst_count_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: inst_count = %d", count);
	return count;
}

static PLC_TASK_PROP *load_plc_task_property(FILE *fp) {
	PLC_TASK_PROP *property = new PLC_TASK_PROP;
	property->name_size = load_task_name_size(fp);
	property->name = load_task_name(fp, property->name_size);
	property->priority = load_task_priority(fp);
	property->interval = load_task_interval(fp);
	property->tds_size = load_tds_size(fp);
	property->inst_count = load_inst_count(fp);
	return property;
}

/* PLC Task Data Loader */
static PLC_TASK_DATA *load_plc_task_data(FILE *fp, PLC_TASK_PROP *property) {
	PLC_TASK_DATA *data = new PLC_TASK_DATA[property->tds_size];
	fread(data, property->tds_size, 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: plc_task_data .first = %d; .last = %d", data[0], data[property->tds_size - 1]);
	return data;
}

/* PLC Task Code Loader */
static inst_id_t load_inst_id(FILE *fp) {
	inst_id_t id;
	fread(&id, sizeof(inst_id_t), 1, fp);
	LOGGER(LOGGER_DBG, "TRACE: inst_id = %d", id);
	return id;
}
static inst_arg_addr_t *load_inst_arg_addr(FILE *fp, PLC_TASK_DATA *data) {
	inst_arg_va_t arg_va;
	inst_arg_addr_t *arg_addr;
	fread(&arg_va, sizeof(inst_arg_va_t), 1, fp);
	int flag = arg_va & ARG_ADDR_FLAG_MASK;
	uint32_t arg_addr_offset = arg_va >> ARG_ADDR_FLAG_SIZE;
	switch (flag) {
		case ARG_ADDR_DATA: arg_addr = &data[arg_addr_offset];break;
		case ARG_ADDR_IO:   arg_addr = &io_shm[arg_addr_offset];break;
		default: LOGGER(LOGGER_ERR, "ERROR: instruction argument virtual address is valid...", 0);break;
	}
	LOGGER(LOGGER_DBG, "TRACE: inst_arg_addr = %d", arg_addr);
	return arg_addr;
}
static PLC_TASK_INST *load_plc_task_inst(FILE *fp, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc) {
	PLC_TASK_INST *inst = new PLC_TASK_INST;
	inst->id = load_inst_id(fp);
	inst->arg_addr = new inst_arg_addr_t*[(*inst_desc)[inst->id].args_count];
	for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
		inst->arg_addr[i] = load_inst_arg_addr(fp, data);
	}
	return inst;
}
static PLC_TASK_CODE *load_plc_task_code(FILE *fp, PLC_TASK_PROP *property, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc) {
	PLC_TASK_CODE *code = new PLC_TASK_CODE;
	code->inst = new PLC_TASK_INST*[property->inst_count];
	for (int i = 0; i < property->inst_count; ++i) {
		code->inst[i] = load_plc_task_inst(fp, data, inst_desc);
	}
	return code;
}
static PLC_TASK *load_plc_task(FILE *fp, inst_desc_map_t *inst_desc) {
	PLC_TASK *task = new PLC_TASK;
	task->property = load_plc_task_property(fp);
	task->data = load_plc_task_data(fp, task->property);
	task->code = load_plc_task_code(fp, task->property, task->data, inst_desc);
	return task;
}
PLC_TASK_LIST *load_plc_task_list(FILE *fp, PLC_CONFIG *config, inst_desc_map_t *inst_desc) {
	PLC_TASK_LIST *task_list = new PLC_TASK_LIST;
	task_list->rt_task = new RT_TASK[config->task_count];
	task_list->plc_task = new PLC_TASK*[config->task_count];
	for (int i = 0; i < config->task_count; ++i) {
		task_list->plc_task[i] = load_plc_task(fp, inst_desc);
	}
	return task_list;
}
