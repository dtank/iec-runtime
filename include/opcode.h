#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <stdint.h>

typedef uint32_t Instruction;

/*-----------------------------------------------------------------------------
 * Instructoin Encoding Defination
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
    /* control opcode */
    OP_EQ,
    OP_LT,
    OP_LE,
    OP_JMP,
    OP_HALT,
    /* call opcode */
    OP_FCALL,
    OP_SCALL,
    OP_RET,
} OpCode;

#define MIN_OPCODE OP_GLOAD
#define MAX_OPCODE OP_RET
/*-----------------------------------------------------------------------------
 * Helper Funtion Macros
 *---------------------------------------------------------------------------*/
/* creates a mask with `n' 1 bits at position `p' */
#define MASK1(n,p)	((~((~(Instruction)0)<<(n)))<<(p))
/* creates a mask with `n' 0 bits at position `p' */
#define MASK0(n,p)	(~MASK1(n,p))
#define cast(type, exp) ((type)(exp))
/*-----------------------------------------------------------------------------
 * Instructoin Decoder Macro
 * Note: decoder won't change original instruction definitely!
 *---------------------------------------------------------------------------*/
#define GET_OPCODE(i) (cast(OpCode, ((i)>>POS_OP) & MASK1(SIZE_OP, 0)))
#define getarg(i,pos,size) (cast(int, ((i)>>pos) & MASK1(size, 0)))
#define GETARG_A(i)   getarg(i, POS_A, SIZE_A)
#define GETARG_B(i)   getarg(i, POS_B, SIZE_B)
#define GETARG_C(i)   getarg(i, POS_C, SIZE_C)
#define GETARG_Bx(i)  getarg(i, POS_Bx, SIZE_Bx)
#define GETARG_sAx(i) (getarg(i, POS_sAx, SIZE_sAx) - BIAS_sAx)
/*-----------------------------------------------------------------------------
 * Instructoin Encoder Macro
 *---------------------------------------------------------------------------*/
#define CREATE_ABC(o,a,b,c)	((cast(Instruction, o)<<POS_OP) \
			| (cast(Instruction, a)<<POS_A)                 \
			| (cast(Instruction, b)<<POS_B)                 \
			| (cast(Instruction, c)<<POS_C))

#define CREATE_ABx(o,a,bx)	((cast(Instruction, o)<<POS_OP) \
			| (cast(Instruction, a)<<POS_A)                 \
			| (cast(Instruction, bx)<<POS_Bx))

/* sax == signed int */
#define CREATE_sAx(o,sAx)		((cast(Instruction, o)<<POS_OP) \
			| (cast(Instruction, sAx+BIAS_sAx)<<POS_sAx))

#define CREATE_GLOAD(a, bx)  CREATE_ABx(OP_GLOAD, a, bx)
#define CREATE_GSTORE(a, bx) CREATE_ABx(OP_GSTORE, a, bx)
#define CREATE_KLOAD(a, bx)  CREATE_ABx(OP_KLOAD, a, bx)
#define CREATE_MOV(a, b)     CREATE_ABC(OP_MOV, a, b, 0)

#define CREATE_ADD(a, b, c)  CREATE_ABC(OP_ADD, a, b, c)
#define CREATE_SUB(a, b, c)  CREATE_ABC(OP_SUB, a, b, c)
#define CREATE_MUL(a, b, c)  CREATE_ABC(OP_MUL, a, b, c)
#define CREATE_DIV(a, b, c)  CREATE_ABC(OP_DIV, a, b, c)
#define CREATE_MOD(a, b, c)  CREATE_ABC(OP_MOD, a, b, c)

#define CREATE_EQ(b, c)  CREATE_ABC(OP_EQ, 1, b, c)
#define CREATE_LT(b, c)  CREATE_ABC(OP_LT, 1, b, c)
#define CREATE_LE(b, c)  CREATE_ABC(OP_LE, 1, b, c)
#define CREATE_NE(b, c)  CREATE_ABC(OP_EQ, 0, b, c)
#define CREATE_GE(b, c)  CREATE_ABC(OP_LT, 0, b, c)
#define CREATE_GT(b, c)  CREATE_ABC(OP_LE, 0, b, c)
#define CREATE_JMP(sAx)  CREATE_sAx(OP_JMP, sAx)
#define CREATE_HALT()  CREATE_ABC(OP_HALT, 0, 0, 0)

#endif
