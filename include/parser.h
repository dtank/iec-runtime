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
static BIN_TPS_HEADER  *read_tps_header(FILE *fp);
static PLC_TASK_PROP   *read_plc_task_property(FILE *fp);

/* PLC Task Data Parser */
static seg_size_t      read_seg_size(FILE *fp);
static BIN_TDS_HEADER *read_tds_header(FILE *fp);
static PLC_TASK_DATA  *read_plc_task_data(FILE *fp);

/* PLC Task Code Parser */
static inst_count_t    read_inst_count(FILE *fp);
static inst_id_t       read_inst_id(FILE *fp);
static inst_arg_t      read_inst_arg(FILE *fp);
static BIN_TCS_HEADER *read_tcs_header(FILE *fp);
static PLC_TASK_INST  *read_plc_task_inst(FILE *fp, inst_desc_map_t *inst_desc);
static PLC_TASK_CODE  *read_plc_task_code(FILE *fp, inst_desc_map_t *info);

/* PLC Task Parser */
static PLC_TASK_PROG *read_plc_task_program(FILE *fp, inst_desc_map_t *info);
static PLC_TASK      *read_plc_task(FILE *fp, inst_desc_map_t *info);
PLC_TASK_LIST        *read_plc_task_list(FILE *fp, inst_desc_map_t *info);
#endif
