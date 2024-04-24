#include <config.h>
#include <compiler.h>
#include <types.h>

extern void * __SP_main[];
extern void *__arm_reset[];
void __systick(void);
void __pendsv(void);
void arm_exception_entry(void);

const void * __vectors[] __section(".vector") __used = {
        __SP_main,              /* SP_main */
        __arm_reset,            /* reset */
        0,    /* nmi */
        0,    /* hard fault */
        0,    /* mem manage */
        0,    /* bus fault */
        0,    /* usage fault */
        0,    /* reserved */
        0,    /* reserved */
        0,    /* reserved */
        0,    /* reserved */
        0,    /* svcall */
        0,    /* debug monitor */
        0,    /* reserved */
        __pendsv,     /* pendsv */
        __systick,    /* systick */

        [16 ... (CONFIG_MCU_INTERRUPT_COUNT-1)] = arm_exception_entry,
};

