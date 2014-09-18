#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <native/task.h>
#include "binformat.h"

/*-----------------------------------------------------------------------------
 * Definition of Runtime System Environment
 *---------------------------------------------------------------------------*/
/* Basic */
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
#define SYS_LDI_WORDSIZE 1 /* unit: Byte */
#define SYS_LDO_WORDSIZE 1 /* unit: Byte */
#define SYS_LAI_WORDSIZE 1 /* unit: Byte */
#define SYS_LAO_WORDSIZE 1 /* unit: Byte */
#define SYS_MAX_IO_MEM_SIZE (SYS_MAX_LDI_COUNT*SYS_LDI_WORDSIZE + \
        SYS_MAX_LDO_COUNT*SYS_LDO_WORDSIZE + \
        SYS_MAX_LAI_COUNT*SYS_LAI_WORDSIZE + \
        SYS_MAX_LAO_COUNT*SYS_LAO_WORDSIZE)
/* Servo */
#define SYS_MAX_AXIS_COUNT 8
#define SYS_MAX_AXIS_NAME_SIZE 16
#define SYS_MIN_AXIS_NODE_ID 1
#define SYS_MAX_AXIS_NODE_ID SYS_MAX_AXIS_COUNT
#define SYS_MIN_SERVO_INTERVAL 2000000 /* unit: ns */
/* PLC Task */
#define SYS_MAX_TASK_NAME_SIZE 16
#define SYS_MAX_TASK_PRIORITY 90
#define SYS_MIN_TASK_PRIORITY 50
#define SYS_MIN_TASK_INTERVAL 8000000
#define SYS_MAX_TASK_DATA_SIZE 65535
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
/*-----------------------------------------------------------------------------
 * Definition of Servo Configuration
 *---------------------------------------------------------------------------*/
typedef struct {
	bool is_combined;   /* independent axis | combined axis */
	char name[SYS_MAX_AXIS_NAME_SIZE];         /* axis name, including '\0' */
	uint8_t node_id;    /* axis id */
	uint8_t axis_type;  /* axis type: FINITE | MODULO */
	uint8_t oper_mode;  /* operating mode: POSITION | VELOCITY | TORQUE */
	double sw_limit_neg; /* negtive position limit (unit:) */
	double sw_limit_pos; /* positive position limit (unit:) */
	double max_vel;      /* velocity limit (unit:) */
	double max_acc;      /* accelaration limit (unit:) */
	double max_dec;      /* decelaration limit (unit:) */
	double max_jerk;     /* jerk limit (unit:) */
} AXIS_CONFIG;

typedef struct {
	uint8_t axis_count;       /* number of axis */
	uint32_t update_interval; /* Servo data update interval */
	AXIS_CONFIG *axis_group;  /* array of axis configuration */
} SERVO_CONFIG;
/*-----------------------------------------------------------------------------
 * Definition of Robot Configuration
 *---------------------------------------------------------------------------*/
typedef struct {
    int axis_count;
    int stub_param2;
} RobotConfig;
/*-----------------------------------------------------------------------------
 * Definition of PLC Task Property
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[SYS_MAX_TASK_NAME_SIZE];
	uint8_t priority;
	uint32_t interval;
	//uint32_t data_size;
	//uint32_t inst_count;
} PLC_TASK_PROP;
/*-----------------------------------------------------------------------------
 * Definition of PLC Task Data
 *---------------------------------------------------------------------------*/
typedef char PLC_TASK_DATA;
/*-----------------------------------------------------------------------------
 * Definition of PLC Task Code
 *---------------------------------------------------------------------------*/
typedef struct {
    uint16_t id;      /* instruction id */
    char **arg_addr; /* actual address of instruction's arguments */
} PLC_TASK_INST;

typedef struct {
    PLC_TASK_INST **inst;
} PLC_TASK_CODE;

/*-----------------------------------------------------------------------------
 * Definition of PLC Task List
 *---------------------------------------------------------------------------*/
typedef struct {
    PLC_TASK_PROP property; /* task property */
    PLC_TASK_DATA *data; /* task data */
    PLC_TASK_CODE code; /* task code */
} PLC_TASK; /* PLC Task Segment */

typedef struct {
    RT_TASK *rt_task;
    PLC_TASK *plc_task;
} PLC_TASK_LIST;

#endif
