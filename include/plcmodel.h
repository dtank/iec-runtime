#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <native/task.h>
#include "binformat.h"

/*-----------------------------------------------------------------------------
 * Definition of Runtime System Environment
 *---------------------------------------------------------------------------*/
/* basic */
#define SYS_TYPE SYS_TYPE_32
#define SYS_BYTE_ORDER BYTE_ORDER_LIT
#define SYS_VERSION 1
#define SYS_MACHINE MACH_CORTEX_A8
/* I/O */
#define SYS_MAX_LDI_COUNT 1
#define SYS_MAX_LDO_COUNT 1
#define SYS_MAX_LAI_COUNT 1
#define SYS_MAX_LAO_COUNT 1
#define SYS_MIN_IO_INTERVAL 2000000 /* unit: ns */

/*-----------------------------------------------------------------------------
 * Definition of I/O Configuration
 *---------------------------------------------------------------------------*/
typedef struct {
	uint32_t update_interval; /* I/O data update interval */
	uint8_t ldi_count;        /* number of local digital input module */
	uint8_t ldo_count;        /* number of local digital output module */
	uint8_t lai_count;        /* number of local analog input module */
	uint8_t lao_count;        /* number of local analog output module */
} IO_CONFIG;
/* Definition of PLC Configuration */
typedef struct {
	io_refresh_interval_t io_refresh_interval;
	task_count_t task_count;
} PLC_CONFIG;

/* Definition of PLC Task Property */
typedef struct {
	task_name_size_t name_size;
	task_name_t *name;
	task_priority_t priority;
	task_interval_t interval;
	tds_size_t tds_size;
	inst_count_t inst_count;
} PLC_TASK_PROP;

/* Definition of PLC Task Data */
typedef char PLC_TASK_DATA;

/* Definition of PLC Task Code */
typedef char inst_arg_addr_t;
typedef struct {
	inst_id_t id;
	inst_arg_addr_t **arg_addr;
} PLC_TASK_INST;

typedef struct {
	PLC_TASK_INST **inst;
} PLC_TASK_CODE;

/* Definition of PLC Task */
typedef struct {
	PLC_TASK_PROP *property;
	PLC_TASK_DATA *data;
	PLC_TASK_CODE *code;
} PLC_TASK;

typedef struct {
	RT_TASK *rt_task;
	PLC_TASK **plc_task;
} PLC_TASK_LIST;
#endif
