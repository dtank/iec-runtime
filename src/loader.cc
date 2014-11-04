#include <string.h>
#include <map>
#include "loader.h"
#include "logger.h"

using namespace std;
extern char *io_shm;
extern ec_map_t ec_msg;
/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
IO_CONFIG *load_io_config(FILE *fp) {
	IO_CONFIG *io_config = new IO_CONFIG;
	if (io_config == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load i/o configuration");
        return NULL;
    }
	fread(io_config, sizeof(*io_config), 1, fp);
    if (io_config->update_interval < SYS_MIN_IO_INTERVAL) {
        LOGGER_ERR(EC_IO_INTERVAL, "");
        delete io_config;
        return NULL;
    }
    if (SYS_MAX_LDI_COUNT < io_config->ldi_count) {
        LOGGER_ERR(EC_LDI_COUNT, "");
        delete io_config;
        return NULL;
    }
	if (SYS_MAX_LDO_COUNT < io_config->ldo_count) {
	    LOGGER_ERR(EC_LDO_COUNT, "");
        delete io_config;
		return NULL;
	}
	if (SYS_MAX_LAI_COUNT < io_config->lai_count) {
	    LOGGER_ERR(EC_LAI_COUNT, "");
        delete io_config;
		return NULL;
	}
	if (SYS_MAX_LAO_COUNT < io_config->lao_count) {
	    LOGGER_ERR(EC_LAO_COUNT, "");
        delete io_config;
		return NULL;
	}
	LOGGER_DBG(
		"IO_CONFIG:\n .update_interval = %d\n .ldi_count = %d\n .ldo_count = %d\n .lai_count = %d\n .lao_count = %d",
		io_config->update_interval, io_config->ldi_count, io_config->ldo_count, io_config->lai_count, io_config->lao_count);
	return io_config;
}
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
AXIS_CONFIG *load_axis_config(FILE *fp) {
	AXIS_CONFIG *axis_config = new AXIS_CONFIG;
	uint8_t name_size;
	if (axis_config == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load axis configuration");
    	return NULL;
    }
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
    LOGGER_ERR(EC_OOM, "Can't load servo configuration");
	return NULL;
}

/*-----------------------------------------------------------------------------
 * PLC Task Data Loader
 *---------------------------------------------------------------------------*/
char *load_plc_task_data(FILE *fp) {
    uint32_t data_size;
    fread(&data_size, sizeof(data_size), 1, fp);
    if (SYS_MAX_TASK_DATA_SIZE < data_size) {
        LOGGER_ERR(EC_TASK_DATA_SIZE, "");
        return NULL;
    }
    char *data = new char[data_size];
    if (data == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load plc task data");
        return NULL;
    }
    fread(data, data_size, 1, fp);
    return data;
}
/*-----------------------------------------------------------------------------
 * PLC Task Code Loader
 *---------------------------------------------------------------------------*/
char *load_inst_arg_addr(FILE *fp, char *data) {
    uint32_t arg_va;
    fread(&arg_va, sizeof(arg_va), 1, fp);
    int flag = arg_va & ARG_ADDR_FLAG_MASK;
    uint32_t arg_addr_offset = arg_va >> ARG_ADDR_FLAG_SIZE;
    char *arg_addr;
    switch (flag) {
        // TODO Error checker
        case ARG_ADDR_DATA: arg_addr = &data[arg_addr_offset];break;
        case ARG_ADDR_IO:   arg_addr = &io_shm[arg_addr_offset];break;
        default: LOGGER_ERR(EC_ARG_VA_INVALID, "");break;
    }
    LOGGER_DBG("inst_arg_addr = %d", arg_addr);
    return arg_addr;
}

PLC_INST *load_plc_task_inst(FILE *fp, char *data, inst_desc_map_t *inst_desc) {
    PLC_INST *inst = new PLC_INST;
    if (inst == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load plc task instruction");
        return NULL;
    }
    fread(&inst->id, sizeof(inst->id), 1, fp);
    inst->arg_addr = new char*[(*inst_desc)[inst->id].args_count];
    if (inst->arg_addr == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load instruction arguments");
        delete inst;
        return NULL;
    }
    for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
        //TODO Error Checker
        inst->arg_addr[i] = load_inst_arg_addr(fp, data);
    }
    return inst;
}
PLC_INST *load_plc_task_code(FILE *fp, char *data, inst_desc_map_t *inst_desc) {
    uint32_t inst_count;
    fread(&inst_count, sizeof(inst_count), 1, fp);
    PLC_INST *code = new PLC_INST[inst_count];
    if (code == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load plc task code");
        return NULL;
    }
    PLC_INST *inst = NULL;
    for (uint32_t i = 0; i < inst_count; ++i) {
        if ((inst=load_plc_task_inst(fp, data, inst_desc)) == NULL) {
            LOGGER_ERR(EC_LOAD_TASK_INST, "");
            delete code;
            return NULL;
        }
        code[i] = *inst;
    }
    return code;
}

