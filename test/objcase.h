#ifndef __OBJ_CASE_H__
#define __OBJ_CASE_H__

#include "objstruct.h"
#include "sysenv.h"

#define OBJ_ARITHMETIC {                                                   \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8},               \
    {4000000, 0, 1, 0, 0}, /* io config */                                 \
    {1, 4000000, { /* servo config */                                      \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS,               \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                              \
    }},                                                                    \
    1, /* plc task count */                                                \
    256, /* string pool size */                                            \
    {                                                                      \
        {{"task1", 80, TASK_TYPE_INTERVAL, 0, 100000000u, 1, 2, 2, 4, 2},{ \
            {"main", 0, 0, 2, 0}, /* pou descriptor */                     \
        },{                                                                \
            {TINT,{1}}, /* constant */                                     \
            {TINT,{2}}, /* constant */                                     \
        },{                                                                \
            {TINT,{0}}, /* global variable */                              \
            {TINT,{0}}, /* global variable */                              \
        },{ /* instructions */                                             \
            0xffffffff,                                                    \
            0xffffffff,                                                    \
        }},                                                                \
    }                                                                      \
}

#endif
