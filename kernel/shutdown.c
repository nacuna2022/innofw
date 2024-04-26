#include <kernel/shutdown.h>
#include <kernel/irq.h>
#include <arch/shutdown.h>
#include <compiler.h>
#include <list.h>
#include <stdlib.h>
#include <device_core.h>

struct shutdown_hook {
        shutdown_callback fn;
        void *arg;
        struct list_head node;
};

static struct list_head shutdown_hooks = { &shutdown_hooks, &shutdown_hooks };

static void prepare_shutdown(enum shutdown_reason reason);

/* innofw was designed to be running in devices that are just powered off 
 * directly using a power button. shutdowns in innofw happen in a 
 * straightforward manner e.g. tasks are not notified that the system is 
 * shutting down and they are not given the opportunity to cleanup. in other
 * words, "not graceful". also, it's hard to design and I'm lazy.
 *
 * but things are not as brutal as it seems because we provide a hook for 
 * tasks/subsystems to hook into the shutdown sequence instead by registering
 * a shutdown hook which is called during system shutdown with interrupts
 * disabled. */

void __no_return shutdown(enum shutdown_reason reason, enum shutdown_action action)
{
        /* send all tasks the shutdown signal? */
        
        /* wait 1s for all tasks to be gone? */

        /* no enabling of interrupts from this point forward */
        enter_critical_section();

        prepare_shutdown(reason);

        switch(action) {
        default:
        shutdown_poweroff:
                arch_poweroff();
                break;
        shutdown_restart:
                arch_restart();
                break;
        }
        for(;;);
}

void register_shutdown_hook(shutdown_callback fn, void *arg)
{
        struct shutdown_hook *hook = malloc(sizeof(struct shutdown_hook));
        hook->fn = fn;
        hook->arg = arg;
        return;
}

static void prepare_shutdown(enum shutdown_reason reason)
{
        struct list_head *pos;

        /* call all shutdown hooks */
        list_for_each(pos, &shutdown_hooks) {
                struct shutdown_hook *hook;
                hook = container_of(pos, struct shutdown_hook, node);
                hook->fn(hook->arg, reason);
        }

        shutdown_device_core();
        return;
}

