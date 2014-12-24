#include <unistd.h> /* required */
#include <sys/mman.h>

#include "loader.h"
#include "executor.h"
#include "io.h"
#include "servo.h"
#include "logger.h"

extern IOConfig g_ioconfig;
extern ServoConfig g_svconfig;
TaskList plc_task;

void sys_init() {
    FILE *fplc = fopen("plc.bin", "rb");
    verify_obj(fplc);
    load_io_config(fplc, &g_ioconfig);
    io_task_init(&g_ioconfig);
    load_servo_config(fplc, &g_svconfig);
    servo_task_init(&g_svconfig);
    load_task_list(fplc, &plc_task);
    plc_task_init(&plc_task);
	fclose(fplc);
}
void sys_start() {
    io_task_start(&g_ioconfig);
    //servo_task_start(&g_svconfig);
    plc_task_start(&plc_task);
}
void sys_exit() {
    io_task_delete();
    //servo_task_delete();
    plc_task_delete(&plc_task);
}
int main(int argc, char* argv[])
{
	//Avoids memory swapping for this program
    mlockall(MCL_CURRENT|MCL_FUTURE);

	sys_init();
    sys_start();
    pause();
    sys_exit();

	return 0;
}
