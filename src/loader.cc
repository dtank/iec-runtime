#include <string.h>
#include <map>
#include "loader.h"
#include "objfile.h"
#include "sysenv.h"
#include "logger.h"

using namespace std;
extern char *io_shm;
extern ec_map_t ec_msg;
/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
int load_io_config(FILE *fp, IO_CONFIG *io_config) {
	fread(io_config, sizeof(IO_CONFIG), 1, fp); /* rely on alignment */
    if (io_config->update_interval < MIN_IO_INTERVAL) {
        LOGGER_ERR(EC_IO_INTERVAL, "");
        return -1;
    }
    if (io_config->ldi_count < 0 || MAX_LDI_COUNT < io_config->ldi_count) {
        LOGGER_ERR(EC_LDI_COUNT, "");
        return -1;
    }
	if (io_config->ldo_count < 0 || MAX_LDO_COUNT < io_config->ldo_count) {
	    LOGGER_ERR(EC_LDO_COUNT, "");
		return -1;
	}
	if (io_config->lai_count < 0 || MAX_LAI_COUNT < io_config->lai_count) {
	    LOGGER_ERR(EC_LAI_COUNT, "");
		return -1;
	}
	if (io_config->lao_count < 0 || MAX_LAO_COUNT < io_config->lao_count) {
	    LOGGER_ERR(EC_LAO_COUNT, "");
		return -1;
	}
	LOGGER_DBG(
		"IO_CONFIG:\n .update_interval = %d\n .ldi_count = %d\n .ldo_count = %d\n .lai_count = %d\n .lao_count = %d",
		io_config->update_interval, io_config->ldi_count, io_config->ldo_count, io_config->lai_count, io_config->lao_count);
	return 0;
}
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
static int load_axis_config(FILE *fp, AXIS_CONFIG *axis_config) {
    fread(axis_config->name, MAX_AXIS_NAME_SIZE, 1, fp);
    fread(&axis_config->is_combined, sizeof(axis_config->is_combined), 1, fp);
    if (axis_config->is_combined != false && axis_config->is_combined != true) {
        LOGGER_ERR(EC_AXIS_COMBINE, "");
        return -1;
    }
    fread(&axis_config->node_id, sizeof(axis_config->node_id), 1, fp);
	if (axis_config->node_id < MIN_AXIS_NODE_ID || MAX_AXIS_NODE_ID < axis_config->node_id) {
		LOGGER_ERR(EC_AXIS_ID_RANGE, "");
		return -1;
	}
    fread(&axis_config->axis_type, sizeof(axis_config->axis_type), 1, fp);
	if (axis_config->axis_type != AXIS_TYPE_FINITE && axis_config->axis_type != AXIS_TYPE_MODULO) {
		LOGGER_ERR(EC_AXIS_TYPE, "");
		return -1;
	}
    fread(&axis_config->oper_mode, sizeof(axis_config->oper_mode), 1, fp);
	if (axis_config->oper_mode != OPER_MODE_POS && axis_config->oper_mode != OPER_MODE_VEL && axis_config->oper_mode != OPER_MODE_TOR) {
		LOGGER_ERR(EC_AXIS_OPER_MODE, "");
		return -1;
	}
    fread(&axis_config->sw_limit_neg, sizeof(axis_config->sw_limit_neg), 1, fp);
    fread(&axis_config->sw_limit_pos, sizeof(axis_config->sw_limit_pos), 1, fp);
    if (axis_config->sw_limit_pos < axis_config->sw_limit_neg) {
        LOGGER_ERR(EC_AXIS_SW, "");
		return -1;
    }
    fread(&axis_config->max_vel, sizeof(axis_config->max_vel), 1, fp);
    if (axis_config->max_vel < 0.0) {
        LOGGER_ERR(EC_AXIS_MAX_VEL, "");
        return -1;
    }
    fread(&axis_config->max_acc, sizeof(axis_config->max_acc), 1, fp);
    if (axis_config->max_acc < 0.0) {
        LOGGER_ERR(EC_AXIS_MAX_ACC, "");
        return -1;
    }
    fread(&axis_config->max_dec, sizeof(axis_config->max_dec), 1, fp);
    if (axis_config->max_dec < 0.0) {
        LOGGER_ERR(EC_AXIS_MAX_DEC, "");
        return -1;
    }
    fread(&axis_config->max_jerk, sizeof(axis_config->max_jerk), 1, fp);
    if (axis_config->max_jerk < 0.0) {
        LOGGER_ERR(EC_AXIS_MAX_JERK, "");
        return -1;
    }
	LOGGER_DBG(
		"AXIS_CONFIG:\n .is_combined = %d\n .name = %s\n .node_id = %d\n .axis_type = %d\n .oper_mode = %d\n .sw_limit_neg = %f\n .sw_limit_pos = %f\n .max_vel = %f\n .max_acc = %f\n .max_dec = %f\n .max_jerk = %f",
		axis_config->is_combined, axis_config->name, axis_config->node_id, axis_config->axis_type, axis_config->oper_mode, axis_config->sw_limit_neg, axis_config->sw_limit_pos, axis_config->max_vel, axis_config->max_acc, axis_config->max_dec, axis_config->max_jerk);

	return 0;
}
int load_servo_config(FILE *fp, SERVO_CONFIG *servo_config) {
    fread(&servo_config->axis_count, sizeof(servo_config->axis_count), 1, fp);
    if (servo_config->axis_count < 0 || MAX_AXIS_COUNT < servo_config->axis_count) {
        LOGGER_ERR(EC_AXIS_COUNT, "");
        return -1;
    }
	fread(&servo_config->update_interval, sizeof(servo_config->update_interval), 1, fp);
	if (servo_config->update_interval < MIN_SERVO_INTERVAL) {
	    LOGGER_ERR(EC_SERVO_INTERVAL, "");
		return -1;
	}
    servo_config->axis_group = new AXIS_CONFIG[servo_config->axis_count];
	if (servo_config->axis_group == NULL) {
        LOGGER_ERR(EC_OOM, "loading axis configuration");
    	return -1;
    }
	LOGGER_DBG("SERVO_CONFIG:\n .axis_count = %d\n .update_interval = %d",
        servo_config->axis_count, servo_config->update_interval);
	for (int i = 0; i < servo_config->axis_count; ++i) {
        if (load_axis_config(fp, &servo_config->axis_group[i]) < 0) {
            delete servo_config->axis_group;
            return -1;
        }
	}
	return 0;
}

