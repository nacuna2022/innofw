#include <kernel/semaphore.h>
#include <kernel/irq.h>

void init_semaphore(struct semaphore *sem, const int count)
{
        sem->count = count;
        init_waitqueue(&sem->waitqueue);
        return;
}

void up(struct semaphore *sem)
{
        irqflag_t irqflag;
        irqflag = enter_critical_section();
        if (list_empty(&sem->waitqueue.list)) {
                sem->count++;
        } else {
                wake_up(&sem->waitqueue);
        }
        exit_critical_section(irqflag);
        return;
}

void down(struct semaphore *sem)
{
        irqflag_t irqflag;
        struct waitqueue_waiter waiter;

        irqflag = enter_critical_section();

        /* if we have any semaphore to give, give it. */
        if (sem->count > 0) {
                sem->count--;
        } else {
               wait(&sem->waitqueue, &waiter);
        }
        exit_critical_section(irqflag);       
        return;
}

