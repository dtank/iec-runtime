#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/*-----------------------------------------------------------------------------
 * Definition of PLC Object File Header
 *---------------------------------------------------------------------------*/
#define MAGIC_SIZE 5
#define OBJ_TYPE_32 1
#define OBJ_TYPE_64 2
#define BYTE_ORDER_LIT 1
#define BYTE_ORDER_BIG 2
#define MACH_CORTEX_A8 1
typedef struct {
	char magic[MAGIC_SIZE];
	uint8_t type;
	uint8_t order;
	uint8_t version;
	uint8_t machine;
} OBJ_HEADER;
/*-----------------------------------------------------------------------------
 * Definition of I/O Configuration Segment
 *---------------------------------------------------------------------------*/
typedef uint32_t io_refresh_interval_t;
/*-----------------------------------------------------------------------------
 * Definition of Servo Configuration Segment
 *---------------------------------------------------------------------------*/
typedef uint8_t axis_count_t;
typedef char axis_name_t;
typedef uint8_t axis_nodeid_t;
typedef uint8_t axis_oper_mode_t;
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
