#include <kernel/sched.h>
#include <kernel/assert.h>
#include <kernel/irq.h>
#include <mmio.h>
#include <compiler.h>
#include <types.h>
#include <string.h>
#include <arm_task.h>
#include <arm_regs.h>

static void arm_task_runtime(void);

/* context switching always happens in handler mode - e.g. we are returning 
 * from an exception. for example, inside the systick handler, we can switch
 * context __switch_context() and modify the stack, when the systick handler
 * performs its return, it will use the values in the stack... which happens
 * to be the 'next' task we want to return to.
 *
 * but there are times that we do not want to wait for a context switch like if
 * we use sched_task_yield(). in this case, we need to force an exception
 * situation where we can return from. this is where pendsv comes in to the 
 * picture. we can trigger the pendsv exception at any time.
 *
 * saving the current task context means we will always have an "exception"
 * context to restore.
 */
void arch_initialize_task(struct task *t)
{
        addr_t task_sp = (addr_t)t->stack + t->stack_size;

        /* make sure the stack start is 8 byte aligned */
        task_sp = task_sp & ~0x7;

        /* initially, we should construct the "saved exception frame"
         * that pendsv() will restore. */
        struct context_switch_frame *frame = (struct context_switch_frame *)task_sp;
        frame--;
        
        memset(frame, 0,sizeof *frame);
        frame->elr = 0xFFFFFFF9; /* EXC_RETURN */
        frame->xpsr = 1 << 24; /* set the thumb mode bit */
        frame->ret_addr = (addr_t)&arm_task_runtime;
        t->frame = (addr_t)frame;

        return;
}

void arch_context_switch(void)
{
        write32(ICSR, 1<<28); /* pendvset */
        return;
}

void arm_context_switch(struct task *old, struct task *next)
{
#if 0
        extern void __arm_context_switch(addr_t *old, addr_t new);
        struct arm_task_private *old_priv = task_private(old);
        struct arm_task_private *next_priv = task_private(next);
        __arm_context_switch(&old_priv->sp, next_priv->sp);
#endif
        return;
}

void __switch_context(struct task *old, struct task *next) __alias("arm_context_switch");

static void arm_task_runtime(void)
{
        current->entry(current->arg);
        sched_set_current_state(TASK_STATE_DEAD);
        sched_reschedule();
        return;
}


