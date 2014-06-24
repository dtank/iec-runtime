#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <stdint.h>
#include "binformat.h"

#define MAX_PLC_TASK_COUNT 10

/* Definition of PLC Task Property */
typedef struct {
	task_name_t *name;
	task_priority_t priority;
	task_interval_t interval;
} PLC_TASK_PROP;

/* Definition of PLC Task Data */
typedef char PLC_TASK_DATA;

/* Definition of PLC Task Code */
typedef struct {
	inst_id_t id;
	inst_arg_t *arg_list;
} PLC_TASK_INST;

typedef struct {
	PLC_TASK_INST **inst_list;
} PLC_TASK_CODE;

/* Definition of PLC Task Program */
typedef struct {
	PLC_TASK_DATA *data;
	PLC_TASK_CODE *code;
} PLC_TASK_PROG;

/* Definition of PLC Task */
typedef struct {
	PLC_TASK_PROP *property;
	PLC_TASK_PROG *program;
} PLC_TASK;

typedef struct {
	task_count_t task_count;
	RT_TASK *rt_task;
	PLC_TASK **plc_task;
} PLC_TASK_LIST;
#endif
