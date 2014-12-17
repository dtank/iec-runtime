#include "executor.h"
#include "opcode.h"
#include "logger.h"

extern inst_desc_map_t inst_desc;
extern char *io_shm;
extern ec_map_t ec_msg;

static void plc_task_execute(void *plc_task) {
    //PLC_TASK *task = (PLC_TASK *)plc_task;
    //rt_task_set_periodic(NULL, TM_NOW, task->prop.interval);
    //while (1) {
        //rt_task_wait_period(NULL);
        //for (uint32_t i = 0; i < task->prop.inst_count; ++i) {
            //((inst_3op_t)inst_desc[task->code[i].id].inst_addr)(
                //(void *)task->code[i].arg_addr[0],
                //(void *)task->code[i].arg_addr[1],
                //(void *)task->code[i].arg_addr[2]);
            //LOGGER_DBG("inst_id = %d, arg3_value = %d",task->code[i].id, *(uint32_t *)task->code[i].arg_addr[2]);
        //}
    //}
}

//void plc_task_init(TASK_LIST *task_list) {
    //for (int i = 0; i < task_list->task_count; ++i) {
        //if (rt_task_create(&task_list->rt_task[i], task_list->plc_task[i].prop.name, 0, task_list->plc_task[i].prop.priority, 0)) {
            //LOGGER_ERR(EC_PLC_TASK_CREATE, "(\"%s\")", task_list->plc_task[i].prop.name);
        //}
    //}
//}
//void plc_task_start(TASK_LIST *task_list) {
    //for (int i = 0; i < task_list->task_count; ++i) {
        //if (rt_task_start(&task_list->rt_task[i], &plc_task_execute, (void *)&task_list->plc_task[i])) {
            //LOGGER_ERR(EC_PLC_TASK_START, "(\"%s\")", task_list->plc_task[i].prop.name);
        //}
    //}
//}
//void plc_task_delete(TASK_LIST *task_list) {
    //for (int i = 0; i < task_list->task_count; ++i) {
        //if (rt_task_delete(&task_list->rt_task[i])) {
            //TODO Error
        //}
    //}
//}
