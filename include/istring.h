#ifndef __ISTRING_H__
#define __ISTRING_H__

#include <stdint.h>

typedef struct {
    uint32_t size;  /* string pool capacity */
    uint32_t index; /* point to free space */
    char *base;     /* string pool base address */
} StrPool;

int sp_init(StrPool *sp, uint32_t size);
char *sp_add(StrPool *sp, const char *str, uint32_t size);
void sp_clean(StrPool *sp);

#endif
