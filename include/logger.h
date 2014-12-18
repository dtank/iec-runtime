#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <map>
#include <stdio.h>
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

#define LOGGER_INF(msg, ...)                                                                             \
    do {                                                                                                 \
        if (LOGGER_LEVEL >= LEVEL_INF) {                                                                 \
            fprintf(stderr, msg, __VA_ARGS__);                                                           \
            fprintf(stderr, "\n"); }                                                                     \
    } while(0)

enum ERROR_CODE {
    /* Basic Error Code*/
    EC_PLC_FILE,
    EC_SYS_TYPE,
    EC_BYTE_ORDER,
    EC_SYS_VERSION,
    EC_SYS_MACHINE,
    /* Memory Error Code*/
    EC_OOM,
    EC_BIND_SHM,
    /* I/O Error Code */
    EC_LDI_COUNT,
    EC_LDO_COUNT,
    EC_LAI_COUNT,
    EC_LAO_COUNT,
    EC_IO_INTERVAL,
    EC_IO_TASK_CREATE,
    EC_IO_TASK_START,
    EC_LOAD_IO_CONFIG,
    /* Servo Error Code */
    EC_AXIS_COUNT,
    EC_AXIS_COMBINE,
    EC_AXIS_ID_RANGE,
    EC_AXIS_TYPE,
    EC_AXIS_OPER_MODE,
    EC_AXIS_SW,
    EC_AXIS_MAX_VEL,
    EC_AXIS_MAX_ACC,
    EC_AXIS_MAX_DEC,
    EC_AXIS_MAX_JERK,
    EC_SERVO_INTERVAL,
    EC_SERVO_TASK_CREATE,
    EC_SERVO_TASK_START,
    EC_LOAD_SERVO_CONFIG,
    /* RC Task Error Code */
    EC_RC_TASK_CREATE,
    EC_RC_TASK_START,
    /* PLC Task Error Code */
    EC_TASK_COUNT,
    EC_LOAD_SP_SIZE,
    EC_TASK_PRIORITY,
    EC_TASK_TYPE,
    EC_TASK_SIGNAL,
    EC_TASK_INTERVAL,
    EC_TASK_POU_COUNT,
    EC_TASK_CONST_COUNT,
    EC_TASK_GLOBAL_COUNT,
    EC_TASK_SFRAME_COUNT,
    EC_POU_PARAM_COUNT,
    EC_LOAD_VTYPE,
    EC_LOAD_STRLEN,
    EC_LOAD_STRING,
    EC_LOAD_TASK_DESC,
    EC_LOAD_POU_DESC,
    EC_LOAD_TASK_CONST,
    EC_LOAD_TASK_GLOBAL,
    EC_LOAD_PLC_TASK,
    EC_PLC_TASK_CREATE,
    EC_PLC_TASK_START,
    /* String Pool Error Code */
    EC_SP_SIZE,
    EC_SP_NEW,
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
    ec_map_t::value_type(EC_LDI_COUNT, "Over maximum count of local digital input module"),
    ec_map_t::value_type(EC_LDO_COUNT, "Over maximum count of local digital output module"),
    ec_map_t::value_type(EC_LAI_COUNT, "Over maximum count of local analog input module"),
    ec_map_t::value_type(EC_LAO_COUNT, "Over maximum count of local analog output module"),
    ec_map_t::value_type(EC_IO_INTERVAL, "Below minimum i/o update interval"),
    ec_map_t::value_type(EC_IO_TASK_CREATE, "Failed to create i/o task"),
    ec_map_t::value_type(EC_IO_TASK_START, "Failed to start i/o task"),
    ec_map_t::value_type(EC_LOAD_IO_CONFIG, "Failed to load i/o configuration"),
    /* System Servo Error Code */
    ec_map_t::value_type(EC_AXIS_COUNT, "Over maximum count of axis"),
    ec_map_t::value_type(EC_AXIS_COMBINE, "Exceptional parameter: combination of axis"),
    ec_map_t::value_type(EC_AXIS_ID_RANGE, "Out of range of axis' node id"),
    ec_map_t::value_type(EC_AXIS_TYPE, "Unknown type of axis"),
    ec_map_t::value_type(EC_AXIS_OPER_MODE, "Unknown operation mode of axis"),
    ec_map_t::value_type(EC_AXIS_SW, "Exceptional sw limit of axis"),
    ec_map_t::value_type(EC_AXIS_MAX_VEL, "Exceptional maximum velocity limit of axis"),
    ec_map_t::value_type(EC_AXIS_MAX_ACC, "Exceptional maximum accelaration limit of axis"),
    ec_map_t::value_type(EC_AXIS_MAX_DEC, "Exceptional maximum decelaration limit of axis"),
    ec_map_t::value_type(EC_AXIS_MAX_JERK, "Exceptional maximum jerk limit of axis"),
    ec_map_t::value_type(EC_SERVO_INTERVAL, "Below minimum servo update interval"),
    ec_map_t::value_type(EC_SERVO_TASK_CREATE, "Failed to create servo task"),
    ec_map_t::value_type(EC_SERVO_TASK_START, "Failed to start servo task"),
    ec_map_t::value_type(EC_LOAD_SERVO_CONFIG, "Failed to load servo configuration"),
    /* System RC Task Error Code */
    ec_map_t::value_type(EC_RC_TASK_CREATE, "Failed to create rc task"),
    ec_map_t::value_type(EC_RC_TASK_START, "Failed to start rc task"),
    /* System PLC Task Error Code */
    ec_map_t::value_type(EC_TASK_COUNT, "Over maximum count of plc task"),
    ec_map_t::value_type(EC_LOAD_SP_SIZE, "Over maximum size of string pool"),
    ec_map_t::value_type(EC_TASK_PRIORITY, "Out of range of plc task priority"),
    ec_map_t::value_type(EC_TASK_TYPE, "Unknown type of plc task"),
    ec_map_t::value_type(EC_TASK_SIGNAL, "Out of range of plc task signal source"),
    ec_map_t::value_type(EC_TASK_INTERVAL, "Below minimum interval of plc task"),
    ec_map_t::value_type(EC_TASK_POU_COUNT, "Over maximum count of POU"),
    ec_map_t::value_type(EC_TASK_CONST_COUNT, "Over maximum count of constant"),
    ec_map_t::value_type(EC_TASK_GLOBAL_COUNT, "Over maximum count of global variables"),
    ec_map_t::value_type(EC_TASK_SFRAME_COUNT, "Over maximum count of stack frame"),
    ec_map_t::value_type(EC_POU_PARAM_COUNT, "Over maximum count of pou's parameters"),
    ec_map_t::value_type(EC_LOAD_VTYPE, "Unknown type of value"),
    ec_map_t::value_type(EC_LOAD_STRLEN, "Over maximum length of string"),
    ec_map_t::value_type(EC_LOAD_STRING, "Failed to load string"),
    ec_map_t::value_type(EC_LOAD_TASK_DESC, "Failed to load plc task descriptor"),
    ec_map_t::value_type(EC_LOAD_POU_DESC, "Failed to load plc task pou descriptors"),
    ec_map_t::value_type(EC_LOAD_TASK_CONST, "Failed to load plc task constant"),
    ec_map_t::value_type(EC_LOAD_TASK_GLOBAL, "Failed to load plc task global variables"),
    ec_map_t::value_type(EC_LOAD_PLC_TASK, "Failed to load plc task"),
    ec_map_t::value_type(EC_PLC_TASK_CREATE, "Failed to create plc task"),
    ec_map_t::value_type(EC_PLC_TASK_START, "Failed to start plc task"),
    /* String Pool Error Code */
    ec_map_t::value_type(EC_SP_SIZE, "Over maximum capacity of string pool"),
    ec_map_t::value_type(EC_SP_NEW, "No enough free space for new string"),
};
static const uint32_t ec_count = sizeof ec_data / sizeof ec_data[0];
static const ec_map_t ec_map(ec_data, ec_data + ec_count);
#endif
