#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/* PLC Task Segment */
typedef uint8_t task_count_t;
typedef uint8_t task_name_size_t;
typedef char * task_name_t;
typedef uint8_t task_priority_t;
typedef uint32_t task_interval_t;


#define TASK_PRIORITY_SIZE 1
typedef uint8_t task_priority_t;

#define TASK_INTERVAL_SIZE 4
typedef uint32_t task_interval_t;


#endif
