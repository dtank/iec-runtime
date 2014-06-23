#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <stdint.h>
#include "binformat.h"

#define MAX_PLC_TASK_COUNT 10

/* defination of PARAMETERS */
typedef struct {
	uint32_t param_index;
} PARAM;

/* defination of INSTRUCTION*/
typedef struct {
	uint16_t id;
	PARAM *param_list;
} INST;

/* defination of CODE_SEG */
typedef INST *CODE_SEG;



/* defination of PROGRAM */
typedef struct {
	CODE_SEG code_seg;
	//CONST_SEG const_seg;
	//BIN_TDS tds;
} PROGRAM;

/* defination of PROPERTY */
typedef struct {
	task_name_t *name;
	task_priority_t priority;
	task_interval_t interval;
} PROPERTY;

/* defination of TASK */
typedef struct {
	PROPERTY property;
	PROGRAM program;
} TASK;

typedef struct {
	task_count_t task_count;
	TASK **task;
} TASK_LIST;
#endif
