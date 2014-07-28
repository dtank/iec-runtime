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
		    LOGGER_ERR(EC_PLC_FILE, "");
			return NULL;
		}
		fread(&header->type, sizeof(header->type), 1, fp);
		if (header->type != SYS_TYPE) {
		    LOGGER_ERR(EC_SYS_TYPE, "");
			return NULL;
		}
		fread(&header->order, sizeof(header->order), 1, fp);
		if (header->order != SYS_BYTE_ORDER) {
		    LOGGER_ERR(EC_BYTE_ORDER, "");
			return NULL;
		}
		fread(&header->version, sizeof(header->version), 1, fp);
		if (SYS_VERSION < header->version) {
		    LOGGER_ERR(EC_SYS_VERSION, "");
			return NULL;
		}
		fread(&header->machine, sizeof(header->machine), 1, fp);
		if (header->machine != SYS_MACHINE) {
		    LOGGER_ERR(EC_SYS_MACHINE, "");
			return NULL;
		}
		LOGGER_DBG(
			"OBJ_HEADER:\n .magic = %s\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
			header->magic, header->type, header->order, header->version, header->machine);
		return header;
	}
    LOGGER_ERR(EC_FULL_MEM, "Can't load PLC object file header");
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
		    LOGGER_ERR(EC_IO_INTERVAL, "");
			return NULL;
		}
		fread(&io_config->ldi_count, sizeof(io_config->ldi_count), 1, fp);
		if (SYS_MAX_LDI_COUNT < io_config->ldi_count) {
		    LOGGER_ERR(EC_LDI_COUNT, "");
			return NULL;
		}
		fread(&io_config->ldo_count, sizeof(io_config->ldo_count), 1, fp);
		if (SYS_MAX_LDO_COUNT < io_config->ldo_count) {
		    LOGGER_ERR(EC_LDO_COUNT, "");
			return NULL;
		}
		fread(&io_config->lai_count, sizeof(io_config->lai_count), 1, fp);
		if (SYS_MAX_LAI_COUNT < io_config->lai_count) {
		    LOGGER_ERR(EC_LAI_COUNT, "");
			return NULL;
		}
		fread(&io_config->lao_count, sizeof(io_config->lao_count), 1, fp);
		if (SYS_MAX_LAO_COUNT < io_config->lao_count) {
		    LOGGER_ERR(EC_LAO_COUNT, "");
			return NULL;
		}
		LOGGER_DBG(
			"IO_CONFIG:\n .update_interval = %d\n .ldi_count = %d\n .ldo_count = %d\n .lai_count = %d\n .lao_count = %d",
			io_config->update_interval, io_config->ldi_count, io_config->ldo_count, io_config->lai_count, io_config->lao_count);
		return io_config;
	}
    LOGGER_ERR(EC_FULL_MEM, "Can't load i/o configuration");
	return NULL;
}
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
AXIS_CONFIG *load_axis_config(FILE *fp) {
	AXIS_CONFIG *axis_config = new AXIS_CONFIG;
	uint8_t name_size;
	if (axis_config != NULL) {
		fread(&axis_config->is_combined, sizeof(axis_config->is_combined), 1, fp);
		fread(&name_size, sizeof(name_size), 1, fp);
		if (SYS_MAX_AXIS_NAME_SIZE < name_size) {
			LOGGER_ERR(EC_AXIS_NAME_SIZE, "");
			return NULL;
		}
		fread(axis_config->name, name_size, 1, fp);
		fread(&axis_config->node_id, sizeof(axis_config->node_id), 1, fp);
		if (axis_config->node_id < SYS_MIN_AXIS_NODE_ID || SYS_MAX_AXIS_NODE_ID < axis_config->node_id) {
			LOGGER_ERR(EC_AXIS_ID_RANGE, "");
			return NULL;
		}
		fread(&axis_config->axis_type, sizeof(axis_config->axis_type), 1, fp);
		if (axis_config->axis_type != AXIS_TYPE_FINITE && axis_config->axis_type != AXIS_TYPE_MODULO) {
			LOGGER_ERR(EC_AXIS_TYPE, "");
			return NULL;
		}
		fread(&axis_config->oper_mode, sizeof(axis_config->oper_mode), 1, fp);
		if (axis_config->oper_mode != OPER_MODE_POS && axis_config->oper_mode != OPER_MODE_VEL && axis_config->oper_mode != OPER_MODE_TOR) {
			LOGGER_ERR(EC_AXIS_OPER_MODE, "");
			return NULL;
		}
		fread(&axis_config->sw_limit_neg, sizeof(axis_config->sw_limit_neg), 1, fp);
		fread(&axis_config->sw_limit_pos, sizeof(axis_config->sw_limit_pos), 1, fp);
		fread(&axis_config->max_vel, sizeof(axis_config->max_vel), 1, fp);
		fread(&axis_config->max_acc, sizeof(axis_config->max_acc), 1, fp);
		fread(&axis_config->max_dec, sizeof(axis_config->max_dec), 1, fp);
		fread(&axis_config->max_jerk, sizeof(axis_config->max_jerk), 1, fp);
		LOGGER_DBG(
			"AXIS_CONFIG:\n .is_combined = %d\n .name = %s\n .node_id = %d\n .axis_type = %d\n .oper_mode = %d\n .sw_limit_neg = %f\n .sw_limit_pos = %f\n .max_vel = %f\n .max_acc = %f\n .max_dec = %f\n .max_jerk = %f",
			axis_config->is_combined, axis_config->name, axis_config->node_id, axis_config->axis_type, axis_config->oper_mode, axis_config->sw_limit_neg, axis_config->sw_limit_pos, axis_config->max_vel, axis_config->max_acc, axis_config->max_dec, axis_config->max_jerk);

		return axis_config;
	}
    LOGGER_ERR(EC_FULL_MEM, "Can't load axis configuration");
	return NULL;
}
SERVO_CONFIG *load_servo_config(FILE *fp) {
	SERVO_CONFIG *servo_config = new SERVO_CONFIG;
	if (servo_config != NULL) {
	    fread(&servo_config->axis_count, sizeof(servo_config->axis_count), 1, fp);
        if (SYS_MAX_AXIS_COUNT < servo_config->axis_count) {
            LOGGER_ERR(EC_AXIS_COUNT, "");
            return NULL;
        }
		LOGGER_DBG("axis_count = %d", servo_config->axis_count);
		fread(&servo_config->update_interval, sizeof(servo_config->update_interval), 1, fp);
		if (servo_config->update_interval < SYS_MIN_SERVO_INTERVAL) {
		    LOGGER_ERR(EC_SERVO_INTERVAL, "");
			return NULL;
		}
		LOGGER_DBG("servo_update_interval = %d", servo_config->update_interval);
        servo_config->axis_group = new AXIS_CONFIG[servo_config->axis_count];
		for (int i = 0; i < servo_config->axis_count; ++i) {
			servo_config->axis_group[i] = *load_axis_config(fp);
		}
		return servo_config;
	}
    LOGGER_ERR(EC_FULL_MEM, "Can't load servo configuration");
	return NULL;
}
/*-----------------------------------------------------------------------------
 * PLC Task Property Loader
 *---------------------------------------------------------------------------*/
