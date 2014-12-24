#include <string.h>
#include "generator.h"

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
	fwrite(&iocs->rdi_count, sizeof(iocs->rdi_count), 1, fp);
	fwrite(&iocs->rdo_count, sizeof(iocs->rdo_count), 1, fp);
	fwrite(&iocs->rai_count, sizeof(iocs->rai_count), 1, fp);
	fwrite(&iocs->rao_count, sizeof(iocs->rao_count), 1, fp);
}
/*-----------------------------------------------------------------------------
 * Servo Configuration Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_acs(FILE *fp, OBJ_ACS *acs) {
	fwrite(acs->name, MAX_AXIS_NAME_SIZE, 1, fp); /* including '\0' */
	fwrite(&acs->is_combined, sizeof(acs->is_combined), 1, fp);
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
 * PLC Task Segment Generator
 *---------------------------------------------------------------------------*/
void generate_obj_tds(FILE *fp, OBJ_TDS *tds) {
	fwrite(tds->name, MAX_TASK_NAME_SIZE, 1, fp);
	fwrite(&tds->priority, sizeof(tds->priority), 1, fp);
	fwrite(&tds->type, sizeof(tds->type), 1, fp);
	fwrite(&tds->signal, sizeof(tds->signal), 1, fp);
	fwrite(&tds->interval, sizeof(tds->interval), 1, fp);
	fwrite(&tds->sp_size, sizeof(tds->sp_size), 1, fp);
    fwrite(&tds->pou_count, sizeof(tds->pou_count), 1, fp);
    fwrite(&tds->const_count, sizeof(tds->const_count), 1, fp);
    fwrite(&tds->global_count, sizeof(tds->global_count), 1, fp);
    fwrite(&tds->inst_count, sizeof(tds->inst_count), 1, fp);
    fwrite(&tds->sframe_count, sizeof(tds->sframe_count), 1, fp);
}
void generate_obj_pds(FILE *fp, OBJ_PDS *pds) {
	fwrite(pds->name, MAX_POU_NAME_SIZE, 1, fp);
	fwrite(&pds->input_count, sizeof(pds->input_count), 1, fp);
	fwrite(&pds->output_count, sizeof(pds->output_count), 1, fp);
	fwrite(&pds->local_count, sizeof(pds->local_count), 1, fp);
	fwrite(&pds->addr, sizeof(pds->addr), 1, fp);
}
void generate_obj_value(FILE *fp, OBJ_VAL *value) {
	fwrite(&value->type, sizeof(value->type), 1, fp);
    switch (value->type) {
        case TINT: fwrite(&value->v.value_i, sizeof(value->v.value_i), 1, fp); break;
        case TDOUBLE: fwrite(&value->v.value_d, sizeof(value->v.value_d), 1, fp); break;
        case TSTRING: fwrite(&value->v.value_s.length, sizeof(value->v.value_s.length), 1, fp);
                      fwrite(value->v.value_s.str, value->v.value_s.length, 1, fp); break;
        default: break;
    }
}
void generate_obj_pts(FILE *fp, OBJ_PTS *pts) {
    generate_obj_tds(fp, &pts->task_desc);
    for (uint32_t i = 0; i < pts->task_desc.pou_count; ++i) {
        generate_obj_pds(fp, &pts->pou_desc[i]);
    }
    for (uint32_t i = 0; i < pts->task_desc.const_count; ++i) {
        generate_obj_value(fp, &pts->vconst[i]);
    }
    for (uint32_t i = 0; i < pts->task_desc.global_count; ++i) {
        generate_obj_value(fp, &pts->vglobal[i]);
    }
    fwrite(pts->code, pts->task_desc.inst_count*sizeof(OBJ_INST), 1, fp);
}
/*-----------------------------------------------------------------------------
 * PLC Object File Generator
 *---------------------------------------------------------------------------*/
void generate_obj_file(FILE *fp, OBJ_FILE *file) {
    generate_obj_header(fp, &file->header);
    generate_obj_iocs(fp, &file->iocs);
    generate_obj_scs(fp, &file->scs);
    fwrite(&file->task_count, sizeof(file->task_count), 1, fp);
    for (int i = 0; i < file->task_count; ++i) {
        generate_obj_pts(fp, &file->task[i]);
    }
}
