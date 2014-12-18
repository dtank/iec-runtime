#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include "objstruct.h"

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
void generate_obj_tds(FILE *fp, OBJ_TDS *tds);
void generate_obj_pds(FILE *fp, OBJ_PDS *pds);
void generate_obj_value(FILE *fp, OBJ_VAL *value);
void generate_obj_pts(FILE *fp, OBJ_PTS *pts);
/*-----------------------------------------------------------------------------
 * PLC Object File Generator
 *---------------------------------------------------------------------------*/
void generate_obj_header(FILE *fp, OBJ_HEADER *header);
void generate_obj_file(FILE *fp, OBJ_FILE *file);
#endif
