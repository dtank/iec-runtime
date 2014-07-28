#include <string.h>
#include "generator.h"
#include "logger.h"


/*-----------------------------------------------------------------------------
 * PLC Object File Header Generator
 *---------------------------------------------------------------------------*/
void generate_obj_header(FILE *fp, OBJ_HEADER *header) {
	fwrite(header->magic, MAGIC_SIZE, 1, fp);
	fwrite(&header->type, sizeof(header->type), 1, fp);
	fwrite(&header->order, sizeof(header->order), 1, fp);
	fwrite(&header->version, sizeof(header->version), 1, fp);
	fwrite(&header->machine, sizeof(header->machine), 1, fp);
}
/*-----------------------------------------------------------------------------
 * I/O Configuration Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_iocs(FILE *fp, OBJ_IOCS *iocs) {
	fwrite(&iocs->update_interval, sizeof(iocs->update_interval), 1, fp);
	fwrite(&iocs->ldi_count, sizeof(iocs->ldi_count), 1, fp);
	fwrite(&iocs->ldo_count, sizeof(iocs->ldo_count), 1, fp);
	fwrite(&iocs->lai_count, sizeof(iocs->lai_count), 1, fp);
	fwrite(&iocs->lao_count, sizeof(iocs->lao_count), 1, fp);
}
/*-----------------------------------------------------------------------------
 * Servo Configuration Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_acs(FILE *fp, OBJ_ACS *acs) {
	fwrite(&acs->is_combined, sizeof(acs->is_combined), 1, fp);
	fwrite(&acs->name_size, sizeof(acs->name_size), 1, fp);
	fwrite(acs->name, acs->name_size, 1, fp); /* including '\0' */
	fwrite(&acs->node_id, sizeof(acs->node_id), 1, fp);
	fwrite(&acs->axis_type, sizeof(acs->axis_type), 1, fp);
	fwrite(&acs->oper_mode, sizeof(acs->oper_mode), 1, fp);
	fwrite(&acs->sw_limit_neg, sizeof(acs->sw_limit_neg), 1, fp);
	fwrite(&acs->sw_limit_pos, sizeof(acs->sw_limit_pos), 1, fp);
	fwrite(&acs->max_vel, sizeof(acs->max_vel), 1, fp);
	fwrite(&acs->max_acc, sizeof(acs->max_acc), 1, fp);
	fwrite(&acs->max_dec, sizeof(acs->max_dec), 1, fp);
	fwrite(&acs->max_jerk, sizeof(acs->max_jerk), 1, fp);
}
void generate_obj_scs(FILE *fp, OBJ_SCS *scs) {
	fwrite(&scs->axis_count, sizeof(scs->axis_count), 1, fp);
	fwrite(&scs->update_interval, sizeof(scs->update_interval), 1, fp);
	for (int i = 0; i < scs->axis_count; ++i) {
		generate_obj_acs(fp, &(scs->axis_group[i]));
	}
}
/*-----------------------------------------------------------------------------
 * PLC Task Property Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_ptps(FILE *fp, OBJ_PTPS *ptps) {
	fwrite(&ptps->name_size, sizeof(ptps->name_size), 1, fp);
	fwrite(ptps->name, ptps->name_size, 1, fp);
	fwrite(&ptps->priority, sizeof(ptps->priority), 1, fp);
	fwrite(&ptps->interval, sizeof(ptps->interval), 1, fp);
	//fwrite(&ptps->ptds_size, sizeof(ptcs->ptds_size), 1, fp);
	//fwrite(&ptps->inst_count, sizeof(ptcs->inst_count), 1, fp);
}
/*-----------------------------------------------------------------------------
 * PLC Task Data Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_ptds(FILE *fp, OBJ_PTDS *ptds) {
	fwrite(&ptds->size, sizeof(ptds->size), 1, fp);
	fwrite(ptds->data, ptds->size, 1, fp);
}
/*-----------------------------------------------------------------------------
 * PLC Task Code Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_inst(FILE *fp, OBJ_INST *inst, inst_desc_map_t *inst_desc) {
    fwrite(&inst->id, sizeof(inst->id), 1, fp);
    for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
        fwrite(&inst->arg_va[i], sizeof(inst->arg_va[0]), 1, fp);
    }
}
void generate_obj_ptcs(FILE *fp, OBJ_PTCS *ptcs, inst_desc_map_t *inst_desc) {
    fwrite(&ptcs->inst_count, sizeof(ptcs->inst_count), 1, fp);
    for (int i = 0; i < ptcs->inst_count; ++i) {
        generate_obj_inst(fp, &ptcs->inst[i], inst_desc);
    }
}
/*-----------------------------------------------------------------------------
 * PLC Task List Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_pts(FILE *fp, OBJ_PTS *pts, inst_desc_map_t *inst_desc) {
    generate_obj_ptps(fp, &pts->prop);
    generate_obj_ptds(fp, &pts->data);
    generate_obj_ptcs(fp, &pts->code, inst_desc);
}
void generate_obj_ptls(FILE *fp, OBJ_PTLS *ptls, inst_desc_map_t *inst_desc) {
    fwrite(&ptls->task_count, sizeof(ptls->task_count), 1, fp);
    for (int i = 0; i < ptls->task_count; ++i) {
        generate_obj_pts(fp, &ptls->task[i], inst_desc);
    }
}
/*-----------------------------------------------------------------------------
 * PLC Object File Generator
 *---------------------------------------------------------------------------*/
void generate_obj_file(FILE *fp, OBJ_FILE *file, inst_desc_map_t *inst_desc) {
    generate_obj_header(fp, &file->header);
    generate_obj_iocs(fp, &file->iocs);
    generate_obj_scs(fp, &file->scs);
    generate_obj_ptls(fp, &file->ptls, inst_desc);
}
