#include <kernel/sched.h>
#include <arch/task.h>

#include <kernel/irq.h>
#include <kernel/timer.h>
#include <kernel/dpc.h>
#include <bug.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static struct list_head runqueue[MAX_TASK_PRIORITY];
static uint32_t runqueue_bitmap;

struct task *current;

static void queue_task(struct list_head *queue, struct task *t)
{
        list_add_tail(&t->node, queue);
        return;
}

/* must be called with interrupts disabled */
static void task_queue_in_runqueue(struct task *t)
{
        queue_task(&runqueue[t->prio], t);
        runqueue_bitmap |= (1 << t->prio);
        return;
}

static void task_set_state(struct task *t, const enum task_state next_state)
{
        switch(t->state) {
        case TASK_STATE_NEW:
        case TASK_STATE_READY:
                BUG_ON(next_state != TASK_STATE_RUNNING);
                break;
        case TASK_STATE_RUNNING:
                BUG_ON((next_state != TASK_STATE_READY) &&
                       (next_state != TASK_STATE_DEAD) &&
                       (next_state != TASK_STATE_BLOCKED));
                break;
        case TASK_STATE_BLOCKED:
                BUG_ON(next_state != TASK_STATE_READY);
                break;
        case TASK_STATE_DEAD:
                break;
        default:
                BUG();
        }
        t->state = next_state;
        return;
}


static void task_set_name(struct task *t, const char *name)
{
        size_t len = strlen(name);
        if (len > (CONFIG_TASK_NAME_LENGTH-1)) {
                len = CONFIG_TASK_NAME_LENGTH-1;
        }
        memcpy(t->name, name, len);
        t->name[len] = '\0';
        return;
}

static struct task *sched_task_create(const char *task_name, 
                                      task_entry entry,
                                      void *arg,
                                      const size_t priority,
                                      size_t stack_size)
{
        struct task *t;
        if ((t = malloc((sizeof *t))) != NULL) {

                memset(t, 0, sizeof *t);
                task_set_name(t, task_name);
                t->entry = entry;
                t->arg = arg;
                t->state = TASK_STATE_NEW;
                t->prio = priority;
                t->quantum = TASK_QUANTUM;
                if (stack_size > 0) {
                        char *s = malloc(stack_size);
                        memset(s, 0, stack_size);
                        t->stack = s;
                        t->stack_size = stack_size;
                        arch_initialize_task(t);
                }
        }
        return t;
}

/* initialize the runqueue
 *
 * create the idle task structure. we are not creating an entire 
 * new task struct - e.g. no creation of a separate stack,
 * no entry point, since we are already running. just enough info 
 * so that we can context switch later on.
 */
void sched_init(void)
{
        size_t i;
        runqueue_bitmap = 0;
        for (i=0;i<MAX_TASK_PRIORITY; i++) {
                list_init(&runqueue[i]);
        }
        current = sched_task_create("idle_task", NULL, NULL, LOWEST_TASK_PRIO,
                                    0);
        sched_set_current_state(TASK_STATE_RUNNING);
        return;
}

void sched_set_current_state(const enum task_state state)
{
        task_set_state(current, state);
        return;
}

void sched_reschedule(void)
{
        arch_context_switch();
        return;
}

struct task *sched_create_task(const char *name,
                               task_entry entry,
                               void *arg)
{
        struct task *t;
        irqflag_t irqflag;
        t = sched_task_create(name, entry, arg, HIGHEST_TASK_PRIO,
                              CONFIG_TASK_STACK_SIZE);
        if (t) {
                irqflag = enter_critical_section();
                task_queue_in_runqueue(t);
                exit_critical_section(irqflag);
        }
        return t;
}

void sched_start_scheduler(void)
{
        for(;;) {
                /* call power management to powerdown the system */

                /* wait for interrupt */
                asm("nop");
                sched_reschedule();
        }
}

static struct task *get_next_task(void)
{
        int runqueue_index;
        struct list_head *nodeptr;

        /* WARNING!!! nacuna??? so the assumption is unsigned int = 32-bits */
        runqueue_index = __builtin_ffs(runqueue_bitmap) - 1;
        nodeptr = list_remove_head(&runqueue[runqueue_index]);
        if (list_empty(&runqueue[runqueue_index])) {
                runqueue_bitmap &= ~(1 << runqueue_index);
        }
        return container_of(nodeptr, struct task, node);
}

static void sched_destroy_task(void *arg)
{
        struct task *t = arg;
        if (t->stack_size > 0) {
                free(t->stack);
        }
        free(t);
        return;
}

addr_t sched_task_switch(const addr_t old_frame)
{
        irqflag_t irqflag;

        irqflag = enter_critical_section();

        /* transition current task to become the old one */
        current->frame = old_frame;

        if (current->state == TASK_STATE_RUNNING) {
                sched_set_current_state(TASK_STATE_READY);
                current->quantum = TASK_QUANTUM;
                task_queue_in_runqueue(current);
        } else if (current->state == TASK_STATE_DEAD) {
                queue_dpc(sched_destroy_task, current);
        }
        
        /* transition new task to be the current one */
        current = get_next_task();
        sched_set_current_state(TASK_STATE_RUNNING);
        exit_critical_section(irqflag);
        return current->frame;
}

enum sched_tick_ret sched_tick(void)
{
        current->quantum--;
        if (current->quantum > 0) {
                return sched_no_reschedule;
        }
        return sched_need_reschedule;
}

void sched_wake(struct task *t)
{
        task_set_state(t, TASK_STATE_READY);
        task_queue_in_runqueue(t);
        return;
}

