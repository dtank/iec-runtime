#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "binformat.h"
#include "instruction.h"

/* PLC Object File Header Generator */
static void generate_io_refresh_interval(FILE *fp, io_refresh_interval_t interval);
static void generate_task_count(FILE *fp, task_count_t count);
void generate_bin_header(FILE *fp, BIN_HEADER *header);

/* PLC Object File Body -- Task Property Segment Generator */
static void generate_task_name_size(FILE *fp, task_name_size_t size);
static void generate_task_name(FILE *fp, task_name_t *name);
static void generate_task_priority(FILE *fp, task_priority_t priority);
static void generate_task_interval(FILE *fp, task_interval_t interval);
static void generate_tds_size(FILE *fp, tds_size_t size);
static void generate_inst_count(FILE *fp, inst_count_t count);
void generate_tps(FILE *fp, BIN_TPS *tps);

/* PLC Object File Body -- Task Data Segment Generator */
void generate_tds(FILE *fp, BIN_TPS *tps, BIN_TDS *tds);

/* PLC Object File Body -- Task Code Segment Generator */
static void generate_inst_id(FILE *fp, inst_id_t inst_id);
static void generate_inst_arg(FILE *fp, inst_arg_t inst_arg);
static void generate_inst(FILE *fp, BIN_INST *inst, inst_desc_map_t *inst_desc);
void generate_tcs(FILE *fp, BIN_TPS *tps, BIN_TCS *tcs, inst_desc_map_t *inst_desc);

#endif
