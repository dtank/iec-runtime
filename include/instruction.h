#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <map>
#include <stdint.h>
#include "stdinst.h"

using namespace std;

enum INST_ID {
	STD_ADD = 1u,
	STD_SUB,
	STD_MUL,
	STD_DIV
};

typedef struct {
	uint8_t args_count;
	void *inst_addr;
} INST_DESC;


typedef void (*inst_3op_t)(void *, void *, void *);

typedef map<uint32_t, INST_DESC> inst_desc_map_t;
static const inst_desc_map_t::value_type inst_desc_data[] = {
	inst_desc_map_t::value_type(STD_ADD, {3u, (void *)std_add}),
	inst_desc_map_t::value_type(STD_SUB, {3u, (void *)std_sub}),
};
static const uint32_t inst_desc_count = sizeof inst_desc_data / sizeof inst_desc_data[0];
static const inst_desc_map_t inst_desc_map(inst_desc_data, inst_desc_data + inst_desc_count);



#endif