static int load_task_prop(FILE *fp, TASK_PROP *task_prop) {
    fread(task_prop->name, MAX_TASK_NAME_SIZE, 1, fp);
    fread(&task_prop->priority, sizeof(task_prop->priority), 1, fp);
    if (task_prop->priority < MIN_TASK_PRIORITY || MAX_TASK_PRIORITY < task_prop->priority) {
        LOGGER_ERR(EC_TASK_PRIORITY, "");
        return -1;
    }
    fread(&task_prop->interval, sizeof(task_prop->interval), 1, fp);
    if (task_prop->interval < MIN_TASK_INTERVAL) {
        LOGGER_ERR(EC_TASK_INTERVAL, "");
        return -1;
    }
    fread(&task_prop->data_size, sizeof(task_prop->data_size), 1, fp);
    if (MAX_TASK_GLOB_COUNT < task_prop->data_size) {
        LOGGER_ERR(EC_TASK_DATA_SIZE, "");
        return -1;
    }
    fread(&task_prop->inst_count, sizeof(task_prop->inst_count), 1, fp); /* NOT need error checker */
    LOGGER_DBG("TASK_PROP:\n .name = %s\n .priority = %d\n .interval = %d\n .data_size = %d\n .inst_count = %d",
        task_prop->name, task_prop->priority, task_prop->interval, task_prop->data_size, task_prop->inst_count);
    return 0;
}
/*-----------------------------------------------------------------------------
 * PLC Task Data Loader
 *---------------------------------------------------------------------------*/
static char *load_plc_task_data(FILE *fp, TASK_PROP *prop) {
    char *data = new char[prop->data_size];
    if (data == NULL) {
        LOGGER_ERR(EC_OOM, "loading plc task data");
        return NULL;
    }
    fread(data, prop->data_size, 1, fp);
    return data;
}
/*-----------------------------------------------------------------------------
 * PLC Task Code Loader
 *---------------------------------------------------------------------------*/
