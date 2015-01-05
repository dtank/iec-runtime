#ifndef __IVALUE_H__
#define __IVALUE_H__

#include <stdint.h>
#include <string.h>
#include "helper.h"
#include "logger.h"

/* Internal Value Type Tag */
#define TINT    1
#define TUINT   2
#define TDOUBLE 3
#define TSTRING 4
//#define TREF    4

#define MIN_VTYPE TINT
#define MAX_VTYPE TSTRING

/* Internal Basic Type */
typedef int64_t  IInt;
typedef uint64_t IUInt;
typedef double   IDouble;
typedef struct {
    uint32_t length; /* '\0' included */
    char *str;
} IString;

/* Internal Value for Register | Constant | Global */
typedef struct Value {
    uint8_t type;
    union {
        IInt value_i;
        IUInt value_u;
        IDouble value_d;
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
#define isuint(v)   checktype(v, TUINT)
#define isdouble(v) checktype(v, TDOUBLE)
#define isstring(v) checktype(v, TSTRING)

/* type setter */
#define settype(v, t) {(v).type = t;}
#define settint(v)    settype(v, TINT)
#define settuint(v)   settype(v, TUINT)
#define settdouble(v) settype(v, TDOUBLE)
#define settstring(v) settype(v, TSTRING)

/* value getter */
#define vint(value)    ((value).v.value_i)
#define vuint(value)   ((value).v.value_u)
#define vdouble(value) ((value).v.value_d)
#define vstring(value) ((value).v.value_s)
#define vstrstr(value) ((value).v.value_s.str)
#define vstrlen(value) ((value).v.value_s.length)
#define vnumber(v, t)  ((t)((t==TINT)*vint(v) + (t==TUINT)*vuint(v) + (t==TDOUBLE)*vdouble(v))) /* CAN'T be left value */

/* value setter */
#define setvint(value, data_i)    {(value).v.value_i = (data_i);}
#define setvuint(value, data_u)   {(value).v.value_u = (data_u);}
#define setvdouble(value, data_d) {(value).v.value_d = (data_d);}
#define setvstring(value, data_s) {(value).v.value_s = (data_s);}
/*-----------------------------------------------------------------------------
 * arithmetic Macro
 * Premise:
 *     1) verifier already checked type error
 *     2) int, uint & double type only
 * Procedue:
 *     1) set type
 *     2) set result value
 *---------------------------------------------------------------------------*/
#define arith2vi(op, a, b) {           \
    settint(a);                        \
    vint(a) = cast(IInt, op(vint(b))); \
}
#define arith2vu(op, a, b) {              \
    settuint(a);                          \
    vuint(a) = cast(IUInt, op(vuint(b))); \
}
#define arith2vd(op, a, b) {                    \
    settdouble(a);                              \
    vdouble(a) = cast(IDouble, op(vdouble(b))); \
}
#define arith2v(op, a, b) { /* a = op(b) */ \
    if (isint(b)) {                         \
        arith2vi(op, a, b);                 \
    } else if (isuint(b)) {                 \
        arith2vu(op, a, b);                 \
    } else if (isdouble(b)) {               \
        arith2vd(op, a, b);                 \
    }                                       \
}
#define arith3vi(op, a, b, c) {   \
    settint(a);                   \
    vint(a) = vint(b) op vint(c); \
}
#define arith3vu(op, a, b, c) {      \
    settuint(a);                     \
    vuint(a) = vuint(b) op vuint(c); \
}
#define arith3vd(op, a, b, c) {            \
    settdouble(a);                         \
    vdouble(a) = vdouble(b) op vdouble(c); \
}
#define arith3v(op, a, b, c) { /* a = b op c */ \
    if (isint(b)) {                             \
        arith3vi(op, a, b, c);                  \
    } else if (isuint(b)) {                     \
        arith3vu(op, a, b, c);                  \
    } else if (isdouble(b)) {                   \
        arith3vd(op, a, b, c);                  \
    }                                           \
}
#define vadd(a, b, c) arith3v(+, a, b, c)
#define vsub(a, b, c) arith3v(-, a, b, c)
#define vmul(a, b, c) arith3v(*, a, b, c)
#define vdiv(a, b, c) arith3v(/, a, b, c)

#define vshl(a, b, c) arith3vu(<<, a, b, c)
#define vshr(a, b, c) arith3vu(>>, a, b, c)
#define vand(a, b, c) arith3vu(&, a, b, c)
#define vor(a, b, c)  arith3vu(|, a, b, c)
#define vxor(a, b, c) arith3vu(^, a, b, c)
#define vnot(a, b)    arith2vu(~, a, b)

#define vland(a, b, c) arith3vu(&&, a, b, c)
#define vlor(a, b, c)  arith3vu(||, a, b, c)
#define vlxor(a, b, c) arith3vu(^, a, b, c)
#define vlnot(a, b)    arith2vu(!, a, b)
//#define vmod(a, b, c) {vint(a) = vint(b) % vint(c);} /* int type only */
/*-----------------------------------------------------------------------------
 * Comparation Macro
 * Premise:
 *     1) verifier has checked type errors already
 *     2) int, uint & double type only
 *---------------------------------------------------------------------------*/
/* EQ */
#define is_eqt(a, b)  (type(a) == type(b))
#define is_eqvi(a, b) (vint(a) == vint(b))
#define is_eqvu(a, b) (vuint(a) == vuint(b))
#define is_eqvd(a, b) (vdouble(a) == vdouble(b))
//#define is_eqvs(a, b) (strcmp(vstrstr(a), vstrstr(b)) == 0 && vstrlen(a) == vstrlen(b))
#define is_eqv(a, b) (is_eqvi(a, b) || is_eqvu(a, b) || is_eqvd(a, b))
#define is_eq(a, b)  (is_eqt(a, b) && is_eqv(a, b)) /* both type & value are equal */

/* LT */
#define is_ltvi(a, b) (vint(a) < vint(b))
#define is_ltvu(a, b) (vuint(a) < vuint(b))
#define is_ltvd(a, b) (vdouble(a) < vdouble(b))
#define is_ltv(a, b)  (is_ltvi(a, b) || is_ltvu(a, b) || is_ltvd(a, b))
#define is_lt(a, b)   (is_eqt(a, b) && is_ltv(a, b))

/* LE */
#define is_levi(a, b) (vint(a) <= vint(b))
#define is_levu(a, b) (vuint(a) <= vuint(b))
#define is_levd(a, b) (vdouble(a) <= vdouble(b))
#define is_lev(a, b)  (is_levi(a, b) || is_levu(a, b) || is_levd(a, b))
#define is_le(a, b)   (is_eqt(a, b) && is_lev(a, b))

#if LEVEL_DBG <= LOGGER_LEVEL
    #define dump_value(s, v)                                                            \
    do {                                                                                \
        switch (type(v)) {                                                              \
            case TINT:                                                                  \
                fprintf(stderr, s " [%.0f(int)]", (double)vint(v)); break;              \
            case TUINT:                                                                 \
                fprintf(stderr, s " [%.0f(uint)]", (double)vuint(v)); break;            \
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
