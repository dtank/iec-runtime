#ifndef __LOADER_H__
#define __LOADER_H__

#include "plcmodel.h"
#include "opcode.h"

bool verify_obj(FILE *fp);
/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
int load_io_config(FILE *fp, IOConfig *io_config);
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
static int load_axis_config(FILE *fp, AxisConfig *axis_config);
int load_servo_config(FILE *fp, ServoConfig *servo_config);
/*-----------------------------------------------------------------------------
 * PLC Task List Loader
 *---------------------------------------------------------------------------*/
static int load_task_prop(FILE *fp, TASK_PROP *task_prop);
static char *load_plc_task_data(FILE *fp, TASK_PROP *prop);
static char *load_inst_arg_addr(FILE *fp, char *data);
// TODO change to memcpy type
static PLC_INST *load_plc_task_inst(FILE *fp, char *data, inst_desc_map_t *inst_desc);
static PLC_INST *load_plc_task_code(FILE *fp, TASK_PROP *prop, char *data, inst_desc_map_t *inst_desc);
static int load_plc_task(FILE *fp, TASK_PROP *prop, PLC_TASK *task, inst_desc_map_t *inst_desc);
int load_plc_task_list(FILE *fp, TASK_LIST *task, inst_desc_map_t *inst_desc);

#endif
