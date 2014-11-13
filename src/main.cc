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
IO_CONFIG io_config;
SERVO_CONFIG servo_config;
TASK_LIST plc_task;

void sys_init() {
    FILE *fplc = fopen("plc.bin", "rb");
    obj_is_valid(fplc);
    load_io_config(fplc, &io_config);
    io_task_init(&io_config);
    load_servo_config(fplc, &servo_config);
    servo_task_init(&servo_config);
    load_plc_task_list(fplc, &plc_task, &inst_desc);
    plc_task_init(&plc_task);
	fclose(fplc);
}
void sys_start() {
    io_task_start(&io_config);
    servo_task_start(&servo_config);
    plc_task_start(&plc_task);
}
void sys_exit() {
    io_task_delete();
    servo_task_delete();
    plc_task_delete(&plc_task);
}
int main(int argc, char* argv[])
{
    OBJ_FILE obj_file = {
        {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8}, // file header
        {4000000, 0, 1, 0, 0}, // io configuration
        {2, 4000000, { // servo configuration
            {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,
			0.0, 180.0, 100.0, 20.0, 20.0, 10.0},
            {"axis2", true, 2, AXIS_TYPE_FINITE, OPER_MODE_POS,
			0.0, 180.0, 100.0, 20.0, 20.0, 10.0},
        }},
        1, // plc task count
        {
            {{"task1", 80, 100000000u, 20, 1},
            {0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13},{
            //{STD_ADD, {0x00000001, 0x00000011, 0x00000001}},
            //{STD_SUB, {0x00000001, 0x00000011, 0x00000001}},
            //{STD_MUL, {0x00000001, 0x00000011, 0x00000001}},
            //{STD_ADD, {0x00000001, 0x00000002, 0x00000002}},
            {STD_LT, {0x00000001, 0x0000002, 0x00000002}},
            }},
            //{{"task2", 90, 500000000u, 20, 1},
            //{0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13},{
            //{STD_ADD, {0x00000001, 0x00000011, 0x00000001}},
            //}},
        }
    };

	//Avoids memory swapping for this program
    mlockall(MCL_CURRENT|MCL_FUTURE);

	FILE *fplc = fopen("plc.bin", "wb");
    generate_obj_file(fplc, &obj_file, &inst_desc);
	fclose(fplc);
	sys_init();

    sys_start();
    pause();
    sys_exit();

	return 0;
}
