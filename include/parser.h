#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include "binformat.h"
#include "plcmodel.h"

task_count_t read_task_count(FILE *fp);
task_name_size_t read_task_name_size(FILE *fp);
task_name_t read_task_name(FILE *fp);
task_priority_t read_task_priority(FILE *fp);
task_interval_t read_task_interval(FILE *fp);
PROPERTY read_task_property(FILE *fp);

#endif
