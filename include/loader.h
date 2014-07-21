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
 * PLC Task Configuration Segment Loader
 *---------------------------------------------------------------------------*/
//OBJ_PTCS *load_obj_ptcs(FILE *fp);
/*-----------------------------------------------------------------------------
 * PLC Task Property Loader
 *---------------------------------------------------------------------------*/
PLC_TASK_PROP *load_plc_task_property(FILE *fp);
/*-----------------------------------------------------------------------------
 * PLC Task Data Loader
 *---------------------------------------------------------------------------*/
PLC_TASK_DATA *load_plc_task_data(FILE *fp);
/* PLC Configuration Loader */
//static io_refresh_interval_t load_io_refresh_interval(FILE *fp);
//static task_count_t load_task_count(FILE *fp);
//PLC_CONFIG *load_plc_config(FILE *fp);

/* PLC Task Property Loader */
//static task_name_size_t load_task_name_size(FILE *fp);
//static task_name_t     *load_task_name(FILE *fp, task_name_size_t size);
//static task_priority_t  load_task_priority(FILE *fp);
//static task_interval_t  load_task_interval(FILE *fp);
//static tds_size_t       load_tds_size(FILE *fp);
//static inst_count_t     load_inst_count(FILE *fp);
//static PLC_TASK_PROP   *load_plc_task_property(FILE *fp);

/* PLC Task Data Loader */
//static PLC_TASK_DATA *load_plc_task_data(FILE *fp, PLC_TASK_PROP *property);

/* PLC Task Code Loader */
//static inst_id_t      load_inst_id(FILE *fp);
//static inst_arg_addr_t     *load_inst_arg(FILE *fp, PLC_TASK_DATA *data);
//static PLC_TASK_INST *load_plc_task_inst(FILE *fp, PLC_TASK_DATA *data, inst_desc_map_t *inst_desc);
//static PLC_TASK_CODE *load_plc_task_code(FILE *fp, PLC_TASK_PROP *property, PLC_TASK_CODE *data, inst_desc_map_t *inst_desc);

/* PLC Task Loader */
//static PLC_TASK *load_plc_task(FILE *fp, inst_desc_map_t *inst_desc);
//PLC_TASK_LIST   *load_plc_task_list(FILE *fp, PLC_CONFIG *config, inst_desc_map_t *inst_desc);
#endif
