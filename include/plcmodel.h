#ifndef __PLC_MODEL_H__
#define __PLC_MODEL_H__

#include <native/task.h>
#include "objdef.h"
#include "limits.h"
#include "sysdef.h"

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
	char name[MAX_TASK_NAME_SIZE];
	uint8_t priority;
	uint32_t interval;
	uint32_t data_size;
	uint32_t inst_count;
} TASK_PROP;

typedef struct {
    uint16_t id;      /* instruction id */
    char **arg_addr; /* actual address of instruction's arguments */
} PLC_INST;

typedef struct {
    TASK_PROP prop;
    char *data; /* task data */
    PLC_INST *code; /* task code */
} PLC_TASK;
/*-----------------------------------------------------------------------------
 * Definition of PLC Medel
 *---------------------------------------------------------------------------*/
typedef struct {
    uint8_t task_count;
    RT_TASK *rt_task;
    PLC_TASK *plc_task;
} TASK_LIST;

#endif
