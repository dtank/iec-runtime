#include <string.h>
#include <map>
#include "loader.h"
#include "objfile.h"
#include "sysenv.h"
#include "istring.h"
#include "logger.h"

using namespace std;

/*-----------------------------------------------------------------------------
 * Helper Funciton Macros
 *---------------------------------------------------------------------------*/
#define loadv(fp, varp) {fread((varp), sizeof(*(varp)), 1, fp);}
#define loadvs(fp, varp, size) {fread((varp), (size), 1, fp);}
#define verify(exp, ecode, msg) { \
    if (exp) {                    \
        LOGGER_ERR(ecode, msg);   \
        return -1;                \
    }}
/* pd: pou descriptor */
#define POU_REGC(pd) ((pd).input_count + (pd).output_count + (pd).local_count)
/*-----------------------------------------------------------------------------
 * Object File Verifier
 *---------------------------------------------------------------------------*/
int verify_obj(FILE *fp) {
    assert(fp != NULL);

    OBJHeader header;
    loadv(fp, &header); /* rely on byte alignment */
    verify(strcmp(header.magic, MAGIC) != 0, EC_PLC_FILE, "");
    verify(header.type != SYS_TYPE, EC_SYS_TYPE, "");
    verify(header.order != SYS_BYTE_ORDER, EC_BYTE_ORDER, "");
    verify(SYS_VERSION < header.version, EC_SYS_VERSION, "");
    verify(header.machine != SYS_MACHINE, EC_SYS_MACHINE, "");
	LOGGER_DBG(DFLAG_LONG,
		"OBJHeader:\n .magic = %s\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
		header.magic, header.type, header.order, header.version, header.machine);
	return 0;
}
/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
int load_io_config(FILE *fp, IOConfig *io_config) {
    assert(fp != NULL);
    assert(io_config != NULL);

    loadv(fp, io_config); /* rely on byte alignment */
    verify(io_config->update_interval < MIN_IO_INTERVAL, EC_IO_INTERVAL, "");
    verify(MAX_LDI_COUNT < io_config->ldi_count, EC_LDI_COUNT, "");
    verify(MAX_LDO_COUNT < io_config->ldo_count, EC_LDO_COUNT, "");
    verify(MAX_LAI_COUNT < io_config->lai_count, EC_LAI_COUNT, "");
    verify(MAX_LAO_COUNT < io_config->lao_count, EC_LAO_COUNT, "");
    verify(MAX_RDI_COUNT < io_config->rdi_count, EC_RDI_COUNT, "");
    verify(MAX_RDO_COUNT < io_config->rdo_count, EC_RDO_COUNT, "");
    verify(MAX_RAI_COUNT < io_config->rai_count, EC_RAI_COUNT, "");
    verify(MAX_RAO_COUNT < io_config->rao_count, EC_RAO_COUNT, "");
	LOGGER_DBG(DFLAG_LONG,
		"IOConfig:\n .update_interval = %d\n .ldi_count = %d\n .ldo_count = %d\n .lai_count = %d\n"
        " .lao_count = %d\n .rdi_count = %d\n .rdo_count = %d\n .rai_count = %d\n .rao_count = %d",
		io_config->update_interval, io_config->ldi_count, io_config->ldo_count, io_config->lai_count,
        io_config->lao_count, io_config->rdi_count, io_config->rdo_count, io_config->rai_count, io_config->rao_count);
	return 0;
}
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
static int load_axis_config(FILE *fp, AxisConfig *axis_config) {
    assert(fp != NULL);
    assert(axis_config != NULL);

    /* ORDER SENSITIVE */
    loadvs(fp, axis_config->name, MAX_AXIS_NAME_SIZE);
    loadv(fp, &axis_config->id);
    loadv(fp, &axis_config->type);
    loadv(fp, &axis_config->combined);
    loadv(fp, &axis_config->opmode);
    loadv(fp, &axis_config->min_pos);
    loadv(fp, &axis_config->max_pos);
    loadv(fp, &axis_config->max_vel);
    loadv(fp, &axis_config->max_acc);
    loadv(fp, &axis_config->max_dec);
    loadv(fp, &axis_config->max_jerk);
    verify(axis_config->id < MIN_AXIS_ID || MAX_AXIS_ID < axis_config->id, EC_AXIS_ID_RANGE, "");
    verify(axis_config->type != AXIS_TYPE_FINITE && axis_config->type != AXIS_TYPE_MODULO, EC_AXIS_TYPE, "");
    verify(axis_config->combined != AXIS_INDEPENDENT && axis_config->combined != AXIS_COMBINED, EC_AXIS_COMBINE, "");
    verify(axis_config->opmode < OPMODE_POS || OPMODE_TOR < axis_config->opmode, EC_AXIS_OPMODE, "");
    verify(axis_config->max_pos < axis_config->min_pos, EC_AXIS_SW, "");
    verify(axis_config->max_vel < 0.0, EC_AXIS_MAX_VEL, "");
    verify(axis_config->max_acc < 0.0, EC_AXIS_MAX_ACC, "");
    verify(axis_config->max_dec < 0.0, EC_AXIS_MAX_DEC, "");
    verify(axis_config->max_jerk < 0.0, EC_AXIS_MAX_JERK, "");
	LOGGER_DBG(DFLAG_SHORT,
		"AxisConfig:\n .name = %s\n .id = %d\n .type = %d\n .combined = %d\n .opmode = %d\n"
        " .min_pos = %f\n .max_pos = %f\n .max_vel = %f\n .max_acc = %f\n .max_dec = %f\n .max_jerk = %f",
		axis_config->name, axis_config->id, axis_config->type, axis_config->combined, axis_config->opmode,
        axis_config->min_pos, axis_config->max_pos, axis_config->max_vel, axis_config->max_acc, axis_config->max_dec, axis_config->max_jerk);
	return 0;
}
int load_servo_config(FILE *fp, ServoConfig *servo_config) {
    assert(fp != NULL);
    assert(servo_config != NULL);

    /* ORDER SENSITIVE */
    loadv(fp, &servo_config->axis_count);
    loadv(fp, &servo_config->update_interval);
    verify(MAX_AXIS_COUNT < servo_config->axis_count, EC_AXIS_COUNT, "");
    verify(servo_config->update_interval < MIN_SERVO_INTERVAL, EC_SERVO_INTERVAL, "");
    servo_config->axis_config = new AxisConfig[servo_config->axis_count];
    verify(servo_config->axis_config == NULL, EC_OOM, "loading axis configuration");
	LOGGER_DBG(DFLAG_LONG, "ServoConfig:\n .axis_count = %d\n .update_interval = %d",
        servo_config->axis_count, servo_config->update_interval);
	for (int i = 0; i < servo_config->axis_count; ++i) {
        if (load_axis_config(fp, &servo_config->axis_config[i]) < 0) {
            LOGGER_ERR(EC_LOAD_SERVO_CONFIG, "");
            delete[] servo_config->axis_config;
            return -1;
        }
	}
	return 0;
}
/*-----------------------------------------------------------------------------
 * PLC Task List Loader
 *---------------------------------------------------------------------------*/
