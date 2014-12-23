#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdint.h>

/*-----------------------------------------------------------------------------
 * Helper Funtion Macros
 *---------------------------------------------------------------------------*/
/* creates a mask with `n' 1 bits at position `p' */
#define MASK1(p,n)	((~((~(uint32_t)0)<<(n)))<<(p))
/* creates a mask with `n' 0 bits at position `p' */
#define MASK0(p,n)	(~MASK1(p,n))
#define RES(num, shift) ((num) & MASK1(0,shift)) /* get residue */
#define cast(type, exp) ((type)(exp))

#endif
