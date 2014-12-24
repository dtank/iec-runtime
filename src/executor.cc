#include "executor.h"
#include "ivalue.h"
#include "opcode.h"
#include "io.h"
#include "libsys.h"
#include "logger.h"

extern IOConfig g_ioconfig;
extern IOMem g_ioshm;

/* program counter */
#define PC  (task->pc)
#define EOC (task->task_desc.inst_count) /* end of code */

/* instruction decoder */
#define instruction (task->code[PC])
#define opcode GET_OPCODE(instruction)
#define A   GETARG_A(instruction)
#define B   GETARG_B(instruction)
#define C   GETARG_C(instruction)
#define Bx  GETARG_Bx(instruction)
#define sAx GETARG_sAx(instruction)

/* calling stack */
#define STK  (task->stack)
#define TOP  (task->stack.top)
#define SF   (STK.base[TOP-1])
#define R(i) (SF.reg[i])
#define G(i) (task->vglobal[i])
#define K(i) (task->vconst[i])

/* system-level POU */
#define SPOU(i) (spou_desc[i].addr)

/* user-level POU */
#define UPOU_DESC(i)    (task->pou_desc[i])
#define UPOU_INPUTC(i)  (UPOU_DESC(i).input_count)
#define UPOU_OUTPUTC(i) (UPOU_DESC(i).output_count)
#define UPOU_LOCALC(i)  (UPOU_DESC(i).local_count)
#define UPOU_REGC(i)    (UPOU_INPUTC(i) + UPOU_OUTPUTC(i) + UPOU_LOCALC(i))
#define UPOU_ENTR(i)    (UPOU_DESC(i).addr)

#if LEVEL_DBG <= LOGGER_LEVEL
    #define dump_opcode(i) {fprintf(stderr, #i ": ");}
    #define dump_data(s, i, v) { \
        fprintf(stderr, #s "(%d)", i); \
        dump_value("", v);\
    }
    #define dump_R(i) dump_data(R, i, R(i))
    #define dump_G(i) dump_data(G, i, G(i))
    #define dump_K(i) dump_data(K, i, K(i))
    /* data mov instruction */
    #define dump_imov(i, s1, i1, s2, i2) {\
        dump_opcode(i);\
        dump_##s1(i1);\
        fprintf(stderr, " <- ");\
        dump_##s2(i2);\
        fprintf(stderr, "\n");\
    }
#else
    #define dump_reg2(i, r1, r2)
#endif
static void executor(void *plc_task) {
    PLCTask *task = (PLCTask *)plc_task;
    rt_task_set_periodic(NULL, TM_NOW, task->task_desc.interval);
    IOMem iomem;
    iomem_init(&iomem, &g_ioconfig);
    while (1) {
        rt_task_wait_period(NULL);
        //TODO ADD LOCK!!
        io_memcpy(iomem, g_ioshm);
        for (PC = 0; PC < EOC; ) {
            LOGGER_DBG(DFLAG_SHORT, "instruction[%d] = %0#10x, OpCode = %d", PC, instruction, opcode);
            switch (opcode) {
                case OP_GLOAD:  R(A) = G(Bx); dump_imov(GLOAD, R, A, G, Bx); PC++; break; /* PC++ MUST be last */
                case OP_GSTORE: G(Bx) = R(A); dump_imov(GSTORE, G, Bx, R, A); PC++; break;
                case OP_KLOAD:  R(A) = K(Bx); dump_imov(KLOAD, R, A, K, Bx); PC++; break;
                case OP_DLOAD:  setvint(R(A), getdch(iomem.diu, B, C)); PC++; break;
                case OP_DSTORE: setdch(iomem.dou, B, C, R(A).v.value_i); PC++; break;
                case OP_ALOAD:  setvint(R(A), getach(iomem.aiu, B, C)); PC++; break;
                case OP_ASTORE: setach(iomem.aou, B, C, R(A).v.value_i); PC++; break;
                case OP_MOV:    R(A) = R(B); dump_imov(MOV, R, A, R, B); PC++; break;
                case OP_ADD:    vadd(R(A), R(B), R(C)); dump_value("R(A)", R(A)); PC++; break;
                case OP_SUB:    vsub(R(A), R(B), R(C)); PC++; break;
                case OP_MUL:    vmul(R(A), R(B), R(C)); PC++; break;
                case OP_DIV:    vdiv(R(A), R(B), R(C)); PC++; break;
                case OP_MOD:    vmod(R(A), R(B), R(C)); PC++; break;
                case OP_EQJ:    if (is_eq(R(B), R(C)) == A) PC++; PC++; break; /* A==1, means EQ; A==0, means NE */
                case OP_LTJ:    if (is_lt(R(B), R(C)) == A) PC++; PC++; break; /* A==1, means LT; A==0, means GE */
                case OP_LEJ:    if (is_le(R(B), R(C)) == A) PC++; PC++; break; /* A==1, means LE; A==0, means GT */
                case OP_JMP:    PC += sAx; PC++; break; /* MUST follow EQ/LT/LE */
                case OP_HALT:   PC = EOC; break;
                case OP_UCALL:  SFrame newsf; sf_init(newsf, Bx, PC+1, UPOU_REGC(Bx)); sf_regcpy(newsf, 0, SF, A, UPOU_REGC(Bx)); cs_push(STK, newsf); PC = UPOU_ENTR(Bx); break;
                case OP_SCALL:  SPOU(Bx)(&R(A)); PC++; break;
                default: LOGGER_DBG(DFLAG_SHORT, "Unknown OpCode(%d)", opcode); break;
            }
        }
        //TODO ADD LOCK!!
        io_memcpy(g_ioshm, iomem);
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
void plc_task_delete(TaskList *task_list) {
    for (int i = 0; i < task_list->task_count; ++i) {
        if (rt_task_delete(&task_list->rt_task[i])) {
            LOGGER_ERR(EC_PLC_TASK_DELETE, "(\"%s\")", task_list->plc_task[i].task_desc.name);
        }
    }
}
