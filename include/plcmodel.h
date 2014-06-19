#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <stdint.h>
#include "binformat.h"

#define MAX_PLC_TASK_COUNT 10

/* defination of PARAMETERS */
typedef struct param {
	uint32_t param_index;
} PARAM;

/* defination of INSTRUCTION*/
typedef struct instruction {
	uint16_t id;
	PARAM *param_list;
} INST;

/* defination of CODE_SEG */
typedef INST *CODE_SEG;

/* defination of CONST_SEG */
typedef void *CONST_SEG;

/* defination of DATA_SEG */
typedef void *DATA_SEG;

/* defination of PROGRAM */
typedef struct program {
	CODE_SEG code_seg;
	CONST_SEG const_seg;
	DATA_SEG data_seg;
} PROGRAM;

/* defination of PROPERTY */
typedef struct property {
	task_name_t name;
	task_priority_t priority;
	task_interval_t interval;
} PROPERTY;

/* defination of TASK */
typedef struct task {
	PROPERTY property;
	PROGRAM program;
} TASK;

typedef struct task_list {
	task_count_t task_count;
	TASK **task;
} TASK_LIST;
#endif
