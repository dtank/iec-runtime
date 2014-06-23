#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <map>

using namespace std;

enum INST_ID {
	STD_ADD = 1u,
	STD_SUB,
	STD_MUL,
	STD_DIV
};

typedef map<uint32_t, uint8_t> args_count_t;
const args_count_t::value_type data[] = {
	args_count_t::value_type(STD_ADD, 3u),
	args_count_t::value_type(STD_SUB, 3u),
	args_count_t::value_type(STD_MUL, 3u),
	args_count_t::value_type(STD_DIV, 3u),
};
const uint32_t elem_count = sizeof data / sizeof data[0];
const args_count_t args_count(data, data + elem_count);

typedef struct {
	args_count_t args_count;
} INST_INFO;

#endif
