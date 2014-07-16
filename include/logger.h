#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <map>
#include <stdarg.h>

using namespace std;

#define LEVEL_OFF 0
#define LEVEL_ERR 1
#define LEVEL_WRN 2
#define LEVEL_INF 3
#define LEVEL_DBG 4
#define LEVEL_ALL 5

extern int LOGGER_LEVEL;

#define LOGGER_DBG(msg, ...)                                                                                       \
	do {                                                                                                     \
		if (LOGGER_LEVEL >= LEVEL_DBG) {                                                                       \
		    fprintf(stderr, "TRACE: File:%s Line:%d Function:%s()\n", __FILE__, __LINE__, __FUNCTION__); \
		    fprintf(stderr, msg, __VA_ARGS__);                                                                \
		    fprintf(stderr, "\n"); }                                                                     \
	} while(0)

#define LOGGER_ERR(code, ...)                                                                                       \
	do {                                                                                                     \
		if (LOGGER_LEVEL >= LEVEL_ERR) {                                                                       \
			fprintf(stderr, "ERROR CODE %d: ", code);                              \
			fprintf(stderr, ec_msg[code]);                              \
			fprintf(stderr, __VA_ARGS__);                               \
		    fprintf(stderr, "...\n"); }                                                                     \
	} while(0)

enum ERROR_CODE {
	EC_PLC_FILE,
	EC_SYS_TYPE,
	EC_BYTE_ORDER,
	EC_SYS_VERSION,
	EC_SYS_MACHINE,
	EC_FULL_MEM,
	EC_IO_INTERVAL,
	EC_LDI_COUNT,
	EC_LDO_COUNT,
	EC_LAI_COUNT,
	EC_LAO_COUNT,
	EC_AXIS_NAME_SIZE,
	EC_AXIS_ID_RANGE,
	EC_AXIS_TYPE,
	EC_AXIS_OPER_MODE,
};

typedef map<ERROR_CODE, const char *> ec_map_t;
static const ec_map_t::value_type ec_data[] = {
	ec_map_t::value_type(EC_PLC_FILE, "Incorrect format of PLC object file"),
	ec_map_t::value_type(EC_SYS_TYPE, "Mismatched system type"),
	ec_map_t::value_type(EC_BYTE_ORDER, "Inverse byte order of PLC object file"),
	ec_map_t::value_type(EC_SYS_VERSION, "Incompatible system version"),
	ec_map_t::value_type(EC_SYS_MACHINE, "Mismatched CPU"),
	ec_map_t::value_type(EC_FULL_MEM, "Full memory. "),
	ec_map_t::value_type(EC_IO_INTERVAL, "Below minimum i/o update interval"),
	ec_map_t::value_type(EC_LDI_COUNT, "Over maximum count of local digital input module"),
	ec_map_t::value_type(EC_LDO_COUNT, "Over maximum count of local digital output module"),
	ec_map_t::value_type(EC_LAI_COUNT, "Over maximum count of local analog input module"),
	ec_map_t::value_type(EC_LAO_COUNT, "Over maximum count of local analog output module"),
	ec_map_t::value_type(EC_AXIS_NAME_SIZE, "Over maximum size of axis name"),
	ec_map_t::value_type(EC_AXIS_ID_RANGE, "Out of range for axis' node id"),
	ec_map_t::value_type(EC_AXIS_TYPE, "Unknown type of axis"),
	ec_map_t::value_type(EC_AXIS_OPER_MODE, "Unknown operation mode of axis"),

};
static const uint32_t ec_count = sizeof ec_data / sizeof ec_data[0];
static const ec_map_t ec_map(ec_data, ec_data + ec_count);
#endif
