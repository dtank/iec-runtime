//#include <map>
#include <stdint.h>
#include "stdinst.h"
//#include "instruction.h"

void std_add(void *in1, void *in2, void *out) {
	int32_t in1_32b = *(int32_t *)in1;
	int32_t in2_32b = *(int32_t *)in2;
	*(int32_t *)out = in1_32b + in2_32b;
}

void std_sub(void *in1, void *in2, void *out) {
	int32_t in1_32b = *(int32_t *)in1;
	int32_t in2_32b = *(int32_t *)in2;
	*(int32_t *)out = in1_32b - in2_32b;
}

