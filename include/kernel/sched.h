#ifndef __INCLUDE_KERNEL_SCHED_H__
#define __INCLUDE_KERNEL_SCHED_H__
#include <config.h>
#include <types.h>
#include <list.h>
#include <compiler.h>
#include <kernel/timer.h>

extern struct task *current;

/* right now we don't let the user define custom priorities. this is here 
 * so that I can determine when the idle task can run - e.g. no more "higher"
 * priority tasks to run.
 *
 * the higher the number, the lower the priority. all other tasks have 
 * priority=0. only the idle task has priority=1 */
#define MAX_TASK_PRIORITY       2

#define HIGHEST_TASK_PRIO       0
#define LOWEST_TASK_PRIO        (MAX_TASK_PRIORITY-1)

#define TASK_QUANTUM            5

enum task_state {
        TASK_STATE_NEW = 0,
        TASK_STATE_READY,
        TASK_STATE_RUNNING,
        TASK_STATE_BLOCKED,
        TASK_STATE_DEAD,
        TASK_STATE_MAX,
};

typedef void (*task_entry)(void *arg);

struct task {
        char name[CONFIG_TASK_NAME_LENGTH];
        enum task_state state;
        task_entry entry;
        void *arg;
        int prio;
        int quantum;
        struct list_head node;

        void *stack;
        size_t stack_size;
        addr_t frame;

        char priv[CONFIG_TASK_PRIVATE_SIZE] __align(8);
};

enum sched_tick_ret {
        sched_need_reschedule = 0,
        sched_no_reschedule,
};

static inline void *task_private(struct task *t)
{
        return t->priv;
}

extern struct task *current;

void sched_init(void);
struct task *sched_create_task(const char *name,
                               task_entry entry,
                               void *arg);

/* we call this to alert the scheduler that we want to perform a 
 * context switch. use the sched_set_current_state() to tell the scheduler
 * how it should behave prior to calling sched_reschedule().
 *
 * if current task is TASK_STATE_RUNNING, then it is just requeued 
 * to the runque and will pick the next task to run. this is usually the case
 * when we just want to yield so there is no need to explicitly set to this 
 * state when just yielding.
 *
 * if current task is TASK_STATE_BLOCKED, then the scheduler assumes it has 
 * been queued to another structure and will just pick the next task to run.
 *
 * if current task is TASK_STATE_DEAD, then the scheduler will perform the
 * proper cleanup on the task prior to releasing its memory back to the system.
 */
void sched_reschedule(void);

void sched_set_current_state(const enum task_state state);

/* called every tick so the timer can determine if need to context switch or
 * not.
 */
enum sched_tick_ret sched_tick(void);

/* make sure task is not queue to any other list before 
 * calling this function */
void sched_wake(struct task *t);

void  __no_return kernel_idle(void);

#endif /* __INCLUDE_KERNEL_SCHED_H__ */

