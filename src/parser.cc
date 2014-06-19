#include "parser.h"
#include "debug.h"

extern int DEBUG_LEVEL;

task_num_t read_task_num(FILE *fp) {
	task_num_t task_num;
	fread(&task_num, TASK_NUM_SIZE, 1, fp);
	PRINT(DEBUG_TRC, "Trace: task num = %d", task_num);
	return task_num;
}
