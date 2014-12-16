#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <map>
#include <stdint.h>
#include "libsys.h"

using namespace std;

enum INST_ID {
    /* Arithmetic */
	STD_ADD = 1u,
	STD_SUB,
	STD_MUL,
	STD_DIV,
	STD_MOV,
    /* Comparation */
    STD_GT,
    STD_LT,
    STD_EQ,
    /* Mathematics */
    STD_ABS,
    STD_SQRT,
    STD_SIN,
    STD_COS,
    STD_TAN,
    /* Bit Operation */
    STD_SHL,
    STD_SHR,
    STD_AND,
    STD_OR,
    STD_XOR,
    STD_NOT,
};

typedef struct {
	uint8_t args_count;
	void *inst_addr;
} INST_DESC;


typedef void (*inst_3op_t)(void *, void *, void *);

typedef map<uint32_t, INST_DESC> inst_desc_map_t;
static const inst_desc_map_t::value_type inst_desc_data[] = {
    /* Arithmetic */
	inst_desc_map_t::value_type(STD_ADD, {3u, (void *)std_add}),
	inst_desc_map_t::value_type(STD_SUB, {3u, (void *)std_sub}),
	inst_desc_map_t::value_type(STD_MUL, {3u, (void *)std_mul}),
	inst_desc_map_t::value_type(STD_DIV, {3u, (void *)std_div}),
	inst_desc_map_t::value_type(STD_MOV, {2u, (void *)std_mov}),
    /* Comparation */
	inst_desc_map_t::value_type(STD_GT, {3u, (void *)std_gt}),
	inst_desc_map_t::value_type(STD_LT, {3u, (void *)std_lt}),
	inst_desc_map_t::value_type(STD_EQ, {3u, (void *)std_eq}),
    /* Mathematics */
	inst_desc_map_t::value_type(STD_ABS, {2u, (void *)std_abs}),
	inst_desc_map_t::value_type(STD_SQRT, {2u, (void *)std_sqrt}),
	inst_desc_map_t::value_type(STD_SIN, {2u, (void *)std_sin}),
	inst_desc_map_t::value_type(STD_COS, {2u, (void *)std_cos}),
	inst_desc_map_t::value_type(STD_TAN, {2u, (void *)std_tan}),
    /* Bit Operation */
	inst_desc_map_t::value_type(STD_SHL, {3u, (void *)std_shl}),
	inst_desc_map_t::value_type(STD_SHR, {3u, (void *)std_shr}),
	inst_desc_map_t::value_type(STD_AND, {3u, (void *)std_and}),
	inst_desc_map_t::value_type(STD_OR, {3u, (void *)std_or}),
	inst_desc_map_t::value_type(STD_XOR, {3u, (void *)std_xor}),
	inst_desc_map_t::value_type(STD_NOT, {2u, (void *)std_not}),
};
static const uint32_t inst_desc_count = sizeof inst_desc_data / sizeof inst_desc_data[0];
static const inst_desc_map_t inst_desc_map(inst_desc_data, inst_desc_data + inst_desc_count);



#endif
