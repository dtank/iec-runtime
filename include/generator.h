#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "binformat.h"
void generate_task_count(FILE *fp, task_count_t count);
void generate_task_name_size(FILE *fp, task_name_size_t size);
void generate_task_name(FILE *fp, task_name_t name);
void generate_task_priority(FILE *fp, task_priority_t priority);
void generate_task_interval(FILE *fp, task_interval_t interval);
void generate_task_property_seg_header(FILE *fp, task_property_seg_header property_seg_header);
void generate_task_property_seg(FILE *fp, task_property_seg property_seg);

#endif
