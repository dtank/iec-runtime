#ifndef __IVALUE_H__
#define __IVALUE_H__

#include <stdint.h>
#include <string.h>
#include "helper.h"
#include "logger.h"

/* Internal Value Type Tag */
#define TINT    1
#define TDOUBLE 2
#define TSTRING 3
//#define TREF    4

#define MIN_VTYPE TINT
#define MAX_VTYPE TSTRING

/* Internal String */
typedef struct {
    uint32_t length; /* '\0' included */
    char *str;
} IString;

/* Internal Value for Register | Constant | Global */
typedef struct Value {
    uint8_t type;
    union {
        int32_t value_i;
        double value_d;
        IString value_s;
        //uint16_t value_p; [> reference or pointer value <]
    } v;
} IValue;

/*-----------------------------------------------------------------------------
 * Value Helper Function Macro
 *---------------------------------------------------------------------------*/
/* type checker */
#define type(v) ((v).type) /* type getter */
#define checktype(v, t) (type(v) == t)
#define isint(v)    checktype(v, TINT)
#define isdouble(v) checktype(v, TDOUBLE)
#define isstring(v) checktype(v, TSTRING)

/* type setter */
#define settype(v, t) {(v).type = t;}
#define settint(v)    settype(v, TINT)
#define settdouble(v) settype(v, TDOUBLE)
#define settstring(v) settype(v, TSTRING)

/* value getter */
#define vint(value)    ((value).v.value_i)
#define vdouble(value) ((value).v.value_d)
#define vstring(value) ((value).v.value_s)
#define vstrstr(value) ((value).v.value_s.str)
#define vstrlen(value) ((value).v.value_s.length)
#define vnumber(v, t)  (t)((t==TINT)*vint(v) + (t==TDOUBLE)*vdouble(v)) /* CAN'T be left value */

/* value setter */
#define setvint(value, data_i) {(value).v.value_i = (data_i);}
#define setvdouble(value, data_d) {(value).v.value_d = (data_d);}
#define setvstring(value, data_s) {(value).v.value_s = (data_s);}
/*-----------------------------------------------------------------------------
 * arithmetic Macro
 * Premise:
 *     1) verifier has checked type error already
 *     2) int & double type only
 * Procedue:
 *     1) set type
 *     2) set result value
 *---------------------------------------------------------------------------*/
#define arith3v(op, a, b, c) { /* a = b op c */\
    if (isint(b)) {                            \
        settint(a);                            \
        vint(a) = vint(b) op vint(c);          \
    } else if (isdouble(b)) {                  \
        settdouble(a);                         \
        vdouble(a) = vdouble(b) op vdouble(c); \
    }                                          \
}
#define vadd(a, b, c) arith3v(+, a, b, c)
#define vsub(a, b, c) arith3v(-, a, b, c)
#define vmul(a, b, c) arith3v(*, a, b, c)
#define vdiv(a, b, c) arith3v(/, a, b, c)
#define vmod(a, b, c) {vint(a) = vint(b) % vint(c);} /* int type only */

#define arith2vi(op, a, b) {          \
    settint(a);                       \
    vint(a) = cast(int, op(vint(b))); \
}
#define arith2vd(op, a, b) {                   \
    settdouble(a);                             \
    vdouble(a) = cast(double, op(vdouble(b))); \
}
#define arith2v(op, a, b) { /* a = op(b) */ \
    if (isint(b)) {                         \
        arith2vi(op, a, b);                 \
    } else if (isdouble(b)) {               \
        arith2vd(op, a, b);                 \
    }                                       \
}
/*-----------------------------------------------------------------------------
 * Comparation Macro
 * Premise:
 *     1) verifier has checked type errors already
 *     2) int & double type only
 *---------------------------------------------------------------------------*/
/* EQ */
#define is_eqt(a, b)  (type(a) == type(b))
#define is_eqvi(a, b) (vint(a) == vint(b))
#define is_eqvd(a, b) (vdouble(a) == vdouble(b))
//#define is_eqvs(a, b) (strcmp(vstrstr(a), vstrstr(b)) == 0 && vstrlen(a) == vstrlen(b))
#define is_eqv(a, b)  (is_eqvi(a, b) || is_eqvd(a, b))
#define is_eq(a, b) (is_eqt(a, b) && is_eqv(a, b)) /* both type & value are equal */

/* LT */
#define is_ltvi(a, b) (vint(a) < vint(b))
#define is_ltvd(a, b) (vdouble(a) < vdouble(b))
#define is_ltv(a, b) (is_ltvi(a, b) || is_ltvd(a, b))
#define is_lt(a, b) (is_eqt(a, b) && is_ltv(a, b))

/* LE */
#define is_levi(a, b) (vint(a) <= vint(b))
#define is_levd(a, b) (vdouble(a) <= vdouble(b))
#define is_lev(a, b) (is_levi(a, b) || is_levd(a, b))
#define is_le(a, b) (is_eqt(a, b) && is_lev(a, b))

#if LEVEL_DBG <= LOGGER_LEVEL
    #define dump_value(s, v)                                                            \
    do {                                                                                \
        switch (type(v)) {                                                              \
            case TINT:                                                                  \
                fprintf(stderr, s " [%d(int)]", vint(v)); break;                        \
            case TDOUBLE:                                                               \
                fprintf(stderr, s " [%f(double)]", vdouble(v)); break;                  \
            case TSTRING:                                                               \
                fprintf(stderr, s " [%s(length = %d)]", vstrstr(v), vstrlen(v)); break; \
            default: fprintf(stderr, "Unknown Value Type(%d)", type(v)); break;         \
        }                                                                               \
    } while(0)
#else
    #define dump_value(value)
#endif

#endif
