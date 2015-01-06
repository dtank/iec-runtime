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
 * OUT & IN: int, uint & double only
 */
void sfun_abs(IValue *reg_base) {
    arith2v(fabs, REGO(0), REGI(SFUN_ABS, 0));
}
/**
 * OUT := SQRT(IN)
 * OUT & IN: double only
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
/**
 * OUT := IN1+IN2+...
 * SIZE := IN0 (uint only)
 * OUT & IN: int, uint & double only
 */
void sfun_add(IValue *reg_base) {
    REGO(0) = REGI(SFUN_ADD, 1);
    for (IUInt i = 2; i <= vuint(REGI(SFUN_ADD, 0)); i++) {
        arith3v(+, REGO(0), REGO(0), REGI(SFUN_ADD, i));
    }
}
void sfun_mul(IValue *reg_base){}
/**
 * OUT := IN0 % IN1
 * OUT & IN: int & uint only
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
 * IN1: int only
 * OUT & IN0: int, uint & double only
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
/**
 * OUT := IN1 & IN2 & ...
 * SIZE := IN0 (uint only)
 * OUT & IN: uint only
 */
void sfun_and(IValue *reg_base) {
    REGO(0) = REGI(SFUN_AND, 1);
    for (IUInt i = 2; i <= vuint(REGI(SFUN_ADD, 0)); i++) {
        arith3vu(&, REGO(0), REGO(0), REGI(SFUN_ADD, i));
    }
}
void sfun_or(IValue *reg_base){}
void sfun_xor(IValue *reg_base){}
void sfun_rol(IValue *reg_base){}
void sfun_ror(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * Comparison Functions
 *---------------------------------------------------------------------------*/
/**
 * OUT := (IN1<IN2) && (IN2<IN3) ...
 * SIZE := IN0 (uint only)
 * OUT: uint only
 * IN: int, uint & double only
 */
void sfun_lt(IValue *reg_base) {
    IValue temp;
    vlt(REGO(0), REGI(SFUN_LT, 1), REGI(SFUN_LT, 2));
    for (IUInt i = 2; i < vuint(REGI(SFUN_ADD, 0)); i++) {
        vlt(temp, REGI(SFUN_LT, i), REGI(SFUN_LT, i+1));
        vland(REGO(0), REGO(0), temp);
    }
}
void sfun_le(IValue *reg_base){}
void sfun_gt(IValue *reg_base){}
void sfun_ge(IValue *reg_base){}
void sfun_eq(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * Selection Functions
 *---------------------------------------------------------------------------*/
/**
 * OUT := IN1(if G == 0) || IN2(if G == 1)
 * G := IN0 (uint only)
 * OUT & IN: int, uint & double only
 */
void sfun_sel(IValue *reg_base) {
    if (vuint(REGI(SFUN_SEL, 0)) == 0) {
        REGO(0) = REGI(SFUN_SEL, 1);
    } else if (vuint(REGI(SFUN_SEL, 0)) == 1) {
        REGO(0) = REGI(SFUN_SEL, 2);
    }
}
void sfun_max(IValue *reg_base){}
void sfun_min(IValue *reg_base){}
void sfun_limit(IValue *reg_base){}
void sfun_mux(IValue *reg_base){}
/*-----------------------------------------------------------------------------
 * String Functions
 *---------------------------------------------------------------------------*/
/**
 * OUT := LEN(STR)
 * STR := IN0 (string only)
 * OUT: uint only
 */
void sfun_len(IValue *reg_base) {
    settuint(REGO(0));
    setvuint(REGO(0), vstrlen(REGI(SFUN_LEN, 0))-1); /* '\0' excluded ! */
}
void sfun_left(IValue *reg_base){}
void sfun_right(IValue *reg_base){}
void sfun_mid(IValue *reg_base){}
void sfun_concat(IValue *reg_base){}
void sfun_insert(IValue *reg_base){}
void sfun_delete(IValue *reg_base){}
void sfun_replace(IValue *reg_base){}
void sfun_find(IValue *reg_base){}
