#include <math.h>
#include <stdint.h>
#include "stdinst.h"
//#include "instruction.h"

/* Arithmetic */
void std_add(void *in1, void *in2, void *out) {
	*(int32_t *)out = *(int32_t *)in1 + *(int32_t *)in2;
}
void std_sub(void *in1, void *in2, void *out) {
	*(int32_t *)out = *(int32_t *)in1 - *(int32_t *)in2;
}
void std_mul(void *in1, void *in2, void *out) {
	*(int32_t *)out = *(int32_t *)in1 * *(int32_t *)in2;
}
void std_div(void *in1, void *in2, void *out) {
	*(int32_t *)out = *(int32_t *)in1 / *(int32_t *)in2;
}
/* Comparation */
void std_gt(void *in1, void *in2, void *out) {
	*(bool *)out = *(int32_t *)in1 > *(int32_t *)in2;
}
void std_lt(void *in1, void *in2, void *out) {
	*(bool *)out = *(int32_t *)in1 < *(int32_t *)in2;
}
void std_eq(void *in1, void *in2, void *out) {
	*(bool *)out = *(int32_t *)in1 == *(int32_t *)in2;
}
/* Mathematics */
void std_abs(void *in, void *out) {
    *(double *)out = fabs(*(double *)in);
}
void std_sqrt(void *in, void *out) {
    *(double *)out = sqrt(*(double *)in);
}
void std_sin(void *in, void *out) {
    *(double *)out = sin(*(double *)in);
}
void std_cos(void *in, void *out) {
    *(double *)out = cos(*(double *)in);
}
void std_tan(void *in, void *out) {
    *(double *)out = tan(*(double *)in);
}
/* Bit Operation */
void std_shl(void *in, void *n, void *out) {
    *(double *)out = *(uint32_t *)in << *(uint32_t *)n;
}
void std_shr(void *in, void *n, void *out) {
    *(double *)out = *(uint32_t *)in >> *(uint32_t *)n;
}
void std_and(void *in1, void *in2, void *out) {
    *(double *)out = *(uint32_t *)in1 & *(uint32_t *)in2;
}
void std_or(void *in1, void *in2, void *out) {
    *(double *)out = *(uint32_t *)in1 | *(uint32_t *)in2;
}
void std_xor(void *in1, void *in2, void *out) {
    *(double *)out = *(uint32_t *)in1 ^ *(uint32_t *)in2;
}
void std_not(void *in, void *out) {
    *(double *)out = ~*(uint32_t *)in;
}
