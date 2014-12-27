#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <stdint.h>
#include <helper.h>

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
    /* data mov opcode */
    OP_GLOAD = 1,
    OP_GSTORE,
    OP_KLOAD,
    OP_DLOAD,
    OP_DSTORE,
    OP_ALOAD,
    OP_ASTORE,
    OP_MOV,
    /* arithmetic opcode */
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    /* flow control opcode */
    OP_EQJ,
    OP_LTJ,
    OP_LEJ,
    OP_JMP,
    OP_HALT,
    /* call opcode */
    OP_SCALL,
    OP_UCALL,
    OP_RET,
} OpCode;

#define MIN_OPCODE OP_GLOAD
#define MAX_OPCODE OP_RET
/*-----------------------------------------------------------------------------
 * Instructoin Decoder Macro
 * Note: decoder won't change original instruction definitely!
 *---------------------------------------------------------------------------*/
#define GET_OPCODE(i) (cast(OpCode, ((i)>>POS_OP) & MASK1(0, SIZE_OP)))
#define getarg(i,pos,size) (cast(int, ((i)>>pos) & MASK1(0, size)))
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

#define CREATE_GLOAD(a, bx)    CREATE_ABx(OP_GLOAD, a, bx)
#define CREATE_GSTORE(a, bx)   CREATE_ABx(OP_GSTORE, a, bx)
#define CREATE_KLOAD(a, bx)    CREATE_ABx(OP_KLOAD, a, bx)
#define CREATE_DLOAD(a, b, c)  CREATE_ABC(OP_DLOAD, a, b, c)
#define CREATE_DSTORE(a, b, c) CREATE_ABC(OP_DSTORE, a, b, c)
#define CREATE_DIXb_c(a, b, c) CREATE_DLOAD(a, b*8+c, 1)
#define CREATE_DIBb(a, b)      CREATE_DLOAD(a, b*8, 8)
#define CREATE_DIWb(a, b)      CREATE_DLOAD(a, b*16, 16)
#define CREATE_DIDb(a, b)      CREATE_DLOAD(a, b*32, 32)
#define CREATE_DOXb_c(a, b, c) CREATE_DSTORE(a, b*8+c, 1)
#define CREATE_DOBb(a, b)      CREATE_DSTORE(a, b*8, 8)
#define CREATE_DOWb(a, b)      CREATE_DSTORE(a, b*16, 16)
#define CREATE_DODb(a, b)      CREATE_DSTORE(a, b*32, 32)
#define CREATE_ALOAD(a, b, c)  CREATE_ABC(OP_ALOAD, a, b, c)
#define CREATE_ASTORE(a, b, c) CREATE_ABC(OP_ASTORE, a, b, c)
#define CREATE_MOV(a, b)       CREATE_ABC(OP_MOV, a, b, 0)

#define CREATE_ADD(a, b, c)  CREATE_ABC(OP_ADD, a, b, c)
#define CREATE_SUB(a, b, c)  CREATE_ABC(OP_SUB, a, b, c)
#define CREATE_MUL(a, b, c)  CREATE_ABC(OP_MUL, a, b, c)
#define CREATE_DIV(a, b, c)  CREATE_ABC(OP_DIV, a, b, c)
#define CREATE_MOD(a, b, c)  CREATE_ABC(OP_MOD, a, b, c)

#define CREATE_EQJ(b, c)  CREATE_ABC(OP_EQJ, 1, b, c)
#define CREATE_LTJ(b, c)  CREATE_ABC(OP_LTJ, 1, b, c)
#define CREATE_LEJ(b, c)  CREATE_ABC(OP_LEJ, 1, b, c)
#define CREATE_NEJ(b, c)  CREATE_ABC(OP_EQJ, 0, b, c)
#define CREATE_GEJ(b, c)  CREATE_ABC(OP_LTJ, 0, b, c)
#define CREATE_GTJ(b, c)  CREATE_ABC(OP_LEJ, 0, b, c)
#define CREATE_JMP(sAx)   CREATE_sAx(OP_JMP, sAx)
#define CREATE_HALT()     CREATE_ABC(OP_HALT, 0, 0, 0)

#define CREATE_SCALL(rid, pid) CREATE_ABx(OP_SCALL, rid, pid) /* r: reg_base id; pid: pou id */
#define CREATE_UCALL(rid, pid) CREATE_ABx(OP_UCALL, rid, pid)
#define CREATE_RET(rid, pid)   CREATE_ABx(OP_RET, rid, pid)

#endif
