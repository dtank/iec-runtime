#ifndef __DEBUG_H_
#define __DEBUG_H_

#define DEBUG_OFF 0
#define DEBUG_ERR 1
#define DEBUG_WRN 2
#define DEBUG_TRC 3
#define DEBUG_INF 4

extern int DEBUG_LEVEL;
#define PRINT(level, fmt, ...)                                                                       \
		do {                                                                                         \
			if (DEBUG_LEVEL >= level) {                                                              \
				fprintf(stderr, "File:%s Line:%d Function:%s() ", __FILE__, __LINE__, __FUNCTION__); \
				fprintf(stderr, fmt, __VA_ARGS__); }                                                 \
				fprintf(stderr, "\n");                                                               \
		}while(0)
#endif
