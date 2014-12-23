#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <stdarg.h>

#define LEVEL_OFF 0
#define LEVEL_ERR 1
#define LEVEL_WRN 2
#define LEVEL_INF 3
#define LEVEL_DBG 4
#define LEVEL_ALL 5

#define LOGGER_LEVEL LEVEL_ALL
/*-----------------------------------------------------------------------------
 * Assert Macro (for debug version)
 *---------------------------------------------------------------------------*/
#if LOGGER_LEVEL < LEVEL_DBG
    #define NDEBUG
#endif
#include <assert.h>
/*-----------------------------------------------------------------------------
 * Debug Macro (for debug version)
 *---------------------------------------------------------------------------*/
#define DFLAG_SHORT 1
#define DFLAG_LONG  2
#if LEVEL_DBG <= LOGGER_LEVEL
    #define LOGGER_DBG(flag, msg, ...)                                                \
    do {                                                                              \
        if (flag == DFLAG_LONG)                                                       \
            fprintf(stderr, "TRACE: " __FILE__ ":%d %s()\n", __LINE__, __FUNCTION__); \
        fprintf(stderr, msg, __VA_ARGS__);                                            \
        fprintf(stderr, "\n");                                                        \
    } while(0)
#else
    #define LOGGER_DBG(flag, msg, ...)
#endif
/*-----------------------------------------------------------------------------
 * Error Check Macro (for released version)
 *---------------------------------------------------------------------------*/
#if LEVEL_ERR <= LOGGER_LEVEL
    #define LOGGER_ERR(code, ...)                 \
    do {                                          \
        fprintf(stderr, "Error Code %d: ", code); \
        fprintf(stderr, err_msg[code]);            \
        fprintf(stderr, __VA_ARGS__);             \
        fprintf(stderr, "...\n");                 \
    } while(0)
#else
    #define LOGGER_ERR(code, ...)
#endif
/*-----------------------------------------------------------------------------
 * Tips Information Macro (for released version)
 *---------------------------------------------------------------------------*/
#if LEVEL_INF <= LOGGER_LEVEL
    #define LOGGER_INF(msg, ...)           \
    do {                                   \
        fprintf(stderr, msg, __VA_ARGS__); \
        fprintf(stderr, "\n");             \
    } while(0)
#else
    #define LOGGER_INF(msg, ...)
#endif

/* order sensitive */
enum ErrorCode {
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
    EC_RDI_COUNT,
    EC_RDO_COUNT,
    EC_RAI_COUNT,
    EC_RAO_COUNT,
    EC_IO_INTERVAL,
    EC_IO_TASK_CREATE,
    EC_IO_TASK_START,
    EC_IO_TASK_DELETE,
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
    EC_SERVO_TASK_DELETE,
    EC_LOAD_SERVO_CONFIG,
    /* RC Task Error Code */
    EC_RC_TASK_CREATE,
    EC_RC_TASK_START,
    EC_RC_TASK_DELETE,
    /* PLC Task Error Code */
    EC_TASK_COUNT,
    EC_TASK_PRIORITY,
    EC_TASK_TYPE,
    EC_TASK_SIGNAL,
    EC_TASK_INTERVAL,
    EC_LOAD_SP_SIZE,
    EC_TASK_POU_COUNT,
    EC_TASK_CONST_COUNT,
    EC_TASK_GLOBAL_COUNT,
    EC_LOAD_OPCODE,
    EC_LOAD_CS_CAP,
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
    EC_PLC_TASK_DELETE,
    /* String Pool Error Code */
    EC_SP_INIT,
    EC_SP_FULL,
    /* Calling Stack Error Code */
    EC_CS_INIT,
    EC_CS_FULL,
    EC_CS_EMPTY,
};

static const char err_msg[][80] = {
    /* Object File Header Error Code*/
    {"Incorrect format of PLC object file"},
    {"Mismatched system type"},
    {"Inverse byte order of PLC object file"},
    {"Incompatible system version"},
    {"Mismatched CPU"},
    /* System Memory Error Code*/
    {"Out of memory. "},
    {"Fail to bind to shared memory. "},
    /* System I/O Error Code */
    {"Over maximum count of local digital input module"},
    {"Over maximum count of local digital output module"},
    {"Over maximum count of local analog input module"},
    {"Over maximum count of local analog output module"},
    {"Over maximum count of remote digital input module"},
    {"Over maximum count of remote digital output module"},
    {"Over maximum count of remote analog input module"},
    {"Over maximum count of remote analog output module"},
    {"Below minimum i/o update interval"},
    {"Fail to create i/o task"},
    {"Fail to start i/o task"},
    {"Fail to delete i/o task"},
    {"Fail to load i/o configuration"},
    /* System Servo Error Code */
    {"Over maximum count of axis"},
    {"Exceptional parameter: combination of axis"},
    {"Out of range of axis' node id"},
    {"Unknown type of axis"},
    {"Unknown operation mode of axis"},
    {"Exceptional sw limit of axis"},
    {"Exceptional maximum velocity limit of axis"},
    {"Exceptional maximum accelaration limit of axis"},
    {"Exceptional maximum decelaration limit of axis"},
    {"Exceptional maximum jerk limit of axis"},
    {"Below minimum servo update interval"},
    {"Fail to create servo task"},
    {"Fail to start servo task"},
    {"Fail to delete servo task"},
    {"Fail to load servo configuration"},
    /* RC Task Error Code */
    {"Fail to create rc task"},
    {"Fail to start rc task"},
    {"Fail to delete rc task"},
    /* PLC Task Error Code */
    {"Over maximum count of plc task"},
    {"Out of range of plc task priority"},
    {"Unknown type of plc task"},
    {"Out of range of plc task signal source"},
    {"Below minimum interval of plc task"},
    {"Over maximum size of string pool"},
    {"Over maximum count of POU"},
    {"Over maximum count of constant"},
    {"Over maximum count of global variables"},
    {"Out of range of OpCode"},
    {"Over maximum count of stack frame"},
    {"Over maximum count of pou's parameters"},
    {"Unknown type of value"},
    {"Over maximum length of string"},
    {"Fail to load string"},
    {"Fail to load plc task descriptor"},
    {"Fail to load plc task pou descriptors"},
    {"Fail to load plc task constant"},
    {"Fail to load plc task global variables"},
    {"Fail to load plc task"},
    {"Fail to create plc task"},
    {"Fail to start plc task"},
    {"Fail to delete plc task"},
    /* String Pool Error Code */
    {"Fail to initialize stirng pool"},
    {"String pool is full, can't add new string"},
    /* Calling Stack Error Code */
    {"Fail to initialize calling stack"},
    {"Calling stack is full, can't push new frame"},
    {"Calling stack is empty, can't pop frame"},
};
#endif
