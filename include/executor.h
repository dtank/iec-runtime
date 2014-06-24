#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "plcmodel.h"

#define PLC_TASK_CREATE_FAILED 1
void plc_task_execute(void *task);
void plc_task_create(PLC_TASK_LIST *task_list);
void plc_task_start(PLC_TASK_LIST *task_list);
#endif
