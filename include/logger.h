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

#define LOGGER_DBG(msg, ...)                                                                             \
	do {                                                                                                 \
		if (LOGGER_LEVEL >= LEVEL_DBG) {                                                                 \
		    fprintf(stderr, "TRACE: File:%s Line:%d Function:%s()\n", __FILE__, __LINE__, __FUNCTION__); \
		    fprintf(stderr, msg, __VA_ARGS__);                                                           \
		    fprintf(stderr, "\n"); }                                                                     \
	} while(0)

#define LOGGER_ERR(code, ...)                                                                            \
	do {                                                                                                 \
		if (LOGGER_LEVEL >= LEVEL_ERR) {                                                                 \
			fprintf(stderr, "ERROR CODE %d: ", code);                                                    \
			fprintf(stderr, ec_msg[code]);                                                               \
			fprintf(stderr, __VA_ARGS__);                                                                \
		    fprintf(stderr, "...\n"); }                                                                  \
	} while(0)

#define LOGGER_INF(msg)                                                                                  \
	do {                                                                                                 \
		if (LOGGER_LEVEL >= LEVEL_INF) {                                                                 \
			fprintf(stderr, msg);                                                                        \
		    fprintf(stderr, "\n"); }                                                                     \
	} while(0)

enum ERROR_CODE {
    /* System Basic Error Code*/
	EC_PLC_FILE,
	EC_SYS_TYPE,
	EC_BYTE_ORDER,
	EC_SYS_VERSION,
	EC_SYS_MACHINE,
    /* System Memory Error Code*/
	EC_OOM,
    EC_BIND_SHM,
    /* System I/O Error Code */
	EC_IO_INTERVAL,
	EC_IO_TASK_CREATE,
	EC_IO_TASK_START,
	EC_LDI_COUNT,
	EC_LDO_COUNT,
	EC_LAI_COUNT,
	EC_LAO_COUNT,
    /* System Servo Error Code */
	EC_AXIS_COUNT,
	EC_AXIS_NAME_SIZE,
	EC_AXIS_ID_RANGE,
	EC_AXIS_TYPE,
	EC_AXIS_OPER_MODE,
	EC_SERVO_INTERVAL,
	EC_SERVO_TASK_CREATE,
	EC_SERVO_TASK_START,
    /* System RC Task Error Code */
	EC_RC_TASK_CREATE,
	EC_RC_TASK_START,
    /* System PLC Task Error Code */
	EC_TASK_NAME_SIZE,
	EC_TASK_PRIORITY,
	EC_TASK_INTERVAL,
	EC_TASK_DATA_SIZE,
    EC_ARG_VA_INVALID,
    EC_LOAD_TASK_INST,
    EC_LOAD_TASK_DATA,
    EC_LOAD_TASK_CODE,
};

typedef map<ERROR_CODE, const char *> ec_map_t;
static const ec_map_t::value_type ec_data[] = {
    /* System Basic Error Code*/
	ec_map_t::value_type(EC_PLC_FILE, "Incorrect format of PLC object file"),
	ec_map_t::value_type(EC_SYS_TYPE, "Mismatched system type"),
	ec_map_t::value_type(EC_BYTE_ORDER, "Inverse byte order of PLC object file"),
	ec_map_t::value_type(EC_SYS_VERSION, "Incompatible system version"),
	ec_map_t::value_type(EC_SYS_MACHINE, "Mismatched CPU"),
    /* System Memory Error Code*/
	ec_map_t::value_type(EC_OOM, "Out of memory. "),
	ec_map_t::value_type(EC_BIND_SHM, "Failed to bind to shared memory. "),
    /* System I/O Error Code */
	ec_map_t::value_type(EC_IO_INTERVAL, "Below minimum i/o update interval"),
	ec_map_t::value_type(EC_IO_TASK_CREATE, "Failed to create i/o task"),
	ec_map_t::value_type(EC_IO_TASK_START, "Failed to start i/o task"),
	ec_map_t::value_type(EC_LDI_COUNT, "Over maximum count of local digital input module"),
	ec_map_t::value_type(EC_LDO_COUNT, "Over maximum count of local digital output module"),
	ec_map_t::value_type(EC_LAI_COUNT, "Over maximum count of local analog input module"),
	ec_map_t::value_type(EC_LAO_COUNT, "Over maximum count of local analog output module"),
    /* System Servo Error Code */
	ec_map_t::value_type(EC_AXIS_COUNT, "Over maximum count of axis"),
	ec_map_t::value_type(EC_AXIS_NAME_SIZE, "Over maximum size of axis name"),
	ec_map_t::value_type(EC_AXIS_ID_RANGE, "Out of range of axis' node id"),
	ec_map_t::value_type(EC_AXIS_TYPE, "Unknown type of axis"),
	ec_map_t::value_type(EC_AXIS_OPER_MODE, "Unknown operation mode of axis"),
	ec_map_t::value_type(EC_SERVO_INTERVAL, "Below minimum servo update interval"),
	ec_map_t::value_type(EC_SERVO_TASK_CREATE, "Failed to create servo task"),
	ec_map_t::value_type(EC_SERVO_TASK_START, "Failed to start servo task"),
    /* System RC Task Error Code */
	ec_map_t::value_type(EC_RC_TASK_CREATE, "Failed to create rc task"),
	ec_map_t::value_type(EC_RC_TASK_START, "Failed to start rc task"),
    /* System PLC Task Error Code */
	ec_map_t::value_type(EC_TASK_NAME_SIZE, "Over maximum size of plc task name"),
	ec_map_t::value_type(EC_TASK_PRIORITY, "Out of range of plc task priority"),
	ec_map_t::value_type(EC_TASK_INTERVAL, "Below minimum interval of plc task"),
	ec_map_t::value_type(EC_TASK_DATA_SIZE, "Over maximum size of plc task data segment"),
	ec_map_t::value_type(EC_ARG_VA_INVALID, "Invalid virtual address of instruction argument"),
	ec_map_t::value_type(EC_LOAD_TASK_INST, "Failed to load plc task instruction"),
	ec_map_t::value_type(EC_LOAD_TASK_DATA, "Failed to load plc task data"),
	ec_map_t::value_type(EC_LOAD_TASK_CODE, "Failed to load plc task code"),
};
static const uint32_t ec_count = sizeof ec_data / sizeof ec_data[0];
static const ec_map_t ec_map(ec_data, ec_data + ec_count);
#endif
