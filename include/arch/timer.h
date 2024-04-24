#ifndef __INCLUDE_ARCH_TIMER_H__
#define __INCLUDE_ARCH_TIMER_H__

unsigned long arch_get_tick(void);

typedef void (*system_tick_fn)(void *arg);

/* the kernel calls this to initialize and register the system tick 
 * on the underlying ARM architecture.
 */
void arch_init_timer(system_tick_fn systick_fn, void *systick_arg, 
                     const unsigned long hz);

#endif /* __INCLUDE_ARCH_TIMER_H__ */

