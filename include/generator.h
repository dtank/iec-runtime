#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "binformat.h"
void generate_task_count(FILE *fp, task_count_t count);

/* Task Property Segment Generator */
static void generate_task_name_size(FILE *fp, task_name_size_t size);
static void generate_task_name(FILE *fp, task_name_t *name);
static void generate_task_priority(FILE *fp, task_priority_t priority);
static void generate_task_interval(FILE *fp, task_interval_t interval);
void generate_task_property_seg_header(FILE *fp, TASK_PROPERTY_SEG_HEADER *property_seg_header);
void generate_task_property_seg(FILE *fp, TASK_PROPERTY_SEG *property_seg);

/* Constant/Data Segment Generator */
static void generate_seg_size(FILE *fp, seg_size_t size);
void generate_data_seg_header(FILE *fp, DATA_SEG_HEADER *data_seg_header);
void generate_data_seg(FILE *fp, DATA_SEG_HEADER *data_seg_header, DATA_SEG *data_seg);


#endif
