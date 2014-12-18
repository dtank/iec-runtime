#include <map>
#include <string>
#include <stdio.h>
#include "objcase.h"
#include "generator.h"

using namespace std;

map<string, OBJ_FILE> case_map;
void init_case() {
    OBJ_FILE obj_case[] = {
        OBJ_ARITHMETIC,
    };
    case_map["arithmetic"] = obj_case[0];
}

int main(int argc, char* argv[]) {
    init_case();
    if (argc != 2) {
        printf("Usage: ./generate_obj casename\n");
    } else {
        string casename(argv[1]);
        FILE *obj = fopen("plc.bin", "wb");
        generate_obj_file(obj, &case_map[casename]);
        fclose(obj);
    }
    return 0;
}