PLC_TASK_PROP *load_plc_task_property(FILE *fp) {
	uint8_t name_size;
    fread(&name_size, sizeof(name_size), 1, fp);
	PLC_TASK_PROP *property = new PLC_TASK_PROP;
	if (property != NULL) {
    	fread(property->name, name_size, 1, fp);
        if (SYS_MAX_TASK_NAME_SIZE < name_size) {
            LOGGER_ERR(EC_TASK_NAME_SIZE, "");
            return NULL;
        }
    	fread(&property->priority, sizeof(property->priority), 1, fp);
        if (property->priority < SYS_MIN_TASK_PRIORITY || SYS_MAX_TASK_PRIORITY < property->priority) {
            LOGGER_ERR(EC_TASK_PRIORITY, "");
            return NULL;
        }
    	fread(&property->interval, sizeof(property->interval), 1, fp);
        if (property->interval < SYS_MAX_TASK_NAME_SIZE) {
            LOGGER_ERR(EC_TASK_INTERVAL, "");
            return NULL;
        }
        //fread(&property->data_size, sizeof(property->data_size), 1, fp);
        //fread(&property->inst_count, sizeof(property->inst_count), 1, fp);
		LOGGER_DBG("PLC_TASK_PROP:\n .name = %s\n .priority = %d\n .interval = %d", property->name, property->priority, property->interval);
		return property;
	}
    LOGGER_ERR(EC_FULL_MEM, "Can't load plc task property");
	return NULL;
}
/*-----------------------------------------------------------------------------
 * PLC Task Data Loader
 *---------------------------------------------------------------------------*/
