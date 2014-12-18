#ifndef __CALLSTK_H__
#define __CALLSTK_H__

#include <stdint.h>
#include "ivalue.h"

typedef struct {
    uint16_t called;   /* index of current pou descriptors */
    uint32_t ret_addr; /* return address(AKA index of instructions) */
    IValue *reg_base;  /* register group base address */
} SFrame; /* Stack Frame */

typedef struct {
    uint16_t capacity; /* stack capacity */
    uint16_t top;      /* top of stack(AKA index of stack frame) */
    SFrame *base;      /* stack base address */
} CStack; /* Calling Stack */

int cs_init(CStack *stk, uint16_t cap);
int cs_push(CStack *stk, SFrame *frame);
int cs_pop(CStack *stk);

#endif
