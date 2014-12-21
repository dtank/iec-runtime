#ifndef __IVALUE_H__
#define __IVALUE_H__

#include <stdint.h>
#include <logger.h>

/* Value Type Tag */
#define TINT    1
#define TDOUBLE 2
#define TSTRING 3
//#define TREF    4

#define MIN_VTYPE TINT
#define MAX_VTYPE TSTRING

#if LEVEL_DBG <= LOGGER_LEVEL
    #define dump_value(value)                                                                                  \
    do {                                                                                                       \
        switch ((value).type) {                                                                                \
            case TINT:                                                                                         \
                LOGGER_DBG("Integer: %d", (value).v.value_i); break;                                           \
            case TDOUBLE:                                                                                      \
                LOGGER_DBG("Double: %f", (value).v.value_d); break;                                            \
            case TSTRING:                                                                                      \
                LOGGER_DBG("String: %s(length = %d)", (value).v.value_s.str, (value).v.value_s.length); break; \
            default: break;                                                                                    \
        }                                                                                                      \
    } while(0)
#else
    #define dump_value(value)
#endif

/* Internal String Type */
typedef struct {
    uint32_t length;
    char *str;
} IString;

/* Internal Value Type for Register | Constant | Global */
typedef struct Value {
    uint8_t type;
    union {
        int32_t value_i;
        double value_d;
        IString value_s;
        //uint16_t value_p; [> reference or pointer value <]
    } v;
} IValue;

#endif
