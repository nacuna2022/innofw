#ifndef __INCLUDE_BUG_H__
#define __INCLUDE_BUG_H__
#include <stddef.h>

/* find a way to not define this here */ 
#define __BUG() __asm__ volatile("bkpt 255")

#define BUG()           \
        do {            \
                __BUG();\
        } while(0)

#define BUG_ON(x)              \
        do {                   \
                if (!!(x))     \
                        BUG(); \
        } while(0)

/* define our compile time assert to generate a compile error when a condition
 * is NOT true.
 *
 * we know true to be 1, and false to be !1 (or 0)
 * (1 * true)-1 = 0
 * (1 * false)-1 = -1
 */
#define CT_ASSERT(condition) \
        ((void)sizeof(char[1 * !!(condition) - 1]))

#endif /* __INCLUDE_BUG_H__ */

