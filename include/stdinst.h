#ifndef __STD_INST_H__
#define __STD_INST_H__

/* Arithmetic */
void std_add(void *in1, void *in2, void *out);
void std_sub(void *in1, void *in2, void *out);
void std_mul(void *in1, void *in2, void *out);
void std_div(void *in1, void *in2, void *out);
/* Comparation */
void std_gt(void *in1, void *in2, void *out);
void std_lt(void *in1, void *in2, void *out);
void std_eq(void *in1, void *in2, void *out);

#endif

