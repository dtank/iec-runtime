#ifndef __IO_H__
#define __IO_H__

#include <string.h>
#include "plcmodel.h"
#include "helper.h"

typedef struct {
    uint32_t diu_size;
    uint32_t dou_size;
    uint32_t aiu_size;
    uint32_t aou_size;
    uint8_t *diu;  /* digital input unit base address */
    uint8_t *dou;  /* digital output unit base address */
    uint32_t *aiu; /* analog input unit base address */
    uint32_t *aou; /* analog output unit base address */
} IOMem;

#define AU_CHANNELS 8 /* channels per analog unit */
#define AU_CH_SIZE 4  /* bytes per channel (uint: Byte) */
#define AU_SIZE (AU_CHANNELS*AU_CH_SIZE) /* size of analog unit (uint: Byte) */
#define DU_SIZE 1 /* size of digital unit (uint: Byte) */


/*-----------------------------------------------------------------------------
 * Digital I/O Unit Manapulation Macros
 *---------------------------------------------------------------------------*/
#define SHIFT 3 /* 8 = 2^3 */
#define BASE(unit, pos) (*(uint32_t*)&(unit)[(pos)>>SHIFT]) /* MUST dereference first, then cast type!! */
#define getdch(diu, pos, size) ((BASE(diu,pos) >> RES(pos,SHIFT)) & MASK1(0,size))
#define setdch(dou, pos, size, value) {                                                       \
    BASE(dou,pos) = BASE(dou,pos) & MASK0(RES(pos,SHIFT), size) | ((value)<<RES(pos, SHIFT)); \
}
/*-----------------------------------------------------------------------------
 * Analog I/O Unit Manapulation Macros
 *---------------------------------------------------------------------------*/
#define getach(aiu, iuint, ich) aiu[iuint*AU_CHANNELS+ich]
#define setach(aou, iuint, ich, value) {aou[iuint*AU_CHANNELS+ich] = value;}

#define io_memcpy(mem1, mem2) {                \
    memcpy(mem1.diu, mem2.diu, mem2.diu_size); \
    memcpy(mem1.dou, mem2.dou, mem2.dou_size); \
    memcpy(mem1.aiu, mem2.aiu, mem2.aiu_size); \
    memcpy(mem1.aou, mem2.aou, mem2.aou_size); \
}
#if LEVEL_DBG <= LOGGER_LEVEL
    #define dump_mem(name, base, size) {                     \
        fprintf(stderr, name "(low -> high):");              \
        for (int i = 0; i < (size); i++) {                   \
            if (i % 16 == 0)                                 \
                fprintf(stderr, "\n");                       \
            fprintf(stderr, "%02x ", ((uint8_t*)(base))[i]); \
        }                                                    \
        fprintf(stderr, "\n");                               \
    }
#else
    #define dum_mem(name, base, size)
#endif

#define IO_TASK_NAME "io_task"
#define IO_TASK_PRIORITY 99

void iomem_init(IOMem *iomem, IOConfig *config);
static inline void ldi_update(IOConfig *config);
static inline void ldo_update(IOConfig *config);
static inline void lai_update(IOConfig *config);
static inline void lao_update(IOConfig *config);
static inline void rdi_update(IOConfig *config);
static inline void rdo_update(IOConfig *config);
static inline void rai_update(IOConfig *config);
static inline void rao_update(IOConfig *config);
static void io_update(void *config);
static void io_task_create();
void io_task_init(IOConfig *config);
void io_task_start(IOConfig *config);
void io_task_delete();
#endif
