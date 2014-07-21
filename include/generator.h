#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "binformat.h"
#include "instruction.h"

/*-----------------------------------------------------------------------------
 * PLC Object File Header Generator
 *---------------------------------------------------------------------------*/
void generate_obj_header(FILE *fp, OBJ_HEADER *header);
/*-----------------------------------------------------------------------------
 * I/O Configuration Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_iocs(FILE *fp, OBJ_IOCS *iocs);
/*-----------------------------------------------------------------------------
 * Servo Configuration Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_acs(FILE *fp, OBJ_ACS *acs);
void generate_obj_scs(FILE *fp, OBJ_SCS *scs);
/*-----------------------------------------------------------------------------
 * PLC Task Property Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_ptps(FILE *fp, OBJ_PTPS *ptps);
/*-----------------------------------------------------------------------------
 * PLC Task Data Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_ptds(FILE *fp, OBJ_PTDS *ptds);
/*-----------------------------------------------------------------------------
 * PLC Task Code Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_inst(FILE *fp, OBJ_INST *inst, inst_desc_map_t *inst_desc);
void generate_obj_ptcs(FILE *fp, OBJ_PTCS *ptcs, inst_desc_map_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Task Configuration Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_pts(FILE *fp, OBJ_PTS *pts, inst_desc_map_t *inst_desc);
void generate_obj_ptls(FILE *fp, OBJ_PTLS *ptls, inst_desc_map_t *inst_desc);

/* PLC Object File Header Generator */
//static void generate_io_refresh_interval(FILE *fp, io_refresh_interval_t interval);
//static void generate_task_count(FILE *fp, task_count_t count);
//void generate_bin_header(FILE *fp, BIN_HEADER *header);

/* PLC Object File Body -- Task Property Segment Generator */
//static void generate_task_name_size(FILE *fp, task_name_size_t size);
//static void generate_task_name(FILE *fp, task_name_t *name);
//static void generate_task_priority(FILE *fp, task_priority_t priority);
//static void generate_task_interval(FILE *fp, task_interval_t interval);
//static void generate_tds_size(FILE *fp, tds_size_t size);
//static void generate_inst_count(FILE *fp, inst_count_t count);
//void generate_tps(FILE *fp, BIN_TPS *tps);

/* PLC Object File Body -- Task Data Segment Generator */
//void generate_tds(FILE *fp, BIN_TPS *tps, BIN_TDS *tds);

/* PLC Object File Body -- Task Code Segment Generator */
//static void generate_inst_id(FILE *fp, inst_id_t inst_id);
//static void generate_inst_arg_va(FILE *fp, inst_arg_va_t arg_va);
//static void generate_inst(FILE *fp, BIN_INST *inst, inst_desc_map_t *inst_desc);
//void generate_tcs(FILE *fp, BIN_TPS *tps, BIN_TCS *tcs, inst_desc_map_t *inst_desc);

#endif
