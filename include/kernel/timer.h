#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__
#include <stddef.h>
#include <list.h>
#include <compiler.h>

#define NO_TIMEOUT      0xFFFFFFFF

#define time_before(a,b) \
        (((long)(a) - (long)(b)) < 0)

#define time_after(a,b) \
        (((long)(a) - (long)(b)) > 0)

struct ktimer;
typedef void (*ktimer_callback)(struct ktimer *ktimer, void *arg);
struct ktimer {
        void *arg;
        ktimer_callback callback; /* called on timeout */
        unsigned long deadline;
        unsigned long period;
        struct list_head node;
};

void ktimer_init(void);
struct ktimer *ktimer_create(ktimer_callback cb, void *arg);
void ktimer_oneshot(struct ktimer *ktimer, const unsigned long timeout_ms);
void ktimer_periodic(struct ktimer *ktimer, const unsigned long period);
void ktimer_cancel(struct ktimer *ktimer);
void ktimer_delete(struct ktimer *ktimer);

enum kernel_tick_ret {
        kernel_tick_no_reschedule = 0,
        kernel_tick_reschedule,
};

typedef enum kernel_tick_ret (*kernel_tick_callback)(void *arg);

static inline __always_inline 
unsigned long kernel_ticks_now(void)
{
        extern unsigned long kernel_ticks;
        return kernel_ticks;
}

void delay(const unsigned long ms);

/* platforms should implement this */
unsigned long __system_clock_hz(void);

/* arm should implement this */
void __init_timer(kernel_tick_callback, void *arg, size_t interval);

#endif /* __INCLUDE_TIMER_H__ */

