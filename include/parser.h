#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include "binformat.h"
#include "plcmodel.h"

task_count_t read_task_count(FILE *fp);

/* Task Property Segment Parser */
static task_name_size_t read_task_name_size(FILE *fp);
static task_name_t *read_task_name(FILE *fp, task_name_size_t size);
static task_priority_t read_task_priority(FILE *fp);
static task_interval_t read_task_interval(FILE *fp);
static TASK_PROPERTY_SEG_HEADER *read_task_property_seg_header(FILE *fp);
TASK_PROPERTY_SEG *read_task_property_seg(FILE *fp);

/* Constant/Data Segment Parser */
static seg_size_t read_seg_size(FILE *fp);
static DATA_SEG_HEADER *read_data_seg_header(FILE *fp);
DATA_SEG *read_data_seg(FILE *fp);

#endif
