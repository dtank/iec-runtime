//#include <map>
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
