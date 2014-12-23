#include <math.h>
#include "libsys.h"

#define REGI_BASE 0
#define REGI_COUNT(id) (spou_desc[id].input_count) /* id = system-level pou id */
#define REGO_BASE(id)  (REGI_BASE + REGI_COUNT(id))
#define REGO_COUNT(id) (spou_desc[id].output_count)
#define REG(n) (reg_base[n])
#define REGI(n) REG(REGI_BASE+n)
#define REGO(id, n) REG(REGO_BASE(id)+n)

/* Numerical Functions */
void sfun_abs(IValue *reg_base) {
    arith2v(fabs, REGO(SFUN_ABS, 0), REGI(0)); /* int & double type only */
}
void sfun_sqrt(IValue *reg_base) {
    dump_value("REGI(0)", REGI(0)); EOL;
    arith2vd(sqrt, REGO(SFUN_SQRT, 0), REGI(0)); /* double type only */
}
