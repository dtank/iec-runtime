#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "binformat.h"
#include "instruction.h"
void generate_task_count(FILE *fp, task_count_t count);

/* Task Property Segment Generator */
static void generate_task_name_size(FILE *fp, task_name_size_t size);
static void generate_task_name(FILE *fp, task_name_t *name);
static void generate_task_priority(FILE *fp, task_priority_t priority);
static void generate_task_interval(FILE *fp, task_interval_t interval);
void generate_tps_header(FILE *fp, BIN_TPS_HEADER *tps_header);
void generate_tps(FILE *fp, BIN_TPS *tps);

/* Task Data Segment Generator */
static void generate_seg_size(FILE *fp, seg_size_t size);
void generate_tds_header(FILE *fp, BIN_TDS_HEADER *tds_header);
void generate_tds(FILE *fp, BIN_TDS_HEADER *tds_header, BIN_TDS *tds);

/* Task Code Segment Generator */
static void generate_inst_count(FILE *fp, inst_count_t inst_count);
static void generate_inst_id(FILE *fp, inst_id_t inst_id);
static void generate_inst_arg(FILE *fp, inst_arg_t inst_arg);
static void generate_inst(FILE *fp, BIN_INST *inst, INST_INFO *info);
void generate_tcs_header(FILE *fp, BIN_TCS_HEADER *tcs_header);
void generate_tcs(FILE *fp, BIN_TCS_HEADER *tcs_hader, BIN_TCS *tcs, INST_INFO *info);

#endif
