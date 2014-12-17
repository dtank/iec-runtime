#ifndef __CALLSTK_H__
#define __CALLSTK_H__

#include <stdint.h>
#include "ivalue.h"

/* Stack Frame */
typedef struct {
    IValue *reg_base;  /* register group base address */
    uint16_t caller;   /* index of current function descriptors */
    uint32_t ret_addr; /* return address(AKA index of instructions) */
} SFrame;

#endif
