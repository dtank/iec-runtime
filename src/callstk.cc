#include "callstk.h"
#include "syslimit.h"
#include "logger.h"

extern ec_map_t ec_msg;

int cs_init(CStack *stk, uint16_t cap) {
    assert(stk != NULL);
    assert(cap <= MAX_CS_CAP); /* guaranteed by verifier */

    stk->capacity = cap;
    stk->top = 1;
    stk->base = new SFrame[stk->capacity];
    if (stk->base == NULL) {
        LOGGER_ERR(EC_OOM, "initializing calling stack");
        return -1;
    }
    return 0;
}
int cs_push(CStack *stk, SFrame *frame) {
    assert(stk != NULL);
    assert(frame != NULL);

    if (stk->top == stk->capacity) {
        LOGGER_ERR(EC_CS_FULL, ""); //TODO expand capacity automatically
        return -1;
    }
    stk->base[stk->top] = *frame;
    stk->top++;
    return 0;
}
int cs_pop(CStack *stk) {
    assert(stk != NULL);

    if (stk->top == 0) {
        LOGGER_ERR(EC_CS_EMPTY, "");
        return -1;
    }
    if (stk->base[stk->top].reg_base != NULL) {
        delete[] stk->base[stk->top].reg_base;
    }
    stk->top--;
    return 0;
}
