#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/*-----------------------------------------------------------------------------
 * Definition of PLC Object File Header
 *---------------------------------------------------------------------------*/
#define MAGIC "\x7FPLC"
#define MAGIC_SIZE 5 /* including '\0' */
#define SYS_TYPE_32 1
#define SYS_TYPE_64 2
#define BYTE_ORDER_LIT 1
#define BYTE_ORDER_BIG 2
#define MACH_CORTEX_A8 1
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
typedef uint32_t io_refresh_interval_t;
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
#define AXIS_TYPE_FINITE 1
#define AXIS_TYPE_MODULO 2
#define OPER_MODE_POS 1
#define OPER_MODE_VEL 2
#define OPER_MODE_TOR 3
typedef struct {
	bool is_combined;   /* independent axis | combined axis */
	uint8_t name_size;  /* including '\0' */
	char *name;         /* axis name */
	uint8_t node_id;    /* axis id */
	uint8_t axis_type;  /* axis type: FINITE | MODULO */
	uint8_t oper_mode;  /* operating mode: POSITION | VELOCITY | TORQUE */
	double sw_limit_neg; /* negtive position limit (unit:) */
	double sw_limit_pos; /* positive position limit (unit:) */
	double max_vel;      /* velocity limit (unit:) */
	double max_acc;      /* accelaration limit (unit:) */
	double max_dec;      /* decelaration limit (unit:) */
	double max_jerk;     /* jerk limit (unit:) */
} OBJ_ACS; /* Axis Configuration Segment */

typedef struct {
	uint8_t axis_count;       /* number of axis */
	uint32_t update_interval; /* servo data update interval */
	OBJ_ACS *axis_group;      /* array of axis */
} OBJ_SCS; /* Servo Configuration Segment */

/*-----------------------------------------------------------------------------
 * Definition of PLC Task Property Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	uint8_t name_size;   /* size of plc task name, including '\0' */
	char *name;          /* plc task name */
	uint8_t priority;    /* plc task priority */
	uint32_t interval;   /* plc task period interval (unit: ns) */
	//uint32_t ptds_size;  [> size of plc task data segment <]
	//uint32_t inst_count; [> number of plc task instructions <]
} OBJ_PTPS; /* PLC Task Property Segment */

/*-----------------------------------------------------------------------------
 * Definition of PLC Task Data Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	uint32_t size; /* size of plc task data segment */
	char *data;    /* starting address of plc task data segment */
} OBJ_PTDS; /* PLC Task Data Segment */
/*-----------------------------------------------------------------------------
 * Definition of PLC Task Code Segment
 *---------------------------------------------------------------------------*/
typedef struct {
    uint16_t id;      /* instruction id */
    uint32_t *arg_va; /* vitual address(AKA index) of instruction's arguments */
} OBJ_INST;

typedef struct {
    uint32_t inst_count; /* number of instructions */
    OBJ_INST *inst;      /* list of instructions */
} OBJ_PTCS; /* PLC Task Code Segment */
/*-----------------------------------------------------------------------------
 * Definition of PLC Task List Segment
 *---------------------------------------------------------------------------*/
typedef struct {
    OBJ_PTPS prop; /* task property */
    OBJ_PTDS data; /* task data */
    OBJ_PTCS code; /* task code */
} OBJ_PTS; /* PLC Task Segment */

typedef struct {
    uint8_t task_count; /* number of plc task */
    OBJ_PTS *task;      /* list of plc task */
} OBJ_PTLS; /* PLC Task List Segment */
/*-----------------------------------------------------------------------------
 * Definition of PLC Object File
 *---------------------------------------------------------------------------*/
typedef struct {
    OBJ_HEADER header;
    OBJ_IOCS iocs;
    OBJ_SCS scs;
    OBJ_PTLS ptls;
} OBJ_FILE;

#define ARG_ADDR_INVALID 0x00
#define ARG_ADDR_DATA    0x01
#define ARG_ADDR_IO      0x02
#define ARG_ADDR_RESERVE 0x03
#define ARG_ADDR_FLAG_SIZE 2
#define ARG_ADDR_FLAG_MASK ~(0xFFFFFFFF << 2)


#endif
