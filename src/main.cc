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
		MAGIC,          /* magic number */
		SYS_TYPE_32,    /* type of object file: 32BIT | 64BIT */
		BYTE_ORDER_LIT, /* byte order: LITTLE-ENDIAN | BIG-ENDIAN */
		1,              /* version of object file */
		MACH_CORTEX_A8  /* CPU platform */
	};
	OBJ_IOCS obj_iocs = {
		4000000,   /* I/O data update interval */
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
/*-----------------------------------------------------------------------------
 * PLC Task 1
 **---------------------------------------------------------------------------*/
	OBJ_PTPS task1_ptps = {
		(uint8_t)strlen("task1")+1, /* size of plc task name, including '\0' */
		"task1",                    /* plc task name */
		80,                         /* plc task priority */
		100000000u,                 /* plc task period interval (unit: ns) */
		//20,                         [> size of plc task data segment <]
		//3                           [> number of plc task instructions <]
	};
    char task1_data[20] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};
    OBJ_PTDS task1_ptds = {
        20,
        task1_data
    };
    uint32_t task1_inst1_args[] = {0x00000001, 0x00000006, 0x00000006};
    uint32_t task1_inst2_args[] = {0x00000001, 0x00000006, 0x00000006};
    uint32_t task1_inst3_args[] = {0x00000001, 0x00000006, 0x00000006};
    OBJ_INST task1_inst[] = {
        {STD_ADD, task1_inst1_args},
        {STD_ADD, task1_inst2_args},
        {STD_ADD, task1_inst3_args}
    };
    OBJ_PTCS task1_ptcs = {
        3,
        task1_inst
    };
    OBJ_PTS task1_pts = {
        task1_ptps,
        task1_ptds,
        task1_ptcs
    };
/*-----------------------------------------------------------------------------
 * PLC Task 2
 **---------------------------------------------------------------------------*/
    OBJ_PTPS task2_ptps = {
		(uint8_t)strlen("task2")+1, /* size of plc task name, including '\0' */
		"task2",                    /* plc task name */
		90,                         /* plc task priority */
		500000000u,                 /* plc task period interval (unit: ns) */
		//20,                         [> size of plc task data segment <]
		//3                           [> number of plc task instructions <]
	};
    char task2_data[20] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13};
    OBJ_PTDS task2_ptds = {
        20,
        task2_data
    };
    uint32_t task2_inst1_args[] = {0x00000001, 0x00000006, 0x00000006};
    uint32_t task2_inst2_args[] = {0x00000001, 0x00000006, 0x00000006};
    uint32_t task2_inst3_args[] = {0x00000001, 0x00000006, 0x00000006};
    OBJ_INST task2_inst[] = {
        {STD_ADD, task2_inst1_args},
        {STD_ADD, task2_inst2_args},
        {STD_ADD, task2_inst3_args}
    };
    OBJ_PTCS task2_ptcs = {
        3,
        task2_inst
    };
    OBJ_PTS task2_pts = {
        task2_ptps,
        task2_ptds,
        task2_ptcs
    };
    OBJ_PTS obj_tasks[] = {
        task1_pts,
        task2_pts
    };
    OBJ_PTLS obj_ptls = {
        2,
        obj_tasks
    };
    OBJ_FILE obj_file = {
        obj_header,
        obj_iocs,
        obj_scs,
        obj_ptls
    };

	FILE *fplc = fopen("plc.bin", "wb");
	generate_obj_file(fplc, &obj_file, &inst_desc);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
	OBJ_HEADER *myobj_header = load_obj_header(fplc);
	IO_CONFIG *io_config = load_io_config(fplc);
	SERVO_CONFIG *servo_config = load_servo_config(fplc);
	//OBJ_PTCS *myobj_ptcs = load_obj_ptcs(fplc);
	//PLC_TASK_PROP *plc_task_prop = load_plc_task_property(fplc);
    //PLC_TASK_DATA *plc_task_data = load_plc_task_data(fplc);
	//PLC_CONFIG *config = load_plc_config(fplc);
    PLC_TASK_LIST *plc_task_list = load_plc_task_list(fplc, &inst_desc);
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
