#include <string.h> 
#include "generator.h"
#include "debug.h"

extern int DEBUG_LEVEL;

void generate_task_count(FILE *fp, task_count_t count) {
	PRINT(DEBUG_TRC, "TRACE: task_count = %d", count);
	if (fwrite(&count, sizeof(task_count_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task count (%d)...", count);
	}
}

/* Task Property Segment Generator */
static void generate_task_name_size(FILE *fp, task_name_size_t size) {
	PRINT(DEBUG_TRC, "TRACE: task_name_size = %d", size);
	if (fwrite(&size, sizeof(task_name_size_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating size of task name (%d)...", size);
	}
}
static void generate_task_name(FILE *fp, task_name_t *name) {
	PRINT(DEBUG_TRC, "TRACE: task_name = %s", name);
	if (fwrite(name, strlen(name), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task name (%s)...", name);
	}
}
static void generate_task_priority(FILE *fp, task_priority_t priority) {
	PRINT(DEBUG_TRC, "TRACE: task_priority = %d", priority);
	if (fwrite(&priority, sizeof(task_priority_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task priority (%d)...", priority);
	}
}
static void generate_task_interval(FILE *fp, task_interval_t interval) {
	PRINT(DEBUG_TRC, "TRACE: task_interval = %d", interval);
	if (fwrite(&interval, sizeof(task_interval_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task interval (%d)...", interval);
	}
}
void generate_tps_header(FILE *fp, BIN_TPS_HEADER *tps_header) {
	generate_task_name_size(fp, tps_header->name_size);
}
void generate_tps(FILE *fp, BIN_TPS *tps) {
	generate_task_name(fp, tps->name);
	generate_task_priority(fp, tps->priority);
	generate_task_interval(fp, tps->interval);
}

/* Task Data Segment Generator */
static void generate_seg_size(FILE *fp, seg_size_t size) {
	if (fwrite(&size, sizeof(seg_size_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating size of segment (%d)...", size);
	}
}
void generate_tds_header(FILE *fp, BIN_TDS_HEADER *tds_header) {
	generate_seg_size(fp, tds_header->size);
}
void generate_tds(FILE *fp, BIN_TDS_HEADER *tds_header, BIN_TDS *tds) {
	PRINT(DEBUG_TRC, "TRACE: tds_size = %d", tds_header->size);
	if (fwrite(tds, tds_header->size, 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating task data segment...", 0);
	}
}

/* Task Code Segment Generator */
static void generate_inst_count(FILE *fp, inst_count_t count) {
	PRINT(DEBUG_TRC, "TRACE: inst_count = %d", count);
	if (fwrite(&count, sizeof(inst_count_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating instruction count (%d)...", count);
	}
}
static void generate_inst_id(FILE *fp, inst_id_t id) {
	PRINT(DEBUG_TRC, "TRACE: inst_id = %d", id);
	if (fwrite(&id, sizeof(inst_id_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating instruction id (%d)...", id);
	}
}
static void generate_inst_arg(FILE *fp, inst_arg_t arg) {
	PRINT(DEBUG_TRC, "TRACE: inst_arg = %d", arg);
	if (fwrite(&arg, sizeof(inst_arg_t), 1, fp) < 1) {
		PRINT(DEBUG_ERR, "ERROR: generating instruction argument (%d)...", arg);
	}
}
static void generate_inst(FILE *fp, BIN_INST *inst, INST_INFO *info) {
	generate_inst_id(fp, inst->id);
	for (int i = 0; i < info->args_count[inst->id]; ++i) {
		generate_inst_arg(fp, inst->arg_list[i]);
	}
}
void generate_tcs_header(FILE *fp, BIN_TCS_HEADER *tcs_header) {
	generate_inst_count(fp, tcs_header->inst_count);
}
void generate_tcs(FILE *fp, BIN_TCS_HEADER *tcs_header, BIN_TCS *tcs, INST_INFO *info) {
	for (int i = 0; i < tcs_header->inst_count; ++i) {
		generate_inst(fp, &(tcs->inst_list[i]), info);
		//PRINT(DEBUG_TRC, "TRACE: inst_arg = %d", arg);
	}
}
