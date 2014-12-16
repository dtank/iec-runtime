#ifndef __SYSLIMIT_H__
#define __SYSLIMIT_H__

/* I/O Limitations */
#define MAX_LDI_COUNT 1
#define MAX_LDO_COUNT 1
#define MAX_LAI_COUNT 1
#define MAX_LAO_COUNT 1
#define MIN_IO_INTERVAL 2000000 /* unit: ns */
#define LDI_WORDSIZE 4 /* unit: Byte */
#define LDO_WORDSIZE 4 /* unit: Byte */
#define LAI_WORDSIZE 4 /* unit: Byte */
#define LAO_WORDSIZE 4 /* unit: Byte */
#define MAX_IO_MEM_SIZE (MAX_LDI_COUNT*LDI_WORDSIZE + \
        MAX_LDO_COUNT*LDO_WORDSIZE + \
        MAX_LAI_COUNT*LAI_WORDSIZE + \
        MAX_LAO_COUNT*LAO_WORDSIZE)

/* Servo Limitations */
#define MAX_AXIS_COUNT 8
#define MAX_AXIS_NAME_SIZE 16
#define MIN_AXIS_NODE_ID 1
#define MAX_AXIS_NODE_ID MAX_AXIS_COUNT
#define MIN_SERVO_INTERVAL 2000000 /* unit: ns */

/* PLC Task Limitations */
#define MAX_TASK_COUNT 16
#define MAX_TASK_NAME_SIZE 16
#define MAX_TASK_PRIORITY 95
#define MIN_TASK_PRIORITY 80
#define MIN_TASK_INTERVAL 8000000
#define MAX_TASK_CONST_COUNT 1024
#define MAX_TASK_GLOB_COUNT 1024 /* global variable */
#define MAX_TASK_INST_COUNT 65535 /* instruction */
#define MAX_TASK_SFRAME_COUNT 1024 /* stack frame */
#define MAX_TASK_FUNC_COUNT 1024 /* user-level FUN|FB */

//TODO
/* User-level FUN|FB Limitations */

#endif
