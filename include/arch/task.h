#ifndef __INCLUDE_ARCH_TASK_H__
#define __INCLUDE_ARCH_TASK_H__

struct task;

/* task manager calls this to let the architecture initialize
 * the correct stack arrangement so it can context switch properly.
 */
void arch_initialize_task(struct task *task);

void arch_context_switch(void);

#endif /* __INCLUDE_ARCH_TASK_H__ */

