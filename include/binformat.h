#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/* PLC Task Segment */
typedef uint8_t  task_count_t;
typedef uint8_t  task_name_size_t;
typedef char     task_name_t;
typedef uint8_t  task_priority_t;
typedef uint32_t task_interval_t;
typedef uint64_t tds_size_t;
typedef uint32_t inst_count_t;
typedef uint16_t inst_id_t;
typedef uint32_t inst_arg_t;

/* Definition of Task Property Segment */
typedef struct {
	task_name_size_t name_size;
	task_name_t *name;
	task_priority_t priority;
	task_interval_t interval;
	tds_size_t tds_size;
	inst_count_t inst_count;
} BIN_TPS;

/* Definition of Task Data Segment */
typedef char BIN_TDS;

 /*Definition of Task Code Segment */
typedef struct {
	inst_id_t id;
	inst_arg_t arg_list[3];
} BIN_INST;

typedef struct {
	BIN_INST inst_list[50];
} BIN_TCS;



#endif
