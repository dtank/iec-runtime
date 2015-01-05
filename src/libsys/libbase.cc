#include <math.h>
#include "libsys.h"

/* id: system-level pou id */
#define SPOU_DESC(id)     (spou_desc[id])
#define SPOU_INPUTC(id)   (SPOU_DESC(id).input_count)
#define SPOU_OUTPOUTC(id) (SPOU_DESC(id).output_count)
#define SPOU_IBASE 0
#define SPOU_OBASE(id)  (SPOU_IBASE + SPOU_INPUTC(id))

#define REG(n)      (reg_base[n])
#define REGI(n)     REG(SPOU_IBASE+n)
#define REGO(id, n) REG(SPOU_OBASE(id)+n)

/* Numerical Functions */
/**
 * REGO(0) := abs(REGI(0))
 * REGO(0).type := REGI(0).type (int, uint & double only)
 */
void sfun_abs(IValue *reg_base) {
    arith2v(fabs, REGO(SFUN_ABS, 0), REGI(0));
}
/**
 * REGO(0) := sqrt(REGI(0))
 * REGO(0).type := REGI(0).type (double only)
 */
void sfun_sqrt(IValue *reg_base) {
    arith2vd(sqrt, REGO(SFUN_SQRT, 0), REGI(0));
}
/**
 * REGO(0) := REGI(0) % REGI(1)
 * REGO(0).type := REGI(0).type (int & uint type only)
 */
void sfun_mod(IValue *reg_base) {
    if (isint(REGI(0))) {
        arith3vi(%, REGO(SFUN_MOD, 0), REGI(0), REGI(1));
    } else {
        arith3vu(%, REGO(SFUN_MOD, 0), REGI(0), REGI(1));
    }
}
/**
 * REGO(0) := REGI(0) ** REGI(1)
 * REGI(1).type MUST be int
 * REGO(0).type := REGI(0).type (int, uint & double only)
 */
void sfun_expt(IValue *reg_base) {
    if (isint(REGI(0))) {
        settint(REGO(SFUN_EXPT, 0));
        vint(REGO(SFUN_EXPT, 0)) = pow(vint(REGI(0)), vint(REGI(1)));
    } else if (isuint(REGI(0))) {
        settuint(REGO(SFUN_EXPT, 0));
        vuint(REGO(SFUN_EXPT, 0)) = pow(vuint(REGI(0)), vint(REGI(1)));
    } else {
        settdouble(REGO(SFUN_EXPT, 0));
        vdouble(REGO(SFUN_EXPT, 0)) = pow(vdouble(REGI(0)), vint(REGI(1)));
    }
}
