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
#include "instruction.h"
#include "debug.h"
#include "stdinst.h"


int DEBUG_LEVEL = DEBUG_INF;

inst_desc_map_t inst_desc = inst_desc_map;
int main(int argc, char* argv[])
{
	BIN_TPS tps = {(uint8_t)strlen("task1"), "task1", 99u, 1000000000u, (tds_size_t)20u, (inst_count_t)3u};
	BIN_TDS tds[20] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};
	BIN_TCS tcs = {
		STD_ADD, 0u, 4u, 4u,
		STD_ADD, 0u, 4u, 4u,
		STD_ADD, 0u, 4u, 4u
	};
	FILE *fplc = fopen("plc.bin", "wb");
	generate_task_count(fplc, 1);
	generate_tps(fplc, &tps);
	generate_tds(fplc, &tps, tds);
	generate_tcs(fplc, &tps, &tcs, &inst_desc);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	PLC_TASK_LIST *plc_task_list = read_plc_task_list(fplc, &inst_desc);
	fclose(fplc);

	//Avoids memory swapping for this program
	mlockall(MCL_CURRENT|MCL_FUTURE);

	plc_task_create(plc_task_list);
	plc_task_start(plc_task_list);
	pause();
	plc_task_delete(plc_task_list);

	return 0;
}
