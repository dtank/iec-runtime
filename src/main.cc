#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>

#include "plcexecutor.h"
#include "plcmodel.h"


extern RT_TASK plc_tasks[10];
TASK *task_list[10];
void catch_signal(int sig)
{
}

int main(int argc, char* argv[])
{
	printf("init\n");
	TASK plc_task1;
	plc_task1.property.interval = 1000000000u;
	plc_task1.property.priority = 99;
	plc_task1.property.name = "task1";
	task_list[0] = &plc_task1;
	printf("ok\n");
	TASK_LIST *plc_task_list = new TASK_LIST;
	plc_task_list->task_num = 1;
	plc_task_list->task = task_list;
	printf("plc_task_list.task_num = %d\n", plc_task_list->task_num);
	printf("plc_task_list.task_list[0].config.interval = %u\n",plc_task_list->task[0]->property.interval);
	signal(SIGTERM, catch_signal);
	signal(SIGINT, catch_signal);

	/* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);

	plc_task_create(plc_task_list);
	plc_task_start(plc_task_list);
	pause();
	rt_task_delete(&plc_tasks[0]);

	return 0;
}
