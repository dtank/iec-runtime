#ifndef __LIBSYS_H__
#define __LIBSYS_H__

#include <stdint.h>
#include "ivalue.h"

#define MAX_SPOU_NAME_SIZE 20
typedef struct {
    char name[MAX_SPOU_NAME_SIZE];
    uint8_t input_count;
    uint8_t output_count;
    void (*addr)(IValue*);
} SPOUDesc; /* System-level POU(Library) descriptor */

/* ORDER SENSITIVE */
enum SPOU_ID {
    /* Numerical Functions */
    SFUN_ABS = 0,
    SFUN_SQRT,
    /* Arithmetic Functions */
    SFUN_MOD,
    SFUN_EXPT,
};

/* Numerical Functions */
void sfun_abs(IValue *reg_base);
void sfun_sqrt(IValue *reg_base);
/* Arithmetic Functions */
void sfun_mod(IValue *reg_base);
void sfun_expt(IValue *reg_base);

static const SPOUDesc spou_desc[] = {
    /* Numerical Functions */
    {"SFUN_ABS", 1, 1, sfun_abs},
    {"SFUN_SQRT", 1, 1, sfun_sqrt},
    /* Arithmetic Functions */
    {"SFUN_MOD", 2, 1, sfun_mod},
    {"SFUN_EXPT", 2, 1, sfun_expt},
};

#endif
