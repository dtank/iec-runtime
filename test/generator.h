#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "objstruct.h"
#include "instdef.h"

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
 * PLC Task Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_ptps(FILE *fp, OBJ_PTPS *ptps);
void generate_obj_inst(FILE *fp, OBJ_INST *inst, inst_desc_t *inst_desc);
void generate_obj_pts(FILE *fp, OBJ_PTS *pts, inst_desc_t *inst_desc);
/*-----------------------------------------------------------------------------
 * PLC Object File Generator
 *---------------------------------------------------------------------------*/
void generate_obj_header(FILE *fp, OBJHeader *header);
void generate_obj_file(FILE *fp, OBJ_FILE *file, inst_desc_t *inst_desc);
#endif
