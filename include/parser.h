#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include "binformat.h"
#include "plcmodel.h"

task_count_t read_task_count(FILE *fp);

/* PLC Task Property Parser */
static task_name_size_t read_task_name_size(FILE *fp);
static task_name_t *read_task_name(FILE *fp, task_name_size_t size);
static task_priority_t read_task_priority(FILE *fp);
static task_interval_t read_task_interval(FILE *fp);
static BIN_TPS_HEADER *read_tps_header(FILE *fp);
PLC_TASK_PROP *parse_plc_task_property(FILE *fp);

/* PLC Task Data Parser */
static seg_size_t read_seg_size(FILE *fp);
static BIN_TDS_HEADER *read_tds_header(FILE *fp);
PLC_TASK_DATA *parse_plc_task_data(FILE *fp);


#endif
