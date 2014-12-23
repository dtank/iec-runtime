#include <native/task.h>
#include <native/heap.h>
#include "io.h"
#include "logger.h"

static RT_TASK io_task;
/* RT_HEAP MUST be separated */
RT_HEAP diu_heap;
RT_HEAP dou_heap;
RT_HEAP aiu_heap;
RT_HEAP aou_heap;
IOMem g_ioshm;
extern ec_map_t ec_msg;

#define LDI_COUNT (config->ldi_count)
#define LDO_COUNT (config->ldo_count)
#define LAI_COUNT (config->lai_count)
#define LAO_COUNT (config->lao_count)
#define RDI_COUNT (config->rdi_count)
#define RDO_COUNT (config->rdo_count)
#define RAI_COUNT (config->rai_count)
#define RAO_COUNT (config->rao_count)

#define LDI_SIZE (LDI_COUNT * DU_SIZE)
#define LDO_SIZE (LDO_COUNT * DU_SIZE)
#define LAI_SIZE (LAI_COUNT * AU_SIZE)
#define LAO_SIZE (LAO_COUNT * AU_SIZE)
#define RDI_SIZE (RDI_COUNT * DU_SIZE)
#define RDO_SIZE (RDO_COUNT * DU_SIZE)
#define RAI_SIZE (RAI_COUNT * AU_SIZE)
#define RAO_SIZE (RAO_COUNT * AU_SIZE)

#define LDI_BASE 0
#define RDI_BASE (LDI_BASE+LDI_COUNT*DU_SIZE)
#define LDO_BASE 0
#define RDO_BASE (LDO_BASE+LDO_COUNT*DU_SIZE)
#define LAI_BASE 0
#define RAI_BASE (LAI_BASE+LAI_COUNT*AU_CHANNELS)
#define LAO_BASE 0
#define RAO_BASE (LAO_BASE+LAO_COUNT*AU_CHANNELS)

#define DIU_COUNT (LDI_COUNT + RDI_COUNT)
#define DOU_COUNT (LDO_COUNT + RDO_COUNT)
#define AIU_COUNT (LAI_COUNT + RAI_COUNT)
#define AOU_COUNT (LAO_COUNT + RAO_COUNT)

#define DIU_SIZE (DIU_COUNT * DU_SIZE)
#define DOU_SIZE (DOU_COUNT * DU_SIZE)
#define AIU_SIZE (AIU_COUNT * AU_SIZE)
#define AOU_SIZE (AOU_COUNT * AU_SIZE)

#define IO_SHM_SIZE (DIU_SIZE + DOU_SIZE + AIU_SIZE + AOU_SIZE)


void iomem_init(IOMem *iomem, IOConfig *config) {
    assert(iomem != NULL);
    assert(config != NULL);

    iomem->diu_size = DIU_SIZE;
    iomem->dou_size = DOU_SIZE;
    iomem->aiu_size = AIU_SIZE;
    iomem->aou_size = AOU_SIZE;
    iomem->diu = new uint8_t[DIU_SIZE];
    iomem->dou = new uint8_t[DOU_SIZE];
    iomem->aiu = new uint32_t[AIU_SIZE];
    iomem->aou = new uint32_t[AOU_SIZE];
    //TODO error check
}

static inline void ldi_update(IOConfig *config) {
    dump_mem("LDI", &g_ioshm.diu[LDI_BASE], LDI_SIZE);
}
static inline void ldo_update(IOConfig *config) {
    dump_mem("LDO", &g_ioshm.dou[LDO_BASE], LDO_SIZE);
}
static inline void lai_update(IOConfig *config) {
    dump_mem("LAI", &g_ioshm.aiu[LAI_BASE], LAI_SIZE);
}
static inline void lao_update(IOConfig *config) {
    dump_mem("LAO", &g_ioshm.aou[LAO_BASE], LAO_SIZE);
}
static inline void rdi_update(IOConfig *config) {
    dump_mem("RDI", &g_ioshm.diu[RDI_BASE], RDI_SIZE);
}
static inline void rdo_update(IOConfig *config) {
    dump_mem("RDO", &g_ioshm.dou[RDO_BASE], RDO_SIZE);
}
static inline void rai_update(IOConfig *config) {
    dump_mem("RAI", &g_ioshm.aiu[RAI_BASE], RAI_SIZE);
}
static inline void rao_update(IOConfig *config) {
    dump_mem("RAO", &g_ioshm.aou[RAO_BASE], RAO_SIZE);
}
static void io_update(void *io_config) {
    IOConfig *config = (IOConfig *)io_config;
	rt_task_set_periodic(NULL, TM_NOW, config->update_interval);
	while (1) {
		rt_task_wait_period(NULL);
        if (config->ldi_count != 0 ) ldi_update(config);
        if (config->ldo_count != 0 ) ldo_update(config);
        if (config->lai_count != 0 ) lai_update(config);
        if (config->lao_count != 0 ) lao_update(config);
        if (config->rdi_count != 0 ) rdi_update(config);
        if (config->rdo_count != 0 ) rdo_update(config);
        if (config->rai_count != 0 ) rai_update(config);
        if (config->rao_count != 0 ) rao_update(config);
	}
}

static void io_task_create() {
	if (rt_task_create(&io_task, IO_TASK_NAME, 0, IO_TASK_PRIORITY, 0)) {
        LOGGER_ERR(EC_IO_TASK_CREATE, "");
	}
}

void io_task_init(IOConfig *config) {
    g_ioshm.diu_size = DIU_SIZE;
    g_ioshm.dou_size = DOU_SIZE;
    g_ioshm.aiu_size = AIU_SIZE;
    g_ioshm.aou_size = AOU_SIZE;
    rt_heap_create(&diu_heap, "diu_shm", DIU_SIZE, H_SHARED);
    rt_heap_create(&dou_heap, "dou_shm", DOU_SIZE, H_SHARED);
    rt_heap_create(&aiu_heap, "aiu_shm", AIU_SIZE, H_SHARED);
    rt_heap_create(&aou_heap, "aou_shm", AOU_SIZE, H_SHARED);
    rt_heap_alloc(&diu_heap, DIU_SIZE, TM_INFINITE, (void **)&g_ioshm.diu);
    rt_heap_alloc(&dou_heap, DOU_SIZE, TM_INFINITE, (void **)&g_ioshm.dou);
    rt_heap_alloc(&aiu_heap, AIU_SIZE, TM_INFINITE, (void **)&g_ioshm.aiu);
    rt_heap_alloc(&aou_heap, AOU_SIZE, TM_INFINITE, (void **)&g_ioshm.aou);
    /* clear up i/o shm*/
    memset(g_ioshm.diu, 0, DIU_SIZE);
    memset(g_ioshm.dou, 0, DOU_SIZE);
    memset(g_ioshm.aiu, 0, AIU_SIZE);
    memset(g_ioshm.aou, 0, AOU_SIZE);


    LOGGER_DBG(DFLAG_LONG, "I/O SHM:\n .total_size = %d\n .diu_size = %d\n .dou_size = %d\n .aiu_size = %d\n .aou_size = %d",
        IO_SHM_SIZE, DIU_SIZE, DOU_SIZE, AIU_SIZE, AOU_SIZE);
    io_task_create();
}
void io_task_start(IOConfig *config) {
	if (rt_task_start(&io_task, &io_update, (void *)config)) {
        LOGGER_ERR(EC_IO_TASK_START, "");
	}
}

void io_task_delete() {
	if (rt_task_delete(&io_task)) {
	}
}
