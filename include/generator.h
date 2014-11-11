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
void generate_obj_tcs(FILE *fp, OBJ_TCS *tcs);
/*-----------------------------------------------------------------------------
 * PLC Task Data Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_ptds(FILE *fp, OBJ_PTDS *ptds, OBJ_PTPS *ptps);
/*-----------------------------------------------------------------------------
 * PLC Task Code Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_inst(FILE *fp, OBJ_INST *inst, inst_desc_map_t *inst_desc);
void generate_obj_ptcs(FILE *fp, OBJ_PTCS *ptcs, inst_desc_map_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Task List Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_pts(FILE *fp, OBJ_PTS *pts, OBJ_PTPS *ptps, inst_desc_map_t *inst_desc);
void generate_obj_ptls(FILE *fp, OBJ_PTLS *ptls, OBJ_TCS *tcs, inst_desc_map_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Object File Generator
 *---------------------------------------------------------------------------*/
void generate_obj_file(FILE *fp, OBJ_FILE *file, inst_desc_map_t *inst_desc);
#endif
