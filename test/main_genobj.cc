#include <stdio.h>
#include "objcase.h"
#include "generator.h"

inst_desc_t inst_desc = inst_desc_map;

int main(int argc, char* argv[]) {
    OBJ_FILE obj_file = OBJ_ARITHMETIC;
	FILE *obj = fopen("plc.bin", "wb");
    generate_obj_file(obj, &obj_file, &inst_desc);
	fclose(obj);
    return 0;
}

