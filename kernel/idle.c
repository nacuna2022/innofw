#include <kernel/sched.h>
#include <arch/idle.h>

void __no_return kernel_idle(void) 
{
        for (;;) {
                
                arch_idle();
        }
}

