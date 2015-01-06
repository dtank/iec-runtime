#include <math.h>
#include "libsys.h"

/* id: system-level pou id */
#define SPOU_DESC(id)     (spou_desc[id])
#define SPOU_OUTPUTC(id) (SPOU_DESC(id).output_count)
#define SPOU_INPUTC(id)   (SPOU_DESC(id).input_count)
#define SPOU_OBASE 0
#define SPOU_IBASE(id)  (SPOU_OBASE + SPOU_OUTPUTC(id))

#define REG(n)      (reg_base[n])
#define REGO(n)     REG(SPOU_OBASE+n)
#define REGI(id, n) REG(SPOU_IBASE(id)+n)

/*-----------------------------------------------------------------------------
 * Numerical Functions
 *---------------------------------------------------------------------------*/
/**
 * OUT := ABS(IN)
 * OUT.type := IN.type (int, uint & double only)
 */
void sfun_abs(IValue *reg_base) {
    arith2v(fabs, REGO(0), REGI(SFUN_ABS, 0));
}
/**
 * OUT := SQRT(IN)
 * OUT.type := IN.type (double only)
 */
void sfun_sqrt(IValue *reg_base) {
    arith2vd(sqrt, REGO(0), REGI(SFUN_SQRT, 0));
}
void sfun_log(IValue *reg_base){}
void sfun_ln(IValue *reg_base){}
void sfun_exp(IValue *reg_base){}
void sfun_sin(IValue *reg_base){}
void sfun_cos(IValue *reg_base){}
void sfun_tan(IValue *reg_base){}
void sfun_asin(IValue *reg_base){}
void sfun_acos(IValue *reg_base){}
void sfun_atan(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * Arithmetic Functions
 *---------------------------------------------------------------------------*/
void sfun_add(IValue *reg_base){}
void sfun_mul(IValue *reg_base){}
/**
 * OUT := IN0 % IN1
 * OUT.type := IN0.type (int & uint type only)
 */
void sfun_mod(IValue *reg_base) {
    if (isint(REGI(SFUN_MOD, 0))) {
        arith3vi(%, REGO(0), REGI(SFUN_MOD, 0), REGI(SFUN_MOD, 1));
    } else {
        arith3vu(%, REGO(0), REGI(SFUN_MOD, 0), REGI(SFUN_MOD, 1));
    }
}
/**
 * OUT := IN0 ** IN1
 * IN1.type MUST be int
 * OUT.type := IN0.type (int, uint & double only)
 */
void sfun_expt(IValue *reg_base) {
    if (isint(REGI(SFUN_EXPT, 0))) {
        settint(REGO(0));
        vint(REGO(0)) = pow(vint(REGI(SFUN_EXPT, 0)), vint(REGI(SFUN_EXPT, 1)));
    } else if (isuint(REGI(SFUN_EXPT, 0))) {
        settuint(REGO(0));
        vuint(REGO(0)) = pow(vuint(REGI(SFUN_EXPT, 0)), vint(REGI(SFUN_EXPT, 1)));
    } else {
        settdouble(REGO(0));
        vdouble(REGO(0)) = pow(vdouble(REGI(SFUN_EXPT, 0)), vint(REGI(SFUN_EXPT, 1)));
    }
}
/*-----------------------------------------------------------------------------
 * Bit Operation Functions
 *---------------------------------------------------------------------------*/
void sfun_and(IValue *reg_base){}
void sfun_or(IValue *reg_base){}
void sfun_xor(IValue *reg_base){}
void sfun_rol(IValue *reg_base){}
void sfun_ror(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * Comparison Functions
 *---------------------------------------------------------------------------*/
void sfun_lt(IValue *reg_base){}
void sfun_le(IValue *reg_base){}
void sfun_gt(IValue *reg_base){}
void sfun_ge(IValue *reg_base){}
void sfun_eq(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * Selection Functions
 *---------------------------------------------------------------------------*/
void sfun_sel(IValue *reg_base){}
void sfun_max(IValue *reg_base){}
void sfun_min(IValue *reg_base){}
void sfun_limit(IValue *reg_base){}
void sfun_mux(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * String Functions
 *---------------------------------------------------------------------------*/
void sfun_len(IValue *reg_base){}
void sfun_left(IValue *reg_base){}
void sfun_right(IValue *reg_base){}
void sfun_mid(IValue *reg_base){}
void sfun_concat(IValue *reg_base){}
void sfun_insert(IValue *reg_base){}
void sfun_delete(IValue *reg_base){}
void sfun_replace(IValue *reg_base){}
void sfun_find(IValue *reg_base){}
