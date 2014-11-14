#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

#define MAGIC_SIZE 5 /* including '\0' */
#define MAX_NAME_SIZE 16
#define MAX_AXIS_COUNT 2
#define MAX_TASK_COUNT 2
#define MAX_DATA_SIZE 64
#define MAX_INST_COUNT 10
#define MAX_ARG_COUNT 4

/*-----------------------------------------------------------------------------
 * Definition of PLC Object File Header
 *---------------------------------------------------------------------------*/
typedef struct {
	char magic[MAGIC_SIZE]; /* magic number */
	uint8_t type;           /* type of object file: 32BIT | 64BIT */
	uint8_t order;          /* byte order: LITTLE-ENDIAN | BIG-ENDIAN */
	uint8_t version;        /* version of object file (default: 1)*/
	uint8_t machine;        /* CPU platform */
} OBJ_HEADER;

/*-----------------------------------------------------------------------------
 * Definition of I/O Configuration Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	uint32_t update_interval; /* I/O data update interval */
	uint8_t ldi_count;        /* number of local digital input module */
	uint8_t ldo_count;        /* number of local digital output module */
	uint8_t lai_count;        /* number of local analog input module */
	uint8_t lao_count;        /* number of local analog output module */
} OBJ_IOCS; /* I/O Configuration Segment */

/*-----------------------------------------------------------------------------
 * Definition of Servo Configuration Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[MAX_NAME_SIZE]; /* axis name */
	bool is_combined;         /* independent axis | combined axis */
	uint8_t node_id;          /* axis id */
	uint8_t axis_type;        /* axis type: FINITE | MODULO */
	uint8_t oper_mode;        /* operating mode: POSITION | VELOCITY | TORQUE */
	double sw_limit_neg;      /* negtive position limit (unit:) */
	double sw_limit_pos;      /* positive position limit (unit:) */
	double max_vel;           /* velocity limit (unit:) */
	double max_acc;           /* accelaration limit (unit:) */
	double max_dec;           /* decelaration limit (unit:) */
	double max_jerk;          /* jerk limit (unit:) */
} OBJ_ACS; /* Axis Configuration Segment */

typedef struct {
	uint8_t axis_count;                 /* number of axis */
	uint32_t update_interval;           /* servo data update interval */
	OBJ_ACS axis_group[MAX_AXIS_COUNT]; /* array of axis */
} OBJ_SCS; /* Servo Configuration Segment */

/*-----------------------------------------------------------------------------
 * Definition of PLC Task Property Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[MAX_NAME_SIZE]; /* plc task name */
	uint8_t priority;         /* plc task priority */
	uint32_t interval;        /* plc task period interval (unit: ns) */
    uint32_t data_size;       /* size of plc task data segment */
    uint32_t inst_count;      /* number of plc task instructions */
} OBJ_PTPS; /* PLC Task Property Segment */

/*-----------------------------------------------------------------------------
 * Definition of PLC Task Code Segment
 *---------------------------------------------------------------------------*/
typedef struct {
    uint16_t id;                    /* instruction id */
    uint32_t arg_va[MAX_ARG_COUNT]; /* vitual address(AKA index) of instruction's arguments */
} OBJ_INST; /* Instruction */

/*-----------------------------------------------------------------------------
 * Definition of PLC Task List Segment
 *---------------------------------------------------------------------------*/
typedef struct {
    OBJ_PTPS prop;
	char data[MAX_DATA_SIZE];      /* plc task data segment */
    OBJ_INST inst[MAX_INST_COUNT]; /* task instructions */
} OBJ_PTS; /* PLC Task Segment */

/*-----------------------------------------------------------------------------
 * Definition of PLC Object File
 *---------------------------------------------------------------------------*/
typedef struct {
    OBJ_HEADER header;
    OBJ_IOCS iocs;
    OBJ_SCS scs;
    uint8_t task_count;
    OBJ_PTS task[MAX_TASK_COUNT];
} OBJ_FILE;

#endif
