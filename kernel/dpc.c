#include <kernel/sched.h>
#include <kernel/semaphore.h>
#include <kernel/dpc.h>
#include <kernel/irq.h>
#include <stdlib.h>

static struct list_head dpc_list;
static struct semaphore dpc_signal;

static void dpc_task(void *arg)
{
        for(;;) {
                struct semaphore *dpc_sem = arg;
                irqflag_t irqflag;

                down(dpc_sem);
                irqflag = enter_critical_section();
                if (!list_empty(&dpc_list)) {
                        struct list_head *node_ptr = dpc_list.next;
                        struct dpc *dpc_ptr;

                        list_del(node_ptr);
                        dpc_ptr = container_of(node_ptr, struct dpc, node);
                        dpc_ptr->fn(dpc_ptr->arg);
                        free(dpc_ptr);
                }
                exit_critical_section(irqflag);
        }
        return;
}

void init_dpc(void)
{
        list_init(&dpc_list);
        init_semaphore(&dpc_signal, 0);
        sched_create_task("dpc task", dpc_task, &dpc_signal);
        return;
}

void queue_dpc(dpc_fn fn, void *arg)
{
        struct dpc *dpc_ptr;
        irqflag_t irqflag;

        dpc_ptr = malloc(sizeof *dpc_ptr);
        dpc_ptr->fn = fn;
        dpc_ptr->arg = arg;
        irqflag = enter_critical_section();
        list_add_tail(&dpc_ptr->node, &dpc_list);
        exit_critical_section(irqflag);
        up(&dpc_signal);
        return;
}

