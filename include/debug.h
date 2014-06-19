#ifndef __DEBUG_H_
#define __DEBUG_H_

#define DEBUG_IN  0x01
#define DEBUG_OUT 0x02
#define DEBUG_ERR 0x04
#define DEBUG_ALL 0xFF

extern int DEBUG_FLAGS;
#define PRINT(flag, fmt, ...)                                                               \
		do {                                                                                \
			if (DEBUG_FLAGS & flag) {                                                       \
				printf("File:%s Line:%d Function:%s() ", __FILE__, __LINE__, __FUNCTION__); \
				printf(fmt, __VA_ARGS__); }                                                 \
		}while(0)
#endif