static int load_task_desc(FILE *fp, TaskDesc *task_desc) {
    assert(fp != NULL);
    assert(task_desc != NULL);

    /* ORDER SENSITIVE */
    loadvs(fp, task_desc->name, MAX_TASK_NAME_SIZE);
    loadv(fp, &task_desc->priority);
    loadv(fp, &task_desc->type);
    loadv(fp, &task_desc->signal);
    loadv(fp, &task_desc->interval);
    loadv(fp, &task_desc->sp_size);
    loadv(fp, &task_desc->cs_size);
    loadv(fp, &task_desc->pou_count);
    loadv(fp, &task_desc->const_count);
    loadv(fp, &task_desc->global_count);
    loadv(fp, &task_desc->inst_count);
    verify(task_desc->priority < MIN_TASK_PRIORITY || MAX_TASK_PRIORITY < task_desc->priority, EC_TASK_PRIORITY, "");
    verify(task_desc->type != TASK_TYPE_SIGNAL && task_desc->type != TASK_TYPE_INTERVAL, EC_TASK_TYPE, "");
    verify(MAX_TASK_SIGNAL < task_desc->signal, EC_TASK_SIGNAL, "");
    verify(task_desc->interval < MIN_TASK_INTERVAL, EC_TASK_INTERVAL, "");
    verify(MAX_SP_SIZE < task_desc->sp_size, EC_LOAD_SP_SIZE, "");
    verify(MAX_CS_CAP < task_desc->cs_size, EC_LOAD_CS_CAP, "");
    verify(MAX_TASK_POU_COUNT < task_desc->pou_count, EC_TASK_POU_COUNT, "");
    verify(MAX_TASK_CONST_COUNT < task_desc->const_count, EC_TASK_CONST_COUNT, "");
    verify(MAX_TASK_GLOBAL_COUNT < task_desc->global_count, EC_TASK_GLOBAL_COUNT, "");
    LOGGER_DBG(DFLAG_SHORT, "TaskDesc:\n .name = %s\n .priority = %d\n .type = %d\n .signal = %d\n .interval = %d\n .sp_size = %d\n"
        " .cs_size = %d\n .pou_count = %d\n .const_count = %d\n .global_count = %d\n .inst_count = %d",
        task_desc->name, task_desc->priority, task_desc->type, task_desc->signal, task_desc->interval, task_desc->sp_size,
        task_desc->cs_size, task_desc->pou_count, task_desc->const_count, task_desc->global_count, task_desc->inst_count);
    return 0;
}
static int load_pou_desc(FILE *fp, UPOUDesc *pou_desc) {
    assert(fp != NULL);
    assert(pou_desc != NULL);

    /* ORDER SENSITIVE */
    loadvs(fp, pou_desc->name, MAX_POU_NAME_SIZE);
    loadv(fp, &pou_desc->input_count);
    loadv(fp, &pou_desc->inout_count);
    loadv(fp, &pou_desc->output_count);
    loadv(fp, &pou_desc->local_count);
    loadv(fp, &pou_desc->entry);
    verify(MAX_POU_PARAM_COUNT < (pou_desc->input_count+pou_desc->inout_count+pou_desc->output_count+pou_desc->local_count), EC_POU_PARAM_COUNT, "");
    LOGGER_DBG(DFLAG_SHORT, "UPOUDesc:\n .name = %s\n .input_count = %d\n .inout_count = %d\n .output_count = %d\n .local_count = %d\n .entry = %d",
        pou_desc->name, pou_desc->input_count, pou_desc->inout_count, pou_desc->output_count, pou_desc->local_count, pou_desc->entry);
    return 0;
}
static int load_string(FILE *fp, IString *str, StrPool *sp) {
    assert(fp != NULL);
    assert(str != NULL);

    loadv(fp, &str->length);
    verify(MAX_STRLEN < str->length, EC_LOAD_STRLEN, "");
    char strtemp[str->length];
    loadvs(fp, strtemp, str->length);
    if ((str->str=sp_add(sp, strtemp, str->length)) == NULL) {
        return -1;
    }
    return 0;
}
static int load_value(FILE *fp, IValue *value, StrPool *sp) {
    assert(fp != NULL);
    assert(value != NULL);

    loadv(fp, &value->type);
    verify(value->type < MIN_VTYPE || MAX_VTYPE < value->type, EC_LOAD_VTYPE, "");
    switch (value->type) {
        case TINT:
            loadv(fp, &value->v.value_i); break;
        case TDOUBLE:
            loadv(fp, &value->v.value_d); break;
        case TSTRING:
            verify(load_string(fp, &value->v.value_s, sp) < 0, EC_LOAD_STRING, ""); break;
        default: break;
    }
    dump_value("loaded value", *value);
    return 0;
}
static int load_plc_task(FILE *fp, PLCTask *task) {
    assert(fp != NULL);
    assert(task != NULL);

    verify(load_task_desc(fp, &task->task_desc) < 0, EC_LOAD_TASK_DESC, "");
    verify(sp_init(&task->strpool, task->task_desc.sp_size) < 0, EC_SP_INIT, ""); /* MUST initialize before loading constant/global */
    task->pou_desc = new UPOUDesc[task->task_desc.pou_count];
    task->vconst = new IValue[task->task_desc.const_count];
    task->vglobal = new IValue[task->task_desc.global_count];
    task->code = new Instruction[task->task_desc.inst_count];
    verify(task->pou_desc==NULL || task->vconst==NULL || task->vglobal==NULL || task->code==NULL, EC_OOM, "loading plc task");
    for (int i = 0; i < task->task_desc.pou_count; i++) {
        if (load_pou_desc(fp, &task->pou_desc[i]) < 0) {
            LOGGER_ERR(EC_LOAD_POU_DESC, "");
            delete[] task->pou_desc;
            delete[] task->vconst;
            delete[] task->vglobal;
            delete[] task->code;
            return -1;
        }
    }
    for (int i = 0; i < task->task_desc.const_count; i++) {
        if (load_value(fp, &task->vconst[i], &task->strpool) < 0) {
            LOGGER_ERR(EC_LOAD_TASK_CONST, "");
            delete[] task->pou_desc;
            delete[] task->vconst;
            delete[] task->vglobal;
            delete[] task->code;
            return -1;
        }
    }
    for (int i = 0; i < task->task_desc.global_count; i++) {
        if (load_value(fp, &task->vglobal[i], &task->strpool) < 0) {
            LOGGER_ERR(EC_LOAD_TASK_GLOBAL, "");
            delete[] task->pou_desc;
            delete[] task->vconst;
            delete[] task->vglobal;
            delete[] task->code;
            return -1;
        }
    }
    loadvs(fp, task->code, task->task_desc.inst_count*sizeof(Instruction));
    for (uint32_t i = 0; i < task->task_desc.inst_count; i++) { // TODO verify instruction
        verify(GET_OPCODE(task->code[i]) < MIN_OPCODE || MAX_OPCODE < GET_OPCODE(task->code[i]), EC_LOAD_OPCODE, "");
        LOGGER_DBG(DFLAG_SHORT, "loaded instruction[%d] = %0#10x, OpCode = %d", i, task->code[i], GET_OPCODE(task->code[i]));
    }
    verify(cs_init(&task->stack, task->task_desc.cs_size) < 0, EC_CS_INIT, ""); /* MUST initialize after loading POU descriptor */
    /* create main() stack frame manually */
    SFrame main;
    sf_init(main, 0, 0, POU_REGC(task->pou_desc[0]));
    verify(main.reg == NULL, EC_OOM, "initializing main() stack frame");
    cs_push(task->stack, main);
    task->pc = 0;
    return 0;
}

int load_task_list(FILE *fp, TaskList *task_list) {
    assert(fp != NULL);
    assert(task_list != NULL);

    /* ORDER SENSITIVE */
    loadv(fp, &task_list->task_count);
    verify(MAX_TASK_COUNT < task_list->task_count, EC_TASK_COUNT, "");
    task_list->rt_task = new RT_TASK[task_list->task_count];
    task_list->plc_task = new PLCTask[task_list->task_count];
    verify(task_list->rt_task == NULL || task_list->plc_task == NULL, EC_OOM, "loading plc task");
    LOGGER_DBG(DFLAG_LONG, "PLCList:\n .task_count = %d", task_list->task_count);
    for (int i = 0; i < task_list->task_count; i++) {
        if (load_plc_task(fp, &task_list->plc_task[i]) < 0) {
            LOGGER_ERR(EC_LOAD_PLC_TASK, "");
            delete[] task_list->rt_task;
            delete[] task_list->plc_task;
            return -1;
        }
    }
    return 0;
}
