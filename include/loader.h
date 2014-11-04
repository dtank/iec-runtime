#ifndef __LOADER_H__
#define __LOADER_H__

#include "binformat.h"
#include "plcmodel.h"
#include "instruction.h"

/*-----------------------------------------------------------------------------
 * I/O Configuration Loader
 *---------------------------------------------------------------------------*/
IO_CONFIG *load_io_config(FILE *fp);
/*-----------------------------------------------------------------------------
 * Servo Configuration Loader
 *---------------------------------------------------------------------------*/
AXIS_CONFIG *load_axis_config(FILE *fp);
SERVO_CONFIG *load_servo_config(FILE *fp);
/*-----------------------------------------------------------------------------
 * PLC Task Loader
 *---------------------------------------------------------------------------*/
char *load_plc_task_data(FILE *fp);
char *load_inst_arg_addr(FILE *fp, char *data);
PLC_INST *load_plc_task_inst(FILE *fp, char *data, inst_desc_map_t *inst_desc);
PLC_INST *load_plc_task_code(FILE *fp, char *data, inst_desc_map_t *inst_desc);
PLC_TASK *load_plc_task(FILE *fp, inst_desc_map_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Model Loader
 *---------------------------------------------------------------------------*/
bool obj_is_valid(FILE *fp);
PLC_MODEL *load_plc_model(FILE *fp, inst_desc_map_t *inst_desc);

#endif
