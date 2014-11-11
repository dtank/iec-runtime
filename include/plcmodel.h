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
#define MAX_LDI_COUNT 1
#define MAX_LDO_COUNT 1
#define MAX_LAI_COUNT 1
#define MAX_LAO_COUNT 1
#define MIN_IO_INTERVAL 2000000 /* unit: ns */
#define LDI_WORDSIZE 1 /* unit: Byte */
#define LDO_WORDSIZE 1 /* unit: Byte */
#define LAI_WORDSIZE 1 /* unit: Byte */
#define LAO_WORDSIZE 1 /* unit: Byte */
#define MAX_IO_MEM_SIZE (MAX_LDI_COUNT*LDI_WORDSIZE + \
        MAX_LDO_COUNT*LDO_WORDSIZE + \
        MAX_LAI_COUNT*LAI_WORDSIZE + \
        MAX_LAO_COUNT*LAO_WORDSIZE)
/* Servo */
#define MAX_AXIS_COUNT 8
#define MAX_AXIS_NAME_SIZE 16
#define MIN_AXIS_NODE_ID 1
#define MAX_AXIS_NODE_ID MAX_AXIS_COUNT
//#define MIN_AXIS_
#define MIN_SERVO_INTERVAL 2000000 /* unit: ns */
/* PLC Task */
#define MAX_TASK_COUNT 64
#define MAX_TASK_NAME_SIZE 16
#define MAX_TASK_PRIORITY 90
#define MIN_TASK_PRIORITY 50
#define MIN_TASK_INTERVAL 8000000
#define MAX_TASK_DATA_SIZE 65535 /* uint16_t */
#define MAX_INST_ID 65535 /* uint16_t */

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
	char name[MAX_AXIS_NAME_SIZE];         /* axis name, including '\0' */
	bool is_combined;   /* independent axis | combined axis */
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
} ROBOT_CONFIG;
/*-----------------------------------------------------------------------------
 * Definition of PLC Task
 *---------------------------------------------------------------------------*/
typedef struct {
    uint16_t id;      /* instruction id */
    char **arg_addr; /* actual address of instruction's arguments */
} PLC_INST;

typedef struct {
	char name[MAX_TASK_NAME_SIZE];
	uint8_t priority;
	uint32_t interval;
	uint32_t data_size;
	uint32_t inst_count;
    char *data; /* task data */
    PLC_INST *code; /* task code */
} PLC_TASK;
/*-----------------------------------------------------------------------------
 * Definition of PLC Medel
 *---------------------------------------------------------------------------*/
typedef struct {
    IO_CONFIG io_config;
    SERVO_CONFIG servo_config;
    RT_TASK *rt_task;
    PLC_TASK *plc_task;
} PLC_MODEL;

#endif
