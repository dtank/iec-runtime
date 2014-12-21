#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <native/task.h>
#include "ivalue.h"
#include "istring.h"
#include "callstk.h"
#include "opcode.h"
#include "syslimit.h"

/*-----------------------------------------------------------------------------
 * I/O Configuration
 *---------------------------------------------------------------------------*/
typedef struct {
	uint32_t update_interval; /* I/O data update interval */
	uint8_t ldi_count;        /* number of local digital input module */
	uint8_t ldo_count;        /* number of local digital output module */
	uint8_t lai_count;        /* number of local analog input module */
	uint8_t lao_count;        /* number of local analog output module */
} IOConfig;
/*-----------------------------------------------------------------------------
 * Servo Configuration
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[MAX_AXIS_NAME_SIZE]; /* axis name, including '\0' */
	bool is_combined;              /* independent axis | combined axis */
	uint8_t node_id;               /* axis id */
	uint8_t axis_type;             /* axis type: FINITE | MODULO */
	uint8_t oper_mode;             /* operating mode: POSITION | VELOCITY | TORQUE */
	double sw_limit_neg;           /* negtive position limit (unit:) */
	double sw_limit_pos;           /* positive position limit (unit:) */
	double max_vel;                /* velocity limit (unit:) */
	double max_acc;                /* accelaration limit (unit:) */
	double max_dec;                /* decelaration limit (unit:) */
	double max_jerk;               /* jerk limit (unit:) */
} AxisConfig;

typedef struct {
	uint8_t axis_count;       /* number of axis */
	uint32_t update_interval; /* Servo data update interval */
	AxisConfig *axis_group;   /* array of axis configuration */
} ServoConfig;
/*-----------------------------------------------------------------------------
 * Robot Configuration
 *---------------------------------------------------------------------------*/
typedef struct {
    int axis_count;
    int stub_param2;
} RobotConfig;
/*-----------------------------------------------------------------------------
 * PLC Task Model
 *---------------------------------------------------------------------------*/
typedef struct {
	char name[MAX_TASK_NAME_SIZE]; /* plc task name */
	uint8_t priority;              /* priority: 80-95 */
    uint8_t type;                  /* task type: SIGNAL | INTERVAL */
    uint8_t signal;                /* signal source: TIMER | I/O */
	uint32_t interval;             /* time interval (uint: ns) */
    uint32_t sp_size;              /* capacity of string pool(unit: Byte) */
    uint16_t pou_count;            /* Program Organization Unit: FUN | FB | PROG */
    uint16_t const_count;          /* number of constant */
    uint16_t global_count;         /* number of global variables */
	uint32_t inst_count;           /* number of instructions(code) */
	uint16_t sframe_count;         /* number of stack frame */
} TaskDesc; /* PLC Task Descriptor */

typedef struct {
    char name[MAX_POU_NAME_SIZE]; /* POU name */
    uint8_t input_count;          /* number of input parameters */
    uint8_t output_count;         /* number of output parameters */
    uint8_t local_count;          /* number of local parameters */
    uint32_t addr;                /* POU address(AKA index of instruction) */
} POUDesc; /* POU Descriptor */

typedef struct {
    TaskDesc task_desc; /* PLC task descriptor */
    StrPool strpool;    /* string pool */
    POUDesc *pou_desc;  /* POU descriptor */
    IValue *vconst;     /* constant pool */
    IValue *vglobal;    /* global variables */
    Instruction *code;  /* task code(instruction) */
    CStack stack;       /* calling stack(constant capacity) */
    uint32_t pc;        /* program counter(AKA instruction pointer) */
} PLCTask;

typedef struct {
    uint8_t task_count; /* number of plc task */
    RT_TASK *rt_task;
    PLCTask *plc_task;
} TaskList;

#endif
