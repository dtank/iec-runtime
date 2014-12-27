#ifndef __OBJ_STRUCT_H__
#define __OBJ_STRUCT_H__

#include <stdint.h>

/*-----------------------------------------------------------------------------
 * Limitations
 *---------------------------------------------------------------------------*/
#define MAGIC "\x7FPLC"
#define MAGIC_SIZE 5 /* including '\0' */
#define MAX_AXIS_NAME_SIZE 16
#define MAX_AXIS_COUNT 2
/* PLC Task */
#define MAX_TASK_NAME_SIZE 16
#define MAX_POU_NAME_SIZE 20
#define MAX_TASK_COUNT 2
#define MAX_POU_COUNT 4
#define MAX_STR_LENGTH 8
#define MAX_CONST_COUNT 8
#define MAX_GLOBAL_COUNT 8
#define MAX_INST_COUNT 20

/*-----------------------------------------------------------------------------
 * Value Type Tag
 *---------------------------------------------------------------------------*/
#define TINT    1
#define TDOUBLE 2
#define TSTRING 3
/*-----------------------------------------------------------------------------
 * Definition of PLC Object File Header
 *---------------------------------------------------------------------------*/
typedef struct {
    char magic[MAGIC_SIZE]; /* magic number */
    uint8_t type;           /* type of object file: 32BIT | 64BIT */
    uint8_t order;          /* byte order: LITTLE-ENDIAN | BIG-ENDIAN */
    uint8_t version;        /* version of object file (default: 1) */
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
	uint8_t rdi_count;        /* number of local digital input module */
	uint8_t rdo_count;        /* number of local digital output module */
	uint8_t rai_count;        /* number of local analog input module */
	uint8_t rao_count;        /* number of local analog output module */
} OBJ_IOCS; /* I/O Configuration Segment */

/*-----------------------------------------------------------------------------
 * Definition of Servo Configuration Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[MAX_AXIS_NAME_SIZE]; /* axis name */
	uint8_t id;                    /* axis id */
	uint8_t type;                  /* axis type: FINITE | MODULO */
	uint8_t combined;              /* independent axis | combined axis */
	uint8_t opmode;                /* operating mode: POSITION | VELOCITY | TORQUE */
	double min_pos;                /* negtive position limit (unit:) */
	double max_pos;                /* positive position limit (unit:) */
	double max_vel;                /* velocity limit (unit:) */
	double max_acc;                /* accelaration limit (unit:) */
	double max_dec;                /* decelaration limit (unit:) */
	double max_jerk;               /* jerk limit (unit:) */
} OBJ_ACS; /* Axis Configuration Segment */

typedef struct {
	uint8_t axis_count;                 /* number of axis */
	uint32_t update_interval;           /* servo data update interval */
	OBJ_ACS axis_config[MAX_AXIS_COUNT]; /* array of axis */
} OBJ_SCS; /* Servo Configuration Segment */

/*-----------------------------------------------------------------------------
 * Definition of PLC Task List Segment
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[MAX_TASK_NAME_SIZE]; /* plc task name */
	uint8_t priority;         /* plc task priority */
    uint8_t type;                  /* task type: SIGNAL | INTERVAL */
    uint8_t signal;                /* signal source: TIMER | I/O */
	uint32_t interval;             /* time interval (uint: ns) */
    uint32_t sp_size;              /* capacity of string pool(unit: Byte) */
	uint16_t cs_size;              /* capacity of calling stack(number of stack frame) */
    uint16_t pou_count;            /* Program Organization Unit: FUN | FB | PROG */
    uint16_t const_count;          /* number of constant */
    uint16_t global_count;         /* number of global variables */
	uint32_t inst_count;           /* number of instructions(code) */
} OBJ_TDS; /* PLC Task Descriptor Segment */

typedef struct {
    char name[MAX_POU_NAME_SIZE]; /* POU name */
    uint8_t input_count;          /* number of input parameters */
    uint8_t inout_count;          /* number of in-out parameters */
    uint8_t output_count;         /* number of output parameters */
    uint8_t local_count;          /* number of local parameters */
    uint32_t entry;               /* POU entry address(AKA index of instruction) */
} OBJ_PDS; /* POU Descriptor Segment */

typedef struct {
    uint8_t type;
    union {
        int32_t value_i;
        double value_d;
        struct {
            uint32_t length; /* '\0' included */
            char str[MAX_STR_LENGTH];
        } value_s;
    } v;
} OBJ_VAL; /* Value */

typedef uint32_t OBJ_INST;
typedef struct {
    OBJ_TDS task_desc;
    OBJ_PDS pou_desc[MAX_POU_COUNT];
	OBJ_VAL vconst[MAX_CONST_COUNT];      /* task constant segment */
	OBJ_VAL vglobal[MAX_GLOBAL_COUNT];      /* task global segment */
    OBJ_INST code[MAX_INST_COUNT]; /* task code segment */
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

enum SPOU_ID {
    /* Numerical Functions */
    SFUN_ABS = 0,
    SFUN_SQRT,
};
#endif
