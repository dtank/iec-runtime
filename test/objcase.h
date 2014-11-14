#ifndef __GENOBJ_H__
#define __GENOBJ_H__

#include "objdef.h"

#define OBJ_ARITHMETIC {                                     \
    {MAGIC, SYS_TYPE_32, BYTE_ORDER_LIT, 1, MACH_CORTEX_A8}, \
    {4000000, 0, 1, 0, 0}, /* io configuration */            \
    {1, 4000000, {                                           \
        {"axis1", false, 1, AXIS_TYPE_FINITE, OPER_MODE_POS, \
		0.0, 180.0, 100.0, 20.0, 20.0, 10.0},                \
    }},                                                      \
    1, /* plc task count */                                  \
    {                                                        \
        {{"task1", 80, 100000000u, 16, 1},                   \
        {0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,     \
         0x00, 0x00, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11},{   \
        {STD_ADD, {0x00000001, 0x00000011, 0x00000001}},     \
        {STD_MOV, {0x00000001, 0x00000002}},                 \
        }},                                                  \
    }                                                        \
}
#endif
