#include "executor.h"
#include "ivalue.h"
#include "opcode.h"
#include "logger.h"

extern char *io_shm;
extern ec_map_t ec_msg;

#define PC  (task->pc)
#define EOC (task->task_desc.inst_count) /* end of code */
#define instruction (task->code[PC])
#define opcode GET_OPCODE(instruction)

#define A   GETARG_A(instruction)
#define B   GETARG_B(instruction)
#define C   GETARG_C(instruction)
#define Bx  GETARG_Bx(instruction)
#define sAx GETARG_sAx(instruction)
#define R(i) (task->stack.base[task->stack.top-1].reg_base[i])
#define G(i) (task->vglobal[i])
#define K(i) (task->vconst[i])

static void executor(void *plc_task) {
    PLCTask *task = (PLCTask *)plc_task;
    rt_task_set_periodic(NULL, TM_NOW, task->task_desc.interval);
    while (1) {
        rt_task_wait_period(NULL);
        //TODO pre input
        for (PC = 0; PC < EOC; ) {
            LOGGER_DBG("instruction[%d] = %0#10x, OpCode = %d", PC, instruction, opcode);
            switch (opcode) {
                case OP_GLOAD:  R(A) = G(Bx); dump_value("R(A)", R(A)); PC++; break; /* PC++ MUST be last */
                case OP_GSTORE: G(Bx) = R(A); dump_value("G(Bx)", G(Bx)); PC++; break;
                case OP_KLOAD:  R(A) = K(Bx); dump_value("R(A)", R(A)); PC++; break;
                case OP_MOV:    R(A) = R(B); PC++; break;
                case OP_ADD:    vadd(R(A), R(B), R(C)); dump_value("R(A)", R(A)); PC++; break;
                case OP_SUB:    vsub(R(A), R(B), R(C)); PC++; break;
                case OP_MUL:    vmul(R(A), R(B), R(C)); PC++; break;
                case OP_DIV:    vdiv(R(A), R(B), R(C)); PC++; break;
                case OP_MOD:    vmod(R(A), R(B), R(C)); PC++; break;
                case OP_JMP:    PC += sAx; break;
                case OP_HALT:   PC = EOC; break;
                default: LOGGER_DBG("Unknown OpCode(%d)", opcode); break;
            }
        }
        //TODO post output
    }
}

void plc_task_init(TaskList *task_list) {
    for (int i = 0; i < task_list->task_count; ++i) {
        if (rt_task_create(&task_list->rt_task[i], task_list->plc_task[i].task_desc.name, 0, task_list->plc_task[i].task_desc.priority, 0)) {
            LOGGER_ERR(EC_PLC_TASK_CREATE, "(\"%s\")", task_list->plc_task[i].task_desc.name);
        }
    }
}
void plc_task_start(TaskList *task_list) {
    for (int i = 0; i < task_list->task_count; ++i) {
        if (rt_task_start(&task_list->rt_task[i], &executor, (void *)&task_list->plc_task[i])) {
            LOGGER_ERR(EC_PLC_TASK_START, "(\"%s\")", task_list->plc_task[i].task_desc.name);
        }
    }
}
//void plc_task_delete(TaskList *task_list) {
    //for (int i = 0; i < task_list->task_count; ++i) {
        //if (rt_task_delete(&task_list->rt_task[i])) {
            //TODO Error
        //}
    //}
//}
