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
	TASK_PROPERTY_SEG_HEADER property_seg_header = {strlen("task1")};
	TASK_PROPERTY_SEG property_seg = {"task1", 99u, 1000000000u};
	CONST_SEG_HEADER const_seg_header = {20};
	CONST_SEG const_seg[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};
	DATA_SEG_HEADER data_seg_header = {20};
	DATA_SEG data_seg[20];
	FILE *fplc = fopen("plc.bin", "wb");
	generate_task_count(fplc, 1);
	generate_task_property_seg_header(fplc, &property_seg_header);
	generate_task_property_seg(fplc, &property_seg);
	generate_const_seg_header(fplc, &const_seg_header);
	generate_const_seg(fplc, &const_seg_header, const_seg);
	generate_data_seg_header(fplc, &data_seg_header);
	generate_data_seg(fplc, &data_seg_header, data_seg);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	read_task_count(fplc);
	TASK_PROPERTY_SEG *mproperty_seg = read_task_property_seg(fplc);
	CONST_SEG *mconst_seg = read_const_seg(fplc);
	DATA_SEG *mdata_seg = read_data_seg(fplc);

	TASK plc_task1;
	plc_task1.property.name = mproperty_seg->name;
	plc_task1.property.priority = mproperty_seg->priority;
	plc_task1.property.interval = mproperty_seg->interval;
	task_list[0] = &plc_task1;
	TASK_LIST *plc_task_list = new TASK_LIST;
	plc_task_list->task_count = 1;
	plc_task_list->task = task_list;
	fclose(fplc);
	 //Avoids memory swapping for this program 
	mlockall(MCL_CURRENT|MCL_FUTURE);

	plc_task_create(plc_task_list);
	plc_task_start(plc_task_list);
	pause();
	rt_task_delete(&plc_tasks[0]);

	return 0;
}
