#include "executor.h"
#include "instruction.h"
#include "logger.h"

extern inst_desc_map_t inst_desc;
extern char *io_shm;
extern ec_map_t ec_msg;

// TODO property data code MUST together
static void plc_task_execute(void *plc_model) {
    //PLC_MODEL *model = (PLC_MODEL *)plc_model;
    //rt_task_set_periodic(NULL, TM_NOW, task->property->interval);
    //while (1) {
        //rt_task_wait_period(NULL);
        //for (int i = 0; i < task->property->inst_count; ++i) {
            //((inst_3op_t)inst_desc[task->code->inst[i]->id].inst_addr)(
                //(void *)task->code->inst[i]->arg_addr[0],
                //(void *)task->code->inst[i]->arg_addr[1],
                //(void *)task->code->inst[i]->arg_addr[2]);
            //LOGGER(LOGGER_DBG, "arg1_value = %d", *(uint32_t *)task->code->inst[i]->arg_addr[0]);
        //}
    //}
}

//void plc_task_init(PLC_MODEL *model) {
    //for (int i = 0; i < model->task_config.task_count; ++i) {
        //if (rt_task_create(&model->rt_task[i], model->task_config.task_prop[i].name, 0, model->task_config.task_prop[i].priority, 0)) {
            //LOGGER_ERR(EC_PLC_TASK_CREATE, "(\"%s\")", model->task_config.task_prop[i].name);
        //}
    //}
//}
//void plc_task_start(PLC_MODEL *model) {
    //for (int i = 0; i < model->task_config.task_count; ++i) {
        //if (rt_task_start(&model->rt_task[i], &plc_task_execute, (void *)model)) {
            //LOGGER_ERR(EC_PLC_TASK_START, "(\"%s\")", model->task_config.task_prop[i].name);
        //}
    //}
//}
//void plc_task_delete(PLC_TASK_LIST *task_list, PLC_CONFIG *config) {
    //for (int i = 0; i < config->task_count; ++i) {
        //if (rt_task_delete(&task_list->rt_task[i])) {
            //LOGGER(LOGGER_ERR, "ERROR: deleting PLC task \"%s\"\n", task_list->plc_task[i]->property->name);
        //}
    //}
//}
