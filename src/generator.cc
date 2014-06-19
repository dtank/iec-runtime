#include <stdio.h>
#include "generator.h"
#include "binformat.h"
#include "debug.h"

extern int DEBUG_LEVEL;
void generate_task_num(FILE *fp, task_num_t task_num) {
	PRINT(DEBUG_TRC, "Trace: task num = %d", task_num);
	if (fwrite(&task_num, sizeof(task_num_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task num...", 0);
	}
}

void generate_task_name(FILE *fp, char *name) {
	PRINT(DEBUG_TRC, "Trace: task name = %d", name);
	if (fwrite(&name, sizeof(name), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "Error: generating task name...", 0);
	}
}
