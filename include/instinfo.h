#ifndef __INST_INFO_H__
#define __INST_INFO_H__

#include <map>

enum INST_IDS {
	STD_ADD = 0,
	STD_SUB,
	STD_MUL,
	STD_DIV
};

const map<int, int> inst_infos {
	make_pire(STD_ADD, 3),
	make_pire(STD_SUB, 3),
	make_pire(STD_MUL, 3),
	make_pire(STD_DIV, 3),
};
#endif
