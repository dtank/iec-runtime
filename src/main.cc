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
	task_property_seg_header property_seg_header = {strlen("task1")};
	task_property_seg property_seg = {"task1", 99u, 1000000000u};
	FILE *fplc = fopen("plc.bin", "wb");
	generate_task_count(fplc, 1);
	generate_task_property_seg_header(fplc, property_seg_header);
	generate_task_property_seg(fplc, property_seg);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	read_task_count(fplc);
	PROPERTY mproperty = read_task_property(fplc);

	TASK plc_task1;
	plc_task1.property = mproperty;
	task_list[0] = &plc_task1;
	TASK_LIST *plc_task_list = new TASK_LIST;
	plc_task_list->task_count = 1;
	plc_task_list->task = task_list;
	fclose(fplc);
	/* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);

	plc_task_create(plc_task_list);
	plc_task_start(plc_task_list);
	pause();
	rt_task_delete(&plc_tasks[0]);

	return 0;
}