/*-----------------------------------------------------------------------------
 * PLC Task Loader
 *---------------------------------------------------------------------------*/
PLC_TASK *load_plc_task(FILE *fp, inst_desc_map_t *inst_desc) {
    PLC_TASK *task = new PLC_TASK;
    if (task == NULL) {
        LOGGER_ERR(EC_OOM, "Can't load plc task");
        return NULL;
    }
    /* PLC Task Property */
	uint8_t name_size;
    fread(&name_size, sizeof(name_size), 1, fp);
    if (SYS_MAX_TASK_NAME_SIZE < name_size) {
        LOGGER_ERR(EC_TASK_NAME_SIZE, "");
        delete task;
        return NULL;
    }
    fread(task->name, name_size, 1, fp);
    fread(&task->priority, sizeof(task->priority), 1, fp);
    if (task->priority < SYS_MIN_TASK_PRIORITY || SYS_MAX_TASK_PRIORITY < task->priority) {
        LOGGER_ERR(EC_TASK_PRIORITY, "");
        delete task;
        return NULL;
    }
    fread(&task->interval, sizeof(task->interval), 1, fp);
    if (task->interval < SYS_MAX_TASK_NAME_SIZE) {
        LOGGER_ERR(EC_TASK_INTERVAL, "");
        delete task;
        return NULL;
    }
    /* PLC Task Data */
    if ((task->data=load_plc_task_data(fp)) == NULL) {
        LOGGER_ERR(EC_LOAD_TASK_DATA, "");
        delete task;
        return NULL;
    }
    /* PLC Task Code */
    if ((task->code=load_plc_task_code(fp, task->data, inst_desc)) == NULL) {
        LOGGER_ERR(EC_LOAD_TASK_CODE, "");
        delete task;
        return NULL;
    }
    return task;
}
/*-----------------------------------------------------------------------------
 * PLC Model Loader
 *---------------------------------------------------------------------------*/
bool obj_is_valid(FILE *fp) {
    OBJ_HEADER header;
	fread(&header, sizeof(header), 1, fp);
    if (strcmp(header.magic, MAGIC) != 0) {
        LOGGER_ERR(EC_PLC_FILE, "");
        return false;
    }
    if (header.type != SYS_TYPE) {
        LOGGER_ERR(EC_SYS_TYPE, "");
        return false;
    }
	if (header.order != SYS_BYTE_ORDER) {
	    LOGGER_ERR(EC_BYTE_ORDER, "");
		return false;
	}
	if (SYS_VERSION < header.version) {
	    LOGGER_ERR(EC_SYS_VERSION, "");
		return false;
	}
	if (header.machine != SYS_MACHINE) {
	    LOGGER_ERR(EC_SYS_MACHINE, "");
		return false;
	}
	LOGGER_DBG(
		"OBJ_HEADER:\n .magic = %s\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
		header.magic, header.type, header.order, header.version, header.machine);
	return true;
}
PLC_MODEL *load_plc_model(FILE *fp, inst_desc_map_t *inst_desc) {
    if (!obj_is_valid(fp)) {
        return NULL;
    }
    PLC_MODEL *model = new PLC_MODEL;
    if (model == NULL) {
        LOGGER_ERR(EC_OOM, "");
        return NULL;
    }
    IO_CONFIG *io_config = load_io_config(fp);
    if (io_config == NULL) {
        //TODO LOGGER_ERR
        return NULL;
    }
    model->io_config = *io_config;
    SERVO_CONFIG *servo_config = load_servo_config(fp);
    if (servo_config == NULL) {
        //TODO LOGGER_ERR
        return NULL;
    }
    model->servo_config = *servo_config;
    uint8_t task_count;
    fread(&task_count, sizeof(task_count), 1, fp);
    if (task_count <= 0) {
        //TODO LOGGER_ERR
        return NULL;
    }
    model->rt_task = new RT_TASK[task_count];
    model->plc_task = new PLC_TASK[task_count];
    if (model->rt_task == NULL || model->plc_task == NULL) {
        LOGGER_ERR(EC_OOM, "");
        return NULL;
    }
    PLC_TASK *plc_task = NULL;
    for (int i = 0; i < task_count; ++i) {
        if ((plc_task=load_plc_task(fp, inst_desc)) == NULL) {
            //TODO LOGGER_ERR
            return NULL;
        }
        model->plc_task[i] = *plc_task;
    }
    return model;
}
