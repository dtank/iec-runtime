#ifndef __LIBSYS_H__
#define __LIBSYS_H__

/* Arithmetic */
void std_add(void *in1, void *in2, void *out);
void std_sub(void *in1, void *in2, void *out);
void std_mul(void *in1, void *in2, void *out);
void std_div(void *in1, void *in2, void *out);
void std_mov(void *in, void *out);
/* Comparation */
void std_gt(void *in1, void *in2, void *out);
void std_lt(void *in1, void *in2, void *out);
void std_eq(void *in1, void *in2, void *out);
/* Mathematics */
void std_abs(void *in, void *out);
void std_sqrt(void *in, void *out);
void std_sin(void *in, void *out);
void std_cos(void *in, void *out);
void std_tan(void *in, void *out);
/* Bit Operation */
void std_shl(void *in, void *n, void *out);
void std_shr(void *in, void *n, void *out);
void std_and(void *in1, void *in2, void *out);
void std_or(void *in1, void *in2, void *out);
void std_xor(void *in1, void *in2, void *out);
void std_not(void *in, void *out);

#endif

