#include <unistd.h> /* required */
#include <sys/mman.h>

#include "binformat.h"
#include "generator.h"
#include "loader.h"
#include "executor.h"
#include "iocontroller.h"
#include "logger.h"


int LOGGER_LEVEL = LEVEL_ALL;
inst_desc_map_t inst_desc = inst_desc_map;
ec_map_t ec_msg = ec_map;

int main(int argc, char* argv[])
{
	OBJ_HEADER obj_header = {
		MAGIC,         /* magic number */
		SYS_TYPE_32,    /* type of object file: 32BIT | 64BIT */
		BYTE_ORDER_LIT, /* byte order: LITTLE-ENDIAN | BIG-ENDIAN */
		1,              /* version of object file */
		MACH_CORTEX_A8  /* CPU platform */
	};
	OBJ_IOCS obj_iocs = {
		4000000, /* I/O data update interval */
		0,         /* number of local digital input module */
		1,         /* number of local digital output module */
		0,         /* number of local analog input module */
		0          /* number of local analog output module */
	};
	OBJ_ACS obj_acs[] = {
		{	false,            /* independent axis */
			(uint8_t)strlen("axis1")+1,  /* NOT include '\0' */
			"axis1",          /* axis name */
			1,                /* axis id */
			AXIS_TYPE_FINITE, /* axis type: FINITE | MODULO */
			OPER_MODE_POS,    /* operating mode: POSITION | VELOCITY | TORQUE */
			0,                /* negtive position limit (unit:) */
			180,              /* positive position limit (unit:) */
			100,              /* velocity limit (unit:) */
			20,               /* accelaration limit (unit:) */
			20,               /* decelaration limit (unit:) */
			10                /* jerk limit (unit:) */
		},
		{	true,             /* combined axis */
			(uint8_t)strlen("axis2")+1,  /* NOT include '\0' */
			"axis2",          /* axis name */
			2,                /* axis id */
			AXIS_TYPE_FINITE, /* axis type: FINITE | MODULO */
			OPER_MODE_POS,    /* operating mode: POSITION | VELOCITY | TORQUE */
			0,                /* negtive position limit (unit:) */
			180,              /* positive position limit (unit:) */
			100,              /* velocity limit (unit:) */
			20,               /* accelaration limit (unit:) */
			20,               /* decelaration limit (unit:) */
			10                /* jerk limit (unit:) */
		}
	};
	OBJ_SCS obj_scs = {
		2, /* number of axis */
		obj_acs
	};
	//BIN_HEADER header = {10000000u, 1};
	//BIN_TPS tps = {(uint8_t)strlen("task1"), "task1", 80u, 100000000u, (tds_size_t)20u, (inst_count_t)3u};
	//BIN_TDS tds[20] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};
	//BIN_TCS tcs = {
		//STD_ADD, 0x00000001, 0x00000006, 0x00000006,
		//STD_ADD, 0x00000001, 0x00000006, 0x00000006,
		//STD_ADD, 0x00000001, 0x00000006, 0x00000006
	//};
	FILE *fplc = fopen("plc.bin", "wb");
	generate_obj_header(fplc, &obj_header);
	generate_obj_iocs(fplc, &obj_iocs);
	generate_obj_scs(fplc, &obj_scs);
	//generate_bin_header(fplc, &header);
	//generate_tps(fplc, &tps);
	//generate_tds(fplc, &tps, tds);
	//generate_tcs(fplc, &tps, &tcs, &inst_desc);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	OBJ_HEADER *myobj_header = load_obj_header(fplc);
	IO_CONFIG *io_config = load_io_config(fplc);
	SERVO_CONFIG *servo_config = load_servo_config(fplc);
	//PLC_CONFIG *config = load_plc_config(fplc);
	//PLC_TASK_LIST *plc_task_list = load_plc_task_list(fplc, config, &inst_desc);
	fclose(fplc);

	//Avoids memory swapping for this program
	//mlockall(MCL_CURRENT|MCL_FUTURE);

	//io_task_create();
	//plc_task_create(plc_task_list, config);
	//io_task_start(io_config);
	//plc_task_start(plc_task_list, config);
	//pause();
	//io_task_delete();
	//plc_task_delete(plc_task_list, config);

	return 0;
}
