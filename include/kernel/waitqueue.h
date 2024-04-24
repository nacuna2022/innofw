#ifndef __INCLUDE_KERNEL_WAITQUEUE_H__
#define __INCLUDE_KERNEL_WAITQUEUE_H__
#include <list.h>

struct waitqueue {
        struct list_head list;
        size_t count;
};

/* the waitqueue_waiter is the object we list to the waitqueue.list
 *
 * it contains a reference to the list we are queued in and a reference to
 * the task that was blocked on the waitqueue that is to be woken up.
 */
struct task;
struct waitqueue_waiter {
        struct task *t;
        struct waitqueue *wq;
        struct list_head node;
};

void init_waitqueue(struct waitqueue *wq);
void wait(struct waitqueue *wq, struct waitqueue_waiter *wq_waiter);
void wait_timeout(struct waitqueue *wq, struct waitqueue_waiter *wq_waiter,
                  const int timeout_ms);
void wake_up(struct waitqueue *wq);

#endif /* __INCLUDE_KERNEL_WAITQUEUE_H__*/

