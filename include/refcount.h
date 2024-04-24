#ifndef __INCLUDE_KERNEL_REFCOUNT_H__
#define __INCLUDE_KERNEL_REFCOUNT_H__
#include <types.h>

/* we embed refcount inside our data structure */
struct refcount {
        unsigned long count;
};

void init_ref(struct refcount *ref);
void get_ref(struct refcount *ref);
void put_ref(struct refcount *ref, void (*release)(struct refcount *ref));


static inline 
unsigned long ref_count(struct refcount *ref)
{
        return ref->count;
}

#endif /* __INCLUDE_KERNEL_REFCOUNT_H__ */