PLC_TASK_DATA *load_plc_task_data(FILE *fp) {
    uint32_t size;
    fread(&size, sizeof(size), 1, fp);
    if (SYS_MAX_TASK_DATA_SIZE < size) {
        LOGGER_ERR(EC_TASK_DATA_SIZE, "");
        return NULL;
    }
    PLC_TASK_DATA *data = new PLC_TASK_DATA[size];
    if (data != NULL) {
        fread(data, size, 1, fp);
        LOGGER_DBG("PLC_TASK_DATA:\n .addr = %d, .first = %d, .last = %d", data, data[0], data[size-1]);
        return data;
    }
    LOGGER_ERR(EC_FULL_MEM, "Can't load plc task data");
    return NULL;
}
/*-----------------------------------------------------------------------------
 * PLC Task Code Loader
 *---------------------------------------------------------------------------*/
char *load_inst_arg_addr(FILE *fp, PLC_TASK_DATA *data) {
    uint32_t arg_va;
    fread(&arg_va, sizeof(arg_va), 1, fp);
    int flag = arg_va & ARG_ADDR_FLAG_MASK;
    uint32_t arg_addr_offset = arg_va >> ARG_ADDR_FLAG_SIZE;
    char *arg_addr;
    LOGGER_DBG("data size = %d", sizeof(data));
    switch (flag) {
        // TODO Error checker
        case ARG_ADDR_DATA: arg_addr = &data[arg_addr_offset];break;
        case ARG_ADDR_IO:   arg_addr = &io_shm[arg_addr_offset];break;
        default: LOGGER_ERR(EC_ARG_VA_INVALID, "");break;
    }
    LOGGER_DBG("inst_arg_addr = %d", arg_addr);
    return arg_addr;
}
PLC_TASK_INST *load_plc_task_inst(FILE *fp, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc) {
    PLC_TASK_INST *inst = new PLC_TASK_INST;
    fread(&inst->id, sizeof(inst->id), 1, fp);
    LOGGER_DBG("inst_id = %d", inst->id);
    inst->arg_addr = new char*[(*inst_desc)[inst->id].args_count];
    for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
        inst->arg_addr[i] = load_inst_arg_addr(fp, data);
    }
    return inst;
}
PLC_TASK_CODE *load_plc_task_code(FILE *fp, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc) {
    uint32_t inst_count;
    fread(&inst_count, sizeof(inst_count), 1, fp);
    PLC_TASK_CODE *code = new PLC_TASK_CODE;
    code->inst = new PLC_TASK_INST*[inst_count];
    for (uint32_t i = 0; i < inst_count; ++i) {
        code->inst[i] = load_plc_task_inst(fp, data, inst_desc);
    }
    return code;
}

/*-----------------------------------------------------------------------------
 * PLC Task List Loader
 *---------------------------------------------------------------------------*/
PLC_TASK *load_plc_task(FILE *fp, inst_desc_map_t *inst_desc) {
    PLC_TASK *task = new PLC_TASK;
    task->property = *load_plc_task_property(fp);
    task->data = load_plc_task_data(fp);
    task->code = *load_plc_task_code(fp, task->data, inst_desc);
    return task;
}
PLC_TASK_LIST *load_plc_task_list(FILE *fp, inst_desc_map_t *inst_desc) {
    uint8_t task_count;
    fread(&task_count, sizeof(task_count), 1, fp);
    PLC_TASK_LIST *task_list = new PLC_TASK_LIST;
    task_list->rt_task = new RT_TASK[task_count];
    task_list->plc_task = new PLC_TASK[task_count];
    for (int i = 0; i < task_count; ++i) {
        task_list->plc_task[i] = *load_plc_task(fp, inst_desc);
    }
    return task_list;
}
