#include <string.h>
#include "istring.h"
#include "syslimit.h"
#include "logger.h"


int sp_init(StrPool *sp, uint32_t size) {
    assert(sp != NULL);
    assert(size <= MAX_SP_SIZE); /* guaranteed by verifier */

    sp->size = size;
    sp->index = 0;
    sp->base = new char[size];
    if (sp->base == NULL) {
        LOGGER_ERR(EC_OOM, "initializing string pool");
        return -1;
    }
    return 0;
}
char *sp_add(StrPool *sp, const char *str, uint32_t size) { /* size include '\0' */
    assert(sp != NULL);
    assert(str != NULL);

    if (sp->size < sp->index+size) {
        LOGGER_ERR(EC_SP_FULL, ""); //TODO expand capacity automatically
        return NULL;
    }
    strcpy(&sp->base[sp->index], str);
    sp->index += size;
    return &sp->base[sp->index-size];
}
void sp_clean(StrPool *sp) {
    assert(sp != NULL);

    sp->size = 0;
    sp->index = 0;
    if (sp->base != NULL) {
        delete[] sp->base;
    }
}
