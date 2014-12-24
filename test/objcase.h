#ifndef __OBJ_CASE_H__
#define __OBJ_CASE_H__

#include "objstruct.h"
#include "opcode.h"
#include "sysenv.h"

#define OBJ_ARITHMETIC {                                                               \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8},                           \
    {4000000, 0, 0, 0, 0, 0, 0, 0, 0}, /* io config */                                 \
    {1, 4000000, { /* servo config */                                                  \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,                           \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                                          \
    }},                                                                                \
    1, /* plc task count */                                                            \
    {                                                                                  \
        {{"task1", 80, TASK_TYPE_INTERVAL, 0, 100000000u,                              \
          256, 1, 2, 2, 4, 4},{ /* sp_size, pouc, constc, globalc, *INSTC*, sframec */ \
            {"main", 0, 0, 3, 0}, /* name, in, out, local, addr */                     \
        },{                                                                            \
            {TINT,{1}}, /* K(0) */                                                     \
            {TINT,{2}}, /* K(1) */                                                     \
        },{                                                                            \
            {TINT,{0}}, /* G(0) */                                                     \
            {TINT,{0}}, /* G(1) */                                                     \
        },{ /* instructions */                                                         \
            CREATE_KLOAD(0, 0),  /* R(0) <- K(0) */                                    \
            CREATE_KLOAD(1, 1),  /* R(1) <- K(1) */                                    \
            CREATE_ADD(2, 0, 1), /* R(2) <- R(0) + R(1) */                             \
            CREATE_GSTORE(2, 0), /* R(2) -> G(0) */                                    \
        }},                                                                            \
    }                                                                                  \
}

#define OBJ_CONTROL {                                                                  \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8},                           \
    {4000000, 0, 0, 0, 0, 0, 0, 0, 0}, /* io config */                                 \
    {1, 4000000, { /* servo config */                                                  \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,                           \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                                          \
    }},                                                                                \
    1, /* plc task count */                                                            \
    {                                                                                  \
        {{"task1", 80, TASK_TYPE_INTERVAL, 0, 100000000u,                              \
          256, 1, 2, 2, 6, 4},{ /* sp_size, pouc, constc, globalc, *INSTC*, sframec */ \
            {"main", 0, 0, 3, 0}, /* name, in, out, local, addr */                     \
        },{                                                                            \
            {TINT,{1}}, /* K(0) */                                                     \
            {TINT,{2}}, /* K(1) */                                                     \
        },{                                                                            \
            {TINT,{0}}, /* G(0) */                                                     \
            {TINT,{0}}, /* G(1) */                                                     \
        },{ /* instructions */                                                         \
            CREATE_KLOAD(0, 0),  /* R(0) <- K(0) */                                    \
            CREATE_KLOAD(1, 1),  /* R(1) <- K(1) */                                    \
            CREATE_LTJ(0, 1),     /* R(0) < R(1) */                                     \
            CREATE_JMP(1),       /* Jump over next 1 instruction */                    \
            CREATE_GSTORE(1, 0), /* R(1) -> G(0) */                                    \
            CREATE_HALT(),                                                             \
        }},                                                                            \
    }                                                                                  \
}
#define OBJ_IO {                                                                       \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8},                           \
    {8000000, 0, 6, 0, 0, 0, 0, 0, 0}, /* io config */                                 \
    {1, 8000000, { /* servo config */                                                  \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,                           \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                                          \
    }},                                                                                \
    1, /* plc task count */                                                            \
    {                                                                                  \
        {{"task1", 80, TASK_TYPE_INTERVAL, 0, 100000000u,                              \
          256, 1, 2, 2, 5, 4},{ /* sp_size, pouc, constc, globalc, *INSTC*, sframec */ \
            {"main", 0, 0, 3, 0}, /* name, in, out, local, addr */                     \
        },{                                                                            \
            {TINT,{1}}, /* K(0) */                                                     \
            {TINT,{2}}, /* K(1) */                                                     \
        },{                                                                            \
            {TINT,{0}}, /* G(0) */                                                     \
            {TINT,{0}}, /* G(1) */                                                     \
        },{ /* instructions */                                                         \
            CREATE_KLOAD(0, 0),  /* R(0) <- K(0) */                                    \
            CREATE_KLOAD(1, 1),  /* R(1) <- K(1) */                                    \
            CREATE_DOBb(0, 0),   /* R(0) -> DO(0) */                                   \
            CREATE_DOBb(1, 1),   /* R(1) -> DO(1) */                                   \
            CREATE_HALT(),                                                             \
        }},                                                                            \
    }                                                                                  \
}

