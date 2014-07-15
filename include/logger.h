#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <map>

using namespace std;

#define LOGGER_OFF 0
#define LOGGER_ERR 1
#define LOGGER_WRN 2
#define LOGGER_INF 3
#define LOGGER_DBG 4
#define LOGGER_ALL 5

// TODO modify include for debug.h
extern int LOGGER_LEVEL;
#define LOGGER(level, ...)                                                                                       \
		do {                                                                                                     \
			if (LOGGER_LEVEL >= level) {                                                                         \
				if (level == LOGGER_DBG) {                                                                       \
				    fprintf(stderr, "TRACE: File:%s Line:%d Function:%s()\n", __FILE__, __LINE__, __FUNCTION__); \
				    fprintf(stderr, __VA_ARGS__);                                                                \
				    fprintf(stderr, "\n"); }                                                                     \
				if (level == LOGGER_ERR) {                                                                       \
				    fprintf(stderr, "ERROR: %s...(Error Code:%d)\n", __VA_ARGS__); }                             \
			}                                                                                                    \
		} while(0)


enum ERROR_CODE {
	EC_PLC_FILE,
	EC_SYS_TYPE,
	EC_BYTE_ORDER,
	EC_SYS_VERSION,
	EC_SYS_MACHINE,
	EC_OBJ_HEADER,
	EC_IO_INTERVAL,
	EC_LDI_COUNT,
	EC_LDO_COUNT,
	EC_LAI_COUNT,
	EC_LAO_COUNT,
	EC_SYS_IOC,
};
typedef map<ERROR_CODE, const char *> ec_map_t;
static const ec_map_t::value_type ec_data[] = {
	ec_map_t::value_type(EC_PLC_FILE, "Incorrect format of PLC object file"),
	ec_map_t::value_type(EC_SYS_TYPE, "Mismatched system type"),
	ec_map_t::value_type(EC_BYTE_ORDER, "Inverse byte order of PLC object file"),
	ec_map_t::value_type(EC_SYS_VERSION, "Incompatible system version"),
	ec_map_t::value_type(EC_SYS_MACHINE, "Mismatched CPU"),
	ec_map_t::value_type(EC_OBJ_HEADER, "Full memory, can't load PLC object file header"),
	ec_map_t::value_type(EC_IO_INTERVAL, "Below minimum i/o update interval"),
	ec_map_t::value_type(EC_LDI_COUNT, "Over maximum count of local digital input module"),
	ec_map_t::value_type(EC_LDO_COUNT, "Over maximum count of local digital output module"),
	ec_map_t::value_type(EC_LAI_COUNT, "Over maximum count of local analog input module"),
	ec_map_t::value_type(EC_LAO_COUNT, "Over maximum count of local analog output module"),
	ec_map_t::value_type(EC_SYS_IOC, "Full memory, can't load I/O configuration"),
};
static const uint32_t ec_count = sizeof ec_data / sizeof ec_data[0];
static const ec_map_t ec_map(ec_data, ec_data + ec_count);
#endif
