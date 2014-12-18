#include <unistd.h> /* required */
#include <sys/mman.h>

#include "loader.h"
#include "executor.h"
#include "io.h"
#include "servo.h"
#include "logger.h"


int LOGGER_LEVEL = LEVEL_ALL;
//inst_desc_map_t inst_desc = inst_desc_map;
ec_map_t ec_msg = ec_map;
IOConfig io_config;
ServoConfig servo_config;
TaskList plc_task;

void sys_init() {
    FILE *fplc = fopen("plc.bin", "rb");
    verify_obj(fplc);
    load_io_config(fplc, &io_config);
    io_task_init(&io_config);
    load_servo_config(fplc, &servo_config);
    servo_task_init(&servo_config);
    load_task_list(fplc, &plc_task);
    //plc_task_init(&plc_task);
	fclose(fplc);
}
void sys_start() {
    io_task_start(&io_config);
    servo_task_start(&servo_config);
    //plc_task_start(&plc_task);
}
void sys_exit() {
    io_task_delete();
    servo_task_delete();
    //plc_task_delete(&plc_task);
}
int main(int argc, char* argv[])
{
	//Avoids memory swapping for this program
    mlockall(MCL_CURRENT|MCL_FUTURE);

	sys_init();
    //sys_start();
    pause();
    sys_exit();

	return 0;
}
