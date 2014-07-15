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
	EC_FILE = 1

};
typedef map<ERROR_CODE, const char *> ec_map_t;
static const ec_map_t::value_type ec_data[] = {
	ec_map_t::value_type(EC_FILE, "Incorrect format for PLC object file"),
};
static const uint32_t ec_count = sizeof ec_data / sizeof ec_data[0];
static const ec_map_t ec_map(ec_data, ec_data + ec_count);
#endif
