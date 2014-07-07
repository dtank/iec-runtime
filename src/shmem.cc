#include <native/heap.h>
#include "shmem.h"
#include "debug.h"

RT_HEAP heap_desc;
void shm_alloc(void *addr, uint32_t size) {
	if (rt_heap_bind(&heap_desc, "test_heap", TM_NONBLOCK)) {
		PRINT(DEBUG_ERR, "ERROR: binding heap...", 0);
	}
	rt_heap_alloc(&heap_desc, size, TM_NONBLOCK, &addr);
}
