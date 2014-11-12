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
    OBJ_FILE obj_file = {
        {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8}, // file header
        {4000000, 0, 1, 0, 0}, // io configuration
        {2, 4000000, { // servo configuration
            {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,
			0.0, 180.0, 100.0, 20.0, 20.0, 10.0},
            {"axis2", true, 2, AXIS_TYPE_FINITE, OPER_MODE_POS,
			0.0, 180.0, 100.0, 20.0, 20.0, 10.0},
        }},
        2, // plc task count
        {
            {{"task1", 80, 100000000u, 20, 3},
            {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13},{
            {STD_ADD, {0x00000001, 0x00000006, 0x00000006}},
            {STD_ADD, {0x00000001, 0x00000006, 0x00000006}},
            {STD_ADD, {0x00000001, 0x00000006, 0x00000006}},
            }},
            {{"task2", 90, 500000000u, 20, 3},
            {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13},{
            {STD_ADD, {0x00000001, 0x00000006, 0x00000006}},
            {STD_ADD, {0x00000001, 0x00000006, 0x00000006}},
            {STD_ADD, {0x00000001, 0x00000006, 0x00000006}},
            }},
        }
    };

	FILE *fplc = fopen("plc.bin", "wb");
    generate_obj_file(fplc, &obj_file, &inst_desc);
	fclose(fplc);
	fplc = fopen("plc.bin", "rb");
    PLC_MODEL *model = load_plc_model(fplc, &inst_desc);
	fclose(fplc);
	//Avoids memory swapping for this program
    mlockall(MCL_CURRENT|MCL_FUTURE);
    io_task_init(&model->io_config);
    servo_task_init(&model->servo_config);
    //plc_task_init(model);


    io_task_start(&model->io_config);
    servo_task_start(&model->servo_config);
    pause();
    io_task_delete();
    servo_task_delete();

	return 0;
}
