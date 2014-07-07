#include <unistd.h> /* required */
#include <sys/mman.h>

#include "generator.h"
#include "parser.h"
#include "executor.h"
#include "iocontroller.h"
#include "debug.h"


int DEBUG_LEVEL = DEBUG_INF;
inst_desc_map_t inst_desc = inst_desc_map;

int main(int argc, char* argv[])
{
	BIN_HEADER header = {10000000u, 1};
	BIN_TPS tps = {(uint8_t)strlen("task1"), "task1", 80u, 100000000u, (tds_size_t)20u, (inst_count_t)3u};
	BIN_TDS tds[20] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};
	BIN_TCS tcs = {
		STD_ADD, 0x00000001, 0x00000006, 0x00000006,
		STD_ADD, 0x00000001, 0x00000006, 0x00000006,
		STD_ADD, 0x00000001, 0x00000006, 0x00000006
	};
	FILE *fplc = fopen("plc.bin", "wb");
	generate_bin_header(fplc, &header);
	generate_tps(fplc, &tps);
	generate_tds(fplc, &tps, tds);
	generate_tcs(fplc, &tps, &tcs, &inst_desc);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	PLC_CONFIG *config = read_plc_config(fplc);
	PLC_TASK_LIST *plc_task_list = read_plc_task_list(fplc, config, &inst_desc);
	fclose(fplc);

	//Avoids memory swapping for this program
	mlockall(MCL_CURRENT|MCL_FUTURE);

	io_task_create();
	plc_task_create(plc_task_list, config);
	io_task_start(config);
	plc_task_start(plc_task_list, config);
	pause();
	io_task_delete();
	plc_task_delete(plc_task_list, config);

	return 0;
}
