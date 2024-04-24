#ifndef __ARMV7M_INCLUDE_ARM_OPS_H__
#define __ARMV7M_INCLUDE_ARM_OPS_H__

static inline 
unsigned long read_primask(void)
{
        unsigned long primask;
        __asm__ volatile("mrs   %0, primask": "=r" (primask) :: );
        return primask;
}

static inline 
void write_primask(const unsigned long primask)
{
        __asm__ volatile("nop");
        return;
}

#endif /* __ARMV7M_INCLUDE_ARM_OPS_H__ */

