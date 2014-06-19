#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>

#include "executor.h"
#include "generator.h"
#include "parser.h"
#include "plcmodel.h"
#include "debug.h"


int DEBUG_LEVEL = DEBUG_INF;
extern RT_TASK plc_tasks[10];
TASK *task_list[10];

int main(int argc, char* argv[])
{
	FILE *fplc = fopen("plc.bin", "wb");
	generate_task_count(fplc, 1);
	generate_task_name_size(fplc, strlen("task1"));
	generate_task_name(fplc, "task1");
	generate_task_priority(fplc, 99);
	generate_task_interval(fplc, 1000000000u);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	read_task_count(fplc);
	read_task_name(fplc);

	TASK plc_task1;
	plc_task1.property.priority = read_task_priority(fplc);
	plc_task1.property.interval = read_task_interval(fplc);
	plc_task1.property.name = "task1";
	task_list[0] = &plc_task1;
	printf("ok\n");
	TASK_LIST *plc_task_list = new TASK_LIST;
	plc_task_list->task_count = 1;
	plc_task_list->task = task_list;
	printf("plc_task_list.task_count = %d\n", plc_task_list->task_count);
	printf("plc_task_list.task_list[0].config.interval = %u\n",plc_task_list->task[0]->property.interval);
	fclose(fplc);
	/* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);

	plc_task_create(plc_task_list);
	plc_task_start(plc_task_list);
	pause();
	rt_task_delete(&plc_tasks[0]);

	return 0;
}
