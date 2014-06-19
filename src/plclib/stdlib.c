#include "stdlib.h"

void std_add(void *in1, void *in2, void *out) {
	int32_t in1_32b = *(int32_t *)in1;
	int32_t in2_32b = *(int32_t *)in2;
	*(int32_t *)out = in1_32b + in2_32b;
}

