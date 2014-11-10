#include <unistd.h> /* required */
#include <sys/mman.h>

#include "binformat.h"
#include "generator.h"
#include "loader.h"
#include "executor.h"
#include "iocontroller.h"
#include "axiscontroller.h"
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
        {	"axis1",          /* axis name */
			false,            /* independent axis */
			1,                /* axis id */
			AXIS_TYPE_FINITE, /* axis type: FINITE | MODULO */
			OPER_MODE_POS,    /* operating mode: POSITION | VELOCITY | TORQUE */
			(double)0.0,                /* negtive position limit (unit:) */
			(double)180.0,              /* positive position limit (unit:) */
			(double)100.0,              /* velocity limit (unit:) */
			(double)20.0,               /* accelaration limit (unit:) */
			(double)20.0,               /* decelaration limit (unit:) */
			(double)10.0                /* jerk limit (unit:) */
		},
        {	"axis2",          /* axis name */
			true,             /* combined axis */
			2,                /* axis id */
			AXIS_TYPE_FINITE, /* axis type: FINITE | MODULO */
			OPER_MODE_POS,    /* operating mode: POSITION | VELOCITY | TORQUE */
			(double)0.0,                /* negtive position limit (unit:) */
			(double)180.0,              /* positive position limit (unit:) */
			(double)100.0,              /* velocity limit (unit:) */
			(double)20.0,               /* accelaration limit (unit:) */
			(double)20.0,               /* decelaration limit (unit:) */
			(double)10.0                /* jerk limit (unit:) */
		}
	};
	OBJ_SCS obj_scs = {
		2, /* number of axis */
        4000000, /* update interval */
		obj_acs
	};
/*-----------------------------------------------------------------------------
 * PLC Task 1
 **---------------------------------------------------------------------------*/
	OBJ_PTPS task1_ptps = {
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
    PLC_MODEL *model = load_plc_model(fplc, &inst_desc);
	fclose(fplc);
	//Avoids memory swapping for this program
    mlockall(MCL_CURRENT|MCL_FUTURE);
    //io_task_init(io_config);
    //servo_task_init(servo_config);


    //io_task_start(io_config);
    //servo_task_start(servo_config);
	//plc_task_create(plc_task_list, config);
	//plc_task_start(plc_task_list, config);
    //pause();
    //io_task_delete();
	//plc_task_delete(plc_task_list, config);

	return 0;
}
