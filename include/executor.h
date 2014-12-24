#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "plcmodel.h"

static void executor(void *task);
void plc_task_init(TaskList *task_list);
void plc_task_start(TaskList *task_list);
void plc_task_delete(TaskList *task_list);
#endif
