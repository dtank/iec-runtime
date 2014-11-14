#ifndef __LOADER_H__
#define __LOADER_H__

#include "plcmodel.h"
#include "instruction.h"

/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
int load_io_config(FILE *fp, IO_CONFIG *io_config);
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
static int load_axis_config(FILE *fp, AXIS_CONFIG *axis_config);
int load_servo_config(FILE *fp, SERVO_CONFIG *servo_config);
/*-----------------------------------------------------------------------------
 * PLC Task Loader
 *---------------------------------------------------------------------------*/
static int load_task_prop(FILE *fp, TASK_PROP *task_prop);
static char *load_plc_task_data(FILE *fp, TASK_PROP *prop);
static char *load_inst_arg_addr(FILE *fp, char *data);
// TODO change to memcpy type
static PLC_INST *load_plc_task_inst(FILE *fp, char *data, inst_desc_map_t *inst_desc);
static PLC_INST *load_plc_task_code(FILE *fp, TASK_PROP *prop, char *data, inst_desc_map_t *inst_desc);
static int load_plc_task(FILE *fp, TASK_PROP *prop, PLC_TASK *task, inst_desc_map_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Model Loader
 *---------------------------------------------------------------------------*/
bool obj_is_valid(FILE *fp);
int load_plc_task_list(FILE *fp, TASK_LIST *task, inst_desc_map_t *inst_desc);

#endif