static char *load_inst_arg_addr(FILE *fp, char *data) {
    uint32_t arg_va;
    fread(&arg_va, sizeof(arg_va), 1, fp);
    int flag = arg_va & ARG_ADDR_FLAG_MASK;
    uint32_t arg_addr_offset = arg_va >> ARG_ADDR_FLAG_SIZE;
    char *arg_addr = NULL;
    switch (flag) {
        // TODO Error checker
        case ARG_ADDR_DATA: arg_addr = &data[arg_addr_offset];break;
        case ARG_ADDR_IO:   arg_addr = &io_shm[arg_addr_offset];break;
        default: LOGGER_ERR(EC_ARG_VA_INVALID, "");break;
    }
    //LOGGER_DBG("io_shm_addr = %d\ninst_arg_addr = %d", io_shm, arg_addr);
    return arg_addr;
}

static int load_plc_task_inst(FILE *fp, PLC_INST *inst, char *data, inst_desc_map_t *inst_desc) {
    fread(&inst->id, sizeof(inst->id), 1, fp);
    if (inst->id < 0 || MAX_TASK_INST_COUNT < inst->id) {
        LOGGER_ERR(EC_INST_ID_RANGE, "");
        return -1;
    }
    inst->arg_addr = new char*[(*inst_desc)[inst->id].args_count];
    if (inst->arg_addr == NULL) {
        LOGGER_ERR(EC_OOM, "loading instruction arguments");
        return -1;
    }
    for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
        if ((inst->arg_addr[i]=load_inst_arg_addr(fp, data)) == NULL) {
            LOGGER_ERR(EC_LOAD_INST_ARG_ADDR, "");
            delete inst->arg_addr;
            return -1;
        }
    }
    return 0;
}
static PLC_INST *load_plc_task_code(FILE *fp, TASK_PROP *prop, char *data, inst_desc_map_t *inst_desc) {
    PLC_INST *code = new PLC_INST[prop->inst_count];
    if (code == NULL) {
        LOGGER_ERR(EC_OOM, "loading plc task code");
        return NULL;
    }
    for (uint32_t i = 0; i < prop->inst_count; ++i) {
        if (load_plc_task_inst(fp, &code[i], data, inst_desc) < 0) {
            LOGGER_ERR(EC_LOAD_TASK_INST, "");
            delete code;
            return NULL;
        }
    }
    return code;
}

/*-----------------------------------------------------------------------------
 * PLC Task Loader
 *---------------------------------------------------------------------------*/
static int load_plc_task(FILE *fp, PLC_TASK *task, inst_desc_map_t *inst_desc) {
    if (load_task_prop(fp, &task->prop) < 0) {
        LOGGER_ERR(EC_LOAD_TASK_PROP, "");
        return -1;
    }
    if ((task->data=load_plc_task_data(fp, &task->prop)) == NULL) {
        LOGGER_ERR(EC_LOAD_TASK_DATA, "");
        return -1;
    }
    if ((task->code=load_plc_task_code(fp, &task->prop, task->data, inst_desc)) == NULL) {
        LOGGER_ERR(EC_LOAD_TASK_CODE, "");
        return -1;
    }
    //LOGGER_DBG("PLC_TASK:\n .data[0] = %d .data[n] = %d\n .instruction[0].id = %d",
        //task->data[0], task->data[task->prop.data_size-1], task->code[0].id);
    return 0;
}
/*-----------------------------------------------------------------------------
 * PLC Model Loader
 *---------------------------------------------------------------------------*/
bool obj_is_valid(FILE *fp) {
    OBJHeader header;
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
		"/BJ_HEADER:\n .magic = %s\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
		header.magic, header.type, header.order, header.version, header.machine);
	return true;
}
int load_plc_task_list(FILE *fp, TASK_LIST *task, inst_desc_map_t *inst_desc) {
    fread(&task->task_count, sizeof(task->task_count), 1, fp);
    if (MAX_TASK_COUNT < task->task_count) {
        LOGGER_ERR(EC_TASK_COUNT, "");
        return -1;
    }
    task->rt_task = new RT_TASK[task->task_count];
    task->plc_task = new PLC_TASK[task->task_count];
    if (task->rt_task == NULL || task->plc_task == NULL) {
        LOGGER_ERR(EC_OOM, "loading plc task");
        return -1;
    }
    for (int i = 0; i < task->task_count; ++i) {
        if (load_plc_task(fp, &task->plc_task[i], inst_desc) < 0) {
            LOGGER_ERR(EC_LOAD_PLC_TASK, "");
            delete task->rt_task;
            delete task->plc_task;
            return -1;
        }
    }
    return 0;
}
