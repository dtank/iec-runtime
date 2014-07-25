#ifndef __LOADER_H__
#define __LOADER_H__

#include "binformat.h"
#include "plcmodel.h"
#include "instruction.h"

/*-----------------------------------------------------------------------------
 * PLC Object File Header Loader
 *---------------------------------------------------------------------------*/
OBJ_HEADER *load_obj_header(FILE *fp);
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
 * PLC Task Property Loader
 *---------------------------------------------------------------------------*/
PLC_TASK_PROP *load_plc_task_property(FILE *fp);
/*-----------------------------------------------------------------------------
 * PLC Task Data Loader
 *---------------------------------------------------------------------------*/
PLC_TASK_DATA *load_plc_task_data(FILE *fp);
/*-----------------------------------------------------------------------------
 * PLC Task Code Loader
 *---------------------------------------------------------------------------*/
char *load_inst_arg_addr(FILE *fp, PLC_TASK_DATA *data);
PLC_TASK_INST *load_plc_task_inst(FILE *fp, PLC_TASK_DATA *data, inst_desc_map_t inst_desc);
PLC_TASK_CODE *load_plc_task_code(FILE *fp, PLC_TASK_CODE *data, inst_desc_map_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Task List Loader
 *---------------------------------------------------------------------------*/
PLC_TASK *load_plc_task(FILE *fp, inst_desc_map_t *inst_desc);
PLC_TASK_LIST *load_plc_task_list(FILE *fp, inst_desc_map_t *inst_desc);

#endif
