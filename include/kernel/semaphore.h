#ifndef __INCLUDE_SEMAPHORE_H__
#define __INCLUDE_SEMAPHORE_H__
#include <kernel/waitqueue.h>

/* in our implementation, we do not check semaphore count bounds. so user code 
 * should implement bounds checking on top of this semaphore implementation.
 *
 * when you create a binary semaphore for example, there is nothing preventing 
 * you from calling up() multiple times - thereby incrementing the count way 
 * past 1 (which is a bug for binary sempahores).
 */
struct semaphore {
        int count;
        struct waitqueue waitqueue;
};

void init_semaphore(struct semaphore *sem, const int count);
void up(struct semaphore *sem);
void down(struct semaphore *sem);

static inline int get_sem_count(struct semaphore *sem)
{
        return sem->count;
}

#endif /* __INCLUDE_SEMAPHORE_H__ */

