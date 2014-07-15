#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/*-----------------------------------------------------------------------------
 * Definition of PLC Object File Header
 *---------------------------------------------------------------------------*/
#define MAGIC "\x7FPLC"
#define MAGIC_SIZE 5 /* including '\0' */
#define OBJ_TYPE_32 1
#define OBJ_TYPE_64 2
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
#define MAX_AXIS_COUNT 8
#define MAX_AXIS_NAME_SIZE 10
#define MIN_AXIS_NODE_ID 1
#define MAX_AXIS_NODE_ID 127
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
	float sw_limit_neg; /* negtive position limit (unit:) */
	float sw_limit_pos; /* positive position limit (unit:) */
	float max_vel;      /* velocity limit (unit:) */
	float max_acc;      /* accelaration limit (unit:) */
	float max_dec;      /* decelaration limit (unit:) */
	float max_jerk;     /* jerk limit (unit:) */
} OBJ_ACS; /* Axis Configuration Segment */

typedef struct {
	uint8_t axis_count;  /* number of axis */
	OBJ_ACS *axis_group; /* array of axis */
} OBJ_SCS; /* Servo Configuration Segment */
/*-----------------------------------------------------------------------------
 * Definition of PLC Task Configuration Segment
 *---------------------------------------------------------------------------*/
typedef uint8_t task_count_t;


typedef struct {
	io_refresh_interval_t io_refresh_interval;
	task_count_t task_count;
} BIN_HEADER;

/*-----------------------------------------------------------------------------
 * Definition of PLC Object File Body
 *---------------------------------------------------------------------------*/
typedef uint8_t  task_name_size_t;
typedef char     task_name_t;
typedef uint8_t  task_priority_t;
typedef uint32_t task_interval_t;
typedef uint64_t tds_size_t;
typedef uint32_t inst_count_t;
typedef uint16_t inst_id_t;
typedef uint32_t inst_arg_va_t;

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
#define ARG_ADDR_INVALID 0x00
#define ARG_ADDR_DATA    0x01
#define ARG_ADDR_IO      0x02
#define ARG_ADDR_RESERVE 0x03
#define ARG_ADDR_FLAG_SIZE 2
#define ARG_ADDR_FLAG_MASK ~(0xFFFFFFFF << 2)
typedef struct {
	inst_id_t id;
	inst_arg_va_t arg_va[3];
} BIN_INST;

typedef struct {
	BIN_INST inst[50];
} BIN_TCS;



#endif
