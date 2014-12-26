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
void sfun_abs(IValue *reg_base) {
    arith2v(fabs, REGO(SFUN_ABS, 0), REGI(0)); /* int & double type only */
}
void sfun_sqrt(IValue *reg_base) {
    arith2vd(sqrt, REGO(SFUN_SQRT, 0), REGI(0)); /* double type only */
}
//TODO add some lib
