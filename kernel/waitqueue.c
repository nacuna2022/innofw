#include <kernel/waitqueue.h>
#include <kernel/sched.h>
#include <kernel/irq.h>
#include <kernel/timer.h>

void init_waitqueue(struct waitqueue *wq)
{
        list_init(&wq->list);
        wq->count = 0;
        return;
}

void wait(struct waitqueue *wq, struct waitqueue_waiter *waiter)
{
        wait_timeout(wq, waiter, NO_TIMEOUT);
        return;
}

static void wait_timer(struct ktimer *ktimer, void *arg)
{
        struct waitqueue_waiter *wq_waiter = arg;
        wake_up(wq_waiter->wq);
        return;
}

void wait_timeout(struct waitqueue *wq, struct waitqueue_waiter *waiter,
                  const int timeout_ms)
{
        irqflag_t irqflag;
        waiter->t = current;
        waiter->wq = wq;
        
        irqflag = enter_critical_section();
        if (timeout_ms != NO_TIMEOUT) {
                struct ktimer *ktimer;
                ktimer = ktimer_create(wait_timer, &waiter);
                ktimer_oneshot(ktimer, timeout_ms);
        }
        list_add(&waiter->node, &wq->list);
        wq->count++;
        sched_set_current_state(TASK_STATE_BLOCKED);
        sched_reschedule();
        exit_critical_section(irqflag);
        return;
}

void wake_up(struct waitqueue *wq)
{
        irqflag_t irqflag;
        irqflag = enter_critical_section();
        if (wq->count) {
                struct list_head *nodeptr = wq->list.next;
                struct waitqueue_waiter *waiter;
                list_del(nodeptr);
                waiter = container_of(nodeptr, struct waitqueue_waiter, node);
                sched_wake(waiter->t);
                wq->count--;
        }
        exit_critical_section(irqflag);
        return;
}

#if 0
static void waiter_task(void *arg)
{
        struct waitqueue *wq_ptr = arg;
        struct waitqueue_waiter waiter;
        wait(wq_ptr, &waiter);

        for (;;) {
                asm("nop");
        }
        return;
}


static int gate_closed = 1;
static void wakeupper_task(void *arg)
{
        do {
                asm("nop");
        } while (gate_closed);

        struct waitqueue *wq_ptr = arg;

        wake_up(wq_ptr);
        
        for (;;) {
                asm("nop");
        }
        return;
}

static void waiter_timeout(void *arg)
{
        struct waitqueue *wq_ptr = arg;
        struct waitqueue_waiter waiter;
        wait_timeout(wq_ptr, &waiter, 5*1000);

        for (;;) {
                asm("nop");
        }
        return;
}

static struct waitqueue wq;
void waitqueue_test(void)
{
        sched_create_task("waiter", waiter_task, &wq);
        sched_create_task("wakeupper", wakeupper_task, &wq);
        sched_create_task("waiter timeout", waiter_timeout, &wq);
        return ;
}
#endif

