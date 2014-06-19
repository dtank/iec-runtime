#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/* PLC Task Segment */
#define TASK_NUM_SIZE 1
typedef uint8_t task_num_t;

typedef char *task_name_t;

#define TASK_PRIORITY_SIZE 1
typedef uint8_t task_priority_t;

#define TASK_INTERVAL_SIZE 4
typedef uint32_t task_interval_t;


#endif
