#ifndef __LOADER_H__
#define __LOADER_H__

#include "plcmodel.h"

/*-----------------------------------------------------------------------------
 * Object File Verifier
 *---------------------------------------------------------------------------*/
int verify_obj(FILE *fp);
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
static int load_task_desc(FILE *fp, TaskDesc *task_desc);
static int load_pou_desc(FILE *fp, POUDesc *pou_desc);
static int load_string(FILE *fp, IString *str);
static int load_value(FILE *fp, IValue *value);
static int load_plc_task(FILE *fp, PLCTask *task);
int load_task_list(FILE *fp, TaskList *task_list);

#endif
