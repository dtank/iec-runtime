#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <native/task.h>
#include "binformat.h"
#include "plcmodel.h"
#include "instruction.h"


/* PLC Task Property Parser */
static task_count_t     read_task_count(FILE *fp);
static task_name_size_t read_task_name_size(FILE *fp);
static task_name_t     *read_task_name(FILE *fp, task_name_size_t size);
static task_priority_t  read_task_priority(FILE *fp);
static task_interval_t  read_task_interval(FILE *fp);
static tds_size_t      read_tds_size(FILE *fp);
static inst_count_t    read_inst_count(FILE *fp);
static PLC_TASK_PROP   *read_plc_task_property(FILE *fp);

/* PLC Task Data Parser */
static PLC_TASK_DATA  *read_plc_task_data(FILE *fp, PLC_TASK_PROP *property);

/* PLC Task Code Parser */
static inst_id_t       read_inst_id(FILE *fp);
static inst_arg_t      read_inst_arg(FILE *fp);
static PLC_TASK_INST  *read_plc_task_inst(FILE *fp, inst_desc_map_t *inst_desc);
static PLC_TASK_CODE  *read_plc_task_code(FILE *fp, PLC_TASK_PROP *property, inst_desc_map_t *inst_desc);

/* PLC Task Parser */
static PLC_TASK_PROG *read_plc_task_program(FILE *fp, PLC_TASK_PROP *property, inst_desc_map_t *inst_desc);
static PLC_TASK      *read_plc_task(FILE *fp, inst_desc_map_t *inst_desc);
PLC_TASK_LIST        *read_plc_task_list(FILE *fp, inst_desc_map_t *inst_desc);
#endif
