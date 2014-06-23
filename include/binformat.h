#ifndef __BIN_FORMAT_H__
#define __BIN_FORMAT_H__

#include <stdint.h>

/* PLC Task Segment */
typedef uint64_t offset_t;
typedef uint8_t  task_count_t;
typedef uint8_t  task_name_size_t;
typedef char     task_name_t;
typedef uint8_t  task_priority_t;
typedef uint32_t task_interval_t;
typedef uint64_t seg_size_t;

/* Task Property Segment Header */
typedef struct {
	task_name_size_t name_size;
} TASK_PROPERTY_SEG_HEADER;

/* Task Property Segment */
typedef struct {
	task_name_t *name;
	task_priority_t priority;
	task_interval_t interval;
} TASK_PROPERTY_SEG;

/* Data Segment Header */
typedef struct {
	seg_size_t size;
} DATA_SEG_HEADER;

/* Data Segment */
typedef char DATA_SEG;



#endif
