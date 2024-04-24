#include <config.h>
#include <kernel/timer.h>
#include <kernel/sched.h>
#include <kernel/irq.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <arch/timer.h>

static struct list_head ktimer_list;

struct ktimer *ktimer_create(ktimer_callback cb, void *arg)
{
        struct ktimer *ktimer;
        if ((ktimer = malloc(sizeof *ktimer)) != NULL) {
                memset(ktimer, 0, sizeof *ktimer);
                ktimer->callback = cb;
                ktimer->arg = arg;
        }
        return ktimer;
}

static void insert_ktimer_sorted_in_list(struct list_head *list, 
                                         struct ktimer *ktimer)
{
        struct list_head *nodeptr;
        list_for_each(nodeptr, list) {
                struct ktimer *entry = container_of(nodeptr, struct ktimer, node);
                if (entry->deadline > ktimer->deadline) {
                        list_add_tail(&ktimer->node, nodeptr);
                        return;
                }
        }

        /* every entry we encountered thus far has an earlier deadline than
         * this ktimer so we insert it at the end */
        list_add_tail(&ktimer->node, list);
        return;
}

static void insert_ktimer_sorted(struct ktimer *ktimer)
{
        insert_ktimer_sorted_in_list(&ktimer_list, ktimer);
        return;
}

static void ktimer_start(struct ktimer *ktimer, const unsigned long timeout_ms,
                         const unsigned long period)
{
        /* need to prevent ktimer from double registering itself */

        ktimer->deadline = arch_get_tick() + timeout_ms;
        ktimer->period = period;
        insert_ktimer_sorted(ktimer);
        return;
}

/* we always keep the timeout queue sorted with the nearest timeout at 
 * the head */
void ktimer_oneshot(struct ktimer *ktimer, const unsigned long timeout_ms)
{
        irqflag_t irqflag = enter_critical_section();
        ktimer_start(ktimer, timeout_ms, 0);
        exit_critical_section(irqflag);
        return;
}

void ktimer_periodic(struct ktimer *ktimer, const unsigned long period)
{
        irqflag_t irqflag = enter_critical_section();
        ktimer_start(ktimer, period, period);
        exit_critical_section(irqflag);
        return;
}

static bool ktimer_active(struct ktimer *ktimer)
{
        return ktimer->node.prev != NULL && ktimer->node.next != NULL;
}

void ktimer_cancel(struct ktimer *ktimer)
{
        irqflag_t irqflag;
        irqflag = enter_critical_section();
        if (ktimer_active(ktimer)) {
                list_del(&ktimer->node);
        }
        exit_critical_section(irqflag);
        return;
}

void ktimer_delete(struct ktimer *ktimer)
{
        /* create DPC to delete ktimer safely */
#if 0
        if (ktimer) {
                if (!ktimer_active(ktimer)) {

                }
        }
#endif
        return;
}

static void process_ktimers(const unsigned long now)
{
        irqflag_t irqflag;
        irqflag = enter_critical_section();
        for (;;) {
                struct ktimer *ktimer;
                struct list_head *nodeptr;
                nodeptr = list_peek_head(&ktimer_list);
                if (!nodeptr) {
                        break;
                }

                ktimer = container_of(nodeptr, struct ktimer, node);
                if (time_before(now, ktimer->deadline)) {
                        break;
                }

                list_del(&ktimer->node);
                ktimer->callback(ktimer, ktimer->arg);

                if (ktimer->period > 0) {
                        ktimer_start(ktimer, ktimer->period, ktimer->period);
                }
        }
        exit_critical_section(irqflag);
        return;
}

static void kernel_tick(void *arg)
{
        process_ktimers(arch_get_tick());
        if (sched_tick() == sched_need_reschedule) {
                sched_reschedule();
        }
        return;
}

void ktimer_init(void)
{
        list_init(&ktimer_list);
        arch_init_timer(kernel_tick, NULL, CONFIG_HZ);
        return;
}

void delay(const unsigned long ms)
{
        unsigned long deadline = arch_get_tick() + ms;
        for (;;) {
                if (time_after(deadline, arch_get_tick())) {
                        break;
                }
        }
        return;
}

