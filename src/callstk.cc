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
