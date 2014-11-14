#ifndef __INST_DEF_H__
#define __INST_DEF_H__

#include <map>
#include <stdint.h>

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
} INST_DESC;

typedef map<uint32_t, INST_DESC> inst_desc_t;
static const inst_desc_t::value_type inst_desc_data[] = {
    /* Arithmetic */
	inst_desc_t::value_type(STD_ADD, {3}),
	inst_desc_t::value_type(STD_SUB, {3}),
	inst_desc_t::value_type(STD_MUL, {3}),
	inst_desc_t::value_type(STD_DIV, {3}),
	inst_desc_t::value_type(STD_MOV, {2}),
    /* Comparation */
	inst_desc_t::value_type(STD_GT, {3}),
	inst_desc_t::value_type(STD_LT, {3}),
	inst_desc_t::value_type(STD_EQ, {3}),
    /* Mathematics */
	inst_desc_t::value_type(STD_ABS, {2}),
	inst_desc_t::value_type(STD_SQRT, {2}),
	inst_desc_t::value_type(STD_SIN, {2}),
	inst_desc_t::value_type(STD_COS, {2}),
	inst_desc_t::value_type(STD_TAN, {2}),
    /* Bit Operation */
	inst_desc_t::value_type(STD_SHL, {3}),
	inst_desc_t::value_type(STD_SHR, {3}),
	inst_desc_t::value_type(STD_AND, {3}),
	inst_desc_t::value_type(STD_OR, {3}),
	inst_desc_t::value_type(STD_XOR, {3}),
	inst_desc_t::value_type(STD_NOT, {2}),
};
static const uint32_t inst_desc_count = sizeof inst_desc_data / sizeof inst_desc_data[0];
static const inst_desc_t inst_desc_map(inst_desc_data, inst_desc_data + inst_desc_count);

#endif
