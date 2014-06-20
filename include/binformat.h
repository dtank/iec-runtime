#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/* PLC Task Segment */
typedef uint8_t  task_count_t;
typedef uint8_t  task_name_size_t;
typedef char *   task_name_t;
typedef uint8_t  task_priority_t;
typedef uint32_t task_interval_t;

typedef struct {
	task_name_size_t name_size;
} task_property_seg_header;

typedef struct {
	task_name_t name;
	task_priority_t priority;
	task_interval_t interval;
} task_property_seg;




#endif
