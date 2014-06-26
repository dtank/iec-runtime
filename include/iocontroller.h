#ifndef __IO_CONTROLLER_H__
#define __IO_CONTROLLER_H__

#include "plcmodel.h"
/* I/O Shared Memory Definition */
#define LDI_SIZE 1
#define LDO_SIZE 1
#define LAI_SIZE 2
#define LAO_SIZE 2

#define IO_SHM_SIZE (LDI_SIZE+LDO_SIZE+LAI_SIZE+LAO_SIZE)

#define LDI_ADDR_OFFSET 0
#define LDO_ADDR_OFFSET (LDI_ADDR_OFFSET+LDO_SIZE)
#define LAI_ADDR_OFFSET (LDO_ADDR_OFFSET+LAI_SIZE)
#define LAO_ADDR_OFFSET (LAI_ADDR_OFFSET+LAO_SIZE)

/* I/O Real-Time Task Definition */
#define IO_TASK_NAME "io_task"
#define IO_TASK_PRIORITY 99

static void io_refresh(void *io_shm);
void io_task_create();
void io_task_start(PLC_CONFIG *config);
void io_task_delete();
#endif
