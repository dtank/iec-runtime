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
	for (int i = 0; i < scs->axis_count; ++i) {
		generate_obj_acs(fp, &(scs->axis_group[i]));
	}
}
/*-----------------------------------------------------------------------------
 * PLC Task Configuration Segment Generator
 *---------------------------------------------------------------------------*/
//void generate_obj_ptcs(FILE *fp, OBJ_PTCS *ptcs) {
	//fwrite(&ptcs->task_count, sizeof(ptcs->task_count), 1, fp);
//}

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
 * Definition of PLC Task Data Segment
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
 * PLC Task Configuration Segment Generator
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
 //PLC Object File Header Generator
//static void generate_io_refresh_interval(FILE *fp, io_refresh_interval_t interval) {
	//LOGGER_DBG("TRACE: io_refresh_interval = %d", interval);
	//if (fwrite(&interval, sizeof(io_refresh_interval_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating io refresh interval (%d)...", interval);
	//}
//}
//static void generate_task_count(FILE *fp, task_count_t count) {
	//LOGGER_DBG("TRACE: task_count = %d", count);
	//if (fwrite(&count, sizeof(task_count_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating task count (%d)...", count);
	//}
//}
//void generate_bin_header(FILE *fp, BIN_HEADER *header) {
	//generate_io_refresh_interval(fp, header->io_refresh_interval);
	//generate_task_count(fp, header->task_count);
//}

 //PLC Object File Body -- Task Property Segment Generator 
//static void generate_task_name_size(FILE *fp, task_name_size_t size) {
	//LOGGER_DBG("TRACE: task_name_size = %d", size);
	//if (fwrite(&size, sizeof(task_name_size_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating size of task name (%d)...", size);
	//}
//}
//static void generate_task_name(FILE *fp, task_name_t *name) {
	//LOGGER_DBG("TRACE: task_name = %s", name);
	//if (fwrite(name, strlen(name), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating task name (%s)...", name);
	//}
//}
//static void generate_task_priority(FILE *fp, task_priority_t priority) {
	//LOGGER_DBG("TRACE: task_priority = %d", priority);
	//if (fwrite(&priority, sizeof(task_priority_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating task priority (%d)...", priority);
	//}
//}
//static void generate_task_interval(FILE *fp, task_interval_t interval) {
	//LOGGER_DBG("TRACE: task_interval = %d", interval);
	//if (fwrite(&interval, sizeof(task_interval_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating task interval (%d)...", interval);
	//}
//}
//static void generate_tds_size(FILE *fp, tds_size_t size) {
	//LOGGER_DBG("TRACE: tds_size = %d", size);
	//if (fwrite(&size, sizeof(tds_size_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating size of task data segment (%d)...", size);
	//}
//}
//static void generate_inst_count(FILE *fp, inst_count_t count) {
	//LOGGER_DBG("TRACE: inst_count = %d", count);
	//if (fwrite(&count, sizeof(inst_count_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating instruction count (%d)...", count);
	//}
//}

//void generate_tps(FILE *fp, BIN_TPS *tps) {
	//generate_task_name_size(fp, tps->name_size);
	//generate_task_name(fp, tps->name);
	//generate_task_priority(fp, tps->priority);
	//generate_task_interval(fp, tps->interval);
	//generate_tds_size(fp, tps->tds_size);
	//generate_inst_count(fp, tps->inst_count);
//}

 //PLC Object File Body -- Task Data Segment Generator 
//void generate_tds(FILE *fp, BIN_TPS *tps, BIN_TDS *tds) {
	//if (fwrite(tds, tps->tds_size, 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating task data segment...", 0);
	//}
//}

 //PLC Object File Body -- Task Code Segment Generator 
//static void generate_inst_id(FILE *fp, inst_id_t id) {
	//LOGGER_DBG("TRACE: inst_id = %d", id);
	//if (fwrite(&id, sizeof(inst_id_t), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating instruction id (%d)...", id);
	//}
//}
//static void generate_inst_arg_va(FILE *fp, inst_arg_va_t arg_va) {
	//LOGGER_DBG("TRACE: inst_arg_va = %d", arg_va);
	//if (fwrite(&arg_va, sizeof(arg_va), 1, fp) < 1) {
		//LOGGER(LOGGER_ERR, "ERROR: generating instruction argument virtual address (%d)...", arg_va);
	//}
//}
//static void generate_inst(FILE *fp, BIN_INST *inst, inst_desc_map_t *inst_desc) {
	//generate_inst_id(fp, inst->id);
	//for (int i = 0; i < (*inst_desc)[inst->id].args_count; ++i) {
		//generate_inst_arg_va(fp, inst->arg_va[i]);
	//}
//}
//void generate_tcs(FILE *fp, BIN_TPS *tps, BIN_TCS *tcs, inst_desc_map_t *inst_desc) {
	//for (int i = 0; i < tps->inst_count; ++i) {
		//generate_inst(fp, &(tcs->inst[i]), inst_desc);
	//}
//}
