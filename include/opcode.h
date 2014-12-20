#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <stdint.h>

typedef uint32_t Instruction;

/*-----------------------------------------------------------------------------
 * Instructoin Encoding
 *---------------------------------------------------------------------------*/
#define SIZE_OP  8
#define SIZE_A   8
#define SIZE_B   8
#define SIZE_C   8
#define SIZE_Bx  (SIZE_B+SIZE_C)
#define SIZE_sAx (SIZE_A+SIZE_B+SIZE_C)

#define POS_C   0
#define POS_B   (POS_C+SIZE_C)
#define POS_A   (POS_B+SIZE_B)
#define POS_OP  (POS_A+SIZE_A)
#define POS_Bx  POS_C
#define POS_sAx POS_C

#define BIAS_sAx (1<<(SIZE_sAx-1))
/*-----------------------------------------------------------------------------
 * Instructoin Decoder Macro
 *---------------------------------------------------------------------------*/
/* creates a mask with `n' 1 bits at position `p' */
#define MASK1(n,p)	((~((~(Instruction)0)<<(n)))<<(p))
/* creates a mask with `n' 0 bits at position `p' */
#define MASK0(n,p)	(~MASK1(n,p))
#define cast(type, exp) ((type)(exp))

#define GET_OPCODE(i) (cast(OpCode, (i>>POS_OP) & MASK1(SIZE_OP, 0)))
#define getarg(i, pos, size) (cast(int, (i>>pos) & MASK1(size, 0)))
#define GETARG_A(i)   getarg(i, POS_A, SIZE_A)
#define GETARG_B(i)   getarg(i, POS_B, SIZE_B)
#define GETARG_C(i)   getarg(i, POS_C, SIZE_C)
#define GETARG_Bx(i)  getarg(i, POS_Bx, SIZE_Bx)
#define GETARG_sAx(i) (getarg(i, POS_sAx, SIZE_sAx) - BIAS_sAx)
/*-----------------------------------------------------------------------------
 * Instructoin OpCode
 *---------------------------------------------------------------------------*/
typedef enum {
    /* basic opcode */
    OP_GLOAD = 1,
    OP_GSTORE,
    OP_KLOAD,
    OP_MOV,
    /* arithmetic opcode */
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    /* compare opcode */
    OP_LT,
    OP_LE,
    OP_GT,
    OP_GE,
    /* control opcode */
    OP_JMP,
    OP_HALT,
    /* call opcode */
    OP_FCALL,
    OP_SCALL,
    OP_RET,
} OpCode;
#endif
