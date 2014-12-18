#ifndef __SYSENV_H__
#define __SYSENV_H__

/*-----------------------------------------------------------------------------
 * PLC Object File Header
 *---------------------------------------------------------------------------*/
#define SYS_TYPE_32 1
#define SYS_TYPE_64 2
#define BYTE_ORDER_LIT 1
#define BYTE_ORDER_BIG 2
#define MACH_CORTEX_A8 1
/*-----------------------------------------------------------------------------
 * Servo
 *---------------------------------------------------------------------------*/
#define AXIS_TYPE_FINITE 1
#define AXIS_TYPE_MODULO 2
#define OPER_MODE_POS 1
#define OPER_MODE_VEL 2
#define OPER_MODE_TOR 3
/*-----------------------------------------------------------------------------
 *  PLC Task
 *---------------------------------------------------------------------------*/
#define TASK_TYPE_SIGNAL   1
#define TASK_TYPE_INTERVAL 2
/*-----------------------------------------------------------------------------
 * System Environment
 *---------------------------------------------------------------------------*/
#define SYS_TYPE SYS_TYPE_32
#define SYS_BYTE_ORDER BYTE_ORDER_LIT
#define SYS_VERSION 1
#define SYS_MACHINE MACH_CORTEX_A8
#endif