/* MUST put value_d the first in IValue */
#define OBJ_NUMFUN {                                                                   \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8},                           \
    {8000000, 0, 0, 0, 0, 0, 0, 0, 0}, /* io config */                                 \
    {1, 8000000, { /* servo config */                                                  \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,                           \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                                          \
    }},                                                                                \
    1, /* plc task count */                                                            \
    {                                                                                  \
        {{"task1", 80, TASK_TYPE_INTERVAL, 0, 100000000u,                              \
          256, 1, 2, 2, 5, 4},{ /* sp_size, pouc, constc, globalc, *INSTC*, sframec */ \
            {"main", 0, 0, 3, 0}, /* name, in, out, local, addr */                     \
        },{                                                                            \
            {TINT,{4}}, /* K(0) */                                                \
            {TINT,{16}}, /* K(1) */                                               \
        },{                                                                            \
            {TINT,{0}}, /* G(0) */                                                     \
            {TINT,{0}}, /* G(1) */                                                     \
        },{ /* instructions */                                                         \
            CREATE_KLOAD(0, 0),  /* R(0) <- K(0) */                                    \
            CREATE_KLOAD(1, 1),  /* R(1) <- K(1) */                                    \
            CREATE_SCALL(1, SFUN_SQRT), /* R(1)=REGI; R(2)=REGO */                     \
            CREATE_GSTORE(2, 0), /* R(2) -> G(0) */                                    \
            CREATE_HALT(),                                                             \
        }},                                                                            \
    }                                                                                  \
}

#define OBJ_UCALL {                                                                    \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8},                           \
    {8000000, 0, 0, 0, 0, 0, 0, 0, 0}, /* io config */                                 \
    {1, 8000000, { /* servo config */                                                  \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,                           \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                                          \
    }},                                                                                \
    1, /* plc task count */                                                            \
    {                                                                                  \
        {{"task1", 80, TASK_TYPE_INTERVAL, 0, 100000000u,                              \
          256, 2, 2, 2, 7, 4},{ /* sp_size, pouc, constc, globalc, *INSTC*, sframec */ \
            {"main", 0, 0, 3, 0}, /* name, in, out, local, addr */                     \
            {"add", 2, 1, 0, 5}, /* name, in, out, local, addr */                      \
        },{                                                                            \
            {TINT,{4}}, /* K(0) */                                                     \
            {TINT,{16}}, /* K(1) */                                                    \
        },{                                                                            \
            {TINT,{0}}, /* G(0) */                                                     \
            {TINT,{0}}, /* G(1) */                                                     \
        },{ /* instructions */                                                         \
            /* main fun (5 instructions) */                                                             \
            CREATE_KLOAD(0, 0),  /* R(0) <- K(0) */                                    \
            CREATE_KLOAD(1, 1),  /* R(1) <- K(1) */                                    \
            CREATE_UCALL(0, 1), /* CALL UPOU(1); R(0)=REG_BASE */                      \
            CREATE_GSTORE(2, 0), /* R(2) -> G(0) */                                    \
            CREATE_HALT(),                                                             \
            /* add fun (2 instructions) */                                                               \
            CREATE_ADD(2, 0, 1), /* R(2) <- R(0) + R(1) */                             \
            CREATE_RET(0, 1), /*  */                             \
        }},                                                                            \
    }                                                                                  \
}
#endif
