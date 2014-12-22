#ifndef __IO_H__
#define __IO_H__

#include "plcmodel.h"

typedef struct {
    uint8_t *diu;  /* digital input unit base address */
    uint8_t *dou;  /* digital output unit base address */
    uint32_t *aiu; /* analog input unit base address */
    uint32_t *aou; /* analog output unit base address */
} IOMem;

#define AU_CHANNELS 8 /* channels per analog unit */
#define AU_CH_SIZE 4  /* bytes per channel (uint: Byte) */
#define AU_SIZE (AU_CHANNELS*AU_CH_SIZE) /* size of analog unit (uint: Byte) */
#define DU_SIZE 1 /* size of digital unit (uint: Byte) */

typedef uint32_t vint_t;

/*-----------------------------------------------------------------------------
 * Helper Funtion Macros
 *---------------------------------------------------------------------------*/
#define Mask1(n,p)	((~((~(vint_t)0)<<(n)))<<(p))
#define Mask0(n,p)	(~Mask1(n,p))
#define RES(num, shift) ((num) & Mask1(shift,0)) /* get residue */
/*-----------------------------------------------------------------------------
 * Digital I/O Unit Manapulation Macros
 *---------------------------------------------------------------------------*/
#define SHIFT 3 /* 8 = 2^3 */
#define BASE(unit, pos) (*(vint_t*)&(unit[(pos)>>SHIFT]))
#define getdch(diu, pos, size) ((BASE(diu,pos) >> RES(pos,SHIFT)) & Mask1(size,0))
#define setdch(dou, pos, size, value) /* value comes from getbits() */ \
    {BASE(dou,pos) = BASE(dou,pos) & Mask0(size, RES(pos,SHIFT)) | (value<<RES(pos, SHIFT));}
/*-----------------------------------------------------------------------------
 * Analog I/O Unit Manapulation Macros
 *---------------------------------------------------------------------------*/
#define getach(aiu, iuint, ich) aiu[iuint*AU_CHANNELS+ich]
#define setach(aou, iuint, ich, value) {aou[iuint*AU_CHANNELS+ich] = value;}

#if LEVEL_DBG <= LOGGER_LEVEL
    #define dump_mem(name, base, size) {                     \
        fprintf(stderr, name ":");                           \
        for (int i = 0; i < (size); i++) {                   \
            if (i % 16 == 0) {                               \
                fprintf(stderr, "\n");                       \
            }                                                \
            fprintf(stderr, "%02x ", ((uint8_t*)(base))[i]); \
        }                                                    \
        fprintf(stderr, "\n");                               \
    }
#else
    #define dum_mem(name, base, size)
#endif

#define IO_TASK_NAME "io_task"
#define IO_TASK_PRIORITY 99

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
